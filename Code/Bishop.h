#ifndef BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece 
{
	protected:
	/* Function takes in a starting position and end position and verifies if a Bishop can follow that path */
	bool validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]);

	/* Function verifies that there are no obstacles in the Bishop's path */
	bool noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8]);
	
	public:
	Bishop(bool colour, const char* piece_name);
	virtual ~Bishop();

};

#define BISHOP_H
#endif
