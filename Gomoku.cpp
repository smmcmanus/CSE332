void Gomoku::set_values()
{
	currentPlayer = 0;
	width = height = 20;
	int spaces = width*height;
	for (int i = 0; i <= spaces; ++i) v.push_back(" ");
	players = { "B", "W" };

	longestString = players[0].length();
}


bool Gomoku::done()
{
	//cout << "Checking for win..." << endl;
	bool winner = false;
	// check for win moving vertically up cols
	for (int i = 1; i < height; i++){

		// check for win moving horizontally along rows
		for (int j = 1; j < width; j++) {

			int index = width*i + j;

			// if potential win within the boundary for the row, check for win
			if (j + 4 < width) {
				winner = !v[index].compare(" ") == 0
					&& v[index].compare(v[index + 1]) == 0
					&& v[index + 1].compare(v[index + 2]) == 0
					&& v[index + 2].compare(v[index + 3]) == 0
					&& v[index + 3].compare(v[index + 4]) == 0;
			}
			if (winner) return true;
			// if potential win within the boundary for the col, check for win
			if (i + 4 < height) {
				winner = !v[index].compare(" ") == 0
					&& v[index].compare(v[index + width]) == 0
					&& v[index + width].compare(v[index + 2 * width]) == 0
					&& v[index + 2 * width].compare(v[index + 3 * width]) == 0
					&& v[index + 3 * width].compare(v[index + 4 * width]) == 0;
			}
			if (winner) return true;
			// check for up-left diagonal
			if (j - 4 > 0 && i + 4 < height) {
				winner = !v[index].compare(" ") == 0
					&& v[index].compare(v[index + width - 1]) == 0
					&& v[index + width - 1].compare(v[index + 2 * width - 2]) == 0
					&& v[index + 2 * width - 2].compare(v[index + 3 * width - 3]) == 0
					&& v[index + 3 * width - 3].compare(v[index + 4 * width - 4]) == 0;
			}
			if (winner) return true;

			// check for up-right diagonal
			if (j + 4 < width && i + 4 < height) {
				winner = !v[index].compare(" ") == 0
					&& v[index].compare(v[index + width + 1]) == 0
					&& v[index + width + 1].compare(v[index + 2 * width + 2]) == 0
					&& v[index + 2 * width + 2].compare(v[index + 3 * width + 3]) == 0
					&& v[index + 3 * width + 3].compare(v[index + 4 * width + 4]) == 0;
			}
			if (winner) return true;
		}
	}

	return false;
}

bool Gomoku::draw()
{
	//cout << "Checking for draw..." << endl;
	bool draw = true;

	// store the opponents string to check against
	string oppo = players[!currentPlayer];

	// check for win moving vertically up cols
	for (int i = 1; i < height; i++){

		// check for win moving horizontally along rows
		for (int j = 1; j < width; j++) {

			//cout << "In for it now..." << endl;
			int index = width*i + j;

			// check for the row by checking for oppo move in space
			if (j + 4 < width) {
				draw = v[index].compare(oppo) == 0
					|| v[index + 1].compare(oppo) == 0
					|| v[index + 2].compare(oppo) == 0
					|| v[index + 3].compare(oppo) == 0
					|| v[index + 4].compare(oppo) == 0;
			}
			if (!draw) return false;

			// check for the col
			if (i + 4 < height) {
				draw = v[index].compare(oppo) == 0
					|| v[index + width].compare(oppo) == 0
					|| v[index + 2 * width].compare(oppo) == 0
					|| v[index + 3 * width].compare(oppo) == 0
					|| v[index + 4 * width].compare(oppo) == 0;
			}
			if (!draw) return false;

			// check for up-left diagonal
			if (j - 4 > 0 && i + 4 < height) {
				draw = v[index].compare(oppo) == 0
					|| v[index + width - 1].compare(oppo) == 0
					|| v[index + 2 * width - 2].compare(oppo) == 0
					|| v[index + 3 * width - 3].compare(oppo) == 0
					|| v[index + 4 * width - 4].compare(oppo) == 0;
			}
			if (!draw) return false;

			// check for up-right diagonal
			if (j + 4 < width && i + 4 < height) {
				draw = v[index].compare(oppo) == 0
					|| v[index + width + 1].compare(oppo) == 0
					|| v[index + 2 * width + 2].compare(oppo) == 0
					|| v[index + 3 * width + 3].compare(oppo) == 0
					|| v[index + 4 * width + 4].compare(oppo) == 0;
			}
			if (!draw) return false;
		}
	}
	// if reached, entire board has been scanned
	return true;
}

int Gomoku::turn()
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
	for (int i = 1; i < height; ++i)
	{
		for (int j = 1; j < width; ++j)
		{
			if (v[width*i + j].compare(players[currentPlayer]) == 0) cout << j << "," << i << "; ";
		}
	}
	cout << endl << endl;

	// switch the player after the method called
	currentPlayer = !currentPlayer;
	return SUCCESS;
}

ostream& operator<<(ostream& stream, const Gomoku &game)
{
	// print from top left corner across, then jump to next line
	//	to start printing the next row, all the way until the bottom right
	unsigned int index;
	int width = game.width;
	int height = game.height;

	cout << endl;

	for (int i = height - 1; i >= 0; --i)
	{
		// print the line separator
		cout << endl << "   " << "---------------------------------------------------------------------------" << endl;

		for (int j = 0; j < width; ++j)
		{

			// print the label along left col with space as necessary
			if (j == 0) cout << (i < 10 ? " " : "") << i << (i == 0 ? "" : "|");
			// print all labels along bottom
			else if (i == 0) cout << (j <= 10 ? "  " : " ") << j << " ";
			// print the board
			else {
				index = width*i + j;
				cout << " " << game.v[index] << " |";
			}
		}
	}
	return stream;
}