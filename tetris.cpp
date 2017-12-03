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
	if(k > m || k > n) throw invalid_argument("Tetris::Tetris: k must be less than n and m"); 
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
	calcIter_prb();
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
	//input is going to be just board
	for(int i=0;i < board.length(); i++) {
		cout << board[i] << " ";
		if(i % m == m-1) cout << endl;
	}
}
void Tetris::print_piece(string p, int rot) {
	//input is some piece
	if(!isValidPiece(p)) throw invalid_argument("Use a valid value for pbits");
	for(int i=0; i < rot; i++) p = rotate(p);
	for(int i=0;i < p.length(); i++) {
		cout << p[i] << " ";
		if(i % pbitsr == pbitsr-1) cout << endl;
	}
}
void Tetris::print_all_configs() {
	for(int i=0; i < all_configs.size(); i++) {
		print_piece(all_configs[i], 0);
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
	//use this function to figure out how many iterations to generate a random board
	return "";
}
string Tetris::getNextBoard(string board, string p, int rot, int col) {
	//TODO:
		//check that the first pbitsr rows are "0" 
	//what if we have floating pieces?
	for(int i=0; i < pbitsr*m; i++) {
		if(board[i] != '0') throw invalid_argument("Tetris::getNextBoard: board must not be in goal state"); 
	}
	if(board.length() != n*m) throw invalid_argument("board size should be n*m");
	if(p.length() != pbits) throw invalid_argument("string p should have length = to pbits");
	if(rot < 0 || rot > 3) throw invalid_argument("rot should be between 0 and 3 inclusive");
	if(col < 0 || col > m-pbitsr) throw invalid_argument("col must be between 0, m-pbitsr inclusive");
	for(int i=0; i < rot; i++) p = rotate(p);
	string slot = "";
	string new_slot = "";
	int slotl = 0;
	for(int i=0; i < n; i++) {
		slot += board.substr(col+i*m, pbitsr);
	}
	/* Testing */
	/*
	cout << endl;
	for(int i=0;i < slot.length(); i++) {
		cout << slot[i] << " ";
		if(i % pbitsr == pbitsr-1) cout << endl;
	}
	cout << endl;
	/* Testing */
	slotl = slot.length();
	new_slot = p + slot.substr(pbits, slotl-pbits);
	/* Testing */
	/*
	cout << endl;
	for(int i=0;i < new_slot.length(); i++) {
		cout << new_slot[i] << " ";
		if(i % pbitsr == pbitsr-1) cout << endl;
	}
	cout << endl;
	/* Testing */
	for(int i=pbits; i < slot.length()-pbitsr; i+=pbitsr) {
		if(intersects(slot.substr(i, pbits), p)) break;
		new_slot = slot.substr(0, i) + merge(slot.substr(i,pbits),p) + slot.substr(i+pbits, slotl-(i+pbits));
		/* Testing */
		/*
		cout << endl;
		for(int i=0;i < new_slot.length(); i++) {
			cout << new_slot[i] << " ";
			if(i % pbitsr == pbitsr-1) cout << endl;
		}
		cout << endl;
		/* Testing */
	}
	/* Testing */
	/*
	cout << endl;
	for(int i=0;i < new_slot.length(); i++) {
		cout << new_slot[i] << " ";
		if(i % pbitsr == pbitsr-1) cout << endl;
	}
	cout << endl;
	/* Testing */		
	for(int i=0; i < n; i++) {
		board = board.substr(0, col+i*m) + new_slot.substr(i*pbitsr, pbitsr) + board.substr(col+i*m+pbitsr, board.length()-(col+i*m+pbitsr));

	}
	return board;
}
bool Tetris::intersects(string s1, string s2) {
	if(s1.length() != s2.length()) throw invalid_argument("intersects: strings s1 and s2 should have equal length");
	/* Testing */
	/*
	cout << s1 << " " << s2 << endl;
	/* Testing */
	for(int i=0; i < s1.length(); i++) {
		if(s1[i] == '1' && s2[i] == '1') {
			return true;
		}
	}
	return false;
}
string Tetris::merge(string s1, string s2) {
	if(s1.length() != s2.length()) throw invalid_argument("merge: strings s1 and s2 should have equal length");
	string ans = "";
	for(int i=0; i < s1.length(); i++) {
		if(s1[i] == '1' && s2[i] == '1') {
			throw invalid_argument("merge not possible with s1, s2");
		}
		else if(s1[i] == '1' || s2[i] == '1') ans += '1';
		else ans += '0'; 
	}
	return ans;
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
	//check for is this valid ...
	if(isGoal(board)) return board;
	if(isReward(board) <= 0) return board;
	string zeros = "";
	for(int i=0; i < m; i++) zeros += '0';
	int inc = 0;
	bool completed = true;
	if(isGoal(board)) return 0;
	for(int i= pbitsr; i < n; i++) {
		completed = true;
		for(int j=0; j < m; j++) {
			if(board[j+i*m] == '0') {
				completed = false;
				break;
			}
		}
		if(completed) {
			board = zeros + board.substr(0, i*m) + board.substr((i+1)*m, board.length() - ((i+1)*m));
		}
	}
	return board;
}
int Tetris::isReward(string board) {
	int inc = 0;
	bool completed = true;
	if(isGoal(board)) return 0;
	for(int i= pbitsr; i < n; i++) {
		completed = true;
		for(int j=0; j < m; j++) {
			if(board[j+i*m] == '0') {
				completed = false;
				break;
			}
		}
		if(completed) inc+= 1;
	}
	return inc;
}
bool Tetris::isGoal(string board) {
	//check for is this valid ...
	for(int i=0; i < pbitsr*m; i++) {
		if(board[i] != '0') return true;
	}
	return false;
}
void Tetris::calcIter_prb() {
	//TODO:
		//figure out # of iterations per random board
		//to ensure a uniform distribution between nearly complete and nearly empty boards
}