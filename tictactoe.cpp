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

int main() {
    char board[3][3] = { {' ',' ',' '},{' ',' ',' '},{' ',' ',' '}}; // Create board
    char currentPlayer = 'X';
    bool playAgain = true;
    string response;

    cout << "-*-*-*- Tic Tac Toe -*-*-*-\n";

    while (playAgain) {

        // Show board
        displayBoard(board);

        int row, col;
        // Get valid input
        cout << "Player " << currentPlayer << " its your turn!\n";
        row = getValidInput("Enter row (1-3): ", 1, 3) - 1;
        col = getValidInput("Enter column (1-3): ", 1, 3) - 1;
        


        // Ensure input is within 3x3 cell
        if (!makeMove(board, row, col, currentPlayer)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        if (checkWin(board, currentPlayer)) { // Player wins
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            cout << "Would you like to play again(y/n)?";
            cin >> response;
            if (response != "y" && response != "Y") {
                playAgain = false; // quit game
            } else {clearBoard(board);} // clear board if player wants to play again
        } else if (isDraw(board)){
            displayBoard(board);
            cout << "Its a draw!";
            cout << "Would you like to play again(y/n)?";
            cin >> response;
            if (response != "y" && response != "Y") {
                playAgain = false; // quit game
            } else { clearBoard(board);} // clear board if player wants to play again
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch players
        }
    }
    return 0;
}
