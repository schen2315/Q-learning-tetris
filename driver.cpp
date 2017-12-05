#include <iostream>
#include "algo_hashed.hpp"
using namespace std;

int n, m, k, iter;
int main() {
	n = 6;
	m = 4;
	k = 2;
	iter = 10;
	srand(time(NULL));
	/* Run experiment by playing 100 random games and tracking the score */
	Tetris tetris(n, m, k, "tetris-piece-set-1.txt");
	int accum_score = 0;
	for(int i=0; i < iter; i++) {
		accum_score += tetris.randPlay();
	}
	int randAvg = (int)((float)accum_score/iter);
	cout << "After " << iter << " games, " << n-k << "x" << m << " board, average random score: " << randAvg << endl;
	
	/* Now train and test with the Q-learning algorithm */
	Model model(n, m, k, "tetris-piece-set-1.txt");
	model.train("dummy");
	accum_score = 0;
	for(int i=0; i < iter; i++) {
		string b = "";
		string p = "";
		int score = 0;
		for(int i=0; i < n*m; i++) b += "0";
		while(!tetris.isGoal(b)) {
			p = tetris.genRandPiece();
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
			b = model.getNextState(b+p);
			/* Testing */
			/*
			cout << endl;
			print_board(b);
			cout << endl;
			/* Testing */
			score += tetris.isReward(b);
			/* Testing */
			/*
			cout << "score: " << score << endl;
			/* Testing */
			b = tetris.updateBoard(b);
		}
		/* Testing */
		/*
		cout << "Final Score: " << score << endl;
		/* Testing */
		accum_score += score;
	}
	int QAvg = (int)((float)accum_score/iter);
	cout << "After " << iter << " games, " << n-k << "x" << m << " board, Q-Learning average score: " << QAvg << endl;
	return 0;
}
