#ifndef TETRIS_HPP
#define TETRIS_HPP
#include "tetris.hpp"
#include <set>
#include <vector>
#include <string>
#include <unordered_map>
#include <time.h>
#define LL long long int

using namespace std;
class Model {
	private:	
		int bbits;		//number of bits representing the board
		int pbits;		//number of bits representing the piece
		int n;
		int m;
		int k;
		string pieceset;
		/* sample goals to test hash implementation */
		set<int> goals;

		//clarify whether each hashmap
		//takes the 2 or one state
		unordered_map<string, int> R;
			//should have the same makeup as Q
			//(board+piece)+(board+piece) -> points
		unordered_map<string, float> Q;
			//(board+piece)+(board+piece) -> Q value
				//BEFORE removing any completed rows
				//ensures we check for a reward first
		unordered_map<string, string> maxQ;
			//board + piece -> board

		vector<LL> getAllNextValidStates(LL state); //user provides method for generating a *valid action
		Tetris * tetris;
	public:
		float gamma;
		int ep;			/*
							ep = total number of episodes
							goal = goal state
						*/
		Model(int n, int m, int k, string file);
		Model(int ep, float gamma, int n, int m, int k, string file); 
			/* ep, learning-rate, board height (including ghost portion), board width, piece width, file containg pieceset */
		bool hasReachedGoalState(string state);		//need tetris simulator
		void train(string train_info);
		void train(string log_info, string train_info, string maxQ_table);		
		void setQ(string state);	//literally forgot what this was for ...
		//void printQ();
		string getNextState(string currState, int &hit);	//use maxQ hashmap to generate a next state
		vector<string> & genAllNextValidStates(string currState, vector<string> &);
		string genNextRandState(string s);	//user provides a method for generating a valid state
										//requires tetris simulator
		string genRandState();
		bool isValidState(string s);
		int isRewardState(string s);
		bool updateMaxQ(string currState, string nextState);
		string updateState(string s);
};
#endif