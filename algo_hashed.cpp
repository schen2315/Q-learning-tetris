#include "algo_hashed.hpp"
#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;
double getTimeElapsed(high_resolution_clock::time_point t1, high_resolution_clock::time_point t2);
Model::Model(int n, int m, int k, string file) {
	this->bbits = n*m;
	this->pbits = k*k;
	this->gamma = 0.90;
	this->ep = 10;
	vector<string> pieces;
	ifstream in(file);
	string temp;
	while(true) {
		in >> temp;
		/*
		cout << "piece: " << temp << endl;
		*/
		pieces.push_back(temp);
		if(in.eof()) break;
	}
	in.close();
	this->tetris = new Tetris(n, m, k, pieces);
};
void Model::train(string file) {
	//Eventually want to log the current maxQ's

	//currState should be a board+piece
	//nextState should also be a board+piece
	//valid should be a vector of board+piece
	int maxNext;
	srand(time(NULL));
	ofstream out(file);
	vector<string> valid;
	long long int explored = 0;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	/* Measurements */
	out << "ep time memory edges" << endl;
	/* Measurements */
	for(int it=0; it < ep; it++) {
		
		// cout << "Episode: " << it << endl;
		string currState = genRandState();
		// cout << "currState generated: " << endl; //<< currState << endl;
		/* Testing */
		/*
		tetris->print_piece(currState.substr(this->bbits, this->pbits), 0);
		cout << endl;
		tetris->print_board(currState.substr(0, this->bbits));
		cout << endl;
		/* Testing */
		while(!hasReachedGoalState(currState)) {
			/* Testing */
			/*
			cout << "Press Enter to Continue" << endl;
			cin.ignore();
			/* Testing */
			string nextState = genNextRandState(currState);		
			valid = genAllNextValidStates(nextState, valid);
			maxNext = 0;
			for(int i=0; i < valid.size(); i++) {		//get the maximum Q value for the nextState
				if(Q.find(nextState+valid[i]) != Q.end()) {
					if(Q[nextState+valid[i]] > maxNext) maxNext = Q[nextState+valid[i]];
				} else {
					Q[nextState+valid[i]] = 0;
					/* Measurements */
					explored++;
					/* Measurements */
				}
			}
			if(R.find(currState+nextState) == R.end()) {	//do we have a reward value currently saved?
				R[currState+nextState] = isRewardState(currState+nextState);
			}
			if(Q.find(currState+nextState) == Q.end()) explored++;
			Q[currState+nextState] = R[currState+nextState] + (int)(gamma*maxNext);
			//Todo fix nextState to ONLY contain the BOARD, not both curr & next States
			//update Q if a goal state has been reached
			updateMaxQ(currState, nextState);
			//need to update the board first if a row has been completed
			currState = updateState(nextState);
			/* Testing */
			/*
			tetris->print_piece(currState.substr(this->bbits, this->pbits), 0);
			cout << endl;
			tetris->print_board(currState.substr(0, this->bbits));
			cout << endl;
			/* Testing */
		}
		/* Measurements */
		t2 = high_resolution_clock::now();
		out << it << " " << getTimeElapsed(t1, t2) << " " << "memory_used_so_far" << " " << explored << endl;
		/* Measurements */
	}
	out.close();
};
string Model::getNextState(string currState) {
	//input is a board+piece
	if(!isValidState(currState))
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");
	if(maxQ.find(currState) != maxQ.end())
		//output board
		cout << "MaxQ: hit! " << endl;
		return maxQ[currState].substr(0, this->bbits);
	string b = currState.substr(0, this->bbits);
	string p = currState.substr(this->bbits, this->pbits);
	//return a random valid next state
	//this case occurs if we've never seen currState before 
	return tetris->genNextRandBoard(b, p);
}
string Model::genNextRandState(string s) {
	//input board+piece
	if(!isValidState(s)) 
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");
	string b = s.substr(0, this->bbits);
	string p = s.substr(this->bbits, this->pbits);
	string retVal = tetris->genNextRandBoard(b, p) + tetris->genRandPiece();
	/* Testing */
	/*
	cout << "Model::genNextRandState: " << endl;
	cout << "Current: " << endl;
	tetris->print_board(b);
	cout << "Next: " << endl;
	tetris->print_board(retVal.substr(0, this->bbits));
	cout << endl;
	/* Testing */
	//return a board+piece
	return retVal;
}
string Model::genRandState() {
	//output board + piece
	string b = tetris->genRandBoard();
	string p = tetris->genRandPiece();
	string retVal = b+p;
	/* Testing */
	/*
	cout << "Model::genRandState: " << endl;
	tetris->print_board(retVal.substr(0, this->bbits));
	cout << endl;
	/* Testing */
	return retVal;
}
bool Model::hasReachedGoalState(string s) {
	//input board+piece
	if(!isValidState(s))
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");
	//check if tetris has reached the top of the board
	//needs tetris simulator
	string b = s.substr(0, this->bbits);
	bool retVal = tetris->isGoal(b);
	/* Testing */
	/*
	cout << "Model::hasReachedGoalState: " << endl;
	cout << "Goal Reached: " << (retVal ? "yes" : "no") << endl;
	cout << endl;
	/* Testing */
	return retVal;
	//output true or false
};
vector<string>& Model::genAllNextValidStates(string s, vector<string>& v) {
	//takes a board+piece and a vector of strings, each string being a next possible board+piece
	if(!isValidState(s)) 
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");
	v.clear();		//clear the vector first just in case
	vector<string> nextBoards;
	string b = s.substr(0, this->bbits);
	string p = s.substr(this->bbits, this->pbits);
	nextBoards = tetris->genAllNextValidBoards(b, p, nextBoards);
	for(int i=0; i < nextBoards.size(); i++) {
		for(int j=0; j < tetris->pieces.size(); j++) {
			v.push_back(nextBoards[i] + tetris->pieces[j]);
		}
	}
	/* Testing */
	/*
	cout << "Model::genAllNextValidStates: " << endl;
	for(int i=0; i < v.size(); i++) {
		cout << "board: " << endl;
		tetris->print_board(v[i].substr(0, this->bbits));
		cout << "piece: " << endl;
		tetris->print_piece(v[i].substr(this->bbits, this->pbits), 0);
	}
	/* Testing */
	//when the algo_hashed recieves all of these next valid boards
	//it will append the pieces of all_config 
	//to actually generate all next valid States

	return v;
	//outputs the vector of strings, each string being a board+piece
}
bool Model::isValidState(string s) {
	//is string s a valid board+piece?
	bool retVal = true;
	/*
	cout << "bbits: " << bbits << " pbits: " << pbits << endl;
	*/
	if(s.length() != bbits+pbits)
		retVal = false;
	/* Testing */
	/*
	cout << "Model::isValidState: "<< s << " length: " << s.length() << endl;
	cout << "isValidState: " << (retVal ? "yes" : "no") << endl;
	cout << endl;
	/* Testing */
	return retVal;
}
int Model::isRewardState(string s) {
	//input should be board+piece+board+piece
	if(s.length() != bbits+pbits+bbits+pbits)
		throw new invalid_argument("the parameter does not represent a valid state (board+piece+board+piece)");
	string b1, p1, b2, p2;
	b1 = s.substr(0, bbits);
	p1 = s.substr(bbits, pbits);
	b2 = s.substr(bbits+pbits, bbits);
	p2 = s.substr(bbits+pbits+bbits, pbits);
	int retVal = tetris->isReward(b2);
	/* Testing */
	/*
	cout << "Model::isRewardState: " << endl;
	cout << "reward: " << retVal << endl;
	cout << endl;
	/* Testing */
	return retVal;
	//output reward value
	//return a value greater than zero if we have a reward, o.w. zero
}
string Model::updateState(string s) {
	//input is board+piece
	if(!isValidState(s))
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");
	string b, p, retVal;
	b = s.substr(0, bbits);
	p = s.substr(bbits, pbits);
	retVal = tetris->updateBoard(b) + p;
	/* Testing */
	/*
	cout << "Model::updateState: " << endl;
	tetris->print_board(retVal.substr(0, this->bbits));
	cout << endl;
	/* Testing */
	//for sample, no update required
	return retVal;
	//output board+piece
}
void Model::updateMaxQ(string currState, string nextState) {
	//input should be board+piece
	//and another board+piece
	if(maxQ.find(currState) == maxQ.end()) {
		maxQ[currState] = nextState;
	}
	if(maxQ.find(currState) == maxQ.end()) throw invalid_argument("No current maxQ entry set for currState");
	if(Q.find(currState+maxQ[currState]) == Q.end()) {
		throw invalid_argument("Q[currState+nextState] has not been set yet");
		//Q[currState+maxQ[currState]] = 0;
	}
	if(Q[currState+maxQ[currState]] < Q[currState+nextState]) {
		maxQ[currState] = nextState;
		//cout << currState << " " << nextState << ": " << Q[currState+nextState] << endl;
	}
}
double getTimeElapsed(high_resolution_clock::time_point t1, high_resolution_clock::time_point t2) {
	double dif = duration_cast<std::chrono::milliseconds>(t2-t1).count();
	return dif;
}