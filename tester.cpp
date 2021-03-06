#include "algo_hashed.hpp"
#include <vector>
#include <iostream>
#include <string>

int n, m;
int k, r, c;
string p;
string b;
string temp = "";
vector<string> pieces;
vector<string> allNextBoards;
int main(int argc, char ** argv) {
	
	if(argc == 2 && strncmp(argv[1], "generate", 8) == 0) {
		n = 10, m = 4, k = 3;
		// pieces.push_back("1111");
		// pieces.push_back("0111");
		// pieces.push_back("1010");
		// pieces.push_back("0010");
		pieces.push_back("111000000");
		Tetris game(n, m, k, pieces);
		//game.print_board(game.genRandBoard());
		//game.genRandBoard();
		//string p = "100100100";
		string p = "010110010";
		int pcols = game.remove_zero_cols(p);
		cout << p << " " << pcols << endl;
		for(int i=0; i < p.length(); i++) {
			cout << p[i] << " ";
			if(i % pcols == pcols-1) cout << endl;
		}
		return 0;
	}
	// if(argc == 2 && strncmp(argv[1], "algo", 8) == 0) {
	// 	cin >> n >> m >> k >> r >> c;
	// 	for(int i=0; i < k; i++) {
	// 		cin >> temp;
	// 		if(temp.length() != k) cout << "Error" << endl;
	// 		p += temp;
	// 	}
	// 	for(int i=0; i < n; i++) {
	// 		cin >> temp;
	// 		if(temp.length() != m) cout << "Error" << endl;
	// 		b += temp;
	// 	}
	// 	Model model(n, m, k, "tetris-piece-set-2.txt");
	// 	/* genRandState */
	// 	model.genRandState();
	// 	/* genNextRandState */
	// 	string b1p1 = model.genNextRandState(b+p);
	// 	/* hasReachedGoalState */
	// 	model.hasReachedGoalState(b1p1);
	// 	/* genAllNextValidStates */
	// 	model.genAllNextValidStates(b+p, allNextBoards);
	// 	/* isValidState */
	// 	model.isValidState(b+p);
	// 	/* isRewardState */
	// 	model.isRewardState(b+p+b1p1);
	// 	/* updateState */
	// 	model.updateState(b1p1);
	// 	return 0;
	// }
	// if(argc == 2 && strncmp(argv[1], "randomgame", 10) ==0) {
	// 	n = 10, m = 4, k = 2;
	// 	pieces.push_back("1111");
	// 	pieces.push_back("0111");
	// 	pieces.push_back("1010");
	// 	pieces.push_back("0010");
	// 	Tetris game(n, m, k, pieces);
	// 	game.randPlay();
	// 	return 0;
	// } 
	// cin >> n >> m >> k >> r >> c;
	// for(int i=0; i < k; i++) {
	// 	cin >> temp;
	// 	if(temp.length() != k) cout << "Error" << endl;
	// 	p += temp;
	// }
	// for(int i=0; i < n; i++) {
	// 	cin >> temp;
	// 	if(temp.length() != m) cout << "Error" << endl;
	// 	b += temp;
	// }
	// pieces.push_back("1000100010001000");
	// //Tetris game(n, m, k, "tetris-piece-set-2.txt");
	// Tetris game(n,m,k,pieces);
	// game.print_piece(p, 0);
	// cout << endl;
	// cout << "rotations: " << r << endl;
	// cout << endl;
	// game.print_piece(p, r);
	// cout << endl;
	// cout << "column: " << c << endl;
	// cout << endl;
	// game.print_board(b);
	// cout << endl;
	// string nextBoard = game.getNextBoard(b, p, r, c);
	// game.print_board(nextBoard);
	// cout << endl;
	// cout << "Reward: " << game.isReward(nextBoard) << endl;
	// cout << "Goal: " << (game.isGoal(nextBoard) ? "yes" : "no") << endl;
	// cout << endl;
	// cout << "Updated board: " << endl;
	// game.print_board(game.updateBoard(nextBoard)); 
	// cout << endl;
	// cout << "All next boards: " << endl;
	// game.genAllNextValidBoards(b, p, allNextBoards);
	// for(int i=0; i < allNextBoards.size(); i++) {
	// 	cout << endl;
	// 	game.print_board(allNextBoards[i]);
	// }
	Tetris game(24, 10, 4, "tetris-piece-set-3.txt");
	return 0;
}