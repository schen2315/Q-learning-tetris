#include <set>
#include <vector>
#include <string>
#include <unordered_map>
#define LL long long int

using namespace std;
class Model {
	private:
		int n;	//number of characters in the string representation of a given state	
		//clarify whether each hashmap
		//takes the 2 or one state
		unordered_map<string, int> R;
			//should have the same makeup as Q
		unordered_map<string, float> Q;
			//requires the state of the board, curr piece, and next piece
			//concatenated to the state of the board for a given next state
				//BEFORE removing any completed rows
		unordered_map<string, string> maxQ;
			//requires the state of the board, curr piece, and next piece
		set<string> goals;

		vector<LL> getAllNextValidStates(LL state); //user provides method for generating a *valid action
	public:
		float gamma;
		int ep;			/*
							ep = total number of episodes
							goal = goal state
						*/
		Model(int num_states);
		//Model(string file);
		
		//void initGoals(vector<LL> states);
		bool hasReachedGoalState(string state);		//need tetris simulator
		int reward(string state, string nextState);	//also need tetris simulator
											//lazily evaluate if going
											//from one state to the next should be 
											//rewarded
		void train(string file);		
		void setQ(string state);	//literally forgot what this was for ...
		//void printQ();
		string getNextState(string currState);	//use maxQ hashmap to generate a next state
		vector<string> & genAllNextValidStates(string currState, vector<string> &);
		string genRandState(string s);		//user provides a method for generating a valid state
										//requires tetris simulator
		string genRandState();
		bool isValidState(string s);
		bool isRewardState(string s);
};