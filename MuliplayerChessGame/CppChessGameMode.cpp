// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessGameMode.h"
#include "Kismet/GameplayStatics.h"
//---------------------------
#include "CppChessController.h"
#include "CppChessPlayer.h"
#include "CppChessBoard.h"
#include "CppChessPiece.h"
#include "CppGameInstance.h"
#include "EnumClass.h"

void ACppChessGameMode::BeginPlay()
{
	Super::BeginPlay();
	this->SetChessControllerReference();
	this->SetChessBoardReference();
	this->SetChessPlayerReference();
}
ACppChessGameMode::ACppChessGameMode()
{
	//this->SetGamePlayInstanceReference();
}
void ACppChessGameMode::SetChessPlayerReference()
{
	if (this->_chessPlayer)
		return;

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	if (controller)
	{
		APawn* pawn = controller->GetPawn();
		if (pawn)
			this->_chessPlayer = Cast<ACppChessPlayer>(pawn);
	}
}
void ACppChessGameMode::SetChessBoardReference()
{
	if (this->_chessBoard)
		return;

	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(AActor::GetWorld(), ACppChessBoard::StaticClass(), allActors);
	if (allActors.Num() > 0)
	{
		this->_chessBoard = Cast<ACppChessBoard>(allActors[0]);
		if (this->_chessBoard)
			this->_chessBoard->SetGameModeReference(this);
	}
}
void ACppChessGameMode::SetChessControllerReference()
{
	if (this->_chessController)
		return;

	// We have multiple times only one Character
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	if (controller)
		this->_chessController = Cast<ACppChessController>(controller);
}
void ACppChessGameMode::PlayGame(bool isRestart)
{
	UGameInstance* instance = AActor::GetGameInstance();
	if (instance)
	{
		UCppGameInstance* gameInstance = Cast<UCppGameInstance>(instance);
		if (gameInstance && gameInstance->GetIsPlayingGame())
		{
			if (!this->_chessBoard)
				this->SetChessBoardReference();
			if (this->_chessBoard)
				this->_chessBoard->PlayGame();
			if (!this->_chessPlayer)
				this->SetChessPlayerReference();
			if (this->_chessPlayer)
				this->_chessPlayer->SetPlayerCamera(EPlayerColors::White);
		}
	}
}
void ACppChessGameMode::SetGameMenuTypes(EGameMenuTypes menuType, bool isNeedShowMenu, bool isPlayGame)
{
	UGameInstance* instance = AActor::GetGameInstance();
	if (instance)
	{
		UCppGameInstance* gameInstance = Cast<UCppGameInstance>(instance);
		if (gameInstance)
		{
			gameInstance->SetActiveMenuType(menuType, isNeedShowMenu);
			gameInstance->SetIsPlayingGame(isPlayGame);

		}
	}
}
void ACppChessGameMode::SetUnHighlightAllSquares()
{
	if (!this->_chessBoard)
		this->SetChessBoardReference();
	if (this->_chessBoard)
		this->_chessBoard->SetUnHighlightAllSquares();
}
EGameMenuTypes ACppChessGameMode::GetGameMenuTypes()
{
	UGameInstance* instance = AActor::GetGameInstance();
	if (instance)
	{
		UCppGameInstance* gameInstance = Cast<UCppGameInstance>(instance);
		if (gameInstance)
			return gameInstance->GetActiveMenuType();
	}
	return EGameMenuTypes::None;
}
bool ACppChessGameMode::GetIsNeedShowMenu()
{
	UGameInstance* instance = AActor::GetGameInstance();
	if (instance)
	{
		UCppGameInstance* gameInstance = Cast<UCppGameInstance>(instance);
		if (gameInstance)
			return gameInstance->GetIsNeedShowMenu();
	}

	return false;
}
bool ACppChessGameMode::GetIsPlayGame()
{
	UGameInstance* instance = AActor::GetGameInstance();
	if (instance)
	{
		UCppGameInstance* gameInstance = Cast<UCppGameInstance>(instance);
		if (gameInstance)
			return gameInstance->GetIsPlayingGame();
	}

	return false;
}
void ACppChessGameMode::SetSelectedChessPiece(ACppChessPiece* chessPiece)
{
	if (!this->_chessBoard)
		this->SetChessBoardReference();
	if (this->_chessBoard)
		this->_chessBoard->SetSelectedChessPiece(chessPiece);
}
void ACppChessGameMode::SetSelectedChessSquare(ACppChessSquare* chessSquare)
{
	if (!this->_chessBoard)
		this->SetChessBoardReference();
	if (this->_chessBoard)
		this->_chessBoard->SetSelectedChessSquare(chessSquare);
}
ACppChessPiece* ACppChessGameMode::GetSelectedChessPiece()
{
	if (!this->_chessBoard)
		this->SetChessBoardReference();
	if (this->_chessBoard)
		return this->_chessBoard->GetSelectedChessPiece();
	return nullptr;
}
ACppChessSquare* ACppChessGameMode::GetSelectedChessSquare()
{
	if (!this->_chessBoard)
		this->SetChessBoardReference();
	if (this->_chessBoard)
		return this->_chessBoard->GetSelectedChessSquare();
	return nullptr;
}
ACppChessSquare* ACppChessGameMode::FindParentSquareByLocation(FVector childLocation)
{
	if (!this->_chessBoard)
		this->SetChessBoardReference();
	
	if (this->_chessBoard)
		return this->_chessBoard->FindParentSquareByLocation(childLocation);

	return nullptr;
}
ACppChessPiece* ACppChessGameMode::FindChildPieceByLocation(FVector parentLocation)
{
	if (!this->_chessBoard)
		this->SetChessBoardReference();

	if (this->_chessBoard)
		return this->_chessBoard->FindChildPieceByLocation(parentLocation);

	return nullptr;
}
EPlayerColors ACppChessGameMode::GetActivePlayerColor()
{
	if (!this->_chessPlayer)
		this->SetChessPlayerReference();

	return this->_chessPlayer->GetActivePlayerColor();
}
int ACppChessGameMode::GetActivePlayerIndex()
{
	if (!this->_chessPlayer)
		this->SetChessPlayerReference();
		
	return this->_chessPlayer->GetActivePlayerIndex();
}
FPlayerInformation* ACppChessGameMode::GetActivePlayerInformation()
{
	if (!this->_chessPlayer)
		this->SetChessPlayerReference();

	return this->_chessPlayer->GetActivePlayerInformation();
}
FPlayerInformation* ACppChessGameMode::GetPlayerInformation(EPlayerColors colorType)
{
	if (!this->_chessPlayer)
		this->SetChessPlayerReference();

	return this->_chessPlayer->GetPlayerInformation(colorType);
}
FPlayerInformation* ACppChessGameMode::GetPlayerInformation(int index)
{
	if (!this->_chessPlayer)
		this->SetChessPlayerReference();

	return this->_chessPlayer->GetPlayerInformation(index);
}
UMaterialInstance* ACppChessGameMode::GetMaterialWithTypes(EMaterialTypes materialType)
{
	switch (materialType)
	{
	case EMaterialTypes::BlackBoard:
	{
		return this->_materialBlackBoard;
		break;
	}
	case EMaterialTypes::WhiteBoard:
	{
		return this->_materialWhiteBoard;
		break;
	}
	case EMaterialTypes::BlackPiece:
	{
		return this->_materialBlackPiece;
		break;
	}
	case EMaterialTypes::WhitePiece:
	{
		return this->_materialWhitePiece;
		break;
	}
	case EMaterialTypes::MarkerAttack:
	{
		return this->_materialMarkerAttack;
		break;
	}
	case EMaterialTypes::MarkerPiece:
	{
		return this->_materialMarkerPiece;
		break;
	}
	case EMaterialTypes::MarkerHighlight:
	{
		return this->_materialMarkerHighlight;
		break;
	}
	case EMaterialTypes::MarkerSelected:
	{
		return this->_materialMarkerSelected;
		break;
	}
	default:
	{
		return nullptr;
		break;
	}
	}
}
UStaticMesh* ACppChessGameMode::GetMeshWithTypes(EChessPieceTypes chessPiece)
{
	switch (chessPiece)
	{
	case EChessPieceTypes::King:
	{
		return this->_meshKing;
		break;
	}
	case EChessPieceTypes::Queen:
	{
		return this->_meshQueen;
		break;
	}
	case EChessPieceTypes::Bishop:
	{
		return this->_meshBishop;
		break;
	}
	case EChessPieceTypes::Knight:
	{
		return this->_meshKnight;
		break;
	}
	case EChessPieceTypes::Rook:
	{
		return this->_meshRook;
		break;
	}
	case EChessPieceTypes::Pawn:
	{
		return this->_meshPawn;
		break;
	}
	default:
	{
		return nullptr;
		break;
	}
	}
}