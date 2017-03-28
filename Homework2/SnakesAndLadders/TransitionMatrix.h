int size = 101;  //TODO 3/11 - JAK setting to 4 to see if it compiles and solve runtime issue 3/26 setting to full matrix
Eigen::MatrixXf TransitionMatrix(size, size);
Eigen::VectorXf v(size);
// std::vector<int> v2(size);

unsigned int ROLLS = 100; //TODO

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
		}
	}
    // If the 0 row is not on the board then need to stay on the board at the last row
	TransitionMatrix(size-1, size-1) = 1;
	
	// Adding snakes and ladders
	for (int i2 = 0; i2 < size; i2++) {
		// First the ladders
/*		// 3 to 19
		if (TransitionMatrix(i2, 3) > 0) {
			TransitionMatrix(i2, 19) = TransitionMatrix(i2, 19) + TransitionMatrix(i2, 3);
			TransitionMatrix(i2, 3) = 0;
		}
		// 15 to 37
		if (TransitionMatrix(i2, 15) > 0) {
			TransitionMatrix(i2, 37) = TransitionMatrix(i2, 37) + TransitionMatrix(i2, 15);
			TransitionMatrix(i2, 15) = 0;
		}
		// 22 to 42
		if (TransitionMatrix(i2, 22) > 0) {
			TransitionMatrix(i2, 42) = TransitionMatrix(i2, 42) + TransitionMatrix(i2, 22);
			TransitionMatrix(i2, 22) = 0;
		}
		// 25 to 64
		if (TransitionMatrix(i2, 25) > 0) {
			TransitionMatrix(i2, 64) = TransitionMatrix(i2, 64) + TransitionMatrix(i2, 25);
			TransitionMatrix(i2, 25) = 0;
		}
		// 41 to 73
		if (TransitionMatrix(i2, 41) > 0) {
			TransitionMatrix(i2, 73) = TransitionMatrix(i2, 73) + TransitionMatrix(i2, 41);
			TransitionMatrix(i2, 41) = 0;
		}
		// 53 to 74
		if (TransitionMatrix(i2, 53) > 0) {
			TransitionMatrix(i2, 74) = TransitionMatrix(i2, 74) + TransitionMatrix(i2, 53);
			TransitionMatrix(i2, 53) = 0;
		}
		// 63 to 86
		if (TransitionMatrix(i2, 63) > 0) {
			TransitionMatrix(i2, 86) = TransitionMatrix(i2, 86) + TransitionMatrix(i2, 63);
			TransitionMatrix(i2, 63) = 0;
		}
		// 76 to 91
		if (TransitionMatrix(i2, 76) > 0) {
			TransitionMatrix(i2, 91) = TransitionMatrix(i2, 91) + TransitionMatrix(i2, 76);
			TransitionMatrix(i2, 76) = 0;
		}
		// 84 to 98
		if (TransitionMatrix(i2, 84) > 0) {
			TransitionMatrix(i2, 98) = TransitionMatrix(i2, 98) + TransitionMatrix(i2, 84);
			TransitionMatrix(i2, 84) = 0;
		}
*/		// Next the snakes
		// 11 to 7
		if (TransitionMatrix(i2, 11) > 0) {
			TransitionMatrix(i2, 7) = TransitionMatrix(i2, 7) + TransitionMatrix(i2, 11);
			TransitionMatrix(i2, 11) = 0;
		}
		// 18 to 13
		if (TransitionMatrix(i2, 18) > 0) {
			TransitionMatrix(i2, 13) = TransitionMatrix(i2, 13) + TransitionMatrix(i2, 18);
			TransitionMatrix(i2, 18) = 0;
		}
		// 28 to 12
		if (TransitionMatrix(i2, 28) > 0) {
			TransitionMatrix(i2, 12) = TransitionMatrix(i2, 12) + TransitionMatrix(i2, 28);
			TransitionMatrix(i2, 28) = 0;
		}
		// 36 to 34
		if (TransitionMatrix(i2, 36) > 0) {
			TransitionMatrix(i2, 34) = TransitionMatrix(i2, 34) + TransitionMatrix(i2, 36);
			TransitionMatrix(i2, 36) = 0;
		}
		// 77 to 16
		if (TransitionMatrix(i2, 77) > 0) {
			TransitionMatrix(i2, 16) = TransitionMatrix(i2, 16) + TransitionMatrix(i2, 77);
			TransitionMatrix(i2, 77) = 0;
		}
		// 47 to 26
		if (TransitionMatrix(i2, 47) > 0) {
			TransitionMatrix(i2, 26) = TransitionMatrix(i2, 26) + TransitionMatrix(i2, 47);
			TransitionMatrix(i2, 47) = 0;
		}
		// 83 to 39
		if (TransitionMatrix(i2, 83) > 0) {
			TransitionMatrix(i2, 39) = TransitionMatrix(i2, 39) + TransitionMatrix(i2, 83);
			TransitionMatrix(i2, 83) = 0;
		}
		// 92 to 75
		if (TransitionMatrix(i2, 92) > 0) {
			TransitionMatrix(i2, 75) = TransitionMatrix(i2, 75) + TransitionMatrix(i2, 92);
			TransitionMatrix(i2, 92) = 0;
		}
		// 99 to 70
		if (TransitionMatrix(i2, 99) > 0) {
			TransitionMatrix(i2, 70) = TransitionMatrix(i2, 70) + TransitionMatrix(i2, 99);
			TransitionMatrix(i2, 99) = 0;
		}

	}
	
	for (int i1 = 0; i1 < size; i1++)
	{
		double rowsum = 0;
		for (int j1 = 0; j1 < size; j1++) {
			rowsum = rowsum + TransitionMatrix(i1, j1);
		}
		if (abs(rowsum - 1) > 0.0000001)  // allow for rounding error
			std::cout << "rowsum <> 1 rowsum = " << rowsum << " i = " << i1 << std::endl;
	}
	

}