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
    bool gameOver = false;

    cout << "-*-*-*- Tic Tac Toe -*-*-*-\n";

    // Show initial board
    displayBoard(board);

    // Main game loop
    while (!gameOver) {
        int row, col;
        // Get input
        cout << "Player " << currentPlayer << ", enter your move (row and column: 1-3): ";
        cin >> row >> col;
        row--; col--; // Adjust for 0 indexing

        // Ensure input is within 3x3 cell
        if (!makeMove(board, row, col, currentPlayer)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        // Update board
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true; // end game
        } else if (isDraw(board)){
            cout << "It's a draw!\n";
            gameOver = true; // end game
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch players
        }
    }
    return 0;
}
