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
enum class EPlayerColors : uint8;


UCLASS()
class MULIPLAYERCHESSGAME_API ACppChessPiece : public APawn
{
	GENERATED_BODY()

public:
	ACppChessPiece();

protected:
	virtual void BeginPlay() override;


private:
	UStaticMeshComponent* _chessPieceMeshComponent;
	
private:
	ACppChessSquare* _parentSquareBoard;
	EPlayerColors _colorType;
	int _moveCount = 0;


public:
	FORCEINLINE bool GetIsInitialMove() const { return this->_moveCount == 0; }
	void SetPieceMesh(UStaticMesh* mesh);
	void SetPieceMaterial(UMaterialInstance* materialInstance);
	FORCEINLINE void SetPieceColor(EPlayerColors colorType) { this->_colorType = colorType; }
	FORCEINLINE EPlayerColors GetPieceColor() const { return this->_colorType; }
	FORCEINLINE void SetPieceMoveCount(bool isReset = false) { this->_moveCount = isReset ? 0 : this->_moveCount + 1; }
	FORCEINLINE int GetPieceMoveCount() const { return this->_moveCount; }
	FORCEINLINE ACppChessSquare* GetParentSquare() const { return this->_parentSquareBoard; }
	FORCEINLINE void SetParentSquare(ACppChessSquare* parentPiece) { this->_parentSquareBoard = parentPiece; }
};
