// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppChessSquare.generated.h"

// Forward Declare
class UStaticMeshComponent;
class UMaterialInstance;
class ACppChessPiece;
class ACppChessGameMode;
enum class EPlayerColors : uint8;

UCLASS()
class MULIPLAYERCHESSGAME_API ACppChessSquare : public AActor
{
	GENERATED_BODY()
	
public:	
	ACppChessSquare();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* _markerBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* _squareBoard;
	
private:
	ACppChessGameMode* _chessGameMode;
	ACppChessPiece* _childPiece;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		EPlayerColors _colorType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		int _xIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		int _yIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		bool _isPosibleMoveSquare = false;

private:
	UFUNCTION()
	void E_SquareBoardClick(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

private:
	void SetBoardSquareMaterial();
	void SetGameModeReference();

public:
	void SetHighlightMaterial(UMaterialInstance* materialInstance, bool isVisible, bool isUnlightAllMaterial);

public:
	FORCEINLINE ACppChessPiece* GetChildPiece() const { return this->_childPiece; }
	FORCEINLINE void SetChildPiece(ACppChessPiece* childPiece) { this->_childPiece = childPiece; }
	FORCEINLINE EPlayerColors GetSquareBoardColor() const { return this->_colorType; }
	FORCEINLINE int GetIndexX() const { return this->_xIndex; }
	FORCEINLINE int GetIndexY() const { return this->_yIndex; }
	FORCEINLINE bool GetIsPosibleMoveSquare() { return this->_isPosibleMoveSquare; }
	FORCEINLINE void SetIsPosibleMoveSquare(bool isPosibleMoveSquare) { this->_isPosibleMoveSquare = isPosibleMoveSquare; }
};
