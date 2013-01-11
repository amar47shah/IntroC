/* Amar Shah
 * 
 * Introduction to Programming Languages, CECS 130-50
 * Lab Assignment #10
 * 13 July 2012
 * 
 * A C++ program that allows the user to play 3D Tic-Tac-Toe against the computer. 
 * The program uses Object-Oriented Design.
 */
 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

/* CLASS: Square
 *     represents a square on a Tic-Tac-Toe board.
 *
 *     attributes (private)
 *         int iValue : can be -1, 0, or 1
 *
 *     constructor/deconstructor
 *         Square() : sets iValue to 0
 *         ~Square() : empty
 *
 *     methods (public)
 *         int iReadValue() const : returns iValue
 *         void setValue(int iNewValue) : changes iValue to iNewValue
 */
class Square {
public:
    // Square() constructor and iReadValue() method are in-line.
    Square() : iValue(0) {};
    ~Square() {};
    int iReadValue() const { return iValue; };
    void setValue(int iNewValue);

private:
    int iValue;
};

/* Square method: setValue() : changes iValue
 *     pre:  iValue == 0 (otherwise no change)
 *     post: iValue changed, takes on iNewValue
 */
void Square::setValue(int iNewValue) {
    if (iReadValue())
        return;
    else 
        iValue = iNewValue;
    return;
}

/* CLASS: Cube
 *    represents a 3D Tic-Tac-Toe Cube
 *
 *    attributes (private)
 *        Square Grid[3][3][3]
 *    
 *    methods (private)
 *        bool cubeFull() const
 *             returns TRUE if Cube is full, else FALSE 
 *        int iGameWon() const
 *             returns -1 if there is a 3-in-a-row of Squares containing -1s
 *             returns  1 if there is a 3-in-a-row of Squares containing  1s
 *             returns  0 if no 3-in-a-row
 *        char cInSquare(int iRow, int iCol, int iBoard) const  
 *             returns 'X' if Grid[iRow][iCol][iBoard] contains -1 
 *             returns 'O' if Grid[iRow][iCol][iBoard] contains  1
 *             (cInSquare() is used by displayCube(), below.)
 * 
 *    constructor/deconstructor
 *        Cube() {} : empty
 *        ~Cube() {} : empty    
 *                                                    
 *    methods (public)
 *        void displayCube() const
 *             displays the cube in standard output
 *        int iGameOutcome() const
 *            returns 0 if game not finished
 *            returns 1 if 'X's win
 *            returns 2 if 'O's win
 *            returns 3 if a draw
 *        bool playSquare(int iNum, int iPlayerNum) 
 *            attempts to claim a Square for a Player and
 *                returns TRUE if successful
 *                returns FALSE if the Square was already occupied
 */

class Cube {
public:
    Cube() {};
    ~Cube() {};
    void displayCube() const;
    int iGameOutcome() const;
    bool playSquare(int iNum, int iPlayerNum);

private:
    Square Grid[3][3][3];
    bool cubeFull() const;
    int iGameWon() const;
    char cInSquare(int iRow, int iCol, int iBoard) const;	
};

// Cube method: displayCube() prints the cube, using cInSquare
void Cube::displayCube() const {
    int i, j;
    cout << endl;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cout << "   " << cInSquare(i, j, 0) << "\t";
            if (j < 2)
                cout << "|";
        }	
        if (i < 2) {
            cout << endl;
			cout << "------------------------" << endl;
		}
    }
    cout << endl;
    for (i = 0; i < 3; i++) {
		cout << "\t\t\t";
        for (j = 0; j < 3; j++) {
            cout << "   " << cInSquare(i, j, 1) << "\t";
            if (j < 2)
                cout << "|";
        }	
        if (i < 2) {
            cout << endl << "\t\t\t";
			cout << "------------------------" << endl;
		}
    }
    cout << endl;
    for (i = 0; i < 3; i++) {
	    cout << "\t\t\t\t\t\t";
        for (j = 0; j < 3; j++) {
            cout << "   " << cInSquare(i, j, 2) << "\t";
            if (j < 2)
                cout << "|";
        }	
        if (i < 2) {
            cout << endl << "\t\t\t\t\t\t";
			cout <<"------------------------" << endl;
		}
    }
    cout << endl << endl; 
}

/* Cube method:iGameOutcome() const : checks whether the game has finished.
 *     if not, returns 0
 *     if so,  returns player number (1 or 2) of winning player
 *         or  returns 3 if a draw
 */
int Cube::iGameOutcome() const {
    if (iGameWon() == -1) 
        return 1;
    else if (iGameWon() == 1)
        return 2;
    else if (cubeFull())
        return 3;
    else
        return 0;
}

/* Cube method:playSquare(int iNum, int iPlayerNum) 
 *     iNum : square to be played
 *     iPlayerNum : player claiming square
 *     attempts to claim square for player
 *         returns TRUE if successful
 *         returns FALSE if unsuccessful
 */
bool Cube::playSquare(int iNum, int iPlayerNum) {
    int iBoard = iNum / 9;
    int iRow = (iNum % 9) / 3;
    int iCol = iNum % 3;
    if (Grid[iRow][iCol][iBoard].iReadValue())
        return false;
    else {
        /* setValue(-1) if iPlayerNum = 1 and
         * setValue( 1) if iPlayerNum = 2
         */
        Grid[iRow][iCol][iBoard].setValue(pow((-1), iPlayerNum));
        displayCube();
        return true;
    }
} 


// Cube method: cubeFull() const : checks if board is full.
bool Cube::cubeFull() const {
    // A counter variable, ctr, is initialized to 0.
    int i, j, k, ctr = 0;
    /* For each square of the board with a nonzero 
     * value, ctr is incremented.
     */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            for (k = 0; k < 3; k++)
                if (Grid[i][j][k].iReadValue()) 
                     ctr++;
    // If ctr reaches its maximum value, 27, then a true value is returned.
    if (ctr == 27)
        return true;
    else
        return false;
}

// Cube method:iGameWon() const : checks for 3-in-a-row in the cube.
int Cube::iGameWon() const {
    int i, j, k, ctr;
    // Cycling through each board: k = 0, 1, 2...
    for (k = 0; k < 3; k++) {
        // Checking horizontal rows on each board.
        for (i = 0; i < 3; i++) {
            ctr = 0;
            for (j = 0; j < 3; j++) 
                ctr += Grid[i][j][k].iReadValue();
            if (abs(ctr) == 3)
                return abs(ctr) / ctr;
        }
        // Checking vertical columns on each board.
        for (j = 0; j < 3; j++) {
            ctr = 0;
            for (i = 0; i < 3; i++)
                ctr += Grid[i][j][k].iReadValue();
            if (abs(ctr) == 3)
                return abs(ctr) / ctr;
        }
        // Checking the major diagonal on each board.
        ctr = 0;
        for (i = 0; i < 3; i++) {
            j = i;
            ctr += Grid[i][j][k].iReadValue();
        }
        if (abs(ctr) == 3)
            return abs(ctr) / ctr;
        // Checking the minor diagonal on each board.
        ctr = 0;
        for (i = 0; i < 3; i++) {
            j = 2 - i;
            ctr += Grid[i][j][k].iReadValue();
        }
        if (abs(ctr) == 3)
            return abs(ctr) / ctr;
    }
    // Checking the straights that go down through all three boards.
    // Cycling through rows: i = 0, 1, 2...
    for (i = 0; i < 3; i++) {
        // Cycling through columns j = 0, 1, 2...
        for (j = 0; j < 3; j++) {
            // Totaling down across boards.
            ctr = 0;
            for (k = 0; k < 3; k++)
                ctr += Grid[i][j][k].iReadValue();
            if (abs(ctr) == 3)
                return abs(ctr) / ctr;
        }
        // Checking the major j-k diagonal in each row-slice (i held constant)
        ctr = 0;
        for (j = 0; j < 3; j++) {
            k = j;
            ctr += Grid[i][j][k].iReadValue();
        }
        if (abs(ctr) == 3)
            return abs(ctr) / ctr;
        // Checking the minor j-k diagonal in each row-slice (i held constant)
        ctr = 0;
        for (j = 0; j < 3; j++) {
            k = 2 - j;
            ctr += Grid[i][j][k].iReadValue();
        }
        if (abs(ctr) == 3)
            return abs(ctr) / ctr;
    }
    // Checking each column-slice : cycling through j = 0, 1, 2
    for (j = 0; j < 3; j++) {
        // Checking the major i-k diagonal in the column-slice (j constant).
        ctr = 0;
        for (i = 0; i < 3; i++) {
            k = i;
            ctr += Grid[i][j][k].iReadValue();
        }
        if (abs(ctr) == 3)
            return abs(ctr) / ctr; 
        // Checking the minor i-k diagonal in the column-slice.
        ctr = 0;
        for (i = 0; i < 3; i++) {
            k = 2 - i;
            ctr += Grid[i][j][k].iReadValue();
        }
        if (abs(ctr) == 3)
            return abs(ctr) / ctr;
    }
    // Four cross-cube diagonals (none of {i, j, k} constant).
    // Diagonal 1.
    ctr = 0;
    for (i = 0; i < 3; i++) {
        j = i;
        k = i;
        ctr += Grid[i][j][k].iReadValue();
    }
    if (abs(ctr) == 3)
        return abs(ctr) / ctr;
    // Diagonal 2.
    ctr = 0;
    for (i = 0; i < 3; i++) {
        j = 2 - i;
        k = i;
        ctr += Grid[i][j][k].iReadValue();
    }
    if (abs(ctr) == 3)
        return abs(ctr) / ctr;    
    // Diagonal 3
    ctr = 0;
    for (i = 0; i < 3; i++) {
        j = i;
        k = 2 - i;
        ctr += Grid[i][j][k].iReadValue();
    }
    if (abs(ctr) == 3)
        return abs(ctr) / ctr;    
    // Diagonal 4.
    ctr = 0;
    for (i = 0; i < 3; i++) {
        j = 2 - i;
        k = 2 - i;
        ctr += Grid[i][j][k].iReadValue();
    }
    if (abs(ctr) == 3)
        return abs(ctr) / ctr;
    // If no straight was found, return 0.
    return 0;
}

/* Cube method: cInSquare(int iRow, int iCol, int iBoard) const
 *     returns 'X' or 'O' according to the value of the Square at Grid[iRow][iCol][iBoard]
 */
char Cube::cInSquare(int iRow, int iCol, int iBoard) const {
    switch (Grid[iRow][iCol][iBoard].iReadValue()) {
        case -1:
            return 'X';
        case 1:
            return 'O';
        default:
            return ' ';
    }
}

/* CLASS: Player
 *     represents a game player, human or computer
 * 
 *     attributes (private)
 *         bool playerIsComputer
 *         int iPlayerNumber : can be 1 or 2
 * 
 *     constructors/deconstructor
 *         Player() : sets the computer Player
 *             randomizes to time seed
 *             gives the computer a random Player number
 *         Player(int iAgainstComputer) : sets the human Player
 *         ~Player() : empty
 * 
 *     methods (public)
 *         int iGetPlayerNumber() const : returns iPlayerNumber
 *         int iChooseSquare() const : gets the Player's choice of next square to play
 *             for computer Player: chooses randomly
 *             for human Player: prompts input
 */
class Player {
public:
    Player();
    Player(int iAgainstComputer);
    ~Player() {};
    int iGetPlayerNumber() const { return iPlayerNumber; };
    int iChooseSquare() const;

private:
    bool playerIsComputer;
    int iPlayerNumber;	
};

//  Default Constructor.  Used to create a player if none exists (computer player).
Player::Player() {
    playerIsComputer = true;
    srand(time(0));
    iPlayerNumber = rand() % 2 + 1;
}

//  Constructor.  Used to create opponent against computer.
Player::Player(int iAgainstComputer) {
    playerIsComputer = false;
    iPlayerNumber = iAgainstComputer % 2 + 1;
}

// Player method: iChooseSquare() const
int Player::iChooseSquare() const {
    int iSquareNum;
    if (playerIsComputer) 
        iSquareNum = rand() % 27;
    else {
        int iRow = 0, iCol = 0, iBoard = 0;
        cout << "Which square will you play?" << endl;
        while (iBoard < 1 || iBoard > 3) {
            cout << "Board (1-3): ";
            cin >> iBoard;
        }
        while (iRow < 1 || iRow > 3) {
            cout << "Row (1-3): ";
            cin >> iRow;
        }
        while (iCol < 1 || iCol > 3) {
            cout << "Column (1-3): ";
            cin >> iCol;
        }
        iSquareNum = (iBoard - 1) * 9 + (iRow - 1) * 3 + (iCol - 1);
    }
    return iSquareNum;
}

// Function protocol.
bool sayYes();

// The main program.
int main()
{
    bool playAgain = true;
    do {
        // Players are constructed: A Computer Player and a User Player.
        Player Computer;
        Player User(Computer.iGetPlayerNumber());
        // A 3D playing field is also constructed.
        Cube GameCube;

        cout << endl << "Let's play 3D Tic-Tac-Toe." << endl;

        // If the computer is Player 1, then the computer plays first.
        if (Computer.iGetPlayerNumber() == 1) {
            cout << endl << "I'll start." << endl;
            /* Choose a move for the computer and play it.
             * No moves have been made, so all moves are legal.
             */
            GameCube.playSquare(Computer.iChooseSquare(), Computer.iGetPlayerNumber());
            cout << "There's my move." << endl << endl;
        }
        // If the computer is Player 2, then the empty board is displayed.
        else {
            GameCube.displayCube();
            cout << "You go first." << endl << endl;
        }

        // Repeat following loop until GameCube.iGameOutcome() returns nonzero <=> end of game.
        do {
            // The user must choose a legal move.
            while (!GameCube.playSquare(User.iChooseSquare(), User.iGetPlayerNumber()))
                cout << "That square is already occupied." << endl << endl;
			// If the game has not ended, the computer follows suit.
            if (GameCube.iGameOutcome() == 0) {
                cout << "I'll play this square:" << endl;
				// Repeat computer's choice until a legal move is chosen.
                while (!GameCube.playSquare(Computer.iChooseSquare(), Computer.iGetPlayerNumber())) {}
            }
        } while (GameCube.iGameOutcome() == 0);
    
        // The final outcome of the game is given by GameBoard.iGameOutcome().
        int iFinalOutcome = GameCube.iGameOutcome();
        // The user is notified of the final outcome.
        if (iFinalOutcome == 3) 
            cout << "Looks like a draw!";
        else {
            cout << "Player " << iFinalOutcome << " won!" << endl;
            if (iFinalOutcome == Computer.iGetPlayerNumber()) 
                cout << "That's me!" << endl << endl << "Good game. :)";
            else if (iFinalOutcome == User.iGetPlayerNumber()) 
                cout << "That's you!" << endl << endl << "Congrats! ;)";
        }
        cout << endl << endl;

        cout << "Would you like to play again? (Y/N) ";
        playAgain = sayYes();
    } while (playAgain);
	cout << "Goodbye!" << endl << endl;
    return 0;
}   // End of main method.

bool sayYes() {
    char cInputString[15] = {'\0'};
    while (*cInputString != 'y' && *cInputString != 'Y' && *cInputString != 'n' && *cInputString != 'N')
        cin >> cInputString;
    if (*cInputString == 'y' || *cInputString == 'Y')
        return true;
    else
        return false;
}