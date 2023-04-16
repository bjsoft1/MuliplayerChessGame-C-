// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppChessBoard.generated.h"

// Forward Declare
enum class EMaterialTypes : uint8;
enum class EPlayerColors : uint8;
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


private:
	void SetGameModeReference();
	void SetChessPiecesReference();
	void SetChessSquareBoardReference();
	

public:
	UMaterialInstance* GetMaterialWithTypes(EMaterialTypes materialType);


public:
	FORCEINLINE void SetGameModeReference(ACppChessGameMode* gameMode) { this->_chessGameMode = gameMode; }
	FORCEINLINE int GetSquareBoardIndex(int xIndex, int yIndex) const { return (((xIndex - 1) * 8) + (yIndex - 1)); }
};
