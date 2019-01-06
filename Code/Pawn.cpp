#include "Pawn.h"
using namespace std;

Pawn::Pawn(bool colour, const char* piece_name):ChessPiece(colour, piece_name){}

bool Pawn::validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	int start_rank = '2';
	int multiplier = 1;

	int deltax = end_point[0]-start_point[0];
	int deltay = end_point[1]-start_point[1];
	
	if(isBlack) 
	{
		start_rank = '7';
		multiplier = -1;
	}

	if (start_point[1] == start_rank && deltax == 0 && (deltay == (1*multiplier) || deltay == (2*multiplier)))
		return true;
	else if ((start_point[1] != start_rank) && deltax == 0 && deltay == (1*multiplier))
		return true;
	else if (deltay == (1*multiplier) && (deltax == 1 || deltax == -1))
	{
		if (myBoard[end_point[0] - 'A'][end_point[1] - '1'] != 0)
		{
			if (myBoard[end_point[0] - 'A'][end_point[1] - '1']->getColour() != isBlack)
				return true;	
		}
	}
	return false;
}

bool Pawn::noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	int deltax = (end_point[0]-start_point[0]);
	int iterator;

	if (deltax == 0)
	{
		if(myBoard[end_point[0] - 'A'][end_point[1] - '1'] != 0)
			return false;

		if(end_point[1] > start_point[1])
			iterator = 1;
		else
			iterator = -1;	

		for (int i = start_point[1] - '1' + iterator; i != end_point[1] - '1'; i = i+iterator)
		{
			if (myBoard[start_point[0]-'A'][i] != 0)
				return false;	
		}
	}
	return true;
}
 
Pawn::~Pawn(){}
