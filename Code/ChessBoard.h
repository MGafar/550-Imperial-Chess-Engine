#ifndef CHESSBOARD_H

#include "ChessPiece.h"
#include "King.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"

#include <iostream>
#include <cstring>

using namespace std;

class ChessBoard
{
	private:
	/* Pointers used to keep track of the kings and undoing moves */
	char* temp_white_king;
	char* temp_black_king;
	char* black_king_position;
	char* white_king_position;

	/* Pointers used for generating chess coordinates, used in 
	function which generates moves to verify there are legal moves left */
	char* test_point;
	char* start_test_point;
	char* end_test_point;

	/* Variables used to keep track of the game and the player turn */
	bool game_over;
	bool player_turn;
	
	/* 2D matrix of ChessPiece pointers */
	ChessPiece* myBoard[8][8];
	
	/* Helper functions used for initialization of variables and ChessPieces */
	void initializeVariables();
	void initializeSet();

	/* Function used to verify if a king is in check */
	bool kingInCheck(bool player_turn);
	
	/* Function used to verify if a used submitted move is legal */
	bool verifyMoveRules(const char* start_point, const char* end_point, bool player_turn);

	/* Function used to verify if a player still has moves legal moves left */
	bool hasValidMovesLeft(bool player_turn);
	
	/* Function to verify the user inputs point to an ChessPiece */
	bool verifyUserInputs(const char* start_point, const char* end_point);
	
	/* Function used to check for a 'stalemate' , 'checkmate' , or 'check' */
	void verifyGameStatus();

	/* Helper function used in verifyMoveRules to undo a move */
	void undoMove(const char* start_point, const char* end_point, ChessPiece* temp_start_point, ChessPiece* temp_end_point);

	/* Helper function used for printing a pieces colour */
	const char* printcolour(bool player_turn);

	/* Function used to delete ChessPiece objects in a loop */
	void deleteobjects();
		
	public:
	ChessBoard();

	/* Main function which takes in the user parameters then checks if it obeys
		the game's rules, in case of an erroneous input an appropriate message
		is displayed */
	void submitMove(const char* start_point, const char* end_point);

	/*Function used to reset the board to the starting configuration for chess */
	void resetBoard();

	~ChessBoard();
};

#define CHESSBOARD_H
#endif
