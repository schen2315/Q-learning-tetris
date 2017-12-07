#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
class Tetris {
private:
	int n, m;
	int bbits;	//board must be n*m 
	int pbits;	//pbits = k*k
	int pbitsr;	//# rows in pbits 
	int iter_prb;	//game iterations per random board
	int score;
	unordered_map<string, int> unique_boards;
	void calcIter_prb();
public:
	vector<string> pieces;			//all unique pieces
	Tetris(int n, int m, int k, vector<string>& pieces);
	Tetris(int n, int m, int k, string file);
	string rotate(string p);
	string genRandBoard();
	string genRandPiece();
	string genNextRandBoard(string b, string p);
	string getNextBoard(string board, string p, int rotations, int column);		//will be used for testing
	vector<string>& genAllNextValidBoards(string board, string p, vector<string> & v);
	string updateBoard(string board);
	string genContour(string p);
	int isReward(string board);
	bool isGoal(string board);
	void print_all_configs();
	void print_board(string board);
	void print_piece(string p, int rot);
	bool isValidPiece(string p);
	int play();	//return final score
	int randPlay();
	bool intersects(string s1, string s2);
	string merge(string s1, string s2);
	int remove_zero_cols(string & s1);
};