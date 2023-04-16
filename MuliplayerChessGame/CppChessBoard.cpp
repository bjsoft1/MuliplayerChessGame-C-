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
void ACppChessBoard::SetChessSquareBoardReference()
{
	if (this->_chessPieces.Num() == 0)
	{
		TArray<AActor*> allActors;
		UGameplayStatics::GetAllActorsOfClass(AActor::GetWorld(), ACppChessSquare::StaticClass(), allActors);
		if (allActors.Num() > 0)
			for (size_t i = 0; i < allActors.Num(); i++)
			{
				ACppChessSquare* chessSquare = Cast<ACppChessSquare>(allActors[i]);
				if (chessSquare)
				{
					this->_chessSquareBoards.Add(chessSquare);
				}
			}
	}
}

UMaterialInstance* ACppChessBoard::GetMaterialWithTypes(EMaterialTypes materialType)
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();
	return this->_chessGameMode->GetMaterialWithTypes(materialType);
}

