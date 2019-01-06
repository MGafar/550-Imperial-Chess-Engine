#ifndef QUEEN_H

#include "ChessPiece.h"

class Queen : public ChessPiece 
{
	protected:
	/* Function used to check if a Queen can move between two points following the chess rules,
	the functions also check if there are no obstacles in the piece's path */
	bool validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]);
	bool noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]);
	
	public:
	Queen(bool colour, const char* piece_name);
	virtual ~Queen();
};

#define QUEEN_H
#endif
