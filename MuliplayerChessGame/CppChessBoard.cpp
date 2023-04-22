// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessBoard.h"
#include "Kismet/GameplayStatics.h"
//------------------------
#include "CppChessGameMode.h"
#include "CppChessPiece.h"
#include "CppChessSquare.h"
#include "EnumClass.h"

ACppChessBoard::ACppChessBoard()
{
	PrimaryActorTick.bCanEverTick = false;
	this->_chessBboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChessBoardMeshComponent"));
	this->_chessBboardMesh->SetupAttachment(AActor::RootComponent);
}
void ACppChessBoard::BeginPlay()
{
	Super::BeginPlay();

	this->SetGameModeReference();
	this->SetChessSquareBoardReference();
	this->SetChessPiecesReference();
}
void ACppChessBoard::SetGameModeReference()
{
	if (this->_chessGameMode)
		return;

	AGameModeBase* gameMode = GetWorld()->GetAuthGameMode();
	if (gameMode)
		this->_chessGameMode = Cast<ACppChessGameMode>(gameMode);
}
void ACppChessBoard::SetChessPiecesReference()
{
	if (this->_chessPieces.Num() == 0)
	{
		TArray<AActor*> allActors;
		UGameplayStatics::GetAllActorsOfClass(AActor::GetWorld(), ACppChessPiece::StaticClass(), allActors);
		if (allActors.Num() > 0)
		{
			for (size_t i = 0; i < allActors.Num(); i++)
			{
				ACppChessPiece* chessPiece = Cast<ACppChessPiece>(allActors[i]);
				if (chessPiece)
				{
					chessPiece->SetPieceMoveCount(true);
					this->_chessPieces.Add(chessPiece);
				}
			}
		}
	}
}
void ACppChessBoard::SetChessSquareBoardReference()
{
	if (this->_chessPieces.Num() == 0)
	{
		TArray<AActor*> allActors;
		UGameplayStatics::GetAllActorsOfClass(AActor::GetWorld(), ACppChessSquare::StaticClass(), allActors);
		if (allActors.Num() > 0)
		{
			for (size_t i = 0; i < allActors.Num(); i++)
			{
				this->_chessSquareBoards.Add(nullptr);
			}
			for (size_t i = 0; i < allActors.Num(); i++)
			{
				ACppChessSquare* chessSquare = Cast<ACppChessSquare>(allActors[i]);
				int index = this->GetSquareBoardIndex(chessSquare->GetIndexX(), chessSquare->GetIndexY());
				this->_chessSquareBoards[index] = chessSquare;
			}
		}
	}
}
TArray<ACppChessSquare*> ACppChessBoard::GetChessPiecePosibleMovesSquares_Pawn(ACppChessPiece* selectedChessPiece)
{
	TArray<ACppChessSquare*> squares;
	if (!selectedChessPiece->GetParentSquare())
		return squares;
	//UE_LOG(LogTemp, Warning, TEXT("No Parent1"));
	int x = selectedChessPiece->GetParentSquare()->GetIndexX();
	int y = selectedChessPiece->GetParentSquare()->GetIndexY();
	ACppChessSquare* square;

	int axisType = selectedChessPiece->GetPieceColor() == EPlayerColors::White ? 1 : -1;

	if (selectedChessPiece->GetIsInitialMove())
	{
		// Forward Y (One Step)
		if (this->GetIsValidSquarePiece(x, y + 1 * axisType))
		{
			square = this->GetChessSquareBoardByAxis(x, y + 1 * axisType);
			if (square)
				if (!square->GetChildPiece())
				{
					squares.Add(square);
					// Forward Y (Two Step)
					if (this->GetIsValidSquarePiece(x, y + 2 * axisType))
					{
						square = this->GetChessSquareBoardByAxis(x, y + 2 * axisType);
						if (!square->GetChildPiece())
							squares.Add(square);
					}
				}
		}

		// ForwardLeft Y (Check Oponent Have?)
		if (this->GetIsValidSquarePiece(x - 1, y + 1))
		{
			square = this->GetChessSquareBoardByAxis(x - 1, y + 1 * axisType);
			if (square)
				if (square->GetChildPiece())
					if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
						squares.Add(square);
		}
		// ForwardRight Y (Check Oponent Have?)
		if (this->GetIsValidSquarePiece(x + 1, y + 1))
		{
			square = this->GetChessSquareBoardByAxis(x + 1, y + 1 * axisType);
			if (square)
				if (square->GetChildPiece())
					if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
						squares.Add(square);
		}
	}
	else
	{
		// Forward Y (One Step)
		if (this->GetIsValidSquarePiece(x, y + 1 * axisType))
		{
			square = this->GetChessSquareBoardByAxis(x, y + 1 * axisType);
			if (square)
				if (!square->GetChildPiece())
					squares.Add(square);
		}

		// ForwardLeft Y (Check Oponent Have?)
		if (this->GetIsValidSquarePiece(x - 1, y + 1))
		{
			square = this->GetChessSquareBoardByAxis(x - 1, y + 1 * axisType);
			if (square)
				if (square->GetChildPiece())
					if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
						squares.Add(square);
		}
		// ForwardRight Y (Check Oponent Have?)
		if (this->GetIsValidSquarePiece(x + 1, y + 1))
		{
			square = this->GetChessSquareBoardByAxis(x + 1, y + 1 * axisType);
			if (square)
				if (square->GetChildPiece())
					if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
						squares.Add(square);
		}
	}

	return squares;
}
TArray<ACppChessSquare*> ACppChessBoard::GetChessPiecePosibleMovesSquares_Rook(ACppChessPiece* selectedChessPiece)
{
	TArray<ACppChessSquare*> squares;
	if (!selectedChessPiece->GetParentSquare())
		return squares;
	//UE_LOG(LogTemp, Warning, TEXT("No Parent1"));
	ACppChessSquare* square;
	int x = selectedChessPiece->GetParentSquare()->GetIndexX();
	int y = selectedChessPiece->GetParentSquare()->GetIndexY();
	//----------------------------------
	//Forward Y
	for (int i = 1; i < 8; i++)
	{
		if (this->GetIsValidSquarePiece(x, y + i))
		{
			square = this->GetChessSquareBoardByAxis(x, y + i);
			if (!square)
				continue;
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
				break;
			}
			else
				break;
		}
		else
			break;
	}
	//----------------------------------

	//----------------------------------
	//Backward Y
	for (int i = 1; i < 8; i++)
	{
		if (this->GetIsValidSquarePiece(x, y - i))
		{
			square = this->GetChessSquareBoardByAxis(x, y - i);
			if (!square)
				continue;
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
				break;
			}
			else
				break;
		}
		else
			break;
	}
	//----------------------------------

	//----------------------------------
	//Forward X
	for (int i = 1; i < 8; i++)
	{
		if (this->GetIsValidSquarePiece(x + i, y))
		{
			square = this->GetChessSquareBoardByAxis(x + i, y);
			if (!square)
				continue;
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
				break;
			}
			else
				break;
		}
		else
			break;
	}
	//----------------------------------

	//----------------------------------
	//Backward X
	for (int i = 1; i < 8; i++)
	{
		if (this->GetIsValidSquarePiece(x - i, y))
		{
			square = this->GetChessSquareBoardByAxis(x - i, y);
			if (!square)
				continue;
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
				break;
			}
			else
				break;
		}
		else
			break;
	}
	//----------------------------------
	return squares;
}
TArray<ACppChessSquare*> ACppChessBoard::GetChessPiecePosibleMovesSquares_Knight(ACppChessPiece* selectedChessPiece)
{
	TArray<ACppChessSquare*> squares;
	if (!selectedChessPiece->GetParentSquare())
		return squares;
	//UE_LOG(LogTemp, Warning, TEXT("No Parent1"));
	ACppChessSquare* square;
	int x = selectedChessPiece->GetParentSquare()->GetIndexX();
	int y = selectedChessPiece->GetParentSquare()->GetIndexY();

	//Forward Y Left
	if (this->GetIsValidSquarePiece(x - 1, y + 2))
	{
		square = this->GetChessSquareBoardByAxis(x - 1, y + 2);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}

	//Forward Y Right
	if (this->GetIsValidSquarePiece(x + 1, y + 2))
	{
		square = this->GetChessSquareBoardByAxis(x + 1, y + 2);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}

	//Backward Y Left
	if (this->GetIsValidSquarePiece(x - 1, y - 2))
	{
		square = this->GetChessSquareBoardByAxis(x - 1, y - 2);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}

	//Backward Y Right
	if (this->GetIsValidSquarePiece(x + 1, y - 2))
	{
		square = this->GetChessSquareBoardByAxis(x + 1, y - 2);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}

	//-----------------------------------------
	//Forward X Left
	if (this->GetIsValidSquarePiece(x + 2, y - 1))
	{
		square = this->GetChessSquareBoardByAxis(x + 2, y - 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}

	//Forward X Right
	if (this->GetIsValidSquarePiece(x + 2, y + 1))
	{
		square = this->GetChessSquareBoardByAxis(x + 2, y + 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}

	//Backward X Left
	if (this->GetIsValidSquarePiece(x - 2, y - 1))
	{
		square = this->GetChessSquareBoardByAxis(x - 2, y - 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}

	//Backward X Right
	if (this->GetIsValidSquarePiece(x - 2, y + 1))
	{
		square = this->GetChessSquareBoardByAxis(x - 2, y + 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}
	//-----------------------------------------
	return squares;
}
TArray<ACppChessSquare*> ACppChessBoard::GetChessPiecePosibleMovesSquares_Bishop(ACppChessPiece* selectedChessPiece)
{
	TArray<ACppChessSquare*> squares;
	if (!selectedChessPiece->GetParentSquare())
		return squares;
	//UE_LOG(LogTemp, Warning, TEXT("No Parent1"));
	ACppChessSquare* square;
	int x = selectedChessPiece->GetParentSquare()->GetIndexX();
	int y = selectedChessPiece->GetParentSquare()->GetIndexY();
	
	//----------------------------------
	//Forward Left Y
	for (int i = 1; i < 8; i++)
	{
		if (this->GetIsValidSquarePiece(x - i, y + i))
		{
			square = this->GetChessSquareBoardByAxis(x - i, y + i);
			if (!square)
				continue;
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
				break;
			}
			else
				break;
		}
		else
			break;
	}
	//----------------------------------

	//----------------------------------
	//Forward Right Y
	for (int i = 1; i < 8; i++)
	{
		if (this->GetIsValidSquarePiece(x + i, y + i))
		{
			square = this->GetChessSquareBoardByAxis(x + i, y + i);
			if (!square)
				continue;
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
				break;
			}
			else
				break;
		}
		else
			break;
	}
	//----------------------------------

	//----------------------------------
	//Backward Left Y
	for (int i = 1; i < 8; i++)
	{
		if (this->GetIsValidSquarePiece(x - i, y - i))
		{
			square = this->GetChessSquareBoardByAxis(x - i, y - i);
			if (!square)
				continue;
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
				break;
			}
			else
				break;
		}
		else
			break;
	}
	//----------------------------------

	//----------------------------------
	//Backward Right Y
	for (int i = 1; i < 8; i++)
	{
		if (this->GetIsValidSquarePiece(x + i, y - i))
		{
			square = this->GetChessSquareBoardByAxis(x + i, y - i);
			if (!square)
				continue;
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
				break;
			}
			else
				break;
		}
		else
			break;
	}
	//----------------------------------

	return squares;
}
TArray<ACppChessSquare*> ACppChessBoard::GetChessPiecePosibleMovesSquares_Queen(ACppChessPiece* selectedChessPiece)
{
	TArray<ACppChessSquare*> squares;
	if (!selectedChessPiece->GetParentSquare())
		return squares;
	//UE_LOG(LogTemp, Warning, TEXT("No Parent1"));

	// Rook (Hatti) Moves
	TArray<ACppChessSquare*> tempSquares = this->GetChessPiecePosibleMovesSquares_Rook(selectedChessPiece);
	for (ACppChessSquare* cs : tempSquares)
		squares.Add(cs);
	
	//// King (Raja) Moves
	//tempSquares = this->GetChessPiecePosibleMovesSquares_King(selectedChessPiece);
	//for (ACppChessSquare* cs : tempSquares)
	//	squares.Add(cs);

	// Bishop (Uta) Moves
	tempSquares = this->GetChessPiecePosibleMovesSquares_Bishop(selectedChessPiece);
	for (ACppChessSquare* cs : tempSquares)
		squares.Add(cs);

	return squares;
}
TArray<ACppChessSquare*> ACppChessBoard::GetChessPiecePosibleMovesSquares_King(ACppChessPiece* selectedChessPiece)
{
	TArray<ACppChessSquare*> squares;
	if (!selectedChessPiece->GetParentSquare())
		return squares;
	//UE_LOG(LogTemp, Warning, TEXT("No Parent1"));
	
	ACppChessSquare* square;
	int x = selectedChessPiece->GetParentSquare()->GetIndexX();
	int y = selectedChessPiece->GetParentSquare()->GetIndexY();

	//------------------------------------
	//Forward Y
	if (this->GetIsValidSquarePiece(x, y + 1))
	{
		square = this->GetChessSquareBoardByAxis(x, y + 1);
		if (square)
		{
			if (!square->GetChildPiece())
			{
				squares.Add(square);
			}
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
			{
				squares.Add(square);
			}
		}
	}
	//------------------------------------

	//------------------------------------
	//Backward Y
	if (this->GetIsValidSquarePiece(x, y - 1))
	{
		square = this->GetChessSquareBoardByAxis(x, y - 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}
	//------------------------------------

	//------------------------------------
	//Forward Left Y
	if (this->GetIsValidSquarePiece(x - 1, y + 1))
	{
		square = this->GetChessSquareBoardByAxis(x - 1, y + 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}
	//------------------------------------

	//------------------------------------
	//Forward Right Y
	if (this->GetIsValidSquarePiece(x + 1, y + 1))
	{
		square = this->GetChessSquareBoardByAxis(x + 1, y + 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}
	//------------------------------------

	//------------------------------------
	//Backward Right Y
	if (this->GetIsValidSquarePiece(x + 1, y - 1))
	{
		square = this->GetChessSquareBoardByAxis(x + 1, y - 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}
	//------------------------------------

	//------------------------------------
	//Backward Left Y
	if (this->GetIsValidSquarePiece(x - 1, y - 1))
	{
		square = this->GetChessSquareBoardByAxis(x - 1, y - 1);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}
	//------------------------------------

	//------------------------------------
	//Forward X
	if (this->GetIsValidSquarePiece(x + 1, y))
	{
		square = this->GetChessSquareBoardByAxis(x + 1, y);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}
	//------------------------------------

	//------------------------------------
	//Backward X
	if (this->GetIsValidSquarePiece(x - 1, y))
	{
		square = this->GetChessSquareBoardByAxis(x - 1, y);
		if (square)
		{
			if (!square->GetChildPiece())
				squares.Add(square);
			else if (!this->IsFriendChessPiece(selectedChessPiece, square->GetChildPiece()))
				squares.Add(square);
		}
	}
	//------------------------------------

	return squares;
}
bool ACppChessBoard::IsFriendChessPiece(ACppChessPiece* self, ACppChessPiece* other)
{
	if (self && other)
		if (self->GetPieceColor() == other->GetPieceColor())
		{
			//UE_LOG(LogTemp, Warning, TEXT("TRue"));
			return true;
		}
	return false;
}
UMaterialInstance* ACppChessBoard::GetMaterialByTypes(EMaterialTypes materialType)
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();
	return this->_chessGameMode->GetMaterialByTypes(materialType);
}
bool ACppChessBoard::GetIsValidSquarePiece(int xIndex, int yIndex)
{
	if (xIndex >= 1 && yIndex <= 8)
	{
		//UE_LOG(LogTemp,Warning, TEXT("T000000000000000000000001"));
		if (this->GetSquareBoardIndex(xIndex, yIndex) >= 0 && this->GetSquareBoardIndex(xIndex, yIndex) <= 63)
		{
			//UE_LOG(LogTemp, Warning, TEXT("T000000000000000000000002"));
			return true;
		}

	}
	//UE_LOG(LogTemp, Warning, TEXT("T000000000000000000000003"));
	return false;
}
ACppChessSquare* ACppChessBoard::GetChessSquareBoardByIndex(int index)
{
	if (this->_chessSquareBoards.Num() == 64 && index >= 0 && index <= 63)
		return this->_chessSquareBoards[index];
	
	return nullptr;
}
ACppChessSquare* ACppChessBoard::GetChessSquareBoardByAxis(int xIndex, int yIndex)
{
	if (this->_chessSquareBoards.Num() == 64)
		for (ACppChessSquare* cs : this->_chessSquareBoards)
		{
			if (cs->GetIndexX() == xIndex && cs->GetIndexY() == yIndex)
				return cs;
		}
	return nullptr;
}
TArray<ACppChessSquare*> ACppChessBoard::GetPosibleMovesChessSquareBoards(ACppChessPiece* selectedChessPiece)
{
	if (!selectedChessPiece)
		selectedChessPiece = this->_selectedChessPiece;

	TArray<ACppChessSquare*> squares;
	switch (selectedChessPiece->GetPieceType())
	{
	case EChessPieceTypes::King:
		squares = this->GetChessPiecePosibleMovesSquares_King(selectedChessPiece);
		break;
	case EChessPieceTypes::Queen:
		squares = this->GetChessPiecePosibleMovesSquares_Queen(selectedChessPiece);
		break;
	case EChessPieceTypes::Bishop:
		squares = this->GetChessPiecePosibleMovesSquares_Bishop(selectedChessPiece);
		break;
	case EChessPieceTypes::Knight:
		squares = this->GetChessPiecePosibleMovesSquares_Knight(selectedChessPiece);
		break;
	case EChessPieceTypes::Rook:
		squares = this->GetChessPiecePosibleMovesSquares_Rook(selectedChessPiece);
		break;
	case EChessPieceTypes::Pawn:
		squares = this->GetChessPiecePosibleMovesSquares_Pawn(selectedChessPiece);
		break;
	default:
		break;
	}
	return squares;
}
void ACppChessBoard::PlayGame()
{
	if (this->_chessPieces.Num() == 32 && this->_chessSquareBoards.Num() == 64)
	{
		UMaterialInstance* blackMaterial = this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::BlackPiece);
		UMaterialInstance* whiteMaterial = this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::WhitePiece);

		UStaticMesh* mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Rook);

		// Set Rook (Hatti)
		//--------------------------------------
		_chessPieces[0]->SetPieceMesh(mesh);
		_chessPieces[0]->SetPieceMaterial(blackMaterial);
		_chessPieces[0]->SetChessPieceLocation(this->_chessSquareBoards[63]->GetActorLocation());
		_chessPieces[0]->SetPieceType(EChessPieceTypes::Rook);
		_chessPieces[0]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[0]->SetParentSquare(this->_chessSquareBoards[63]);
		this->_chessSquareBoards[63]->SetChildPiece(this->_chessPieces[0]);

		_chessPieces[1]->SetPieceMesh(mesh);
		_chessPieces[1]->SetPieceMaterial(blackMaterial);
		_chessPieces[1]->SetChessPieceLocation(this->_chessSquareBoards[7]->GetActorLocation());
		_chessPieces[1]->SetPieceType(EChessPieceTypes::Rook);
		_chessPieces[1]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[1]->SetParentSquare(this->_chessSquareBoards[7]);
		this->_chessSquareBoards[7]->SetChildPiece(this->_chessPieces[1]);

		_chessPieces[2]->SetPieceMesh(mesh);
		_chessPieces[2]->SetPieceMaterial(whiteMaterial);
		_chessPieces[2]->SetChessPieceLocation(this->_chessSquareBoards[0]->GetActorLocation());
		_chessPieces[2]->SetPieceType(EChessPieceTypes::Rook);
		_chessPieces[2]->SetPieceColor(EPlayerColors::White);
		_chessPieces[2]->SetParentSquare(this->_chessSquareBoards[0]);
		this->_chessSquareBoards[0]->SetChildPiece(this->_chessPieces[2]);
		
		_chessPieces[3]->SetPieceMesh(mesh);
		_chessPieces[3]->SetPieceMaterial(whiteMaterial);
		_chessPieces[3]->SetChessPieceLocation(this->_chessSquareBoards[56]->GetActorLocation());
		_chessPieces[3]->SetPieceType(EChessPieceTypes::Rook);
		_chessPieces[3]->SetPieceColor(EPlayerColors::White);
		_chessPieces[3]->SetParentSquare(this->_chessSquareBoards[56]);
		this->_chessSquareBoards[56]->SetChildPiece(this->_chessPieces[3]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Knight);
		// Set Knight (Ghoda)
		//--------------------------------------
		_chessPieces[4]->SetPieceMesh(mesh);
		_chessPieces[4]->SetPieceMaterial(blackMaterial);
		_chessPieces[4]->SetChessPieceLocation(this->_chessSquareBoards[15]->GetActorLocation());
		_chessPieces[4]->SetActorRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));
		_chessPieces[4]->SetPieceType(EChessPieceTypes::Knight);
		_chessPieces[4]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[4]->SetParentSquare(this->_chessSquareBoards[15]);
		this->_chessSquareBoards[15]->SetChildPiece(this->_chessPieces[4]);

		_chessPieces[5]->SetPieceMesh(mesh);
		_chessPieces[5]->SetPieceMaterial(blackMaterial);
		_chessPieces[5]->SetChessPieceLocation(this->_chessSquareBoards[55]->GetActorLocation());
		_chessPieces[5]->SetActorRelativeRotation(FRotator(0.0f, 135.0f, 0.0f));
		_chessPieces[5]->SetPieceType(EChessPieceTypes::Knight);
		_chessPieces[5]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[5]->SetParentSquare(this->_chessSquareBoards[55]);
		this->_chessSquareBoards[55]->SetChildPiece(this->_chessPieces[5]);

		_chessPieces[6]->SetPieceMesh(mesh);
		_chessPieces[6]->SetPieceMaterial(whiteMaterial);
		_chessPieces[6]->SetChessPieceLocation(this->_chessSquareBoards[48]->GetActorLocation());
		_chessPieces[6]->SetActorRelativeRotation(FRotator(0.0f, -135.0f, 0.0f));
		_chessPieces[6]->SetPieceType(EChessPieceTypes::Knight);
		_chessPieces[6]->SetPieceColor(EPlayerColors::White);
		_chessPieces[6]->SetParentSquare(this->_chessSquareBoards[48]);
		this->_chessSquareBoards[48]->SetChildPiece(this->_chessPieces[6]);

		_chessPieces[7]->SetPieceMesh(mesh);
		_chessPieces[7]->SetPieceMaterial(whiteMaterial);
		_chessPieces[7]->SetChessPieceLocation(this->_chessSquareBoards[8]->GetActorLocation());
		_chessPieces[7]->SetActorRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));
		_chessPieces[7]->SetPieceType(EChessPieceTypes::Knight);
		_chessPieces[7]->SetPieceColor(EPlayerColors::White);
		_chessPieces[7]->SetParentSquare(this->_chessSquareBoards[8]);
		this->_chessSquareBoards[8]->SetChildPiece(this->_chessPieces[7]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Bishop);
		// Set Bishop (Uta)
		//--------------------------------------
		_chessPieces[8]->SetPieceMesh(mesh);
		_chessPieces[8]->SetPieceMaterial(blackMaterial);
		_chessPieces[8]->SetChessPieceLocation(this->_chessSquareBoards[23]->GetActorLocation());
		_chessPieces[8]->SetPieceType(EChessPieceTypes::Bishop);
		_chessPieces[8]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[8]->SetParentSquare(this->_chessSquareBoards[23]);
		this->_chessSquareBoards[23]->SetChildPiece(this->_chessPieces[8]);

		_chessPieces[9]->SetPieceMesh(mesh);
		_chessPieces[9]->SetPieceMaterial(blackMaterial);
		_chessPieces[9]->SetChessPieceLocation(this->_chessSquareBoards[47]->GetActorLocation());
		_chessPieces[9]->SetPieceType(EChessPieceTypes::Bishop);
		_chessPieces[9]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[9]->SetParentSquare(this->_chessSquareBoards[47]);
		this->_chessSquareBoards[47]->SetChildPiece(this->_chessPieces[9]);

		_chessPieces[10]->SetPieceMesh(mesh);
		_chessPieces[10]->SetPieceMaterial(whiteMaterial);
		_chessPieces[10]->SetChessPieceLocation(this->_chessSquareBoards[16]->GetActorLocation());
		_chessPieces[10]->SetPieceType(EChessPieceTypes::Bishop);
		_chessPieces[10]->SetPieceColor(EPlayerColors::White);
		_chessPieces[10]->SetParentSquare(this->_chessSquareBoards[16]);
		this->_chessSquareBoards[16]->SetChildPiece(this->_chessPieces[10]);

		_chessPieces[11]->SetPieceMesh(mesh);
		_chessPieces[11]->SetPieceMaterial(whiteMaterial);
		_chessPieces[11]->SetChessPieceLocation(this->_chessSquareBoards[40]->GetActorLocation());
		_chessPieces[11]->SetPieceType(EChessPieceTypes::Bishop);
		_chessPieces[11]->SetPieceColor(EPlayerColors::White);
		_chessPieces[11]->SetParentSquare(this->_chessSquareBoards[40]);
		this->_chessSquareBoards[40]->SetChildPiece(this->_chessPieces[11]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::King);
		// Set King (Raja)
		//--------------------------------------
		_chessPieces[12]->SetPieceMesh(mesh);
		_chessPieces[12]->SetPieceMaterial(blackMaterial);
		_chessPieces[12]->SetChessPieceLocation(this->_chessSquareBoards[31]->GetActorLocation());
		_chessPieces[12]->SetPieceType(EChessPieceTypes::King);
		_chessPieces[12]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[12]->SetParentSquare(this->_chessSquareBoards[31]);
		this->_chessSquareBoards[31]->SetChildPiece(this->_chessPieces[12]);

		_chessPieces[13]->SetPieceMesh(mesh);
		_chessPieces[13]->SetPieceMaterial(whiteMaterial);
		_chessPieces[13]->SetChessPieceLocation(this->_chessSquareBoards[24]->GetActorLocation());
		_chessPieces[13]->SetPieceType(EChessPieceTypes::King);
		_chessPieces[13]->SetPieceColor(EPlayerColors::White);
		_chessPieces[13]->SetParentSquare(this->_chessSquareBoards[24]);
		this->_chessSquareBoards[24]->SetChildPiece(this->_chessPieces[13]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Queen);
		// Set Queen (Mantri)
		//--------------------------------------
		_chessPieces[14]->SetPieceMesh(mesh);
		_chessPieces[14]->SetPieceMaterial(blackMaterial);
		_chessPieces[14]->SetChessPieceLocation(this->_chessSquareBoards[39]->GetActorLocation());
		_chessPieces[14]->SetPieceType(EChessPieceTypes::Queen);
		_chessPieces[14]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[14]->SetParentSquare(this->_chessSquareBoards[39]);
		this->_chessSquareBoards[39]->SetChildPiece(this->_chessPieces[14]);

		_chessPieces[15]->SetPieceMesh(mesh);
		_chessPieces[15]->SetPieceMaterial(whiteMaterial);
		_chessPieces[15]->SetChessPieceLocation(this->_chessSquareBoards[32]->GetActorLocation());
		_chessPieces[15]->SetPieceType(EChessPieceTypes::Queen);
		_chessPieces[15]->SetPieceColor(EPlayerColors::White);
		_chessPieces[15]->SetParentSquare(this->_chessSquareBoards[32]);
		this->_chessSquareBoards[32]->SetChildPiece(this->_chessPieces[15]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Pawn);
		// Set Pawn (Piuso)
		//--------------------------------------
		_chessPieces[16]->SetPieceMesh(mesh);
		_chessPieces[16]->SetPieceMaterial(blackMaterial);
		_chessPieces[16]->SetChessPieceLocation(this->_chessSquareBoards[6]->GetActorLocation());
		_chessPieces[16]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[16]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[16]->SetParentSquare(this->_chessSquareBoards[6]);
		this->_chessSquareBoards[6]->SetChildPiece(this->_chessPieces[16]);

		_chessPieces[17]->SetPieceMesh(mesh);
		_chessPieces[17]->SetPieceMaterial(whiteMaterial);
		_chessPieces[17]->SetChessPieceLocation(this->_chessSquareBoards[1]->GetActorLocation());
		_chessPieces[17]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[17]->SetPieceColor(EPlayerColors::White);
		_chessPieces[17]->SetParentSquare(this->_chessSquareBoards[1]);
		this->_chessSquareBoards[1]->SetChildPiece(this->_chessPieces[17]);

		_chessPieces[18]->SetPieceMesh(mesh);
		_chessPieces[18]->SetPieceMaterial(blackMaterial);
		_chessPieces[18]->SetChessPieceLocation(this->_chessSquareBoards[14]->GetActorLocation());
		_chessPieces[18]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[18]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[18]->SetParentSquare(this->_chessSquareBoards[14]);
		this->_chessSquareBoards[14]->SetChildPiece(this->_chessPieces[18]);

		_chessPieces[19]->SetPieceMesh(mesh);
		_chessPieces[19]->SetPieceMaterial(whiteMaterial);
		_chessPieces[19]->SetChessPieceLocation(this->_chessSquareBoards[9]->GetActorLocation());
		_chessPieces[19]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[19]->SetPieceColor(EPlayerColors::White);
		_chessPieces[19]->SetParentSquare(this->_chessSquareBoards[9]);
		this->_chessSquareBoards[9]->SetChildPiece(this->_chessPieces[19]);

		_chessPieces[20]->SetPieceMesh(mesh);
		_chessPieces[20]->SetPieceMaterial(blackMaterial);
		_chessPieces[20]->SetChessPieceLocation(this->_chessSquareBoards[22]->GetActorLocation());
		_chessPieces[20]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[20]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[20]->SetParentSquare(this->_chessSquareBoards[22]);
		this->_chessSquareBoards[22]->SetChildPiece(this->_chessPieces[20]);

		_chessPieces[21]->SetPieceMesh(mesh);
		_chessPieces[21]->SetPieceMaterial(whiteMaterial);
		_chessPieces[21]->SetChessPieceLocation(this->_chessSquareBoards[17]->GetActorLocation());
		_chessPieces[21]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[21]->SetPieceColor(EPlayerColors::White);
		_chessPieces[21]->SetParentSquare(this->_chessSquareBoards[17]);
		this->_chessSquareBoards[17]->SetChildPiece(this->_chessPieces[21]);

		_chessPieces[22]->SetPieceMesh(mesh);
		_chessPieces[22]->SetPieceMaterial(blackMaterial);
		_chessPieces[22]->SetChessPieceLocation(this->_chessSquareBoards[30]->GetActorLocation());
		_chessPieces[22]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[22]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[22]->SetParentSquare(this->_chessSquareBoards[30]);
		this->_chessSquareBoards[30]->SetChildPiece(this->_chessPieces[22]);

		_chessPieces[23]->SetPieceMesh(mesh);
		_chessPieces[23]->SetPieceMaterial(whiteMaterial);
		_chessPieces[23]->SetChessPieceLocation(this->_chessSquareBoards[25]->GetActorLocation());
		_chessPieces[23]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[23]->SetPieceColor(EPlayerColors::White);
		_chessPieces[23]->SetParentSquare(this->_chessSquareBoards[25]);
		this->_chessSquareBoards[25]->SetChildPiece(this->_chessPieces[23]);

		_chessPieces[24]->SetPieceMesh(mesh);
		_chessPieces[24]->SetPieceMaterial(blackMaterial);
		_chessPieces[24]->SetChessPieceLocation(this->_chessSquareBoards[38]->GetActorLocation());
		_chessPieces[24]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[24]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[24]->SetParentSquare(this->_chessSquareBoards[38]);
		this->_chessSquareBoards[38]->SetChildPiece(this->_chessPieces[24]);

		_chessPieces[25]->SetPieceMesh(mesh);
		_chessPieces[25]->SetPieceMaterial(whiteMaterial);
		_chessPieces[25]->SetChessPieceLocation(this->_chessSquareBoards[33]->GetActorLocation());
		_chessPieces[25]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[25]->SetPieceColor(EPlayerColors::White);
		_chessPieces[25]->SetParentSquare(this->_chessSquareBoards[33]);
		this->_chessSquareBoards[33]->SetChildPiece(this->_chessPieces[25]);

		_chessPieces[26]->SetPieceMesh(mesh);
		_chessPieces[26]->SetPieceMaterial(blackMaterial);
		_chessPieces[26]->SetChessPieceLocation(this->_chessSquareBoards[46]->GetActorLocation());
		_chessPieces[26]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[26]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[26]->SetParentSquare(this->_chessSquareBoards[46]);
		this->_chessSquareBoards[46]->SetChildPiece(this->_chessPieces[26]);

		_chessPieces[27]->SetPieceMesh(mesh);
		_chessPieces[27]->SetPieceMaterial(whiteMaterial);
		_chessPieces[27]->SetChessPieceLocation(this->_chessSquareBoards[41]->GetActorLocation());
		_chessPieces[27]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[27]->SetPieceColor(EPlayerColors::White);
		_chessPieces[27]->SetParentSquare(this->_chessSquareBoards[41]);
		this->_chessSquareBoards[41]->SetChildPiece(this->_chessPieces[27]);

		_chessPieces[28]->SetPieceMesh(mesh);
		_chessPieces[28]->SetPieceMaterial(blackMaterial);
		_chessPieces[28]->SetChessPieceLocation(this->_chessSquareBoards[54]->GetActorLocation());
		_chessPieces[28]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[28]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[28]->SetParentSquare(this->_chessSquareBoards[54]);
		this->_chessSquareBoards[54]->SetChildPiece(this->_chessPieces[28]);

		_chessPieces[29]->SetPieceMesh(mesh);
		_chessPieces[29]->SetPieceMaterial(whiteMaterial);
		_chessPieces[29]->SetChessPieceLocation(this->_chessSquareBoards[49]->GetActorLocation());
		_chessPieces[29]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[29]->SetPieceColor(EPlayerColors::White);
		_chessPieces[29]->SetParentSquare(this->_chessSquareBoards[49]);
		this->_chessSquareBoards[49]->SetChildPiece(this->_chessPieces[29]);

		_chessPieces[30]->SetPieceMesh(mesh);
		_chessPieces[30]->SetPieceMaterial(blackMaterial);
		_chessPieces[30]->SetChessPieceLocation(this->_chessSquareBoards[62]->GetActorLocation());
		_chessPieces[30]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[30]->SetPieceColor(EPlayerColors::Black);
		_chessPieces[30]->SetParentSquare(this->_chessSquareBoards[62]);
		this->_chessSquareBoards[62]->SetChildPiece(this->_chessPieces[30]);

		_chessPieces[31]->SetPieceMesh(mesh);
		_chessPieces[31]->SetPieceMaterial(whiteMaterial);
		_chessPieces[31]->SetChessPieceLocation(this->_chessSquareBoards[57]->GetActorLocation());
		_chessPieces[31]->SetPieceType(EChessPieceTypes::Pawn);
		_chessPieces[31]->SetPieceColor(EPlayerColors::White);
		_chessPieces[31]->SetParentSquare(this->_chessSquareBoards[57]);
		this->_chessSquareBoards[57]->SetChildPiece(this->_chessPieces[31]);
		//--------------------------------------
	}
}
void ACppChessBoard::SetUnHighlightAllSquares()
{
	if (this->_chessSquareBoards.Num() != 64)
		this->SetChessSquareBoardReference();
	//this->GetPosibleMovesChessSquareBoards(this->_selectedChessPiece);
	for (ACppChessSquare* cs : this->_chessSquareBoards)
	{
		cs->SetHighlightMaterial(nullptr, false, false);
		cs->SetIsPosibleMoveSquare(false);
	}
}
void ACppChessBoard::SetHighlightPosibleMoveLocation()
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();
	if (!this->_selectedChessPiece || !this->_chessGameMode)
		return;

	if (this->_selectedChessPiece->GetPieceColor() == this->_chessGameMode->GetActivePlayerColor())
	{
		TArray<ACppChessSquare*> squares;
		squares = this->GetPosibleMovesChessSquareBoards(this->_selectedChessPiece);
		if (squares.Num() > 0)
		{
			this->SetUnHighlightAllSquares();
			//UE_LOG(LogTemp, Warning, TEXT("TotalPosibleSquare-%d"),squares.Num());
			for (ACppChessSquare* cs : squares)
			{
				if (cs)
				{
					if (!this->IsUpcomingCheckSelf(this->_selectedChessPiece, cs))
					{
						//UE_LOG(LogTemp, Warning, TEXT("No CHeck"));
						cs->SetHighlightMaterial(this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::MarkerHighlight), true, false);
						cs->SetIsPosibleMoveSquare(true);
					}
					//else
					//{
					//	UE_LOG(LogTemp, Warning, TEXT("Yes CHeck"));
					//	cs->SetHighlightMaterial(this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::MarkerPiece), true, false);
					//	cs->SetIsPosibleMoveSquare(true);
					//}
				}
			}
			this->_selectedChessPiece->GetParentSquare()->SetHighlightMaterial(this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::MarkerPiece), true, false);
		}
		else
			this->_selectedChessPiece->GetParentSquare()->SetHighlightMaterial(this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::MarkerSelected), true, true);
	}
	//UE_LOG(LogTemp, Warning, TEXT("*****************************"));
}
ACppChessSquare* ACppChessBoard::FindParentSquareByLocation(FVector childLocation)
{
	for (ACppChessSquare* cs : this->_chessSquareBoards)
	{
		if (cs && cs->GetActorLocation() == childLocation)
			return cs;
	}
	return nullptr;
}
ACppChessPiece* ACppChessBoard::FindChildPieceByLocation(FVector parentLocation)
{
	for (ACppChessPiece* cp : this->_chessPieces)
	{
		if (cp && cp->GetActorLocation() == parentLocation)
			return cp;
	}
	return nullptr;
}
TArray<ACppChessPiece*> ACppChessBoard::GetAllPiecesByColor(EPlayerColors colorType)
{
	TArray<ACppChessPiece*> allPieces;
	for (ACppChessPiece* cp : this->_chessPieces)
	{
		if (cp->GetPieceColor() == colorType)
			allPieces.Add(cp);
	}

	return allPieces;
}
ACppChessPiece* ACppChessBoard::GetKingPiece(EPlayerColors colorType)
{
	for (ACppChessPiece* cp : this->_chessPieces)
	{
		if (cp->GetPieceColor() == colorType && cp->GetPieceType() == EChessPieceTypes::King)
			return cp;
	}
	return nullptr;
}
bool ACppChessBoard::IsUpcomingCheckSelf(ACppChessPiece* selectedChessPiece, ACppChessSquare* upcomingParentSquare)
{
	if (!selectedChessPiece || !upcomingParentSquare)
		return false;

	ACppChessPiece* s_c_p = selectedChessPiece; // Selected Chess Piece
	ACppChessSquare* s_c_p_p = selectedChessPiece->GetParentSquare(); // Selected Chess Piece Parent
	ACppChessSquare* u_p_s = upcomingParentSquare; // Upcoming Parent Square
	ACppChessPiece* u_p_s_c = upcomingParentSquare->GetChildPiece(); // Upcoming Parent Square Child

	if (upcomingParentSquare->GetChildPiece())
	{
		upcomingParentSquare->GetChildPiece()->SetParentSquare(nullptr);
		upcomingParentSquare->SetChildPiece(nullptr);
	}
	
	if (selectedChessPiece->GetParentSquare())
		selectedChessPiece->GetParentSquare()->SetChildPiece(nullptr);
	
	selectedChessPiece->SetParentSquare(upcomingParentSquare);
	upcomingParentSquare->SetChildPiece(selectedChessPiece);

	ACppChessPiece* kingPiece = this->GetKingPiece(selectedChessPiece->GetPieceColor());
	
	bool isTrue = false; 
	TArray<ACppChessPiece*> opponentPices = this->GetAllPiecesByColor(selectedChessPiece->GetPieceColor() == EPlayerColors::White ? EPlayerColors::Black : EPlayerColors::White);

	for (ACppChessPiece* cp : opponentPices)
	{		
		TArray<ACppChessSquare*> getAllPosibleSquares = this->GetPosibleMovesChessSquareBoards(cp);
		for (ACppChessSquare* cs : getAllPosibleSquares)
		{
			//UE_LOG(LogTemp, Warning, TEXT("For-02"));
			if (cs == kingPiece->GetParentSquare())
			{
				//UE_LOG(LogTemp, Warning, TEXT("For-02 - true"));
				isTrue = true;
				break;
			}
		}
	}
	//---------------------------
	upcomingParentSquare->SetChildPiece(u_p_s_c);
	if (upcomingParentSquare->GetChildPiece())
		upcomingParentSquare->GetChildPiece()->SetParentSquare(upcomingParentSquare);
	selectedChessPiece->SetParentSquare(s_c_p_p);
	if(selectedChessPiece->GetParentSquare())
		selectedChessPiece->GetParentSquare()->SetChildPiece(selectedChessPiece);

	return isTrue;
}
bool ACppChessBoard::IsCurrentHaveCheckFlagForOpponent(EPlayerColors colorType)
{
	ACppChessPiece* kingPiece = this->GetKingPiece(colorType);
	TArray<ACppChessPiece*> opponentPices = this->GetAllPiecesByColor(colorType == EPlayerColors::White ? EPlayerColors::Black : EPlayerColors::White);

	for (ACppChessPiece* cp : opponentPices)
	{
		TArray<ACppChessSquare*> getAllPosibleSquares = this->GetPosibleMovesChessSquareBoards(cp);
		for (ACppChessSquare* cs : getAllPosibleSquares)
		{
			if (cs == kingPiece->GetParentSquare())
				return true;
		}
	}
	return false;
}
