#include "tetris.hpp"
#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;
Tetris::Tetris(int n, int m, int k, vector<string> & pieces) {
	this->n = n;
	this->m = m;
	this->bbits = n*m;			//1st k rows are dummy rows to check if the board has reached its goal state
	this->pbits = k*k;
	this->pbitsr = k;
	this->pieces = pieces;		//deep copy
	//get all unique rotations
	//insert the pieces into the all_config
	unordered_map<string, int> unique;
	string p;
	for(int i=0; i < pieces.size(); i++) {
		p = pieces[i];
		for(int i=0; i < 4; i++) {
			p = rotate(p);
			if(unique.find(p) == unique.end()) {
				unique[p] = 1;
				this->all_configs.push_back(p);
			}
		}
	}
}
void Tetris::play() {

}
string Tetris::rotate(string p) {		//O(n)
	string retVal = "";
	for(int i=0; i < pbitsr; i++) {
		for(int j=pbitsr-1; j >= 0; j--) {
			retVal += p[i+pbitsr*j];
		}
	}
	return retVal;
}
void Tetris::print_board(string board) {
	//input is going to be board + piece?
}
void Tetris::print_piece(string p) {
	//input is some piece
	if(!isValidPiece(p)) throw invalid_argument("Use a valid value for pbits");
	for(int i=0;i < p.length(); i++) {
		cout << p[i] << " ";
		if(i % pbitsr == pbitsr-1) cout << endl;
	}
}
void Tetris::print_all_configs() {
	for(int i=0; i < all_configs.size(); i++) {
		print_piece(all_configs[i]);
		cout << endl;
	}
}
bool Tetris::isValidPiece(string p) {
	//check that it is all ones & zeros
	if(p.length() != pbits) return false;
	for(int i=0; i < p.length(); i++) {
		if(p[i] != '1' && p[i] != '0') {
			return false;
		}
	}
	return true;
}
string Tetris::genRandBoard() {
	//uses getNextBoard
	return "";
}
string Tetris::getNextBoard(string board, string p, int rot, int col) {
	if(board.length() != n*m) throw invalid_argument("board size should be n*m");
	if(p.length() != pbits) throw invalid_argument("string p should have length = to pbits");
	if(rot < 0 || rot > 3) throw invalid_argument("rot should be between 0 and 3 inclusive");
	if(col < 0 || col > m-pbitsr) throw invalid_argument("col must be between 0, m-pbitsr inclusive");
	for(int i=0; i < rot; i++) p = rotate(p);
	string slot = "";
	string new_slot = "";
	int slotl = 0;
	for(int i=0; i < n; i++) {
		slot += board.substr(col+i*pbitsr, pbitsr);
	}
	slotl = slot.length();
	new_slot = p + slot.substr(pbits, slotl-pbits);
	for(int i=pbits; i < slot.length() - pbits;i+=pbitsr) {
		if(intersects(slot.substr(i, pbits), p)) break;
		new_slot = slot.substr(0, i) + p + slot.substr(i+pbits, slotl-(i+pbits));
	}
	for(int i=0; i < n; i++) {
		board = board.substr(0, col+i*pbitsr) + slot.substr(col+i*pbitsr, pbitsr) + board.substr(col+i*pbitsr+pbitsr, board.length()-(col+i*pbitsr+pbitsr));
	}
	return board;
}
bool Tetris::intersects(string s1, string s2) {
	if(s1.length() != s2.length()) throw invalid_argument("strings s1 and s2 should have equal length");
	for(int i=0; i < s1.length(); i++) {
		if(slot[i+j] == '1' && p[j] == '1') {
			return false;
		}
	}
	return true;
}
string Tetris::genContour(string p) {
	bool zero;
	for(int i=0; i < pbitsr; i++) {
		zero = false;
		for(int j=pbitsr-1; j >= 0; j--) {
			if(p[i+pbitsr*j] == '1' && zero) p[i+pbitsr*j] = '0';
			if(p[i+pbitsr*j] == '1') zero = true;
		}
	}
	return p;
}
vector<string>& Tetris::genAllNextValidBoards(string board, vector<string> & v) {
	v.clear();
	return v;
}
string Tetris::updateBoard(string board) {
	return "";
}
bool Tetris::isReward(string board) {
	return false;
}
bool Tetris::isGoal(string board) {
	return false;
}