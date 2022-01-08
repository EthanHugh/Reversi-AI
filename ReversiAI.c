/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: Ethan Hugh
 *
 * Date: March 2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lab8part2lib.h"
#include "project_reversi_skeleton.h" // DO NOT modify this line

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
void copyBoard(const char firstBoard[26][26], char copy[26][26], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			copy[i][j] = firstBoard[i][j];
		}
	}
}

int scoreCount(const char board[26][26], int n, char colour) {
	double score = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == colour);
			score++;
		}
	}
	return score;
}

// ========= Function implementation ==========
/*
 * Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n) {
	printf("  ");
	for (int i = 0; i < n; i++) {
		printf("%c", 97 + i);
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%c ", 97 + i);
		for (int j = 0; j < n; j++) {
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
}


/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) {
	
	if (row > n - 1 || row < 0) 
		return false;
	if (col > n - 1 || col < 0)
		return false;
	
    return true;  
}


//another check
bool nextCheck(char board[][26], int n, int row, int col, int deltaRow, int deltaCol, char colour) {
	//seeing if the next position is in bounds
	if (positionInBounds(n, row + deltaRow, col + deltaCol) == false) 
		return false;
	//seeing if next position is unoccupied
	if (board[row + deltaRow][col + deltaCol] == 'U')
		return false;
	if (board[row + deltaRow][col + deltaCol] == colour)
		return true; //checks to see if the next tile contains the same colour as the player, making it a legal move
	
	if (colour == 'B') {
		if (board[row + deltaRow][col + deltaCol] == 'W') {
			if (nextCheck(board, n, row + deltaRow, col + deltaCol, deltaRow, deltaCol, colour) == true)
				return true;
			else
				return false;
		}
	}
	else if (colour == 'W') {
		if (board[row + deltaRow][col + deltaCol] == 'B') {
			if (nextCheck(board, n, row + deltaRow, col + deltaCol, deltaRow, deltaCol, colour) == true)
				return true;
			else
				return false;
		}
	}
	return false;
}
/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[][26], int n, int row,
 		int col, char colour, int deltaRow, int deltaCol) {

	//seeing if the positionis in bounds
	if (positionInBounds(n, row, col) == false) 
		return false;
	
	//seeing if the place is occupied
	if (board[row][col] != 'U')
		return false;
	
	if (positionInBounds(n, row + deltaRow, col + deltaCol) == false)
		return false;
	
	//checking if colour is 'B'
	if (colour == 'B') {
		if (board[row + deltaRow][col + deltaCol] == 'W') {
			if (nextCheck(board, n, row + deltaRow, col + deltaCol, deltaRow, deltaCol, colour) == true)
				return true;
		}
	}
	//if the colour is 'W'
	else if (colour == 'W') {
		if ((int)board[row + deltaRow][col + deltaCol] == 'B') {
			if (nextCheck(board, n, row + deltaRow, col + deltaCol, deltaRow, deltaCol, colour) == true)
				return true;
		}
	}
    return false;             
}



bool checkLegal(char board[26][26], int n, int row, int col, char colour) {
	for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
		for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
			if (deltaRow != 0 || deltaCol != 0) {
				if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) == true)
					return true;
			}
		}
	}
	return false;
}

//function that returns winner as a char. returns 'U' if game is not over and 'T' if tied
char checkWinner(const char board[26][26], int n) {
	int bScore, wScore;
	bScore = wScore = 0;
	bool notOver = false;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 'W')
				wScore++;
			else if (board[i][j] == 'B')
				bScore++;
		}
	}
	for (int k = 0; k < n; k++) {
		for (int l = 0; l < n; l++) {
			if (checkLegal(board, n, k, l, 'W') || checkLegal(board, n, k, l, 'B')) {
				notOver = true;
			}
		}
	}
	if (notOver)
		return 'U';
	else {
		if (bScore > wScore) 
			return 'B';
		else if (bScore == wScore)
			return 'T';
		else
			return 'W';
	}
}

void move(char board[26][26], int n, int row, int col, char colour) {
	for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
		for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
			if (deltaRow != 0 || deltaCol != 0) {
				if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) == true) {
					int iteration = 1; //creating a number that will be used as a counter
					while (board[row + deltaRow * iteration][col + deltaCol * iteration] != colour) {
						board[row + deltaRow * iteration][col + deltaCol * iteration] = colour;
						iteration++;
					}
				}
			}
		}
	}
	board[row][col] = colour;
	return;
}

bool hasAvailableMoves(char board[26][26], int n, char colour) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 'U') {
				if (checkLegal(board, n, i, j, colour) == true)
					return true;
			}
		}
	}
	return false;
}

int miniMax(char board[26][26], int depth, bool isMax, char turn, int n) {
	int score, topScore; //topScore will try to be maximised for 'turn' player and minimised for 'opponent' player
	char winner, opponent;
	if (turn == 'B')
		opponent = 'W';
	else
		opponent = 'B';
	//checking for winner first
	/*
	winner = checkWinner(board, n);
	if (winner == turn) {
		score = 1000; //arbitrarily large number
		return score;
	}
	else if (winner == opponent) {
		score = -1000; //arbitrarily large negative number
		return score;
	}
	*/
	if (depth == 0) {
		score = scoreCount(board, n, turn);
		return score;
	}
	
	
	if (isMax) {
		topScore = -1000;
		if (hasAvailableMoves(board, n, turn) == false) {
			score = miniMax(board, depth - 1, false, turn, n);
			if (score > topScore)
				topScore = score;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (checkLegal(board, n, i, j, turn)) {
					board[i][j] = turn;
					score = miniMax(board, depth - 1, false, turn, n);
					board[i][j] = 'U';
					//topScore = max(score, topScore); 
					if (score > topScore)
						topScore = score;
				}
			}
		}
		return topScore;
	}
	else {
		topScore = 1000;
		if (hasAvailableMoves(board, n, opponent) == false) {
			score = miniMax(board, depth - 1, true, turn, n);
			if (score < topScore)
				topScore = score;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (checkLegal(board, n, i, j, opponent)) {
					board[i][j] = opponent;
					score = miniMax(board, depth - 1, true, turn, n);
					board[i][j] = 'U';
					//topScore = min(score, topScore); 
					if (score < topScore) 
						topScore = score;
				}
			}
		}
		return topScore;
	}
}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    int maxScore = -1000;
	int score;
	char copy[26][26];
	
	copyBoard(board, copy, n);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (checkLegal(board, n, i, j, turn)) {
				copy[i][j] = turn;
				score = miniMax(copy, 4, true, turn, n); //using a minimax algorithm with any depth
				copy[i][j] = 'U';
				if (score > maxScore) {
					maxScore = score;
					*row = i;
					*col = j;
				}
			}
		}
	}
	return 0;
}


#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
	char board[26][26];
	char comp, player, turn, winner; //computer, player, turn and winner colour
	int n; //board dimension
	int cRow; 
	int cCol;//computer row and col for next move
	char rowM, colM; //row and col of next player move
	int temp; //dump value for makeMove
	bool invalid = false;
	
	cRow = cCol = 0;
	
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	
	//initialising the board
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			board[i][j] = 'U';
		}
	}
	board[n/2 - 1][n/2 - 1] = 'W';
	board[n/2][n/2] = 'W';
	board[n/2 - 1][n/2] = 'B';
	board[n/2][n/2 - 1] = 'B';
	
	printf("Computer plays (B/W) : ");
	scanf(" %c", &comp);
	
	if (comp == 'B') 
		player = 'W';
	else 
		player = 'B';
		
	printBoard(board, n);
	
	turn = 'B';

	while (true) {
		if (turn == player) {
			//player's move
			printf("Enter move for colour %c (RowCol): ", player);
			scanf(" %c%c", &rowM, &colM);
			//findSmarterMove(board, n, player, &rowM, &colM);
			//printf("Testing AI move (row, col): %c%c\n", rowM + 'a', colM +'a');
		
			if (checkLegal(board, n, rowM - 'a', colM - 'a', player) == true)
				move(board, n, rowM - 'a', colM - 'a', player);
			//if (checkLegal(board, n, rowM, colM, player) == true)
				//move(board, n, rowM, colM, player);
			else {
				printf("Invalid move.\n");
				winner = comp;
				invalid = true;
				break;
			}
			printBoard(board, n);
			//finding out whose turn is next, if any
			if (hasAvailableMoves(board, n, comp))
				turn = comp;
			else {
				if (hasAvailableMoves(board, n, player) == false)
					break;
				else 
					printf("%c player has no valid move.\n", comp);
			}
		}
		else {
			//computer's move
			temp = makeMove(board, n, comp, &cRow, &cCol);
			move(board, n, cRow, cCol, comp);
			printf("Computer places %c at %c%c.\n", comp, cRow + 'a', cCol + 'a');
			printBoard(board, n);
			if (hasAvailableMoves(board, n, player))
				turn = player;
			else {
				if (hasAvailableMoves(board, n, comp) == false) 
					break;
				else
					printf("%c player has no valid move.\n", player);
			}
		}
	}
	if (invalid == false)
		winner = checkWinner(board, n);
	if (winner != 'T')
		printf("%c player wins.\n", winner);
	else
		printf("Draw!\n");
    return 0;
}
#endif // DO NOT DELETE THIS LINE