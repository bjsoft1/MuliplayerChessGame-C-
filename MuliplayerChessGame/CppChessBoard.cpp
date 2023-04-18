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
UMaterialInstance* ACppChessBoard::GetMaterialWithTypes(EMaterialTypes materialType)
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();
	return this->_chessGameMode->GetMaterialWithTypes(materialType);
}
void ACppChessBoard::PlayGame()
{
	if (this->_chessPieces.Num() == 32 && this->_chessSquareBoards.Num() == 64)
	{
		UMaterialInstance* blackMaterial = this->_chessGameMode->GetMaterialWithTypes(EMaterialTypes::BlackPiece);
		UMaterialInstance* whiteMaterial = this->_chessGameMode->GetMaterialWithTypes(EMaterialTypes::WhitePiece);

		UStaticMesh* mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Rook);

		// Set Rook (Hatti)
		//--------------------------------------
		_chessPieces[0]->SetPieceMesh(mesh);
		_chessPieces[0]->SetPieceMaterial(blackMaterial);
		_chessPieces[0]->SetChessPieceLocation(this->_chessSquareBoards[0]->GetActorLocation());
		_chessPieces[0]->SetParentSquare(this->_chessSquareBoards[0]);
		this->_chessSquareBoards[0]->SetChildPiece(this->_chessPieces[0]);

		_chessPieces[1]->SetPieceMesh(mesh);
		_chessPieces[1]->SetPieceMaterial(blackMaterial);
		_chessPieces[1]->SetChessPieceLocation(this->_chessSquareBoards[7]->GetActorLocation());
		_chessPieces[1]->SetParentSquare(this->_chessSquareBoards[7]);
		this->_chessSquareBoards[7]->SetChildPiece(this->_chessPieces[1]);

		_chessPieces[2]->SetPieceMesh(mesh);
		_chessPieces[2]->SetPieceMaterial(whiteMaterial);
		_chessPieces[2]->SetChessPieceLocation(this->_chessSquareBoards[56]->GetActorLocation());
		_chessPieces[2]->SetParentSquare(this->_chessSquareBoards[56]);
		this->_chessSquareBoards[56]->SetChildPiece(this->_chessPieces[2]);

		_chessPieces[3]->SetPieceMesh(mesh);
		_chessPieces[3]->SetPieceMaterial(whiteMaterial);
		_chessPieces[3]->SetChessPieceLocation(this->_chessSquareBoards[63]->GetActorLocation());
		_chessPieces[3]->SetParentSquare(this->_chessSquareBoards[63]);
		this->_chessSquareBoards[63]->SetChildPiece(this->_chessPieces[3]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Knight);
		// Set Knight (Ghoda)
		//--------------------------------------
		_chessPieces[4]->SetPieceMesh(mesh);
		_chessPieces[4]->SetPieceMaterial(blackMaterial);
		_chessPieces[4]->SetChessPieceLocation(this->_chessSquareBoards[1]->GetActorLocation());
		_chessPieces[4]->SetActorRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));
		_chessPieces[4]->SetParentSquare(this->_chessSquareBoards[1]);
		this->_chessSquareBoards[1]->SetChildPiece(this->_chessPieces[4]);

		_chessPieces[5]->SetPieceMesh(mesh);
		_chessPieces[5]->SetPieceMaterial(blackMaterial);
		_chessPieces[5]->SetChessPieceLocation(this->_chessSquareBoards[6]->GetActorLocation());
		_chessPieces[5]->SetActorRelativeRotation(FRotator(0.0f, 135.0f, 0.0f));
		_chessPieces[5]->SetParentSquare(this->_chessSquareBoards[6]);
		this->_chessSquareBoards[6]->SetChildPiece(this->_chessPieces[5]);

		_chessPieces[6]->SetPieceMesh(mesh);
		_chessPieces[6]->SetPieceMaterial(whiteMaterial);
		_chessPieces[6]->SetChessPieceLocation(this->_chessSquareBoards[57]->GetActorLocation());
		_chessPieces[6]->SetActorRelativeRotation(FRotator(0.0f, -45.0f, 0.0f));
		_chessPieces[6]->SetParentSquare(this->_chessSquareBoards[57]);
		this->_chessSquareBoards[57]->SetChildPiece(this->_chessPieces[6]);

		_chessPieces[7]->SetPieceMesh(mesh);
		_chessPieces[7]->SetPieceMaterial(whiteMaterial);
		_chessPieces[7]->SetChessPieceLocation(this->_chessSquareBoards[62]->GetActorLocation());
		_chessPieces[7]->SetActorRelativeRotation(FRotator(0.0f, -135.0f, 0.0f));
		_chessPieces[7]->SetParentSquare(this->_chessSquareBoards[62]);
		this->_chessSquareBoards[62]->SetChildPiece(this->_chessPieces[7]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Bishop);
		// Set Bishop (Uta)
		//--------------------------------------
		_chessPieces[8]->SetPieceMesh(mesh);
		_chessPieces[8]->SetPieceMaterial(blackMaterial);
		_chessPieces[8]->SetChessPieceLocation(this->_chessSquareBoards[2]->GetActorLocation());
		_chessPieces[8]->SetParentSquare(this->_chessSquareBoards[2]);
		this->_chessSquareBoards[2]->SetChildPiece(this->_chessPieces[8]);

		_chessPieces[9]->SetPieceMesh(mesh);
		_chessPieces[9]->SetPieceMaterial(blackMaterial);
		_chessPieces[9]->SetChessPieceLocation(this->_chessSquareBoards[5]->GetActorLocation());
		_chessPieces[9]->SetParentSquare(this->_chessSquareBoards[5]);
		this->_chessSquareBoards[5]->SetChildPiece(this->_chessPieces[5]);

		_chessPieces[10]->SetPieceMesh(mesh);
		_chessPieces[10]->SetPieceMaterial(whiteMaterial);
		_chessPieces[10]->SetChessPieceLocation(this->_chessSquareBoards[58]->GetActorLocation());
		_chessPieces[10]->SetParentSquare(this->_chessSquareBoards[58]);
		this->_chessSquareBoards[58]->SetChildPiece(this->_chessPieces[10]);

		_chessPieces[11]->SetPieceMesh(mesh);
		_chessPieces[11]->SetPieceMaterial(whiteMaterial);
		_chessPieces[11]->SetChessPieceLocation(this->_chessSquareBoards[61]->GetActorLocation());
		_chessPieces[11]->SetParentSquare(this->_chessSquareBoards[61]);
		this->_chessSquareBoards[61]->SetChildPiece(this->_chessPieces[11]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::King);
		// Set King (Raja)
		//--------------------------------------
		_chessPieces[12]->SetPieceMesh(mesh);
		_chessPieces[12]->SetPieceMaterial(blackMaterial);
		_chessPieces[12]->SetChessPieceLocation(this->_chessSquareBoards[3]->GetActorLocation());
		_chessPieces[12]->SetParentSquare(this->_chessSquareBoards[3]);
		this->_chessSquareBoards[3]->SetChildPiece(this->_chessPieces[12]);

		_chessPieces[13]->SetPieceMesh(mesh);
		_chessPieces[13]->SetPieceMaterial(whiteMaterial);
		_chessPieces[13]->SetChessPieceLocation(this->_chessSquareBoards[59]->GetActorLocation());
		_chessPieces[13]->SetParentSquare(this->_chessSquareBoards[59]);
		this->_chessSquareBoards[59]->SetChildPiece(this->_chessPieces[13]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Queen);
		// Set Queen (Mantri)
		//--------------------------------------
		_chessPieces[14]->SetPieceMesh(mesh);
		_chessPieces[14]->SetPieceMaterial(blackMaterial);
		_chessPieces[14]->SetChessPieceLocation(this->_chessSquareBoards[4]->GetActorLocation());
		_chessPieces[14]->SetParentSquare(this->_chessSquareBoards[4]);
		this->_chessSquareBoards[4]->SetChildPiece(this->_chessPieces[14]);

		_chessPieces[15]->SetPieceMesh(mesh);
		_chessPieces[15]->SetPieceMaterial(whiteMaterial);
		_chessPieces[15]->SetChessPieceLocation(this->_chessSquareBoards[60]->GetActorLocation());
		_chessPieces[15]->SetParentSquare(this->_chessSquareBoards[60]);
		this->_chessSquareBoards[60]->SetChildPiece(this->_chessPieces[15]);
		//--------------------------------------

		mesh = this->_chessGameMode->GetMeshWithTypes(EChessPieceTypes::Pawn);
		// Set Pawn (Piuso)
		//--------------------------------------
		_chessPieces[16]->SetPieceMesh(mesh);
		_chessPieces[16]->SetPieceMaterial(blackMaterial);
		_chessPieces[16]->SetChessPieceLocation(this->_chessSquareBoards[8]->GetActorLocation());
		_chessPieces[16]->SetParentSquare(this->_chessSquareBoards[8]);
		this->_chessSquareBoards[8]->SetChildPiece(this->_chessPieces[16]);

		_chessPieces[17]->SetPieceMesh(mesh);
		_chessPieces[17]->SetPieceMaterial(whiteMaterial);
		_chessPieces[17]->SetChessPieceLocation(this->_chessSquareBoards[48]->GetActorLocation());
		_chessPieces[17]->SetParentSquare(this->_chessSquareBoards[48]);
		this->_chessSquareBoards[48]->SetChildPiece(this->_chessPieces[17]);

		_chessPieces[18]->SetPieceMesh(mesh);
		_chessPieces[18]->SetPieceMaterial(blackMaterial);
		_chessPieces[18]->SetChessPieceLocation(this->_chessSquareBoards[9]->GetActorLocation());
		_chessPieces[18]->SetParentSquare(this->_chessSquareBoards[9]);
		this->_chessSquareBoards[9]->SetChildPiece(this->_chessPieces[18]);

		_chessPieces[19]->SetPieceMesh(mesh);
		_chessPieces[19]->SetPieceMaterial(whiteMaterial);
		_chessPieces[19]->SetChessPieceLocation(this->_chessSquareBoards[49]->GetActorLocation());
		_chessPieces[19]->SetParentSquare(this->_chessSquareBoards[49]);
		this->_chessSquareBoards[49]->SetChildPiece(this->_chessPieces[19]);

		_chessPieces[20]->SetPieceMesh(mesh);
		_chessPieces[20]->SetPieceMaterial(blackMaterial);
		_chessPieces[20]->SetChessPieceLocation(this->_chessSquareBoards[10]->GetActorLocation());
		_chessPieces[20]->SetParentSquare(this->_chessSquareBoards[10]);
		this->_chessSquareBoards[10]->SetChildPiece(this->_chessPieces[20]);

		_chessPieces[21]->SetPieceMesh(mesh);
		_chessPieces[21]->SetPieceMaterial(whiteMaterial);
		_chessPieces[21]->SetChessPieceLocation(this->_chessSquareBoards[50]->GetActorLocation());
		_chessPieces[21]->SetParentSquare(this->_chessSquareBoards[50]);
		this->_chessSquareBoards[50]->SetChildPiece(this->_chessPieces[21]);

		_chessPieces[22]->SetPieceMesh(mesh);
		_chessPieces[22]->SetPieceMaterial(blackMaterial);
		_chessPieces[22]->SetChessPieceLocation(this->_chessSquareBoards[11]->GetActorLocation());
		_chessPieces[22]->SetParentSquare(this->_chessSquareBoards[11]);
		this->_chessSquareBoards[11]->SetChildPiece(this->_chessPieces[22]);

		_chessPieces[23]->SetPieceMesh(mesh);
		_chessPieces[23]->SetPieceMaterial(whiteMaterial);
		_chessPieces[23]->SetChessPieceLocation(this->_chessSquareBoards[51]->GetActorLocation());
		_chessPieces[23]->SetParentSquare(this->_chessSquareBoards[51]);
		this->_chessSquareBoards[51]->SetChildPiece(this->_chessPieces[23]);

		_chessPieces[24]->SetPieceMesh(mesh);
		_chessPieces[24]->SetPieceMaterial(blackMaterial);
		_chessPieces[24]->SetChessPieceLocation(this->_chessSquareBoards[12]->GetActorLocation());
		_chessPieces[24]->SetParentSquare(this->_chessSquareBoards[12]);
		this->_chessSquareBoards[12]->SetChildPiece(this->_chessPieces[24]);

		_chessPieces[25]->SetPieceMesh(mesh);
		_chessPieces[25]->SetPieceMaterial(whiteMaterial);
		_chessPieces[25]->SetChessPieceLocation(this->_chessSquareBoards[52]->GetActorLocation());
		_chessPieces[25]->SetParentSquare(this->_chessSquareBoards[52]);
		this->_chessSquareBoards[52]->SetChildPiece(this->_chessPieces[25]);

		_chessPieces[26]->SetPieceMesh(mesh);
		_chessPieces[26]->SetPieceMaterial(blackMaterial);
		_chessPieces[26]->SetChessPieceLocation(this->_chessSquareBoards[13]->GetActorLocation());
		_chessPieces[26]->SetParentSquare(this->_chessSquareBoards[13]);
		this->_chessSquareBoards[13]->SetChildPiece(this->_chessPieces[26]);

		_chessPieces[27]->SetPieceMesh(mesh);
		_chessPieces[27]->SetPieceMaterial(whiteMaterial);
		_chessPieces[27]->SetChessPieceLocation(this->_chessSquareBoards[53]->GetActorLocation());
		_chessPieces[27]->SetParentSquare(this->_chessSquareBoards[53]);
		this->_chessSquareBoards[53]->SetChildPiece(this->_chessPieces[27]);

		_chessPieces[28]->SetPieceMesh(mesh);
		_chessPieces[28]->SetPieceMaterial(blackMaterial);
		_chessPieces[28]->SetChessPieceLocation(this->_chessSquareBoards[14]->GetActorLocation());
		_chessPieces[28]->SetParentSquare(this->_chessSquareBoards[14]);
		this->_chessSquareBoards[14]->SetChildPiece(this->_chessPieces[28]);

		_chessPieces[29]->SetPieceMesh(mesh);
		_chessPieces[29]->SetPieceMaterial(whiteMaterial);
		_chessPieces[29]->SetChessPieceLocation(this->_chessSquareBoards[54]->GetActorLocation());
		_chessPieces[29]->SetParentSquare(this->_chessSquareBoards[54]);
		this->_chessSquareBoards[54]->SetChildPiece(this->_chessPieces[29]);

		_chessPieces[30]->SetPieceMesh(mesh);
		_chessPieces[30]->SetPieceMaterial(blackMaterial);
		_chessPieces[30]->SetChessPieceLocation(this->_chessSquareBoards[15]->GetActorLocation());
		_chessPieces[30]->SetParentSquare(this->_chessSquareBoards[15]);
		this->_chessSquareBoards[15]->SetChildPiece(this->_chessPieces[30]);

		_chessPieces[31]->SetPieceMesh(mesh);
		_chessPieces[31]->SetPieceMaterial(whiteMaterial);
		_chessPieces[31]->SetChessPieceLocation(this->_chessSquareBoards[55]->GetActorLocation());
		_chessPieces[31]->SetParentSquare(this->_chessSquareBoards[55]);
		this->_chessSquareBoards[55]->SetChildPiece(this->_chessPieces[31]);
		//--------------------------------------
	}

}
void ACppChessBoard::SetUnHighlightAllSquares()
{
	if (this->_chessSquareBoards.Num() != 32)
		this->SetChessSquareBoardReference();
	for (ACppChessSquare* cs : this->_chessSquareBoards)
	{
		cs->SetHighlightMaterial(nullptr, false, false);
	}
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