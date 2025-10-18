#include <iostream>
using namespace std;

// 2D array represents a 3x3 grid for tic-tac-toe.
char board[3][3] = {
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
};

// Print board to players screen. 
void displayBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " \n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

// Clear board
void clearBoard(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        // Clear each row
        board[0][i] = ' ';
        board[1][i] = ' ';
        board[2][i] = ' ';
    }
}

// Validate input
int getValidInput(string prompt, int min, int max) {
    int number;
    cout << prompt;

    // Loop until valid input reached
    while (true) {
        if (cin >> number && number >= min && number <= max) {
            cin.ignore(10000, '\n'); 
            return number; 
        } else {
            cout << "Invalid input. Enter a number between " << min << " and " << max << ": ";
            cin.clear(); 
            cin.ignore(100000, '\n'); 
        }
    }
}

// Make move on board based on players input. 
bool makeMove(char board[3][3], int row, int col, char player) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = player;
        return true; // Move valid
    }
    return false; // Move invalid
}

// Check if win conditions have been met.
bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; ++i) {
        // Check rows.
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            // Check columns.
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true; 
    }
    // Check diagonals.
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true; 

    return false; 
}

// Checks for draws.
// Checks for any empty cells - if any are found then game is not finished.
// If all cells are full and no winning condition has been met - must be a draw.
bool isDraw(char board[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ') return false;
    return true;
}

// Ask user to play again
bool askPlayAgain() {
    string response;
    cout << "\nWould you like to play again (y/n)?";
    cin >> response;
    return (response == "y" || response == "Y");
}

// Display win count
void displayScore(int xWins, int oWins) {
    cout << "\nWin count:";
    cout << "\nPlayer X: " << xWins;
    cout << "\nPlayer O: " << oWins << "\n";
}

// Play a game / round
void playGame(int &xWins, int &oWins) {
    char board[3][3];
    clearBoard(board);

    char currentPlayer = 'X';
    bool gameOver = false;
    int xTurns = 0, oTurns = 0;

    cout << "-*-*-*- Tic Tac Toe -*-*-*-\n";
    displayBoard(board);

    while (!gameOver) {
        cout << "Player " << currentPlayer << "'s turn.\n";

        // Get valid input
        int row = getValidInput("Enter row (1-3): ", 1, 3) - 1;
        int col = getValidInput("Enter column (1-3): ", 1, 3) - 1;

        // Ensure input is within 3x3 cell
        if (!makeMove(board, row, col, currentPlayer)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        displayBoard(board);
        if (currentPlayer == 'X') xTurns++; else oTurns++; // Increment turns

        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins in "
            << ((currentPlayer == 'X') ? xTurns : oTurns) << " turns!\n";
            if (currentPlayer == 'X') xWins++; else oWins++;
            gameOver = true; // end game
        } else if (isDraw(board)) {
            cout << "Its a draw!\n";
            gameOver = true; // end game
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch players
        }
    }
    displayScore(xWins, oWins); // display current win count
}

int main() {
    int xWins = 0, oWins = 0;
    bool playAgain = true;

    // Game loop
    while (playAgain) {
        playGame(xWins, oWins);
        playAgain = askPlayAgain();
    }

    cout << "\nFinal Scores:";
    displayScore(xWins, oWins); // final win count
    cout << "Quitting...\n";
    return 0;
}

