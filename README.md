## How to Run:
```
$ make
$ python parameters.py > <your-parameters.txt>
$ chmod +x all_training_testing.sh
$ ./all_training_testing.sh parameters.txt <your-log-file.txt>
```
To play the Tetris 4x4:
```
$ cd Tetris_Player
```
A results directory will be made with each instance of the experiment represented as a random string of characters followed by -log.txt, -maxQ.txt, -performance.txt, and -training.txt. Included in these files are collected data in csv format.
## Implementation:

There are 3 main components to this project written in C++:
* Q-Learning
* Program that computes Tetris boards
* Tetris 4x4 game player

### Q-Learning:
This program is simple and generally follows the pseudocode presented from here: [http://mnemstudio.org/path-finding-q-learning-tutorial.htm](http://mnemstudio.org/path-finding-q-learning-tutorial.htm). The most interesting portion is that the Q and R tables as well as the final actions that AI learns are stored in hashtables. The hashtable input is of the form:
`Q[currentState+nextState] = value`.  
API:  
```
Model::Model(int ep, float gamma, int n, int m, int k, string file)
```
Constructor. Takes as parameters # of episodes, gamma learning factor, height (height of board + height of piece), width of board, width/height of piece, file containing line seperated binary representation of each piece.
```
void Model::train(string log_info, string train_info, string maxQ_table)
```
Trains the AI. outputs log info, data relating to training and the maxQ table (final actions learned by AI).
```
string Model::getNextState(string currState, int & hit)
```
Only call after training the AI. Will get the next state given the current state. Pass a counter to keep track of the hit/miss rate.