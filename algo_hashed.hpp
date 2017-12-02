#include <set>
#include <vector>
#include <string>
#include <unordered_map>
#define LL long long int

using namespace std;
class Model {
	private:	
		int bbits;		//number of bits representing the board
		int pbits;		//number of bits representing the piece

		/* sample # of states */
		int n;
		/* sample state graph to test hash implementation */
		int ** actions;
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
	public:
		float gamma;
		int ep;			/*
							ep = total number of episodes
							goal = goal state
						*/
		Model(int bbits, int pbits);
		Model(string file);
		bool hasReachedGoalState(string state);		//need tetris simulator
		void train(string file);		
		void setQ(string state);	//literally forgot what this was for ...
		//void printQ();
		string getNextState(string currState);	//use maxQ hashmap to generate a next state
		vector<string> & genAllNextValidStates(string currState, vector<string> &);
		string genRandState(string s);	//user provides a method for generating a valid state
										//requires tetris simulator
		string genRandState();
		bool isValidState(string s);
		int isRewardState(string s);
		void updateMaxQ(string currState, string nextState);
		string updateBoard(string s);
};