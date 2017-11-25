#include <set>
#include <vector>
#define LL long long int

using namespace std;
class Model {
	private:
		int n;	/* n = number of states */
		int **R;
		int **Q;
		int *maxQ;
		set<LL> goals;

		vector<LL> getAllNextValidStates(LL state); //user provides method for generating a *valid action
	public:
		float gamma;
		int ep;			/*
							ep = total number of episodes
							goal = goal state
						*/
		Model(int num_states);
		Model(string file);
		
		void initR(LL s1, LL s2, int val);
		void initGoals(vector<LL> states);
		void train();
		void printQ();
		LL getNextState(LL currState);	
		LL genRandState();		//user provides a method for generating a *valid state
};