// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CppChessSquare.generated.h"

// Forward Declare
class UStaticMeshComponent;
class UMaterialInstance;
class ACppChessPiece;
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
		ACppChessPiece* _childPiece;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		EPlayerColors _colorType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		int _xIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessBoard", meta = (AllowPrivateAccess = "true"))
		int _yIndex;

private:
	void SetBoardSquareMaterial();


public:
	void SetHighlightMaterial(UMaterialInstance* materialInstance, bool isVisible);

public:
	FORCEINLINE ACppChessPiece* GetChildPiece() const { return this->_childPiece; }
	FORCEINLINE void SetChildPiece(ACppChessPiece* childPiece) { this->_childPiece = childPiece; }
	FORCEINLINE EPlayerColors GetSquareBoardColor() const { return this->_colorType; }
	FORCEINLINE int GetIndexX() const { return this->_xIndex; }
	FORCEINLINE int GetIndexY() const { return this->_yIndex; }
	//FORCEINLINE void SetIndexX(int xIndex) { this->_xIndex = xIndex; }
	//FORCEINLINE void SetIndexY(int yIndex) { this->_yIndex = yIndex; }
};
