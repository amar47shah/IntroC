/* Amar Shah
 * 
 * Introduction to Programming Languages, CECS 130-50
 * Lab Assignment #9
 * 6 July 2012
 * 
 * A C++ program that allows the user to play Tic-Tac-Toe
 * against the computer. The program uses Object-Oriented
 * Design.
 */
 
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

/* CLASS: SquareType
 *
 * The SquareType class contains the single integer 
 * attribute iValue and the two methods iReadValue()
 * and setValue().  The constructor SquareType()
 * merely sets the private attribute iValue to 0.
 *
 * An instance of the SquareType class represents an
 * actual square on the Tic-Tac-Toe board.
 */
class SquareType {
    int iValue;

public:
    /* iReadValue() merely returns the private attribute
     * iValue.
     */
    int iReadValue() const { return iValue; };
    void setValue(int iNewValue);

    SquareType() : iValue(0) {};
};

/* The method SquareType::setValue() checks whether 
 * iValue contains a nonzero value and if not, assigns
 * it the value of the formal argument iNewValue.
 */
void SquareType::setValue(int iNewValue) {
    if (iReadValue())
        return;
    else 
        iValue = iNewValue;
    return;
}

/* CLASS: BoardType
 *
 * The BoardType class contains a private 3x3 array 
 * of SquareType, called Grid, as well as private 
 * methods boardFull(), iGameWon(), and cInSquare().
 * BoardType contains public methods displayboard(), 
 * iGameOutCome(), and playSquare(). BoardType uses 
 * the default constructor and default destructor.
 * 
 * An instance of BoardType represents a Tic-Tac-Toe board.
 */
class BoardType {
    SquareType Grid[3][3];
    bool boardFull() const;
    int iGameWon() const;
    char cInSquare(int iRow, int iCol) const;	
	
public:
    void displayBoard() const;
    int iGameOutcome() const;
    bool playSquare(int iNum, int iPlayerNum);
};

/* BoardType::boardFull() returns a boolean value 
 * (true or false) corresponding to whether the 
 * Tic-Tac-Toe board has been completely filled 
 * through play.  
 */
bool BoardType::boardFull() const {
    // A counter variable, ctr, is initialized to 0.
    int i, j, ctr = 0;
    /* For each square of the board with a nonzero 
     * value, ctr is incremented.
     */
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (Grid[i][j].iReadValue()) 
                ctr++;
    /* If ctr reaches its maximum value, 9, then 
     * a true value is returned.
     */
    if (ctr == 9)
        return true;
    else
        return false;
}
/* BoardType::iGameWon returns 0 if the board shows 
 * no three-in-a-row straights, 1 if the board shows 
 * a three-in-a-row straight of 1s and -1 if the board 
 * shows a three-in-a-row straight of -1s.
 */
int BoardType::iGameWon() const {
    int i, j, ctr;
    // Checking horizontal rows.
    for (i = 0; i < 3; i++) {
        ctr = 0;
        for (j = 0; j < 3; j++) 
            ctr += Grid[i][j].iReadValue();
        if (abs(ctr) == 3)
            return abs(ctr) / ctr;
    }
    // Checking vertical columns.
    for (j = 0; j < 3; j++) {
        ctr = 0;
        for (i = 0; i < 3; i++)
            ctr += Grid[i][j].iReadValue();
        if (abs(ctr) == 3)
            return abs(ctr) / ctr;
    }
    // Checking the major diagonal.
    ctr = 0;
    for (i = 0; i < 3; i++)
        ctr += Grid[i][i].iReadValue();
    if (abs(ctr) == 3)
        return abs(ctr) / ctr;
    // Checking the minor diagonal.
    ctr = 0;
    for (i = 0; i < 3; i++)
        ctr += Grid[i][2 - i].iReadValue();
    if (abs(ctr) == 3)
        return abs(ctr) / ctr;
    // If no straight was found, return 0.
    return 0;
}

/* Method BoardType::cInSquare is used to decide what
 * character to print for each square when printing the
 * board.  cInSquare decodes the value -1 as 'X', the
 * value 1 as '0' and the value 0 as a space ' '.
 */
char BoardType::cInSquare(int iRow, int iCol) const {
    int iLocalValue = Grid[iRow][iCol].iReadValue();
    if (iLocalValue) {
        if (iLocalValue == -1) 
            return 'X';   
        else if (iLocalValue == 1)
            return 'O';
    }
    else
        return ' ';
}


/* BoardType::displayBoard() prints the board according to its
 * SquareType::iValue values and their BoardType::cInSquare()
 * decodings.
 */
void BoardType::displayBoard() const {
    int i, j;
    cout << endl;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cout << "   " << cInSquare(i, j) << "\t";
            if (j < 2)
                cout << "|";
        }	
        if (i < 2)
            cout << endl << "------------------------" << endl;
    }
    cout << endl << endl; 
}

/* BoardType::iGameOutcome() checks whether the game has finished.
 * If a player has won the game, iGameOutcome determines and
 * returns the player number of the winner. If no one has won,
 * iGameWon() checks whether the board is full and if so, returns
 * 3 to signify a draw. In other cases, iGameOutcome() returns 0.
 */
int BoardType::iGameOutcome() const {
    if (iGameWon() == -1) 
        return 1;
    else if (iGameWon() == 1)
        return 2;
    else if (boardFull())
        return 3;
    else
        return 0;
}

/* BoardType::playSquare() accepts formal arguments iNum
 * and iPlayNum. iNum represents the square to be played
 * on the board and iPlayNum represents the player who
 * has claimed that square. If the particular square
 * has already been played, playSquare() returns a false
 * value to indicate that the attempt to play the square
 * failed. Otherwise it sets the value of the square
 * displays the board, and returns true.
 */
bool BoardType::playSquare(int iNum, int iPlayerNum) {
    int iRow = iNum / 3;
    int iCol = iNum % 3;
    if (Grid[iRow][iCol].iReadValue())
        return false;
    else {
        /* setValue(-1) if iPlayerNum = 1 and
         * setValue( 1) if iPlayerNum = 2
         */
        Grid[iRow][iCol].setValue(pow((-1), iPlayerNum));
        displayBoard();
        return true;
    }
} 

/* CLASS: PlayerType
 *
 * The class PlayerType contains a private boolean 
 * attribute that indicates whether the player 
 * instance is or is not an automated computer player.
 * PlayerType also contains a public attribute
 * indicating the player number and a public method
 * iChooseSquare(). PlayerType uses two constructors.
 */
class PlayerType {
    bool playerIsComputer;
	
public:
    int iPlayerNumber;
    int iChooseSquare() const;

    PlayerType();
    PlayerType(int iAgainstComputer);
};

/* PlayerType::iChooseSquare() determines the player's
 * move choice. If the player is the computer, the
 * square is chosen randomly (note that the randomizer
 * has been seeded in the constructor).  If the player
 * is the user (not a computer) her choice is obtained
 * through a standard input prompt.
 */
int PlayerType::iChooseSquare() const {
    int iSquareNum;
    if (playerIsComputer) 
        iSquareNum = rand() % 9;
    else {
        int iRow = 0, iCol = 0;
        cout << "Which square will you play?" << endl;
        while (iRow < 1 || iRow > 3) {
            cout << "Row (1-3): ";
            cin >> iRow;
        }
        while (iCol < 1 || iCol > 3) {
            cout << "Column (1-3): ";
            cin >> iCol;
        }
        iSquareNum = (iRow - 1) * 3 + (iCol - 1);
    }
    return iSquareNum;
}

//  Default Constructor.  Used to create a player if none exists (computer player).
PlayerType::PlayerType() {
    playerIsComputer = true;
    srand(time(0));
    iPlayerNumber = rand() % 2 + 1;
}

//  Constructor.  Used to create opponent against computer.
PlayerType::PlayerType(int iAgainstComputer) {
    playerIsComputer = false;
    iPlayerNumber = iAgainstComputer % 2 + 1;
}

// The main program.
int main()
{
    // Players are constructed: A Computer player and a User player.
    PlayerType Computer;
    PlayerType User(Computer.iPlayerNumber);
    // A board is also constructed.
    BoardType Board;

    cout << "Let's play Tic-Tac-Toe." << endl;

    // If the computer is Player 1, then the computer plays first.
    if (Computer.iPlayerNumber == 1) {
        cout << endl << "I'll start." << endl;
        /* Choose a move until a legal move is found. (The while
         * loop is unnecessary here because no move has been made
         * and all randomly generated moves are legal.)
         */
        while (!Board.playSquare(Computer.iChooseSquare(), Computer.iPlayerNumber)) {}
        cout << "There's my move." << endl << endl;
    }
    // If the computer is Player 2, then the empty board is displayed.
    else {
        Board.displayBoard();
        cout << "You go first." << endl << endl;
    }
    /* The following loop repeats until Board.iGameOutcome() returns
     * a nonzero value, signifying the end of the game.
     */   
    do {
        // The user must choose a legal move.
        while (!Board.playSquare(User.iChooseSquare(), User.iPlayerNumber))
            cout << "That square is already occupied." << endl << endl;
        // If the game has not ended, the computer follows suit.
        if (Board.iGameOutcome() == 0) {
            cout << "I'll play this square:" << endl;
            while (!Board.playSquare(Computer.iChooseSquare(), Computer.iPlayerNumber)) {}
        }
    } while (Board.iGameOutcome() == 0);
    
    // The final outcome of the game is given by Board.iGameOutcome().
    int iFinalOutcome = Board.iGameOutcome();
    // The user is notified of the final outcome.
    if (iFinalOutcome == 3) 
        cout << "Looks like a draw!";
    else {
        cout << "Player " << iFinalOutcome << " won!" << endl;
        if (iFinalOutcome == Computer.iPlayerNumber) 
            cout << "That's me!" << endl << endl << "Good game. :)";
        else if (iFinalOutcome == User.iPlayerNumber) 
            cout << "That's you!" << endl << endl << "Congrats! ;)";
    }
    cout << endl << endl;
    // End of main method.
    return 0;
}
