#include "Rook.h"

Rook::Rook(bool colour, const char* piece_name):ChessPiece(colour, piece_name){}

bool Rook::validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	int deltax = end_point[0]-start_point[0];
	int deltay = end_point[1]-start_point[1];

	if((deltax == 0 || deltay == 0) && (deltax != deltay))
		return true;

	return false;
}

bool Rook::noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	int deltax = (end_point[0]-start_point[0]);
	int deltay = (end_point[1]-start_point[1]);
	int iterator;

	if(end_point[0] > start_point[0] || end_point[1] > start_point[1])
		iterator = 1;
	else
		iterator = -1;	

	if (deltax == 0)
	{
		for (int i = start_point[1] - '1' + iterator; i != end_point[1] - '1'; i = i+iterator)
		{
			if (myBoard[start_point[0]-'A'][i] != 0)
				return false;	
		}
	}

	if (deltay == 0)
	{
		for (int i = start_point[0] - 'A' + iterator; i != end_point[0] - 'A'; i = i+iterator)
		{
			if (myBoard[i][start_point[1]-'1'] != 0)
				return false;	
		}
	}
	return true;
}

Rook::~Rook(){}
