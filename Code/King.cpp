#include "King.h"

King::King(bool colour, const char* piece_name):ChessPiece(colour, piece_name){}

bool King::validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	int deltax = abs(end_point[0]-start_point[0]);
	int deltay = abs(end_point[1]-start_point[1]);

	if(deltax == 1 || deltay == 1)
	{
		if((deltax + deltay) < 3)
			return true;
	}
	return false; 
}

bool King::noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	return true;
}

King::~King(){}
