#include <iostream>
#include <fstream>
#include "algo_hashed.hpp"
using namespace std;

int ep, n, m, k, iter;
float ga;
string pieceset, log_file, training_file, maxQ_file, performance_file;
int main(int argc, char ** argv) {
	if(argc != 11) throw invalid_argument("Main: not enough parameters to run experiment\nParameters are: ep ga n m k pieceset log_file training_file maxQ_file performance_file");
	

	/* Setting up parameters of experiment */
	ep = stoi(argv[1]);
	ga = stof(argv[2]);
	n = stoi(argv[3]);
	m = stoi(argv[4]);
	k = stoi(argv[5]);
	pieceset = argv[6];
	log_file = argv[7];
	training_file = argv[8];
	maxQ_file = argv[9];
	performance_file = argv[10];

	iter = 100;
	cout << "Running Experiment with these parameters:" << endl;
	cout << "episodes: " << ep << " gamma: " << ga << " board height (including ghost squares): " << n << " board width: " << m << " piece width/height: " << k << " pieceset file: " << pieceset << " log file: " << log_file << " training file: " << training_file << " maxQ file: " << maxQ_file << " performance_file: " << performance_file << endl; 
	/* Setting up parameters of experiment */
	

	/* Run experiment by playing iter # of random games and tracking the score */
	srand(time(NULL));
	Tetris tetris(n, m, k, pieceset);
	int accum_score = 0;
	for(int i=0; i < iter; i++) {
		accum_score += tetris.randPlay();
	}
	int randAvg = (int)((float)accum_score/iter);
	cout << "After " << iter << " games, " << n-k << "x" << m << " board, average random score: " << randAvg << endl;
	
	/* Now train and test with the Q-learning algorithm */
	ofstream performance_file_out(performance_file);
	performance_file_out << ep << " " << ga << " " << n << " " << m << " " << k << " " << pieceset << endl; 
	//Model model(ep, ga, n, m, k, pieceset);
	Model model(ep, ga, n, m, k, pieceset);
	model.train(log_file, training_file, maxQ_file);
	accum_score = 0;
	for(int i=0; i < iter; i++) {
		string b = "";
		string p = "";
		int score = 0;
		int hit = 0;
		int moves = 0;
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
			b = model.getNextState(b+p, hit);
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
			moves++;
		}
		/* Testing */
		/*
		cout << "Final Score: " << score << endl;
		/* Testing */
		performance_file_out << i << "," << score << "," << ((float)hit)/moves << endl;
		accum_score += score;
	}
	performance_file_out.close();
	int QAvg = (int)((float)accum_score/iter);
	cout << "After " << iter << " games, " << n-k << "x" << m << " board, Q-Learning average score: " << QAvg << endl;
	return 0;
}
