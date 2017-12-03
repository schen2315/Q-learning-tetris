#include <iostream>
#include "tetris.hpp"
#include "algo_hashed.hpp"
using namespace std;

int main() {
	//Model m("sample.txt");
	//m.train("dummy");
	
	//testing tetris
	vector<string> pieces;
	string p[] = {"1011", "1010", "0010", "1111", "1001"};
	
	for(int i=0; i < 5; i++) pieces.push_back(p[i]);
	Tetris board(6, 4, 2, pieces);
	/*
	board.print_all_configs();
	
	for(int i=0; i < 5; i++) {
		board.print_piece(board.genContour(p[i]));
		cout << endl;
	}
	
	string p1r = p1;
	cout << "Original:" << endl;
	board.print_piece(p1);
	cout << "Rotated:" << endl;
	for(int i=0; i < 4; i++) {
		p1r = board.rotate(p1r);
		board.print_piece(p1r);
		cout << endl;
	}
	*/
	
	string b1 = "000000000000000001000100";
	cout << "piece, board: " << endl;
	board.print_piece(p[0], 2);
	cout << endl;
	board.print_board(b1);
	cout << endl;
	b1 = board.getNextBoard(b1, p[0], 2, 1);
	board.print_board(b1);
	return 0;
}
