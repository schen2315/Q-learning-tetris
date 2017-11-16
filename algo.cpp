#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <time.h>
#include <fstream>
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
Model::Model(string file) {
	int numGoals = 0;
	vector<LL> goalStates;
	ifstream in(file);
	in >> n;
	R = new int* [n];
	Q = new int* [n];
	maxQ = new int[n];
	for(int i=0; i < n; i++) {
		R[i] = new int[n];
		Q[i] = new int[n];
	}
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++) {
			in >> R[i][j];
			Q[i][j] = 0;
		}
	}
	in >> numGoals;
	LL temp;
	for(int i=0; i < numGoals; i++) {
		in >> temp;
		goalStates.push_back(temp);
	}
	initGoals(goalStates);
	gamma = 0.8;
	ep = 100;
	in.close();
	cout << "# of states: " << n << endl;
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++) cout << R[i][j] << " ";
		cout << endl;
	}
	set<LL>::iterator it;
	for(it = goals.begin(); it != goals.end(); ++it) cout << *it << endl;
}
void Model::initR(LL s1, LL s2, int val) {
	R[s1][s2] = val;
}
void Model::initGoals(vector<LL> states) {
	for(int i=0; i < states.size(); i++) {
		goals.insert(states[i]);
	}
}
LL Model::genRandState() {
	//the user provides the genRandState function because
	//the algorithm cannot know if a state is valid or not
	//assume already seede
	LL retVal = rand() % n;
	return retVal;
}
vector<LL> Model::getAllNextValidStates(LL state) {
	//the user provides a function that returns all next valid states
	//to a given state
	//I decided to implement q-learning this way
	//the state space of tetris is a very sparse graph
	//so the probability that one state can go to another state is very small
	vector<LL> retVal;
	for(LL x=0; x < n; x++) {
		if(R[state][x] != -1) {
			retVal.push_back(x);
		}
	}
	return retVal;
};
void Model::train() {
	if(goals.empty()) {
		cout << "Error: Must initialize goal states before training" << endl;
	}
	srand(time(NULL));
	vector<LL> valid;
	for(int it=0; it < ep; it++) {
		cout << "Episode: " << it << endl;
		LL currState = genRandState();
		int j = 0;
		while(goals.find(currState) == goals.end()) {	//check if the currState is a goal state
			valid = getAllNextValidStates(currState);
			//cout << rand()/(float)RAND_MAX << endl;
			//cout << valid.size() << endl;
			LL nextState = valid[(LL)((rand()/(float)RAND_MAX)*valid.size())];	//generate a randome valid next state
			int max_next = Q[nextState][0];
			for(int i=1; i < n; i++) {
				if(Q[nextState][i] > max_next) max_next = Q[nextState][i];
			}
			Q[currState][nextState] = R[currState][nextState] + (int)(gamma*max_next);
			currState = nextState;
			cout << "current state: " << currState << endl;
			j++;
		}
		j = 0;
	}
	for(int i=0; i < n; i++) {
		int curr_max = Q[i][0];
		for(int j=1; j < n; j++) {
			if(Q[i][j] > curr_max) curr_max = Q[i][j];
		}
		maxQ[i] = curr_max;
	}
	printQ();
}
void Model::printQ() {
	for(int i=0; i < n; i++) {
		for(int j=0; j < n; j++) {
			cout << Q[i][j] << " ";
		}
		cout << endl;
	}
}
LL Model::getNextState(LL currState) {
	return maxQ[currState];
}




