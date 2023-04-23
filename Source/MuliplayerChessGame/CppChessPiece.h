// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CppChessPiece.generated.h"

// Forward Declare
class UStaticMeshComponent;
class UStaticMesh;
class UMaterialInstance;
class ACppChessSquare;
class ACppChessGameMode;
enum class EPlayerColors : uint8;
enum class EChessPieceTypes : uint8;


UCLASS()
class MULIPLAYERCHESSGAME_API ACppChessPiece : public APawn
{
	GENERATED_BODY()

public:
	ACppChessPiece();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:
	UStaticMeshComponent* _chessPieceMeshComponent;
	
private:
	ACppChessSquare* _parentSquareBoard;
	ACppChessGameMode* _chessGameMode;
	EPlayerColors _colorType;
	EChessPieceTypes _pieceType;
	int _moveCount = 0;
	FVector _location;

private:
	UFUNCTION()
		void E_ChessPieceClick(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

private:
	void SetGameModeReference();
	void SetLocation(float DeltaTime);

public:
	void SetPieceMesh(UStaticMesh* mesh);


public:
	FORCEINLINE bool GetIsInitialMove() const { return this->_moveCount == 0; }
	void SetPieceMaterial(UMaterialInstance* materialInstance);
	FORCEINLINE void SetPieceColor(EPlayerColors colorType) { this->_colorType = colorType; }
	FORCEINLINE EPlayerColors GetPieceColor() const { return this->_colorType; }
	FORCEINLINE void SetPieceType(EChessPieceTypes pieceType) { this->_pieceType = pieceType; }
	FORCEINLINE EChessPieceTypes GetPieceType() const { return this->_pieceType; }
	FORCEINLINE void SetPieceMoveCount(bool isReset = false) { this->_moveCount = isReset ? 0 : this->_moveCount + 1; }
	FORCEINLINE int GetPieceMoveCount() const { return this->_moveCount; }
	FORCEINLINE ACppChessSquare* GetParentSquare() const { return this->_parentSquareBoard; }
	FORCEINLINE void SetParentSquare(ACppChessSquare* parentPiece) { this->_parentSquareBoard = parentPiece; }
	FORCEINLINE void SetChessPieceLocation(FVector newLocation) { this->_location = newLocation; }
};
