int usage_message(string str, string info);

string lower(string & x);

enum array_indices_t{ PROGRAM_NAME, INPUT_FILE_NAME, CMD_LINE_ARG_NUM };

enum result_{
	SUCCESS,
	DRAW_RESULT,
	INVALID_INPUT_STRING,
	INVALID_MOVE,
	USER_QUIT,
	INVALID_START,
	BAD_ALLOC
};
