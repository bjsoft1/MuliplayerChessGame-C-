// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessPiece.h"
//------------------------
#include "EnumClass.h"
#include "CppChessSquare.h"
#include "CppChessGameMode.h"

ACppChessPiece::ACppChessPiece()
{
	PrimaryActorTick.bCanEverTick = true;
	this->_chessPieceMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChessPieceMeshComponent"));
	this->_chessPieceMeshComponent->SetupAttachment(AActor::RootComponent);
}
void ACppChessPiece::BeginPlay()
{
	Super::BeginPlay();
	this->SetGameModeReference();
	this->_chessPieceMeshComponent->SetCastShadow(false);
	this->_chessPieceMeshComponent->OnClicked.AddDynamic(this, &ACppChessPiece::E_ChessPieceClick);
}
void ACppChessPiece::Tick(float DeltaTime)
{
	if (this->GetActorLocation() != this->_location)
		SetLocation(DeltaTime);
}
void ACppChessPiece::E_ChessPieceClick(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();

	if (!this->_parentSquareBoard)
		this->_chessGameMode->FindParentSquareByLocation(this->GetActorLocation());

	if (!this->_parentSquareBoard->GetIsPosibleMoveSquare())
	{
		if (this->_chessGameMode)
		{
			//if (this->_parentSquareBoard)
			//	this->_parentSquareBoard->SetHighlightMaterial(this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::MarkerHighlight), true, true);
			this->_chessGameMode->SetSelectedChessPiece(this);
			this->_chessGameMode->SetHighlightPosibleMoveLocation();
		}
	}
	else
	{
		TArray<ACppChessSquare*> squares = _chessGameMode->GetPosibleMovesChessSquareBoards(this->_chessGameMode->GetSelectedChessPiece());
		for (ACppChessSquare* cs : squares)
		{
			if (cs == this->_parentSquareBoard)
			{
				ACppChessPiece* chessPiece = this->_chessGameMode->GetSelectedChessPiece();
				chessPiece->GetParentSquare()->SetChildPiece(nullptr);
				this->_parentSquareBoard->SetChildPiece(chessPiece);
				chessPiece->SetParentSquare(this->_parentSquareBoard);
				chessPiece->SetChessPieceLocation(this->_parentSquareBoard->GetActorLocation());
				chessPiece->SetPieceMoveCount(false);
				this->_parentSquareBoard->SetHighlightMaterial(this->_chessGameMode->GetMaterialByTypes(EMaterialTypes::MarkerPiece), true, true);
				this->_parentSquareBoard = nullptr;
				
				this->_chessGameMode->SetPlayerCaptureCount(this->_chessGameMode->GetActivePlayerColor());
				this->_chessGameMode->SetPlayerMoveCount(this->_chessGameMode->GetActivePlayerColor(), false);
				this->_chessGameMode->SetPlayerCamera(this->_chessGameMode->GetActivePlayerColor()
					== EPlayerColors::White ? EPlayerColors::Black : EPlayerColors::White);
				this->_chessGameMode->SetPlayerIndicator();

				if (chessPiece->GetPieceType() == EChessPieceTypes::Pawn)
				{
					if (chessPiece->GetPieceColor() == EPlayerColors::White && chessPiece->GetParentSquare()->GetIndexY() == 8)
					{
						chessPiece->SetPieceType(EChessPieceTypes::Queen);
						chessPiece->SetPieceMesh(this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Queen));
					}
					else if(chessPiece->GetPieceColor() == EPlayerColors::Black && chessPiece->GetParentSquare()->GetIndexY() == 1)
					{
						chessPiece->SetPieceType(EChessPieceTypes::Queen);
						chessPiece->SetPieceMesh(this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Queen));
					}
				}
				this->Destroy();
			}
		}
	}
}
void ACppChessPiece::SetGameModeReference()
{
	if (this->_chessGameMode)
		return;

	AGameModeBase* gameMode = GetWorld()->GetAuthGameMode();
	if (gameMode)
		this->_chessGameMode = Cast<ACppChessGameMode>(gameMode);
}
void ACppChessPiece::SetLocation(float DeltaTime)
{
	const FVector oldLocation = this->GetActorLocation();
	const FVector newLocation = FVector(
		FMath::FInterpTo(oldLocation.X, this->_location.X, GetWorld()->GetDeltaSeconds(), 3.5f),
		FMath::FInterpTo(oldLocation.Y, this->_location.Y, GetWorld()->GetDeltaSeconds(), 3.5f),
		FMath::FInterpTo(oldLocation.Z, this->_location.Z, GetWorld()->GetDeltaSeconds(), 3.5f));
	this->SetActorLocation(newLocation);
}
void ACppChessPiece::SetPieceMesh(UStaticMesh* mesh)
{
	if (mesh)
		this->_chessPieceMeshComponent->SetStaticMesh(mesh);
}
void ACppChessPiece::SetPieceMaterial(UMaterialInstance* materialInstance)
{
	if (materialInstance && this->_moveCount == 0)
		this->_chessPieceMeshComponent->SetMaterial(0, materialInstance);
}
