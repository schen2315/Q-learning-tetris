#include "algo_hashed.hpp"
#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <time.h>
#include <fstream>

using namespace std;
Model::Model(int bbits, int pbits) {
	this->bbits = bbits;
	this->pbits = pbits;
	this->gamma = 0.8;
	this->ep = 100;
};
Model::Model(string file) {

	this->bbits = 1;
	this->pbits = 0;
	this->gamma = 0.8;
	this->ep = 100;
	int n, k;
	int temp;
	ifstream in(file);
	bbits = 1; pbits = 0;
	in >> n;
	this->n = n;
	actions = new int* [n];
	for(int i=0; i < n; i++) {
		actions[i] = new int[n];
	}
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++) {
			in >> actions[i][j];
		}
	}
	in >> k;
	for(int i=0; i < k; i++) {
		in >> temp;
		goals.insert(temp);
	}
}
void Model::train(string file) {
	//Eventually want to log the current maxQ's

	//currState should be a board+piece
	//nextState should also be a board+piece
	//valid should be a vector of board+piece
	int maxNext;
	srand(time(NULL));
	//ofstream out(file);
	vector<string> valid;
	for(int it=0; it < ep; it++) {
		cout << "Episode: " << it << endl;
		string currState = genRandState();
		cout << "currState generated: " << currState << endl;
		while(!hasReachedGoalState(currState)) {
			string nextState = genRandState(currState);		
			valid = genAllNextValidStates(nextState, valid);
			maxNext = 0;
			for(int i=0; i < valid.size(); i++) {		//get the maximum Q value for the nextState
				if(Q.find(nextState+valid[i]) != Q.end()) {
					if(Q[nextState+valid[i]] > maxNext) maxNext = Q[nextState+valid[i]];
				} else Q[nextState+valid[i]] = 0;
			}
			if(R.find(currState+nextState) == R.end()) {	//do we have a reward value currently saved?
				R[currState+nextState] = isRewardState(currState+nextState);
			}
			Q[currState+nextState] = R[currState+nextState] + (int)(gamma*maxNext);
			//need to update the board first if a row has been completed
			//Todo fix nextState to ONLY contain the BOARD, not both curr & next States
			//update maxQ[currState] = nextState if nextState > maxQ[currState]
			updateMaxQ(currState, nextState);
			currState = updateBoard(nextState);
			//update Q if a goal state has been reached
		}
	}
	//out.close();

	/*check sample implementation*/
	cout << "Q table:" << endl;
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++) {
			if(Q.find(to_string(i) + to_string(j)) != Q.end()) cout << Q[to_string(i) + to_string(j)] << " ";
			else cout << "0 ";
		}
		cout << endl;
	}
	cout << "Max Q table: " << endl;
	for(int i=0; i < n; i++) {
		cout << i << ": " << maxQ[to_string(i)] << ": " << Q[to_string(i)+maxQ[to_string(i)]] << endl;
	}
};
string Model::getNextState(string currState) {
	//input is a board+piece
	if(!isValidState(currState))
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");
	if(maxQ.find(currState) != maxQ.end())
		//output board
		return maxQ[currState];

	//return a random valid next state
	//this case occurs if we've never seen currState before 
	return "";
}
string Model::genRandState(string s) {
	//input board+piece
	if(!isValidState(s)) 
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");

	vector<string> v;
	v = genAllNextValidStates(s, v);
	string val = v[rand() % v.size()];
	//return a board+piece
	return val;
}
string Model::genRandState() {
	//output board + piece
	int val = rand() % n;
	return to_string(val);
}
bool Model::hasReachedGoalState(string state) {
	//input board+piece
	if(!isValidState(state))
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");
	//check if tetris has reached the top of the board
	//needs tetris simulator
	if(goals.find(stoi(state)) != goals.end()) return true;
	return false;
	//output true or false
};
vector<string>& Model::genAllNextValidStates(string state, vector<string>& v) {
	//takes a board+piece and a vector of strings, each string being a next possible board+piece
	if(!isValidState(state)) 
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");
	v.clear();		//clear the vector first just in case
	
	for(int x=0; x < n; x++) {
		if(actions[stoi(state)][x] != -1) {
			v.push_back(to_string(x));
		}
	}
	return v;
	//outputs the vector of strings, each string being a board+piece
}
bool Model::isValidState(string s) {
	//is string s a valid board+piece?
	if(s.length() != bbits+pbits)
		return false;
	return true;
}
int Model::isRewardState(string s) {
	//input should be board+piece+board+piece
	if(s.length() != bbits+pbits+bbits+pbits)
		throw new invalid_argument("the parameter does not represent a valid state (board+piece+board+piece)");
	//should check to see if there is a completed row
	if(actions[s[0]-'0'][s[1]-'0'] > 0) return actions[s[0]-'0'][s[1]-'0'];
	return 0;
	//output reward value
	//return a value greater than zero if we have a reward, o.w. zero
}
string Model::updateBoard(string s) {
	//input is board+piece
	if(!isValidState(s))
		throw new invalid_argument("the parameter does not represent a valid state (board+piece)");

	//for sample, no update required
	return s;
	//output board+piece
}
void Model::updateMaxQ(string currState, string nextState) {
	//input should be board+piece
	//and another board+piece
	if(Q.find(currState+maxQ[currState]) == Q.end()) Q[currState+maxQ[currState]] = 0;
	if(Q[currState+maxQ[currState]] < Q[currState+nextState]) {
		maxQ[currState] = nextState;
		cout << currState << " " << nextState << ": " << Q[currState+nextState] << endl;
	}
	//update maxQ[currState] = nextState[board]
}
