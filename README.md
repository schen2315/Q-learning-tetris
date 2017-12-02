## Todos:
* check if my current implementation works as expected on a very small case
* experiment with using a hashmap -> string 2 states together to get their Q, R values?
* get generating random state + all next valid states given a particular state
* handling the situation where a state is reached that has not been explored yet?
	-> what is the probability that a given state has not been explored given the total # of states & the # of episodes?
* What happens if we reach a state we've never encountered before and thus don't know how to handle? What about doing a bfs from that state to find a next state that we have encountered before. BFS vs DFS in this situation? We want to get to a state we've seen before as fast as possible.
* What about learning patterns and relating these patterns to states never seen before?
	Any general pattern matching algorithms that can be used?
* Todo fix nextState to ONLY contain the BOARD, not both curr & next States
* Can we use the solution for a 4x4 board to play nx5, nx6, nx7, etc. boards?