#include "ChessBoard.h"

ChessBoard::ChessBoard() 
{
	cout << "A new chess game is started!" << endl;

	//Pointers used to keep track of king position
	black_king_position = new char[2];
	white_king_position = new char[2];	
	
	//Pointers used to undo moves
	temp_white_king = new char[2];
	temp_black_king = new char[2];

	//Used as test points to generate valid moves or a piece with a starting point 'test_point'
	//checks the king
	test_point = new char[2];
	start_test_point = new char[2];
	end_test_point = new char[2]; 

	initializeSet();
	initializeVariables();
}
 
void ChessBoard::resetBoard() 
{
	deleteobjects();	
	initializeSet();
	initializeVariables();
}

//Deletes any remaining chess pieces in a loop
void ChessBoard::deleteobjects()
{
	for(int rank = 0; rank < 8; rank++)
	{
		for (int file = 0; file < 8; file++)
		{
			if (myBoard[file][rank] != 0)
				delete myBoard[file][rank];
		}
	}
}

//Function takes in a start and end point and verifies if the move is legal loop
//Appropriate messages are displayed if the move isn't legal
void ChessBoard::submitMove(const char* start_point, const char* end_point)
{
	string piecename;
	
	if(game_over)
	{
		cout << "Moves will not be processed after a checkmate or stalemate," << endl;
		cout << "unless the ChessBoard has been reset." << endl << endl;
		return;
	}

	//Verify user inputs point to a ChessPiece
	if(!verifyUserInputs(start_point, end_point))
		return;
	
	//Reassign pointers to a specific piece if the input is a legal chess move
	//If a piece captures an opponents chess piece then it is deleted before
	//the pointer is reassigned to the new occupying chess piece.
	if(verifyMoveRules(start_point, end_point, player_turn))
	{
		piecename = myBoard[start_point[0] - 'A'][start_point[1] - '1']->getName();
		cout << printcolour(player_turn) << "'s " << piecename << " moves from " << start_point << " to " << end_point;

		if(myBoard[end_point[0] - 'A'][end_point[1] - '1'] != 0)
		{
			piecename = myBoard[end_point[0] - 'A'][end_point[1] - '1']->getName();
			cout << " taking " << printcolour(!player_turn) << "'s " << piecename;

			delete myBoard[end_point[0] - 'A'][end_point[1] - '1'];
		}

		myBoard[end_point[0] - 'A'][end_point[1] - '1'] = myBoard[start_point[0] - 'A'][start_point[1] - '1'];
		myBoard[start_point[0] - 'A'][start_point[1] - '1'] = 0;

		//Used to keep track of king coordinates, to facilitate the function used verify 'check'
		if(!strncmp(start_point, black_king_position, 2))
			strcpy(black_king_position, end_point);
			
		if(!strncmp(start_point, white_king_position, 2))
			strcpy(white_king_position, end_point);
	}else
	{
		if(myBoard[start_point[0] - 'A'][start_point[1] - '1']->getColour() != player_turn)
			cout << "It's not " << printcolour(!player_turn) << "'s turn to move!" << endl;
		
		else
		{
			cout << printcolour(myBoard[start_point[0] - 'A'][start_point[1] - '1']->getColour());
			piecename = myBoard[start_point[0] - 'A'][start_point[1] - '1']->getName();
			cout << "'s " << piecename << " cannot move to " << end_point << endl;
		}
		return;
	}

	//Check for status of the 'stalemate', 'checkmate', and 'check' then switch player turn
	verifyGameStatus();
	player_turn = !player_turn;
	cout << endl;
}
 
//Used for verification of game status
void ChessBoard::verifyGameStatus()
{
	if(!hasValidMovesLeft(!player_turn))
	{
		if (!kingInCheck(player_turn))	
			cout << endl << printcolour(!player_turn) << " is in stalemate";
		
		if (kingInCheck(player_turn))
			cout << endl << printcolour(!player_turn) << " is in checkmate";
		
		game_over = true;

	} else if (kingInCheck(player_turn))
		cout << endl << printcolour(!player_turn) << " is in check";
}

//Used to verify user inputs valid start and end point that point to ChessPieces
bool ChessBoard::verifyUserInputs(const char* start_point, const char* end_point)
{
	if(start_point[0] < 'A' || start_point[0] > 'H' || start_point[1] < '1' || start_point[1] > '8' || strlen(start_point) != 2)
	{
		cout << start_point << " is an invalid starting point" << endl;
		return false;
	}

	if(end_point[0] < 'A' || end_point[0] > 'H' || end_point[1] < '1' || end_point[1] > '8' || strlen(end_point) != 2)
	{
		cout << end_point << " is an invalid end point" << endl;
		return false;
	}	

	if(myBoard[start_point[0] - 'A'][start_point[1] - '1'] == 0)
	{
		cout << "There is no piece in starting position " << start_point << "!" << endl;
		return false;	
	}
	return true;
}

//Function uses 'moveIsValid' function to check if the path is correct for the piece
//and there are no obstacles on the way. If true it temporarily moves the piece then
//checks for further move validity by checking if the move doesn't result in the
//player leading himself to a 'check'
bool ChessBoard::verifyMoveRules(const char* start_point, const char* end_point, bool player_turn)
{
	if(myBoard[start_point[0]-'A'][start_point[1]-'1']->moveIsValid(start_point, end_point, myBoard, player_turn))
	{
		ChessPiece* temp_end_point = myBoard[end_point[0] - 'A'][end_point[1] - '1'];
		ChessPiece* temp_start_point = myBoard[start_point[0] - 'A'][start_point[1] - '1'];

		strcpy(temp_white_king, white_king_position);
		strcpy(temp_black_king, black_king_position);
		
		myBoard[end_point[0] - 'A'][end_point[1] - '1'] = myBoard[start_point[0] - 'A'][start_point[1] - '1'];
		myBoard[start_point[0] - 'A'][start_point[1] - '1'] = 0;

		if(!strncmp(start_point, black_king_position, 2))
			strcpy(black_king_position, end_point);
		
		if(!strncmp(start_point, white_king_position, 2))
			strcpy(white_king_position, end_point);
			
		if (kingInCheck(!player_turn))
		{
			undoMove(start_point, end_point, temp_start_point, temp_end_point);
			return false;
		}

		undoMove(start_point, end_point, temp_start_point, temp_end_point);		
	
		return true; 	
	}
	return false;
}

//Helper function used to undo a move that has been checked for validity in the
//verifyMoveRules function
void ChessBoard::undoMove(const char* start_point, const char* end_point, ChessPiece* temp_start_point, ChessPiece* temp_end_point)
{
	myBoard[end_point[0] - 'A'][end_point[1] - '1'] = temp_end_point;
	myBoard[start_point[0] - 'A'][start_point[1] - '1'] = temp_start_point;

	strcpy(black_king_position, temp_black_king);
	strcpy(white_king_position, temp_white_king);
}

//Function used to check if a particular king is in check
bool ChessBoard::kingInCheck(bool player_turn)
{
	char* king;

	if(player_turn)
		king = white_king_position;
	else
		king = black_king_position;

	for(int i = 0; i < 8; i++)
	{
		for(int m = 0; m < 8; m++)
		{
			test_point[0] = 'A' + i;
			test_point[1] = '1' + m;	

			if (myBoard[i][m] != 0)
			{
				if(myBoard[i][m]->moveIsValid(test_point, king, myBoard, player_turn))
					return true;
			}
		}	
	}
	return false;
}

//Function used to initialize variables
void ChessBoard::initializeVariables()
{
	game_over = false;
	player_turn = false;
	strcpy(black_king_position, "E8");
	strcpy(white_king_position, "E1");
}


//Function used to check for any valid move usign a 'Brute Force'
//way of generating moves then checking if they are valid
bool ChessBoard::hasValidMovesLeft(bool player_turn)
{	
	for(int j = 0; j < 8; j++)
	{
		start_test_point[0] = 'A' + j;

		for(int k = 0; k < 8; k++)
		{
			start_test_point[1] = '1' + k;
			
			for(int i = 0; i < 8; i++)
			{
				end_test_point[0] = 'A' + i;

				for(int m = 0; m < 8; m++)
				{	
					end_test_point[1] = '1' + m;		

					if (myBoard[j][k] != 0 && (myBoard[j][k]->getColour() == player_turn))
						if(verifyMoveRules(start_test_point, end_test_point, player_turn))
							return true;
				}	
			}
		}
	}
	return false;
}

//Function used to initialize a set of ChessPieces using a 'team_identifiers'
//variable to identify the pieces (Black or White)
void ChessBoard::initializeSet()
{
	bool team_identifier = false;	
	
	for (int rank = 0; rank < 8; rank = rank+7)
	{
		for (int file = 0; file < 8; file = file+7)
			myBoard[file][rank] = new Rook(team_identifier, "Rook");
	
		team_identifier = !team_identifier;
	}

	for (int rank = 0; rank < 8; rank = rank+7)
	{
		for (int file = 1; file < 7; file = file+5)
			myBoard[file][rank] = new Knight(team_identifier, "Knight");
	
		team_identifier = !team_identifier;
	}

	for (int rank = 0; rank < 8; rank = rank+7)
	{
		for (int file = 2; file < 6; file = file+3)
			myBoard[file][rank] = new Bishop(team_identifier, "Bishop");
	
		team_identifier = !team_identifier;
	}

	for (int rank = 1; rank < 7; rank = rank+5)
	{
		for (int file = 0; file < 8; file++)
			myBoard[file][rank] = new Pawn(team_identifier, "Pawn");
	
		team_identifier = !team_identifier;
	}
	
	bool isBlack = true;
	myBoard[4][0] = new King(!isBlack, "King");
	myBoard[3][0] = new Queen(!isBlack, "Queen");

	myBoard[4][7] = new King(isBlack, "King");
	myBoard[3][7] = new Queen(isBlack, "Queen");

	for (int rank = 2; rank < 6; rank++)
	{
		for (int file = 0; file < 8; file++)
			myBoard[file][rank] = 0;
	}
}

//Helper function used for printing out messages
const char* ChessBoard::printcolour(bool player_turn)
{
	if (player_turn)
		return "Black";
	else
		return "White";
}

ChessBoard::~ChessBoard()
{
	//Delete strings used to keep track of king positions
	delete [] black_king_position;
	delete [] white_king_position;
	
	//Delete pointers used to keep track of kings in temp moves
	delete [] temp_white_king;
	delete [] temp_black_king;

	//Delete test points to generate valid moves or a piece with a starting point 'test_point'
	//checks the king
	delete [] test_point;
	delete [] start_test_point;
	delete [] end_test_point; 

	//Delete any remaining pieces on the board.
	deleteobjects();
}
