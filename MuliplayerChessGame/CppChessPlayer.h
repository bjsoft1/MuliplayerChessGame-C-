// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CppChessPlayer.generated.h"


// Forward Declare
class UBillboardComponent;
class UCameraComponent;
class UTexture2D;
enum class EPlayerColors : uint8;
struct FPlayerInformation;

UCLASS()
class MULIPLAYERCHESSGAME_API ACppChessPlayer : public APawn
{
	GENERATED_BODY()

public:
	ACppChessPlayer();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess Board", meta = (AllowPrivateAccess = "true"))
		UBillboardComponent* _billBoardRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess Board", meta = (AllowPrivateAccess = "true"))
		UBillboardComponent* _billBoardCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess Board", meta = (AllowPrivateAccess = "true"))
		UBillboardComponent* _billBoardBlack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess Board", meta = (AllowPrivateAccess = "true"))
		UBillboardComponent* _billBoardWhite;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess Board", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* _rootCamere;

	//FVector _blackLocation;
	//FRotator _blackRotation;
	//FVector _whiteLocation;
	//FRotator _whiteRotation;
	bool _isMovingCamera = false;
	EPlayerColors _activeColor;
	FPlayerInformation* _chessPlayerInformations1;
	FPlayerInformation* _chessPlayerInformations2;
private:
	void SetLocationRotation(float DeltaTime);


public:
	void SetPlayerCamera(EPlayerColors colorType);

public:
	FPlayerInformation* GetPlayerInformation(int index);
	FPlayerInformation* GetPlayerInformation(EPlayerColors colorType);
	int GetActivePlayerIndex();
	FPlayerInformation* GetActivePlayerInformation();

public:
	FORCEINLINE void SetActivePlayerColor(EPlayerColors colorType) { this->_activeColor = colorType; }
	FORCEINLINE EPlayerColors GetActivePlayerColor() const { return this->_activeColor; }
};
