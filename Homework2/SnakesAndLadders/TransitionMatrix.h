int size = 12;  //TODO 3/11 - JAK setting to 4 to see if it compiles and solve runtime issue
Eigen::MatrixXf TransitionMatrix(size, size);
Eigen::VectorXf v(size);
// std::vector<int> v2(size);

unsigned int ROLLS = 0; //TODO

double prob = 1.0 / 6.0 ;  //TODO




void SetTransitionMatrix()
{
	TransitionMatrix.setZero();

	//TODO
	// How to load the Transition Matrix
	for (int i = 0; i < size; i++)
	{
		int jstart = i;
		int jstop = i + 6;
		if (jstop >= size) jstop = size;
		

		for (int j = jstart; j < jstop; j++)
		{
			TransitionMatrix(i, j) = prob;
			if (j == jstop-1 && (jstop - jstart) < 6)
				TransitionMatrix(i, j) =  prob * (7 - (jstop - jstart));
			//if (i == 1 && j == 1)	TransitionMatrix(i, j) = 5;
			//if (i == 2 && j == 3) TransitionMatrix(i, j) = 2;
			//if (i == 0 && j == 2) TransitionMatrix(i, j) = 14;
		}
	}


}