// Agent.cpp: implementation of the SIMAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Behavior.h"
#include "Agent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//Construct static variables
//Their real values are set in static function SIMAgent::InitValues()
vector<SIMAgent*> SIMAgent::agents;
bool SIMAgent::debug = false;
float SIMAgent::radius = 20.0;
float SIMAgent::Mass = 1.0;
float SIMAgent::Inertia = 1.0;
float SIMAgent::MaxVelocity = 20.0;
float SIMAgent::MaxForce = 10.0;
float SIMAgent::MaxTorque = 40.0;
float SIMAgent::MaxAngVel = 10.0;
float SIMAgent::Kv0 = 1.0;
float SIMAgent::Kp1 = 1.0;
float SIMAgent::Kv1 = 1.0;
float SIMAgent::KArrival = 1.0;
float SIMAgent::KDeparture = 1.0;
float SIMAgent::KNoise = 1.0;
float SIMAgent::KWander = 1.0;
float SIMAgent::KAvoid = 1.0;
float SIMAgent::TAvoid = 1.0;
float SIMAgent::RNeighborhood = 1.0;
float SIMAgent::KSeparate = 1.0;
float SIMAgent::KAlign = 1.0;
float SIMAgent::KCohesion = 1.0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////////////// 
vec2 SIMAgent::WorldToLocal(vec2 &w)
{
	vec2 l;
	float s = sin(state[1]);
	float c = cos(state[1]);
	l[0] = c * w[0] + s * w[1];
	l[1] = -s * w[0] + c * w[1];
	return l;
}

vec2 SIMAgent::LocalToWorld(vec2 &l)
{
	vec2 w;
	float s = sin(state[1]);
	float c = cos(state[1]);
	w[0] = c * l[0] - s * l[1];
	w[1] = s * l[0] + c * l[1];
	return w;
}

void SIMAgent::SetVTheta(vec2 &V)
{
	vd = V.Length();
	if (vd < 0.0001) {
		thetad = 0.0;
	}
	else {
		if (abs(V[0]) < 0.0001) {
			if (V[1] > 0)
				thetad = M_PI / 2.0;
			else
				thetad = M_PI / -2.0;
		}
		else
			thetad = atan2(V[1], V[0]);
	}

	ClampAngle(thetad);
}

SIMAgent::SIMAgent()
{
}

SIMAgent::~SIMAgent()
{
}

void SIMAgent::Display()
{
	glPushMatrix();
	glTranslatef(GPos[0], rootHeight[frameNum], GPos[1]);
	if (showLeader && this == SIMAgent::agents[0]) {
		float red[] = { 1.0, 0.0, 0.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
		glPushMatrix();
		glTranslatef(0.0, 100.0, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidCone(10.0, 20.0, 24, 24);
		glPopMatrix();
	}

	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	if (SIMAgent::debug) {
		glutSolidSphere(10.0, 24, 24);
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glRotatef(-state[1] / M_PI * 180.0, 0.0, 1.0, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0); glVertex3f(12 + state[2], 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glRotatef(-thetad / M_PI * 180.0, 0.0, 1.0, 0.0);
		glLineWidth(3.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0); glVertex3f(12 + vd, 0.0, 0.0);
		glEnd();
		glPopMatrix();
		glLineWidth(1.0);
		glEnable(GL_LIGHTING);
	}
	else {
		glRotatef(90.0f - state[1] * Rad2Deg, 0.0, 1.0, 0.0);
		//glutSolidSphere(6.0f, 12, 12);
		glCallList(AgentDisplay::listNames + frameNum);
	}
	glPopMatrix();
}

void SIMAgent::ClearAgents() {
	for (unsigned int i = 0; i < agents.size(); i++)
		delete SIMAgent::agents[i];
	SIMAgent::agents.clear();
}

SIMAgent::SIMAgent(float* color, CEnvironment* env) {
	memcpy(this->color, color, sizeof(float) * 3);
	dimState = 4;
	dimInput = 2;
	frameNum = rand() % totalFrames;
	this->env = env;
	float angle = float(rand() % 360) / 180.0 * M_PI;
	vWander[0] = cos(angle) * SIMAgent::KWander;
	vWander[1] = sin(angle) * SIMAgent::KWander;
	angle = float(rand() % 360) / 180.0 * M_PI;
	v0[0] = cos(angle) * SIMAgent::MaxVelocity / 2.0;
	v0[1] = sin(angle) * SIMAgent::MaxVelocity / 2.0;
	SIMAgent::agents.push_back(this);
}

void SIMAgent::SetInitState(float pos[], float angle)
{
	int i;
	GPos[0] = pos[0];
	GPos[1] = pos[1];
	for (i = 0; i < dimState; i++) {
		state[i] = 0.0;
	}
	for (i = 0; i < dimInput; i++)
		input[i] = 0.0;
	state[1] = angle;
}

void SIMAgent::Sense(int type)
{
	showLeader = (type == LEADER);
	goal = env->goal;
	switch (type) {
	case SEEK: Seek(); break;
	case FLEE: Flee(); break;
	case ARRIVAL: Arrival(); break;
	case DEPARTURE: Departure(); break;
	case WANDER: Wander(); break;
	case AVOID: Avoid(); break;
	case SEPARATION: Separation(); break;
	case ALIGNMENT: Alignment(); break;
	case COHESION: Cohesion(); break;
	case FLOCKING: Flocking(); break;
	case LEADER: Leader(); break;
	}
}

void SIMAgent::Act(float deltaT)
{
	int dframe;
	this->deltaT = deltaT;
	FindDeriv();
	UpdateState();
	if (abs(state[2]) < 0.001)
		dframe = 0;
	else {
		dframe = int(state[2] / SIMAgent::MaxVelocity * 2 + 1);
	}
	frameNum += dframe;
	if (frameNum >= totalFrames) {
		frameNum = frameNum - totalFrames;
	}
}

void SIMAgent::SetV0()
{
	v0 = env->goal - GPos;
	v0 = v0.Normalize() * SIMAgent::MaxVelocity / 2;
}

/*
Sets the intial Values
*/
void SIMAgent::InitValues()
{
	/*********************************************
	// TODO: JAK 4/15/17 added
	Set initial value for control and behavior settings
	You need to find out appropriate values for:
	SIMAgent::Kv0, SIMAgent::Kp1, SIMAgent::Kv1, SIMAgent::KArrival, SIMAgent::KDeparture,
	SIMAgent::KNoise, SIMAgent::KWander, SIMAgent::KAvoid, SIMAgent::TAvoid, SIMAgent::RNeighborhood,
	SIMAgent::KSeparate, SIMAgent::KAlign, SIMAgent::KCohesion.
	*********************************************/
	Kv0 = 10.0;			// velocity
	Kp1 = -400.0;		// Everything worked better when I made this negative - controls the direction the agent faces
	Kv1 = 20.0;			// Angular momentum 
	KArrival = 400.0;		// Get this close then stop or slow way down
	KDeparture = 900.0;	// Maximum distance to get away when departing
	KNoise = 3.0;
	KWander = 8.0;
	KAvoid = 400.0;
	TAvoid = 0.60;
	RNeighborhood = 200.0;
	KSeparate = 1.0;
	KAlign = 5.0;
	KCohesion = 4.0;

}

/*
*	You should apply the control rules given desired velocity vd and desired orientation thetad.
*/
void SIMAgent::Control()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	Truncate(vd, -SIMAgent::MaxVelocity, SIMAgent::MaxVelocity);
	input[0] = SIMAgent::Mass * SIMAgent::Kv0 * (vd - state[2]);
	Truncate(input[0], -SIMAgent::MaxForce, SIMAgent::MaxForce);

	double dangle = AngleDiff(state[1], thetad);
	input[1] = SIMAgent::Inertia * (Kp1 * dangle - Kv1 * state[3]);
	Truncate(input[1], -SIMAgent::MaxTorque, SIMAgent::MaxTorque);

}
/*
*	Compute derivative vector given input and state vectors
*  This function sets derive vector to appropriate values after being called
*/
void SIMAgent::FindDeriv()
{

	/*********************************************
	// TODO: Add code here
	*********************************************/
	//State vector dimension: 4
	/*
	*	State Vector: 4 dimensions
	*  0 : position in local coordinates. Useless.
	*  1 : orientation angle in global coordinates.
	*  2 : velocity in local coordinates.
	*  3 : angular velocity in global coordinates.
	*/
	/*
	*	Input Vector: 2 dimensions
	*  0 : force
	*  1 : torque
	*/
	deriv[0] = state[2];
	deriv[1] = state[3];
	deriv[2] = input[0] / Mass;
	deriv[3] = input[1] / Inertia;
	/*for (int i = 0; i < dimState; i++) {
		deriv[i] += deriv[i] * deltaT;
	}
	*/
}

/*
*	Update the state vector given derivative vector
*  Compute global position and store it in GPos
*  Perform validation check to make sure all values are within MAX values
*/
void SIMAgent::UpdateState()
// Added from piazza 4/8/17
{

	for (int i = 0; i < dimState; i++) {
		state[i] += deriv[i] * deltaT;
	}
	state[0] = 0.0;

	// JAK 4/15/17 Seek seems to work except if the goal is too far behind the agent
	// Try changing Clamp to ClampAngle to see if this resolves
	// Using ClampAngle appears to resolve that issue
   // Clamp(state[1], -M_PI, M_PI);
	ClampAngle(state[1]);
	Truncate(state[2], -SIMAgent::MaxVelocity, SIMAgent::MaxVelocity);

	vec2 GVelocity;
	GVelocity[0] = state[2] * cos(state[1]);
	GVelocity[1] = state[2] * sin(state[1]);
	GPos += GVelocity;

	Truncate(GPos[0], -1.0 * env->groundSize, env->groundSize);
	Truncate(GPos[1], -1.0 * env->groundSize, env->groundSize);

	Truncate(state[3], -SIMAgent::MaxAngVel, SIMAgent::MaxAngVel);

}


/*
*	Seek behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Seek()
{
	//State vector dimension: 4
	/*
	*	State Vector: 4 dimensions
	*  0 : position in local coordinates. Useless.
	*  1 : orientation angle in global coordinates.
	*  2 : velocity in local coordinates.
	*  3 : angular velocity in global coordinates.
	*/
	vec2 tmp;

	tmp = goal - GPos;
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);

	vd = SIMAgent::MaxVelocity;
	
	return vec2(cos(thetad)*vd, sin(thetad)*vd);
}

/*
*	Flee behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Flee()
{
	vec2 tmp;

	// JAK code added 4/10/17
	tmp = env->goal - GPos;
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	thetad = thetad+M_PI;
	// JAK 4/15/17 tried M_PI/2 and the agent starts to flee and then comes back
	// JAK 4/15/17 one might think I could recognize the difference between + and * by now, one would be wrong

	vd = SIMAgent::MaxVelocity;

	return vec2(cos(thetad)*vd, sin(thetad)*vd);
	//return tmp;
}

/*
*	Arrival behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  Arrival setting is in SIMAgent::KArrival
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Arrival()
{
	// JAK 4/15/17 Added code based on webcourses	
	vec2 tmp;
	tmp = goal - GPos;
	vd = tmp.Length() - KArrival;

	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);

	if (vd <= KArrival) {
		vd = 0;
		return vec2(cos(thetad), sin(thetad));
	}
	vd = 0.1*vd;
	Truncate(vd, 0, SIMAgent::MaxVelocity);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

}

/*
*	Departure behavior
*  Global goal position is in goal
*  Agent's global position is in GPos
*  Departure setting is in KDeparture
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Departure()
{
	vec2 tmp;

	tmp = goal - GPos;
	// JAK 4/15/17 Departure radius minus Distance from goal should be big when close to goal and shrink when closer to departure radius
	// if tmp.Length() is larger than departure radius vd should be negative and get truncated to 1
	vd = (KDeparture - tmp.Length());
	Truncate(vd, 1, SIMAgent::MaxVelocity);

	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	thetad = thetad + M_PI;

	return vec2(cos(thetad)*vd, sin(thetad)*vd);


//	return tmp;
}

/*
*	Wander behavior
*  VWander is in vWander
*  V0(nominal velocity) is in v0
*  Wander setting is in KWander
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Wander()
{
	// Implement random engine for Wander based on Homework 2
	std::random_device rd;
	std::ranlux48 engine(rd());
	std::uniform_real_distribution<> dist(0, 360);
	auto genAngle = std::bind(dist, engine);

	// JAK 4/15/17 Started with code from seek
	// Yet, another way to implement this is to pick a random angle 
	// multiply some random noise (Knoise) to the x and y directions of the velocity, 
	// and multiply a damping term (KWander).
	thetad = genAngle() /180.0 * M_PI;
	//vd = (v0[0] * KNoise + v0[1] * KNoise)*KWander;
	vd = SIMAgent::MaxVelocity / 2;

	// Using code from SIMAgent creation
	//float angle = float(rand() % 360) / 180.0 * M_PI;
	vWander[0] = cos(thetad) * SIMAgent::KWander;
	vWander[1] = sin(thetad) * SIMAgent::KWander;
	//angle = float(rand() % 360) / 180.0 * M_PI;
	//v0[0] = cos(angle) * SIMAgent::MaxVelocity / 2.0;
	//v0[1] = sin(angle) * SIMAgent::MaxVelocity / 2.0;


	return vWander;
}

/*
*	Avoid behavior
*  Obstacles are in env->obstacles
*  Number of obstacles is env->obstaclesNum
*  env->obstacles[i][0] and env->obstacles[i][1] are the global position of the ith obstacle
*  env->obstacles[i][2] is the radius of the ith obstacle
*  Agent bounding sphere radius is in SIMAgent::radius
*  Avoidance settings are in SIMAgent::TAvoid and SIMAgent::KAvoid
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/

vec2 SIMAgent::Avoid()
{
	/*********************************************
	// TODO: Add code here
	*********************************************/
	vec2 tmp;
	vec2 ahead1;
	vec2 ahead2;

	// Set where we want to go if there ar no obstacles
	tmp = goal - GPos;
	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);
	vd = SIMAgent::MaxVelocity / 2;
	// Look for obstacles
	ahead1 = GPos + v0.Normalize() * KAvoid;
	ahead2 = GPos + v0.Normalize() * KAvoid * 0.5;
	for (int i=0; i < env->obstaclesNum; i++) {
		vec2 obs;
		obs[0] = env->obstacles[i][0];
		obs[1] = env->obstacles[i][1];

		float dist1 = (obs - ahead1).Length();
		float dist2 = (obs - ahead2).Length();

		// Avoid obstacles that are in our path
//		if (dist1 <= obs.Length() || dist2 <= obs.Length()) {
		if (dist1 <= env->obstacles[i][2] + KAvoid || dist2 <= env->obstacles[i][2] + KAvoid) {
//		if (dist1 <= env->obstacles[i][2] + KAvoid && dist2 <= env->obstacles[i][2] + KAvoid) {
				// need to avoid the obstacle
			thetad = thetad + TAvoid;
			ClampAngle(thetad);
			return vec2(cos(thetad)*vd, sin(thetad)*vd);
		}
	}
	
	return vec2(cos(thetad)*vd, sin(thetad)*vd);

//	return tmp;
}

/*
*	Separation behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Separation settings are in SIMAgent::RNeighborhood and SIMAgent::KSeperate
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Separation()
{
	/*********************************************
	// \sum_{n \in N} Normalize (goal-position)
	*********************************************/
	vec2 tmp;
	vec2 sumtmp(0.0, 0.0);

	
	for (int i=0; i< SIMAgent::agents.size(); i++) {
		tmp = SIMAgent::agents[i]->GPos - GPos;
		if (tmp.Length() < SIMAgent::RNeighborhood) {
			tmp = goal - SIMAgent::agents[i]->GPos;
			sumtmp += (tmp / tmp.Length()) * SIMAgent::KSeparate;
		}
	}
//	return sumtmp;
	thetad = atan2(sumtmp[1], sumtmp[0]);
	vd = MaxVelocity / 2;
	return vec2(cos(thetad)*vd, sin(thetad)*vd);
} 

/*
*	Alignment behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Alignment settings are in SIMAgent::RNeighborhood and SIMAgent::KAlign
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Alignment()
{
	/*********************************************
	// \sum_{n \in N} Normalize(n_v)
	*********************************************/
	vec2 tmpsum (0.0, 0.0);
	vec2 tmp;
	
	for (int i = 0; i < SIMAgent::agents.size(); i++) {
		tmp = SIMAgent::agents[i]->GPos - GPos;
		if (tmp.Length() < SIMAgent::RNeighborhood)
			//			tmp += SIMAgent::agents[i]->vd.Normalize();
			tmpsum = SIMAgent::agents[i]->v0.Normalize();
	}
//	return tmpsum*KAlign;
//	thetad = atan2(tmpsum[1], tmpsum[0]);
//	tmp = goal - GPos;
//	thetad = atan2(tmp[1] + tmpsum[1], tmp[0] + tmpsum[0]);
	tmp = goal - GPos + tmpsum;
	thetad = atan2(tmp[1], tmp[0]);
	vd = tmp.Length() * KArrival;
	Truncate(vd, 0, SIMAgent::MaxVelocity);
	return vec2(cos(thetad)*vd, sin(thetad)*vd);
}

/*
*	Cohesion behavior
*  SIMAgent::agents[i] gives the pointer to the ith agent in the environment
*  Cohesion settings are in SIMAgent::RNeighborhood and SIMAgent::KCohesion
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Cohesion()
{
	/*********************************************
	// \frac{\sum_{n \in N} n_{pos}}{|N|}
	//sum the position of all neighbors and then divide the position by the number of neighbors.
	*********************************************/
	vec2 tmp;
	vec2 sumtmp(0.0, 0.0);
	int num=0;

	for (int i = 0; i< SIMAgent::agents.size(); i++) {
		tmp = SIMAgent::agents[i]->GPos - GPos;
		if (tmp.Length() < RNeighborhood) {
			sumtmp += tmp;
			num++;
		}

	}
	
	sumtmp = ((sumtmp / num) - GPos);
	//sumtmp = ((sumtmp / num) - GPos)*KCohesion;
	//	return sumtmp;

	tmp = goal - GPos + sumtmp;
	vd = tmp.Length() * KArrival;
	Truncate(vd, 0, SIMAgent::MaxVelocity);

	tmp.Normalize();
	thetad = atan2(tmp[1], tmp[0]);

	return vec2(cos(thetad)*vd, sin(thetad)*vd);



}

/*
*	Flocking behavior
*  Utilize the Separation, Cohesion and Alignment behaviors to determine the desired velocity vector
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Flocking()
{
	/*********************************************
	// 4/21/17 V_{flock}= c_{seperate}V_{seperate}+c_{align}V_{align}+c_{cohesion}V_{cohesion}
	// where V_{seperate}, V_{cohesion}, V_{align} Vseperate,Vcohesion,Valign are computed from the 
	// separation, cohesion and alignment computation. c_{separate}cseparate, c_{cohesion}ccohesion 
	// and c_{align}calign are constant coefficients
	*********************************************/
	vec2 tmp;
	vec2 vflock;

	vflock = SIMAgent::KSeparate * SIMAgent::Separation() + SIMAgent::KAlign*SIMAgent::Alignment() + SIMAgent::KCohesion*SIMAgent::Cohesion();
	//vflock = SIMAgent::Separation() + SIMAgent::Alignment() + SIMAgent::Cohesion();

	return vflock;
	//vd = vflock.Length();
	//thetad = atan2(vflock[1], vflock[0]);

	//return vec2(cos(thetad)*vd, sin(thetad)*vd);
}

/*
*	Flocking behavior
*  Utilize the Separation, Arrival behaviors to determine the desired velocity vector
*  You need to find the leader, who is always the first agent in SIMAgent::agents
*  You need to compute the desired velocity and desired orientation
*  Store them into vd and thetad respectively
*  return a vec2 that represents the goal velocity with its direction being thetad and its norm being vd
*/
vec2 SIMAgent::Leader()
{
	/*********************************************
	// V_{leaderfollow}=c_{seperate}V_{seperate}+c_{arrivial}V_{arrivial}
	*********************************************/
	vec2 tmp;

	if (SIMAgent::agents[0] == this) {
		return SIMAgent::Seek();
	}
	//for (int i = 1; i< SIMAgent::agents.size(); i++) {
	//	tmp = SIMAgent::agents[i]->GPos;
	else
		tmp = SIMAgent::KSeparate*Separation() + KArrival*Arrival();

	return tmp;
}