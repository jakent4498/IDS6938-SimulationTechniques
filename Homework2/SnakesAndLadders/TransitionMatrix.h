int size = 4;  //TODO 3/11 - JAK setting to 4 to see if it compiles and solve runtime issue
Eigen::MatrixXf TransitionMatrix(size, size);
Eigen::VectorXf v(size);

unsigned int ROLLS = 0; //TODO

double prob = 1.0 / 6.0 ;  //TODO




void SetTransitionMatrix()
{
	TransitionMatrix.setZero();

	//TODO
	// How to load the Transition Matrix
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == 1 && j == 1)	TransitionMatrix(i, j) = 5;
			if (i == 2 && j == 3) TransitionMatrix(i, j) = 2;
			if (i == 0 && j == 2) TransitionMatrix(i, j) = 14;
		}
	}


}