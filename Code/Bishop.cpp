#include "Bishop.h"
 
Bishop::Bishop(bool colour, const char* piece_name):ChessPiece(colour, piece_name){}

bool Bishop::validatePiecePath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	int deltax = abs((end_point[0] - 'A')-(start_point[0] - 'A'));
	int deltay = abs((end_point[1] - '1')-(start_point[1] - '1'));

	if((deltax == deltay) && (deltax != 0))
		return true;

	return false;
}

bool Bishop::noObstaclesInPath(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8])
{
	int deltax = (end_point[0]-start_point[0]);
	int deltay = (end_point[1]-start_point[1]);
	
	int multiplier;

	if((deltax < 0 && deltay < 0) || (deltax > 0 && deltay > 0))
		multiplier = 1;
	else if ((deltax < 0 && deltay > 0) || (deltax > 0 && deltay < 0))	
		multiplier = -1;
	
	if (deltax < 0)
	{
		for (int i = -1; i != deltax; i--)
		{
			if (myBoard[start_point[0]-'A'+i][start_point[1]-'1'+(i*multiplier)] != 0)
				return false;	
		}
	}

	if (deltax > 0)
	{
		for (int i = 1; i != deltax; i++)
		{
			if (myBoard[start_point[0]-'A'+i][start_point[1]-'1'+(i*multiplier)] != 0)
				return false;	
		}
	}
	return true;
}

Bishop::~Bishop()
{
}
