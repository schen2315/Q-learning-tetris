#include "algo_hashed.hpp"
#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <time.h>
#include <fstream>

using namespace std;
Model::Model(int num_states) {
	this->n = num_states;
	this->gamma = 0.8;
	this->ep = 100;
};
bool Model::hasReachedGoalState(string state) {
	//check if tetris has reached the top of the board
	//needs tetris simulator
	return false;
};
int Model::reward(string state, string nextState) {

	return 0;
};
void Model::train(string file) {
	srand(time(NULL));
	//ofstream out(file);
	vector<string> valid;
	for(int it=0; it < ep; it++) {
		cout << "Episode: " << it << endl;
		string currState = genRandState();
		while(!hasReachedGoalState(currState)) {
			string nextState = genRandState(currState);
			valid = genAllNextValidStates(nextState, valid);
			maxnext = 0;
			for(int i=0; i < valid.size(); i++) {
				if(Q.find(valid[i]) != Q.end()) {
					if(Q[valid[i]] > maxnext) maxnext = Q[valid][i];
				} else {
					Q[valid[i]] = 0;
				}
			}
			if(R.find(nextState) == R.end()) {
				if(isRewardState(valid[i]) > 0) {
					R[nextState] = isRewardState(nextState);
				} else R[nextState] = 0;
			}
			Q[nextState] = R[nextState] + (int)(gamma*maxnext);
			//Todo fix nextState to ONLY contain the BOARD, not both curr & next States
			//update maxQ[currState] = nextState if nextState > maxQ[currState]
		}
	}
	//out.close();
};
string Model::getNextState(string currState) {
	if(maxQ.find(currState) != maxQ.end()) {
		return maxQ[currState];
	} else {
		//return a random valid next state
		//this case occurs if we've never seen currState before 
		return "";
	}
};
string Model::genRandState(string s) {
	//needs tetris simulator
	//provide a next random valid state given the current state or
	//just a random valid state given ""
	if(!isValidState(s)) 
		throw new invalid_argument("the parameter does not represent a valid state");	
	//generate a random state given this state
	//needs my tetris simulator
	return "";
};
string Model::genRandState() {
	//needs tetris simulator
	return "";
}
vector<string>& Model::genAllNextValidStates(string state, vector<string>& v) {
	//these values should consist of the concatenation of the given state with
	//the each possible next state strings
	return v;
}
bool Model::isValidState(string s) {
	if(s.length() != n)
		throw new invalid_argument("the parameter\'s length does not match # of characters in string representation of a state");
	//need tetris simulator to check
	return true;
}
int Model::isRewardState(string s) {
	return 0;
}