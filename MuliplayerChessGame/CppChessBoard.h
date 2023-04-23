// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppChessBoard.generated.h"

// Forward Declare
enum class EMaterialTypes : uint8;
enum class EPlayerColors : uint8;
enum class EChessPieceTypes : uint8;
class ACppChessGameMode;
class ACppChessPiece;
class ACppChessSquare;
class UStaticMeshComponent;

UCLASS()
class MULIPLAYERCHESSGAME_API ACppChessBoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACppChessBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* _chessBboardMesh;
		
private:
	ACppChessGameMode* _chessGameMode;
	TArray<ACppChessPiece*> _chessPieces;
	TArray<ACppChessSquare*> _chessSquareBoards;
	ACppChessPiece* _selectedChessPiece;
	ACppChessSquare* _selectedChessSquare;

private:
	void SetGameModeReference();
	void SetChessPiecesReference();
	void SetChessSquareBoardReference();
	//-------------------------

private:
	TArray<ACppChessSquare*> GetChessPiecePosibleMovesSquares_Pawn(ACppChessPiece* selectedChessPiece);
	TArray<ACppChessSquare*> GetChessPiecePosibleMovesSquares_Rook(ACppChessPiece* selectedChessPiece);
	TArray<ACppChessSquare*> GetChessPiecePosibleMovesSquares_Knight(ACppChessPiece* selectedChessPiece);
	TArray<ACppChessSquare*> GetChessPiecePosibleMovesSquares_Bishop(ACppChessPiece* selectedChessPiece);
	TArray<ACppChessSquare*> GetChessPiecePosibleMovesSquares_Queen(ACppChessPiece* selectedChessPiece);
	TArray<ACppChessSquare*> GetChessPiecePosibleMovesSquares_King(ACppChessPiece* selectedChessPiece);
	bool IsFriendChessPiece(ACppChessPiece* self, ACppChessPiece* other);

public:
	UMaterialInstance* GetMaterialByTypes(EMaterialTypes materialType);
	bool GetIsValidSquarePiece(int xIndex, int yIndex);
	ACppChessSquare* GetChessSquareBoardByIndex(int index);
	ACppChessSquare* GetChessSquareBoardByAxis(int xIndex, int yIndex);
	TArray<ACppChessSquare*> GetPosibleMovesChessSquareBoards(ACppChessPiece* selectedChessPiece);
	void PlayGame();
	void SetUnHighlightAllSquares();
	void SetHighlightPosibleMoveLocation();
	ACppChessSquare* FindParentSquareByLocation(FVector childLocation);
	ACppChessPiece* FindChildPieceByLocation(FVector parentLocation);

	TArray<ACppChessPiece*> GetAllPiecesByColor(EPlayerColors colorType);
	ACppChessPiece* GetKingPiece(EPlayerColors colorType);
	bool IsUpcomingCheckSelf(ACppChessPiece* selectedChessPiece, ACppChessSquare* upcomingParentSquare);
	bool IsCurrentHaveCheckFlagForOpponent(EPlayerColors colorType);

public:
	FORCEINLINE void SetGameModeReference(ACppChessGameMode* gameMode) { this->_chessGameMode = gameMode; }
	FORCEINLINE int GetSquareBoardIndex(int xIndex, int yIndex) const { return (((xIndex - 1) * 8) + (yIndex - 1)); }
	FORCEINLINE void SetSelectedChessPiece(ACppChessPiece* chessPiece) { this->_selectedChessPiece = chessPiece; }
	FORCEINLINE void SetSelectedChessSquare(ACppChessSquare* chessSquare) { this->_selectedChessSquare = chessSquare; }
	FORCEINLINE ACppChessPiece* GetSelectedChessPiece() const { return this->_selectedChessPiece; }
	FORCEINLINE ACppChessSquare* GetSelectedChessSquare() const { return this->_selectedChessSquare; }
};
