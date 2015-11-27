// Defines all methods and printing for playing 
//	Tic Tac Toe

void TicTacToe::set_values()
{
	currentPlayer = 0;
	width = height = 5;
	for (int i = 0; i < 25; ++i) v.push_back(" ");
	players = { "X", "O" };

	longestString = players[0].length();
}

bool TicTacToe::done()
{
	bool winner = false;
	// check each row
	for (int i = 1; i < height - 1 && !winner; ++i)
	{
		int index = width*i + 1;
		winner = !v[index].compare(" ") == 0 && v[index].compare(v[index + 1]) == 0 && v[index + 1].compare(v[index + 2]) == 0;
	}

	// check each column
	for (int i = 1; i < width - 1 && !winner; ++i)
	{
		int index = width + i;
		winner = !v[index].compare(" ") == 0 && v[index].compare(v[index + 5]) == 0 && v[index + 5].compare(v[index + 10]) == 0;
	}

	// check the diagonals
	if (!winner) winner = !v[6].compare(" ") == 0 && v[6].compare(v[12]) == 0 && v[12].compare(v[18]) == 0;
	if (!winner) winner = !v[8].compare(" ") == 0 && v[8].compare(v[12]) == 0 && v[12].compare(v[16]) == 0;

	return winner;
}

bool TicTacToe::draw()
{
	bool draw = true;
	// if any space contains empty string, game is not a draw
	for (int i = 1; i < height - 1 && draw; ++i)
	{
		int index = width*i + 1;
		draw = !(v[index].compare(" ") == 0) && !v[index + 1].compare(" ") == 0 && !v[index + 2].compare(" ") == 0;
	}

	return draw;
}

int TicTacToe::turn()
{
	cout << "It is Player " << players[currentPlayer] << "'s turn." << endl;

	unsigned int col;
	unsigned int row;

	// prompt guarantees a valid string or quit 
	int result = prompt(col, row);
	if (result == USER_QUIT) return USER_QUIT;

	// make the move and update longestString if needed
	if (players[currentPlayer].length() > longestString){
		longestString = players[currentPlayer].length();
	}
	v[width*row + col] = players[currentPlayer];

	// print the board
	cout << *this << endl << endl;

	// print all valid moves the player has made
	cout << "Player " << players[currentPlayer] << ": ";
	for (int i = 1; i < height - 1; ++i)
	{
		for (int j = 1; j < width - 1; ++j)
		{
			if (v[width*i + j].compare(players[currentPlayer]) == 0) cout << j << "," << i << "; ";
		}
	}
	cout << endl << endl;

	// switch the player after the method called
	currentPlayer = !currentPlayer;
	return SUCCESS;
}

ostream& operator<<(ostream& stream, const TicTacToe &game)
{
	// print from top left corner across, then jump to next line
	//	to start printing the next row, all the way until the bottom right
	unsigned int index;
	int width = game.width;
	int height = game.height;

	cout << endl;

	for (int i = height - 1; i >= 0; --i)
	{
		for (int j = 0; j < width; ++j)
		{
			// print the label along left col
			if (j == 0) cout << i;
			// print all labels along bottom
			else if (i == 0) cout << "  " << j << " ";
			// print the board
			else {
				index = width*i + j;
				cout << game.v[index];
				if (j < width - 2 && i < height - 1) cout << " | ";
			}

			// print the left and right borders
			if ((j == 0 || j == width - 1) && (i > 0 && i < height - 1)) cout << "| ";
		}
		if (i > 0) cout << endl << "  " << "-----------" << endl;
		else cout << endl;
	}
	return stream;
}