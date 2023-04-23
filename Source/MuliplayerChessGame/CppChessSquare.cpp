// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessSquare.h"
//-------------------------
#include "EnumClass.h"
#include "CppChessPiece.h"
#include "CppChessGameMode.h"

ACppChessSquare::ACppChessSquare()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->_squareBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SquareBoard"));
	this->_squareBoard->SetupAttachment(AActor::RootComponent);
	this->_markerBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MarkerBoard"));
	this->_markerBoard->SetupAttachment(AActor::RootComponent);	
	this->_markerBoard->SetVisibility(true);
}
void ACppChessSquare::BeginPlay()
{
	Super::BeginPlay();
	FVector currentLocation = this->_squareBoard->GetRelativeLocation();
	currentLocation.Z += 1.0f;

	this->_markerBoard->SetRelativeLocation(currentLocation);
	
	this->SetGameModeReference();
	this->SetBoardSquareMaterial();

	this->_markerBoard->OnClicked.AddDynamic(this, &ACppChessSquare::E_SquareBoardClick);
	this->_squareBoard->OnClicked.AddDynamic(this, &ACppChessSquare::E_SquareBoardClick);
}
void ACppChessSquare::E_SquareBoardClick(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	//UE_LOG(LogTemp, Warning, TEXT("%d"), this->_chessGameMode->GetSquareBoardIndex(this->_xIndex, this->_yIndex));
	if (!this->_chessGameMode)
		this->SetGameModeReference();
	
	if (this->_isPosibleMoveSquare)
	{
		TArray<ACppChessSquare*> squares = _chessGameMode->GetPosibleMovesChessSquareBoards(this->_chessGameMode->GetSelectedChessPiece());
		for (ACppChessSquare * cs : squares)
		{
			if (cs == this)
			{
				ACppChessPiece* chessPiece = this->_chessGameMode->GetSelectedChessPiece();
				chessPiece->GetParentSquare()->SetChildPiece(nullptr);
				if (this->_childPiece)
				{
					this->_childPiece->Destroy();
					this->_chessGameMode->SetPlayerCaptureCount(this->_chessGameMode->GetActivePlayerColor());
				}
				this->SetChildPiece(chessPiece);
				chessPiece->SetParentSquare(this);
				this->SetHighlightMaterial(this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::MarkerPiece), true, true);
				//--------------------------------
				this->_chessGameMode->SetPlayerCheckFlag(EPlayerColors::Black,this->_chessGameMode->
					IsCurrentHaveCheckFlagForOpponent(EPlayerColors::White));
				this->_chessGameMode->SetPlayerCheckFlag(EPlayerColors::White, this->_chessGameMode->
					IsCurrentHaveCheckFlagForOpponent(EPlayerColors::Black));
				//--------------------------------
				chessPiece->SetChessPieceLocation(this->GetActorLocation());
				chessPiece->SetPieceMoveCount(false);
	
				this->_chessGameMode->SetPlayerMoveCount(this->_chessGameMode->GetActivePlayerColor(), false);
				this->_chessGameMode->SetPlayerCamera(this->_chessGameMode->GetActivePlayerColor()
					== EPlayerColors::White ? EPlayerColors::Black : EPlayerColors::White);
				
				this->_chessGameMode->SetPlayerIndicator();

				if (chessPiece->GetPieceType() == EChessPieceTypes::Pawn)
				{
					if (chessPiece->GetPieceColor() == EPlayerColors::White && this->_yIndex == 8)
					{
						chessPiece->SetPieceMoveCount(true);
						chessPiece->SetPieceType(EChessPieceTypes::Queen);
						chessPiece->SetPieceMesh(this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Queen));
					}
					else if (chessPiece->GetPieceColor() == EPlayerColors::Black && this->_yIndex == 1)
					{
						chessPiece->SetPieceMoveCount(true);
						chessPiece->SetPieceType(EChessPieceTypes::Queen);
						chessPiece->SetPieceMesh(this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Queen));
					}
				}
			}
		}
	}
}
void ACppChessSquare::SetBoardSquareMaterial()
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();

	this->_squareBoard->SetMaterial(0, this->_chessGameMode->GetMaterialByTypes
	(this->_colorType == EPlayerColors::Black ? EMaterialTypes::BlackBoard : EMaterialTypes::WhiteBoard));
}
void ACppChessSquare::SetGameModeReference()
{
	if (this->_chessGameMode)
		return;

	AGameModeBase* gameMode = GetWorld()->GetAuthGameMode();
	if (gameMode)
		this->_chessGameMode = Cast<ACppChessGameMode>(gameMode);
}
void ACppChessSquare::SetHighlightMaterial(UMaterialInstance* materialInstance, bool isVisible, bool isUnlightAllMaterial)
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();

	if (isUnlightAllMaterial && this->_chessGameMode)
		this->_chessGameMode->SetUnHighlightAllSquares();

	this->_markerBoard->SetMaterial(0, materialInstance);
	this->_markerBoard->SetVisibility(isVisible);

}