# Homework 3 : Agent based Simulation Assignment 

## IDS6938-Simulation Techniques - [University of Central Florida](http://www.ist.ucf.edu/grad/)

[University of Central Florida](http://www.ist.ucf.edu/grad/)
This is the framework for homework #3. 

The assignment is due: **Monday, April  24 at 11:59PM (EST)**

# Introduction
The goal of this assignment is to enable the behavioral animation of vehicle-like walking agents. 

You will be expected to compose a *final report* which demonstrates your understanding on the material in each section of the assignment. Be visual! - Pictures say a thousand words so you do not have to. Show off your different configurations and really explore the assignment.


### Part 1: Behaviors

The goal of this assignment is to enable the steering behavioral animation of agents.

Great, if I keep typing up the report as I work the project, maybe I will not spend the entire day of the 24th typing.

We represent an agent as a two-dimensional disk with mass (**m**) and moment-of-inertia (**I**) that is capable of generating a force **F** along body x-axis with a torque about the z-axis. For this assignment assume that the agent only translates in the world x-y plane and rotates about the body z-axis.

![](images/behavior.png?raw=true)

**(a) - 10 points** : Compute derivative vector given input and state vectors. Implement the function *SIMAgent::FindDeriv()*. This function sets derive vector to appropriate values after being called.

I think I managed to implement FindDeriv().  I have the agent moving.
state[0] is position so its derivative would be velocity.  deriv[0] = state[2]
state[1] is the orientation or rotation so its derivative would be the angular momentum.  deriv[1] = state[3]
state[2] is the velocity so its derivative would be acceleration.  Force equals mass times acceleration.  Therefore, acceleration equals the force divided by mass.  deriv[2] = Force / mass
state[3] is the angular momentum so its derivative would be torque.  deriv[3] = Torque / Inertia

Description of agent state vector and input vector:  
* state[0] is the position of the agent in local body coordinates (almost useless in this project);  
* state[1] is the orientation angle of the agent with respect to world (i.e. global) coordinates;  
* state[2] is the velocity of the agent  in local body coordinates.  
* state[3] is the angular velocity of the agent in world coordinates. 
* input[0] is the force in local body coordinates;  
* input[1] is the torque in local body coordinates

You will need to set deriv[0], deriv[1], deriv[2], deriv[3]. Compute derivative vector given input and state vectors. This function sets derive vector to appropriate values after being called. 
* deriv[0] is the velocity of the agent  in local body coordinates
* deriv[1] is the angular velocity of the agent in world coordinates
* deriv[2] is the force in local body coordinates divided by the mass.
* deriv[3] is the torque in local body coordinates divided by the inertia.

You also must implement *SIMAgent::InitValues()*: Try to figure out appropriate values for control and behavior settings. You need to find out appropriate values for: *SIMAgent::Kv0, SIMAgent::Kp1, SIMAgent::Kv1, SIMAgent::KArrival, SIMAgent::KDeparture,
SIMAgent::KNoise,	SIMAgent::KWander, SIMAgent::KAvoid, SIMAgent::TAvoid, SIMAgent::RNeighborhood, SIMAgent::KSeparate, SIMAgent::KAlign, SIMAgent::KCohesion.*


**(b) - 20 points**: In this part of the assignment you will need to implement 6 types of individual behaviors and 5 types of group behaviors. Create the following behaviors through appropriate computation of V<sub> d</sub>  and θ<sub>d</sub>  commands:
* Seek - implemented - seek velocity is 1/2 max velocity
* Flee - implemented - flee at maximum velocity
* Arrival - implemented - from far away use max velcity, slow to 0 at arrival
* Departure - implemented - from goal flee at max velocity slow to 0 at departure radisu
* Wander - sort of implemented - chose a random angle and go that way, haven't figured out the Knoise
* Obstacle Avoidance - sort of implemented - will veer away from objects, was this also supposed to seek the goal?

**(c) - 20 points**: Implement the functions for the following group behaviors: 
* Seperation
* Cohesion 
* Alignment 
* Flocking
* Leader Following

# Part 2 - Simulating a simple pedestrian flow

The goal of this part of the assigment is to simulate the pedestrain flow for various configurations. Pedestrian traffic simulation is an important, sometimes required, stage for certain construction projects such as shopping centers, airports, railway stations, or stadiums. hese analyses can be used by architects in the design stage, by facilities owners contemplating changes, by city planners to evaluate rush hours, or even by civil authorities to simulate evacuations or other emergencies. 

![](images/flow.png?raw=true)

**(a) - 0 points**: Follow the Anylogic example for the [Subway Entrance example](https://help.anylogic.com/index.jsp?topic=/com.xj.anylogic.help/html/_PL/tutorial/Subway_Entrance.html). Create the appropriate [boundaries and walls](https://help.anylogic.com/index.jsp?topic=/com.xj.anylogic.help/html/markup/Wall.html), and the display ther pedestrian density map, [statistics](https://help.anylogic.com/index.jsp?nav=/4_1_5), [2D and 3D animations](https://help.anylogic.com/index.jsp?topic=/com.xj.anylogic.help/html/_PL/reference/Animation.html).

![](images/density.png?raw=true)

I did this and I created a 3D version.  I did not think all the pedestrians should look alike so I used CreateRandom to make a number of different subway riders.
My 2D image looks very similar to the one above 
![](images/subway2d.png)

In the 3D image you can see the variety of pedestrians.
![](images/subway3d.png)

**(b) - 20 points**: Create a maze. Generate the pdm, stats, and animations like before. Vary [parameters in your agents](https://help.anylogic.com/index.jsp?topic=/com.xj.anylogic.help/html/_PL/reference/Attributes.html) to give them different behaviors and show the pedistrians change how they navigate the maze.
I started with a simple maze and created the pdm.  Not sure what stats to capture.  I need to add pictures here.

Initially all the pedestrians took one of two routes to the maze exit.  I added points in the dead ends and set those as destinations for a percentage of the population.  I also partially blocked one portion of the maze to see the change in the pdm.

AnyLogic asked me to upgrade to AnyLogic 8 which had a new Space Markup Object - Ped Flow Statistics.  I created two of these and connected them to a chart to get the traffic flow through the left and right sides of the maze.  See the screenshot at ![](images/maze2-inuse.png)

**(c) - 30 points**: Model and analyze a building (or floor/outdoor space/stadium) on campus. (There is help on piazza how to find rough building plans - we expect something plausible). Create a senario: evacuation, daily office routine, special event, normal egress.... etc., and model and design your own experiment to determine if the building design suits the needs of its users. Start with photographs of your site, describe your site, describe your senario and hypothesis. Then use an agent-based pedistrian simulation to visualize your experiment's results.

I am working on the student union.  I may not get all the details as this is a complex space.  I would like to be able to model movement from the first floor to the second floor.  I also want to be able to model several different kinds of activities because many activities occur in this building.  

The new release of AnyLogic said there was a sort of evacuation option.  I want to read more about that and try it.  I currently have folks coming in and going out different doors, waiting for food at Subway and getting print jobs.  There are clearly many different activities in the student union and there are already some areas with pedestrian traffic challenges.
