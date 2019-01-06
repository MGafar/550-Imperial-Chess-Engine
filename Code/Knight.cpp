#include "Knight.h"

Knight::Knight(bool colour, const char* piece_name):ChessPiece(colour, piece_name){}

bool Knight::validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	int deltax = abs(end_point[0]-start_point[0]);
	int deltay = abs(end_point[1]-start_point[1]);

	if((deltax + deltay == 3) && (deltax == 1 || deltay == 1))
		return true;

	return false;
}

bool Knight::noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	return true;
} 

Knight::~Knight(){}
