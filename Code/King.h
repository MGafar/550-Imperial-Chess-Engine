#ifndef KING_H

#include "ChessPiece.h"

class King : public ChessPiece 
{
	protected:
	/* Function used to check if a King can move between two points following the chess rules,
	the functions also check if there are no obstacles in the piece's path */
	bool validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]);
	bool noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]);

	public:
	King(bool colour, const char* piece_name);
	virtual ~King();
};

#define KING_H
#endif
