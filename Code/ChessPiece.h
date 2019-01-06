#ifndef CHESSPIECE_H
#include <stdlib.h>

class ChessPiece
{
	protected:
	/* Variables used for piece identification */
	bool isBlack;
	const char* name;

	/* Poplymorphic functions whose behaviour is defined purely in derived classes
	these function check if a piece can move between two points following the chess rules,
	the functions also check if there are no obstacles in the piece's path */
	virtual bool validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]) = 0;
	virtual bool noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]) = 0;

	public:
	ChessPiece(bool colour, const char* piece_name);
	
	/* Getter functions for piece identifiers */
	bool getColour() const;
	const char* getName() const;
	
	/* Function used to verify a move is legal and has no pieces blocking it in it's path, uses 
		'validatePiecePath' and 'noObstaclesinPath' as helpers */
	bool moveIsValid(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8], bool blacks_turn);
	
	virtual ~ChessPiece();
};

#define CHESSPIECE_H
#endif
