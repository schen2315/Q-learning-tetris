#include "tetris.hpp"
#include <vector>
#include <iostream>
#include <string>

int n, m;
int k, r, c;
string p;
string b;
string temp = "";
int main() {
	vector<string> pieces;
	cin >> n >> m >> k >> r >> c;
	for(int i=0; i < k; i++) {
		cin >> temp;
		if(temp.length() != k) cout << "Error" << endl;
		p += temp;
	}
	for(int i=0; i < n; i++) {
		cin >> temp;
		if(temp.length() != m) cout << "Error" << endl;
		b += temp;
	}
	Tetris game(n, m, k, pieces);
	game.print_piece(p, 0);
	cout << endl;
	cout << "rotations: " << r << endl;
	cout << endl;
	game.print_piece(p, r);
	cout << endl;
	cout << "column: " << c << endl;
	cout << endl;
	game.print_board(b);
	cout << endl;
	game.print_board(game.getNextBoard(b, p, r, c));
	return 0;
}