#include <string>
#include <vector>

using namespace std;
class Tetris {
private:
	int n, m;
	int bbits;	//board must be n*m 
	int pbits;	//pbits = k*k
	int pbitsr;	//# rows in pbits 
	int iter_prb;	//game iterations per random board
	int score;
	vector<string> pieces;			//all unique pieces
	vector<string> all_configs;		//all unique configurations for every piece

	void calcIter_prb();
public:
	Tetris(int n, int m, int k, vector<string>& pieces);
	string rotate(string p);
	string genRandBoard();
	string getNextBoard(string board, string p, int rotations, int column);		//will be used for testing
	vector<string>& genAllNextValidBoards(string board, vector<string> & v);
	string updateBoard(string board);
	string genContour(string p);
	int isReward(string board);
	bool isGoal(string board);
	void print_all_configs();
	void print_board(string board);
	void print_piece(string p, int rot);
	bool isValidPiece(string p);
	void play();
	bool intersects(string s1, string s2);
	string merge(string s1, string s2);
	void resetScore();
};