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
### Tetris Utility
Includes functions to compute the next board given a current board, generate random boards, get all next possible boards given a current board, functions to have the computer play a random tetris game. All of these functions take the binary representation of the tetris board. These functions are used by the Q-Learning algorithm to get next and random states (tetris board) given the current state.

### Tetris Player:

To run program:
	0) Download SDL 2.0 
	1) make
	2)./Tetris

Pieces: Class for defineing the different tetris pieces 
	Piece (int pieceType, int pieceRotation); // Constructor

	void rotatePiece(int pieceRotation = 1); 		// Rotates Piece array clockwise
	int getXInitialPosition (); 					// Since pieces do not are not the same this get the displacement from the middle of board where the piece spawns
	int getYInitialPosition (); 					// Like getXInitialPosition it deplaces the piece by each piece up and down 

	int mPiece [2][2];    							// Piece array for 2x2 pieces
	int pieceType;        							// Piece indicator (0 - 4)
	std::string getPieceString(); 					// Returns the string of the piece in a binary string
	int getType(); 									// Returns piece type
	
	
	int getLeftMostColumn();						// functions that find the leftmost column of a rotated piece
	int getRightMostColumn();						// functions that find the rightmost column of a rotated piece
	int getLeft();									// gets the number of coloums that contain a piece left from the middle column
	int getRight();									// gets the number of coloums that contain a piece right from the middle column
	
	void getPiece		(int pieceType); 	 		// Returns the piece with the piece type
	enum {ZERO, _I, _L, _Lm, _S}; 					//Piece names on every piece
	
Board: Class for the teris board that will handle tetris pieces
	Board(Piece *pPiece, int pScreenHeight);

    int getXPosInPixels         (int pPos);// Returns the column that where the piece will be placed on the board
    int getYPosInPixels         (int pPos);// Returns the row that where the piece will be placed on the board usually place 1 above the height limit
    bool isFreeBlock            (int pX, int pY); // Returns whether or not the piece at px,py on the board is filled 
    int getScore		();

    bool isPossibleMovement     (int pX, int pY); 	// Checks collisions with the board walls or other placed boards
    void storePiece             (int pX, int pY); 	// Denote the board at px,py to be a filled position
    void deletePossibleLines    ();				  	// Checks if a row or mulitple row on the board is entirely filled
    bool isGameOver             ();				  	// Checks if the board at row 0 + pieceSize is has a filled position. if it sees a place piece then game over
    void updateCurrentPiece     (Piece * piece);  	// Updates the playing piece to the next piece
    void clearBoard             ();				  	// Clear the board of all pieces
    int storedPieceType         (int x, int y);   	// Checks the piece type on the board on x,y cooridinate 
    std::string getBoardString	();					// Returns the board into a binary string where 1 is filled poition or 0 as a empty position
    void setBoard		(std::string input);		// Takes a Binary string to fill board 
    Piece* getPiece		();							// Gets the current playing piece

    enum { POS_FREE, POS_FILLED };          		// POS_FREE = free position of the board; POS_FILLED = filled position of the board
    int mBoard [BOARD_WIDTH][BOARD_HEIGHT]; 		// Defines the board with BOARD_WIDTH, BOARD_HEIGHT
    Piece* piece;									// A tetris piece
    int mScreenHeight;								// Height of board
    int mscore;										// Score
		
    void initBoard();								// Defines the creation of the board
    void deleteLine (int pY);						// Deletes the row py and moves all rows above it down
	
View: Using SDL 2.0 to define how to display the game window and other objects
	View                ();							//Construct the View

    void drawBlock      (int pX1, int pY1, int pX2, int pY2, enum color pC);	// SDL creates and fills a rectangle
    void clearScreen    ();														// Calls the function to clear the screen to black
    int getScreenHeight ();														// Returns the ScreenHeight
    int initGraph       ();														// Creates the window for the program SDL Render and textures
    void updateScreen   ();														// SDL function to update the render
    void cleanUp        ();														// Function when the user quits the game
    void loadBackGround ();														// SDL display a bmp image
    int messageBox      ();														// SDL message box 
	
Commands: Using SDL 2.0 to read the user input/keystokes for the program
	int pollkey    (SDL_Event *e);												// Uses SDL that repeated loops to until a key is pressed
    int isKeyDown  (int pKey);  												// Usings SDL to determine when the key board is pressed down
	
Game: Including all previous classes it defines game mechanics and calls to other class functions
Game    (  View *pView,
               Commands *pCommands,
               int pScreenHeight );

    void drawScene      ();														// calls to redraw the board after every tick or key press
    void createNewPiece ();														// Creates the next piece 
    bool restart        ();														// Handle response after a game over

    int posX, posY;														  		// Track posx and posy of the playing piece on the board
    int pieceType, rotation;													// Tracks Piece type and rotation

    Board *board;																// Init Board
    Piece *piece;																// Playing piece
    
    void aiMove(int rotations, int column);										// Randomly place piece of rotation rotation at column column
	
    int mScreenHeight;															// the board Screen Height
    int nextPosX, nextPosY;														// next piece starting x and y pos
    int nextPieceType, nextRotation;											// next piece piece type and starting rotation

    Piece *nextPiece;															// the next tetris piece object
    View *view;																	// window object
    Commands *commands;															// input objects

    int getRand     (int pA, int pB); 											// creates a random num with the parameters 
    void initGame   (); 														// Calls functions to start the game enviroment
    void drawPiece  (int pX, int pY/*, color pColor*/, Piece* piece); 			// draws the playing piece at every tick
    void drawBoard  (); 														// draws the limits of the board and every stored piece

Main: While the ESC keys is not pressed it loops the calling game commands on a timer.

				---------
				   Main
				---------
					|
			-----------------
				   Game
			-----------------
			/   	| 		\
	--------- 	---------	---------
	   View		  Board		 Commands
	---------	---------	---------
					|
				---------
				  Pieces
				---------

