#include <iostream>
#include "algo_hashed.hpp"
using namespace std;

int n, m, k, iter;
int main() {
	n = 6;
	m = 4;
	k = 2;
	iter = 10;
	/* Run experiment by playing 100 random games and tracking the score */
	Model m(n, m, k, "tetris-piece-set-1.txt");
	m.train("dummy");

	Tetris tetris(n, m, k, "tetris-piece-set-1.txt");
	int accum_score = 0;
	for(int i=0; i < iter; i++) {
		accum_score += tetris.randPlay();
	}
	int randAvg = (int)((float)accum_score/iter);
	cout << "After " << iter << " games, " << n-k << "x" << m << " board, average random score: " << randAvg << endl;

	accum_score = 0;

	for(int i=0; i < iter; i++) {
		string b = "";
		string p = "";
		int score = 0;
		for(int i=0; i < n*m; i++) b += "0";
		while(!isGoal(b)) {
			p = genRandPiece();
			/* Testing */
			/*
			cout << endl;
			print_piece(p, 0);
			cout << endl;
			print_board(b);
			cout << endl;
			cout << "Press Enter to Continue" << endl;
			cin.ignore();
			/* Testing */
			b = m.getNextState(b, p);
			/* Testing */
			/*
			cout << endl;
			print_board(b);
			cout << endl;
			/* Testing */
			score += isReward(b);
			/* Testing */
			/*
			cout << "score: " << score << endl;
			/* Testing */
			b = updateBoard(b);
		}
		/* Testing */
		/*
		cout << "Final Score: " << score << endl;
		/* Testing */
		accum_score += score;
	}
	int QAvg = (int)((float)accum_score/iter);
	return 0;
}
