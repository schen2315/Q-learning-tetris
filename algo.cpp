#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <time.h>
#include "algo.hpp"
#define LL long long int

using namespace std;
Model::Model(int num_states) {
	n = num_states;
	R = new int* [n];
	Q = new int* [n];
	maxQ = new int[n];
	for(int i=0; i < n; i++) {
		R[i] = new int[n];
		Q[i] = new int[n];
	}
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++) {
			R[i][j] = -1;
			Q[i][j] = 0;
		}
	}
	gamma = 0.8;
	ep = 100;
}
void Model::initR(LL s1, LL s2, int val) {
	R[s1][s2] = val;
}
void Model::initGoals(vector<LL> states) {
	for(int i=0; i < states.size(); i++) {
		goals.insert(states[i]);
	}
}
int Model::genRandState() {
	//the user provides the genRandState function because
	//the algorithm cannot know if a state is valid or not
	return 0;
}
vector<LL> Model::getAllNextValidStates(LL state) {
	//the user provides a function that returns all next valid states
	//to a given state
	vector<LL> retVal;
	return retVal;
};
void Model::train() {
	if(goals.empty()) {
		cout << "Error: Must initialize goal states before training" << endl;
	}
	srand(time(NULL));
	vector<LL> valid;
	for(int it=0; it < ep; it++) {
		LL currState = genRandState();
		while(goals.find(currState) == goals.end()) {
			valid = getAllNextValidStates(currState);
			LL nextState = (rand()/(float)RAND_MAX)*valid.size();
			int max_next = Q[nextState][0];
			for(int i=1; i < n; i++) {
				if(Q[nextState][i] > max_next) max_next = Q[nextState][i];
			}
			Q[currState][nextState] = R[currState][nextState] + (int)gamma*max_next;
			currState = nextState;
		}
	}
	for(int i=0; i < n; i++) {
		int curr_max = Q[i][0];
		for(int j=1; j < n; j++) {
			if(Q[i][j] > curr_max) curr_max = Q[i][j];
		}
		maxQ[i] = curr_max;
	}
}
LL Model::getNextState(LL currState) {
	return maxQ[currState];
}




