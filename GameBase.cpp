// Defines all methods and printing for playing 
//	any game

static GameBase* chooseGame(int argc, char* argv[]) {
	if (argc != 2) return 0;

	GameBase* gb;
	// See step 16-20 for implementation instructions
	if (strcmp(argv[1], "TicTacToe") == 0) {
		try {
			gb = new TicTacToe;
		}
		catch (...) {
			throw BAD_ALLOC;
		}
		return gb;
	}

	else if (strcmp(argv[1], "Gomoku") == 0) {
		try {
			gb = new Gomoku;
		}
		catch (...) {
			throw BAD_ALLOC;
		}
		return gb;
	}

	else return 0;
}

int GameBase::prompt(unsigned int &col, unsigned int &row)
{
	bool validInput = false;

	while (!validInput)
	{
		int result = SUCCESS;
		cout << endl << "Player  " << players[currentPlayer] << ", enter a valid move 'x,y' or 'quit' to exit:" << endl;

		string input;
		cin >> input;

		// if string is quit, return quit instruction
		if (input == "quit") return USER_QUIT;

		// if the string contains a comma, attempt to extract values
		if (input.find(",") != string::npos) input.replace(input.find(","), sizeof(" ") - 1, " ");
		else result = INVALID_INPUT_STRING;
		istringstream iss(input);

		if (!(iss >> col)) result = INVALID_INPUT_STRING;
		if (!(iss >> row)) result = INVALID_INPUT_STRING;

		if (result == SUCCESS)
		{
			if (col < 1 || col > width - 1 || row < 1 || row > height - 1) result = INVALID_MOVE;
			else if (v[width*row + col] != " ") result = INVALID_MOVE;
		}

		// print out the correct error
		if (result != SUCCESS)
		{
			if (result == INVALID_INPUT_STRING) cout << "Error: Invalid string input" << endl;
			else if (result == INVALID_MOVE) cout << "Error: Invalid move" << endl
				<< "Please pick an open space within the board" << endl;
			else cout << "Error: An unknown error occured" << endl;
		}

		validInput = result == SUCCESS;
	}

	return SUCCESS;
}

int GameBase::play()
{
	// print board
	print();
	int turns = 0;
	bool gameOver = false;

	while (!gameOver)
	{
		int result = turn();
		if (result == USER_QUIT) {
			cout << endl << "Player " << players[currentPlayer] << " has quit." << endl
				<< turns << " turns were played." << endl;
			return USER_QUIT;
		}

		gameOver = done();
		if (gameOver) {
			cout << "Player " << players[!currentPlayer] << " has won!" << endl
				<< turns << " turns were played." << endl;
			return SUCCESS;
		}

		gameOver = draw();
		if (gameOver) {
			cout << "It's a draw after " << turns << " turns!" << endl;
			return DRAW_RESULT;
		}

		turns++;
	}
	return SUCCESS;
}