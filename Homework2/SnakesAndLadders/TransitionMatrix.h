int size = 101;  //TODO 3/11 - JAK setting to 4 to see if it compiles and solve runtime issue 3/26 setting to full matrix
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
	for (int i = 0; i <= size; i++)
	{
		// Does the 0 row in the matrix count as being on the board?
		int jstart = i + 1;
//		int jstart = i;
		int jstop = jstart + 6;
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
// If the 0 row is not on the board then need to stay on the board at the last row

	TransitionMatrix(size-1, size-1) = 1;
	
	for (int i1 = 0; i1 < size; i1++)
	{
		double rowsum = 0;
		for (int j1 = 0; j1 < size; j1++) {
			rowsum = rowsum + TransitionMatrix(i1, j1);
		}
		if (abs(rowsum - 1) > 0)
			std::cout << "rowsum <> 1 rowsum = " << rowsum << "i = " << i1 << std::endl;
	}
	

}