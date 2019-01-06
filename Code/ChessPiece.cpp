#include "ChessPiece.h"
using namespace std;

ChessPiece::ChessPiece(bool colour, const char* piece_name)
{
	isBlack = colour;
	name = piece_name;  
}

bool ChessPiece::getColour() const
{ 
	return isBlack;
}

const char* ChessPiece::getName() const
{
	return name; 
}

bool ChessPiece::moveIsValid(const char* start_point, const char* end_point, ChessPiece* const myBoard[][8], bool blacks_turn)
{
	//check if correct colour's turn
	if(myBoard[start_point[0] - 'A'][start_point[1] - '1']->getColour() != blacks_turn)
		return false;

	//check if final destination is null or piece is rivals
	if(myBoard[end_point[0] - 'A'][end_point[1] - '1'] != 0)
		if(myBoard[end_point[0] - 'A'][end_point[1] - '1']->getColour() == blacks_turn)
			return false;

	//check if path is allowed for the piece and no obstacles are present in path
	if(!(myBoard[start_point[0] - 'A'][start_point[1] - '1']->validatePiecePath(start_point, end_point, myBoard)))
		return false;
	
	//checks if there are obstancles in path (noObstaclesinPath is false)
	if(!(myBoard[start_point[0] - 'A'][start_point[1] - '1']->noObstaclesInPath(start_point, end_point, myBoard)))
		return false;
		
	return true;
}

ChessPiece::~ChessPiece(){}
