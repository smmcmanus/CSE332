

class GameBase {
protected:
	static shared_ptr<GameBase> ptr;

	vector<string> v;
	int width, height;
	int currentPlayer;
	vector<string> players;
	unsigned int longestString;

public:
	static GameBase* chooseGame(int argc, char* argv[]);

	// pure virtual methods
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;
	virtual void print() = 0;

	int prompt(unsigned int&, unsigned int&);
	int play();

};

class TicTacToe : public GameBase {

public:
	void set_values();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print() override {
		cout << *this << endl;
	};

	TicTacToe() {
		set_values();
	}

	friend ostream& operator<<(ostream& stream, const TicTacToe &game);
};

class Gomoku : public GameBase {

public:
	void set_values();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print() override {
		cout << *this << endl;
	};

	Gomoku() {
		set_values();
	}

	friend ostream& operator<<(ostream& stream, const Gomoku &game);
};