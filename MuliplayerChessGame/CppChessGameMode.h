// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CppChessGameMode.generated.h"

// Forward Declare
class ACppChessPlayer;
class ACppChessBoard;
class ACppChessPiece;
class ACppChessController;
class UCppGameInstance;
class UStaticMesh;
class UMaterialInstance;
enum class EPlayerColors : uint8;
enum class EGameMenuTypes : uint8;
enum class EMaterialTypes : uint8;
struct FPlayerInformation;


UCLASS()
class MULIPLAYERCHESSGAME_API ACppChessGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;
	ACppChessGameMode();


private:
	ACppChessPlayer* _chessPlayer;
	ACppChessBoard* _chessBoard;
	ACppChessController* _chessController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Mesh", meta = (BindWidget, AllowPrivateAccess = "true"))
		UStaticMesh* _meshKing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Mesh", meta = (BindWidget, AllowPrivateAccess = "true"))
		UStaticMesh* _meshQueen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Mesh", meta = (BindWidget, AllowPrivateAccess = "true"))
		UStaticMesh* _meshBishop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Mesh", meta = (BindWidget, AllowPrivateAccess = "true"))
		UStaticMesh* _meshKnight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Mesh", meta = (BindWidget, AllowPrivateAccess = "true"))
		UStaticMesh* _meshRook;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Mesh", meta = (BindWidget, AllowPrivateAccess = "true"))
		UStaticMesh* _meshPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Materials", meta = (BindWidget, AllowPrivateAccess = "true"))
		UMaterialInstance* _materialBlackBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Materials", meta = (BindWidget, AllowPrivateAccess = "true"))
		UMaterialInstance* _materialWhiteBoard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Materials", meta = (BindWidget, AllowPrivateAccess = "true"))
		UMaterialInstance* _materialBlackPiece;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece Materials", meta = (BindWidget, AllowPrivateAccess = "true"))
		UMaterialInstance* _materialWhitePiece;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marker Materials", meta = (BindWidget, AllowPrivateAccess = "true"))
		UMaterialInstance* _materialMarkerAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marker Materials", meta = (BindWidget, AllowPrivateAccess = "true"))
		UMaterialInstance* _materialMarkerPiece;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marker Materials", meta = (BindWidget, AllowPrivateAccess = "true"))
		UMaterialInstance* _materialMarkerHighlight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marker Materials", meta = (BindWidget, AllowPrivateAccess = "true"))
		UMaterialInstance* _materialMarkerSelected;

private:
	//void SetGameInstanceReference();
	void SetChessPlayerReference();
	void SetChessBoardReference();
	void SetChessControllerReference();
	void SetChessPiecesReference();

public:
	void PlayGame(bool isRestart = false);
	void SetGameMenuTypes(EGameMenuTypes menuType, bool isNeedShowMenu);
	EGameMenuTypes GetGameMenuTypes();
	bool GetIsNeedShowMenu();
	EPlayerColors GetActivePlayerColor();
	int GetActivePlayerIndex();
	FPlayerInformation* GetActivePlayerInformation();
	FPlayerInformation* GetPlayerInformation(EPlayerColors colorType);
	FPlayerInformation* GetPlayerInformation(int index);
	UMaterialInstance* GetMaterialWithTypes(EMaterialTypes materialType);
	
};
