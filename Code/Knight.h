#ifndef KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece 
{
	protected:
	/* Function used to check if a Knight can move between two points following the chess rules,
	the functions also check if there are no obstacles in the piece's path */
	bool validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]);
	bool noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]);

	public:
	Knight(bool colour, const char* piece_name);
	virtual ~Knight();
};

#define KNIGHT_H
#endif
