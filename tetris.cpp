#include "tetris.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>
#define ITER 100
using namespace std;
Tetris::Tetris(int n, int m, int k, vector<string> & pieces) {
	this->n = n;
	this->m = m;
	this->bbits = n*m;			//1st k rows are dummy rows to check if the board has reached its goal state
	this->pbits = k*k;
	this->pbitsr = k;
	this->pieces = pieces;		//deep copy 
	//cout << "Tetris::Tetris" << endl;
	for(int i=0; i<pieces.size(); i++) {
		print_piece(pieces[i], 0);
	}
	if(k > m || k > n) throw invalid_argument("Tetris::Tetris: k must be less than n and m"); 
	srand(time(NULL));
	calcIter_prb();

}
Tetris::Tetris(int n, int m, int k, string file) {
	ifstream in(file);
	string temp;
	vector<string> pieces;
	while(true) {
		in >> temp;
		pieces.push_back(temp);
		if(in.eof()) break;
	}
	this->n = n;
	this->m = m;
	this->bbits = n*m;			//1st k rows are dummy rows to check if the board has reached its goal state
	this->pbits = k*k;
	this->pbitsr = k;
	this->pieces = pieces;		//deep copy 
	if(k > m || k > n) throw invalid_argument("Tetris::Tetris: k must be less than n and m"); 
	srand(time(NULL));
	calcIter_prb();
	for(int i=0; i<pieces.size(); i++) {
		print_piece(pieces[i], 0);
		cout << endl;
	}
	in.close();
}
int Tetris::play() {
	return 0;
}
int Tetris::randPlay() {
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
		b = genNextRandBoard(b, p);
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
	return score;
}
string Tetris::rotate(string p) {		//O(n)
	string retVal = "";
	string zerorows = "";
	for(int i=0; i < pbitsr; i++) {
		for(int j=pbitsr-1; j >= 0; j--) {
			retVal += p[i+pbitsr*j];
		}
	}
	bool zeros = true;
	int inc = 0;
	for(int i=pbitsr-1; i >= 0; i--) {
		for(int j=0; j < pbitsr; j++) {
			if(retVal[j+i*pbitsr] == '1') {
				zeros = false;
				break;
			}
		}
		if(!zeros) break;
		inc++;
	}
	for(int i=0; i < pbitsr*inc; i++) zerorows += '0';
	retVal = zerorows + retVal.substr(0, (pbitsr-inc)*pbitsr);
	return retVal;
}
void Tetris::print_board(string board) {
	//input is going to be just board
	if(board.length() != n*m) throw invalid_argument("board size must be n*m");
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
	/*
	for(int i=0; i < all_configs.size(); i++) {
		print_piece(all_configs[i], 0);
		cout << endl;
	}
	*/
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
	string retVal;
	string p;
	//int r, c;
	int it = rand() % this->iter_prb;
	do {
		retVal = "";
		for(int i=0; i < this->bbits; i++) retVal += '0';
		for(int i=0; i < it; i++) {
			if(isGoal(retVal)) break;
			p = pieces[rand() % pieces.size()];
			//r = rand() % 4;
			//c = rand() % (m-pbitsr+1); 
			//retVal = getNextBoard(retVal, p, r, c);
			retVal = genNextRandBoard(retVal, p);
			/* Testing */
			/*
			cout << endl;
			print_board(retVal);
			cout << endl;
			/* Testing */
			if(isReward(retVal)) retVal = updateBoard(retVal);
		}
		/* Testing */
		/*
		cout << "iterating ... " << it << endl;
		print_board(retVal);
		/* Testing */
	} while(isGoal(retVal));
	return retVal;
}
string Tetris::genNextRandBoard(string b, string p) {
	//check that board and piece are valid
	/*
	int r, c;
	string retVal = "";
	r = rand() % 4;
	c = rand() % (m-pbitsr+1);
	retVal = getNextBoard(b, p, r, c);
	*/
	vector<string> nextBoards;
	nextBoards = genAllNextValidBoards(b, p, nextBoards);
	string retVal = nextBoards[rand() % nextBoards.size()];
	return retVal;
}
string Tetris::genRandPiece() {
	string p = pieces[rand() % this->pieces.size()];
	return p;
}
string Tetris::getNextBoard(string board, string p, int rot, int col) {
	//TODO: 
	//what if we have floating pieces?
	for(int i=0; i < pbitsr*m; i++) {
		if(board[i] != '0') throw invalid_argument("Tetris::getNextBoard: board must not be in goal state"); 
	}
	if(board.length() != n*m) throw invalid_argument("board size should be n*m");
	if(p.length() != pbits) throw invalid_argument("string p should have length = to pbits");
	if(rot < 0 || rot > 3) throw invalid_argument("rot should be between 0 and 3 inclusive");
	//if(col < 0 || col > m-pbitsr) throw invalid_argument("col must be between 0, m-pbitsr inclusive");
	for(int i=0; i < 4; i++) p = rotate(p);
	for(int i=0; i < rot; i++) p = rotate(p);
	/*
		remove any zero row and columns in the piece
		update the piece width & height
	*/
	int pcols = remove_zero_cols(p);

	string slot = "";
	string new_slot = "";
	int slotl = 0;
	for(int i=0; i < n; i++) {
		slot += board.substr(col+i*m, pcols);
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
	new_slot = p + slot.substr(p.length(), slot.length()-p.length());
	/* Testing */
	/*
	cout << endl;
	cout << "Testing new_slot on " << pcols << " " << col << endl;
	for(int i=0;i < new_slot.length(); i++) {
		cout << new_slot[i] << " ";
		if(i % pbitsr == pbitsr-1) cout << endl;
	}
	cout << endl;
	/* Testing */
	for(int i=0; i <= slot.length()-p.length(); i+=pcols) {
		if(intersects(slot.substr(i, p.length()), p)) break;
		new_slot = slot.substr(0, i) + merge(slot.substr(i,p.length()),p) + slot.substr(i+p.length(), slotl-(i+p.length()));
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
		board = board.substr(0, col+i*m) + new_slot.substr(i*pcols, pcols) + board.substr(col+i*m+pcols, board.length()-(col+i*m+pcols));
	}
	return board;
}
int Tetris::remove_zero_cols(string & p) {
	/* Testing */
	/*
	cout << pbitsr << endl;
	/* Testing */
	string p_zeros_removed = "";
	int pcols = pbitsr;
	int zero_cols[pbitsr];
	for(int i=0; i < pbitsr; i++) zero_cols[i] = 1;
	bool isZero;
	for(int i=0; i < pbitsr; i++) {
		isZero = true;
		for(int j=0; j < pbitsr; j++) {
			if(p[i+j*pbitsr] == '1') {
				isZero = false;
				break;
			}
		}
		if(isZero) {
			zero_cols[i] = 0;
			pcols--;
		}
	}
	for(int i=0; i < pbitsr; i++) {
		for(int j=0; j < pbitsr; j++) {
			if(zero_cols[j]) p_zeros_removed += p[j+i*pbitsr];
		}
	}
	p = p_zeros_removed;
	return pcols;
}
bool Tetris::intersects(string s1, string s2) {
	/* Testing */
	/*
	cout << s1 << " " << s2 << endl;
	/* Testing */
	if(s1.length() != s2.length()) throw invalid_argument("intersects: strings s1 and s2 should have equal length");
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
vector<string>& Tetris::genAllNextValidBoards(string board, string p, vector<string> & v) {
	//vector is composed of board ONLY
	v.clear();
	unique_boards.clear();
	string nextBoard = "";
	if(isGoal(board)) return v;
	/* Testing */
	/*
	cout << "Tetris::genAllNextValidBoards" << endl;
	print_board(board);
	cout << endl;
	print_piece(p, 0);
	cout << endl;
	/* Testing */
	int pcols;
	string temp_p;
	for(int i=0; i < m; i++) {	//each valid column
		for(int j=0; j <= 3; j++) {
			temp_p = p;
			for(int k=0; k < j; k++) temp_p = rotate(temp_p);
			pcols = remove_zero_cols(temp_p);
			/* Testing */
			/*
			print_piece(p, j);
			cout << i << " " << j << " " << pcols << " " << m << endl;
			/* Testing */
			if(i+pcols <= m) {
				nextBoard = getNextBoard(board, p, j, i);
				//make sure each board is unique ...
				//use a hash table
				if(unique_boards.find(nextBoard) == unique_boards.end()) {
					unique_boards[nextBoard] = 1;
					/* Testing */
					/*
					cout << "Tetris::genAllNextValidBoards, nextBoard: " << endl;
					print_board(nextBoard);
					cout << endl;
					/* Testing */
					v.push_back(nextBoard);
				}
			}
		}
	}
	unique_boards.clear();
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
	int iter2goal[ITER];
	int inc, r, c;
	int average = 0;
	string board, p;
	/* Testing */
	/*
	cout << "Calculating iter_prb" << endl;
	cout << average << " " << ITER << endl;
	/* Testing */
	for(int it=0; it < ITER; it++) {
		inc = 0;
		string board = "";
		for(int i=0; i < this->bbits; i++) board += '0';
		while(!isGoal(board)) {
			// cout << pieces.size() << " " << (m-pbitsr+1) << endl;
			p = pieces[rand() % pieces.size()];
			// r = rand() % 4;
			// c = rand() % (m-pbitsr+1); 
			// cout << p << " " << r << " " << c << endl;
			board = genNextRandBoard(board, p);
			/* Testing */
			/*
			cout << endl;
			print_board(board);
			cout << endl;
			/* Testing */
			if(isReward(board)) board = updateBoard(board);
			inc++;
			// cout << inc << endl;
		}
		iter2goal[it] = inc;
		/* Testing */
		/*
		cout << "iterations: " << inc << endl;
		/* Testing */
	}	
	/* Calculate average */
	for(int it=0; it < ITER; it++) average += iter2goal[it];
	average = (int)((float)average / ITER);
	/* Testing */
	/*
	cout << endl;
	cout << "average: " << average << endl;
	/* Testing */
	this->iter_prb = average+1;
	return;
}








