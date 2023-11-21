// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CppChessPlayer.generated.h"


// Forward Declare
class UBillboardComponent;
class UCameraComponent;
class UTexture2D;
class UCppWidgetInformation;
enum class EPlayerColors : uint8;
//struct FPlayerInformation;

USTRUCT(BlueprintType)
struct FPlayerInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		FString playerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		EPlayerColors playerType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		int playerIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		bool isCheck;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		bool isLegalMoves;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		bool iswatcher;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		int moveCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		int captures;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
		UTexture2D* profilePicture;
};


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
	UCppWidgetInformation* _widgetInformation;
	EPlayerColors _activeColor;
	FPlayerInformation _chessPlayerInformations1;
	FPlayerInformation _chessPlayerInformations2;
private:
	void SetLocationRotation(float DeltaTime);


public:
	void SetPlayerCamera(EPlayerColors colorType);

public:
	FPlayerInformation GetPlayerInformation(int index);
	FPlayerInformation GetPlayerInformation(EPlayerColors colorType);
	int GetActivePlayerIndex();
	FPlayerInformation GetActivePlayerInformation();
	void SetPlayerMoveCount(EPlayerColors colorType, bool isReset);
	int GetPlayerMoveCount(EPlayerColors colorType);
	void SetPlayerCaptureCount(EPlayerColors colorType);
	int GetPlayerCaptureCount(EPlayerColors colorType);
	void SetPlayerCheckFlag(EPlayerColors colorType, bool isCheckFlag);
	void SetPlayerIndicator();
	bool GetPlayerCheckFlag(EPlayerColors colorType);

public:
	FORCEINLINE void SetActivePlayerColor(EPlayerColors colorType) { this->_activeColor = colorType; }
	FORCEINLINE EPlayerColors GetActivePlayerColor() const { return this->_activeColor; }
	FORCEINLINE void SetWidgetInformation(UCppWidgetInformation* widgetInformation) { this->_widgetInformation = widgetInformation; }
};
