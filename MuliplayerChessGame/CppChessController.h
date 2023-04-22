// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CppChessController.generated.h"

// Forward Declare
enum class EGameMenuTypes : uint8;
enum class EPlayerColors : uint8;
struct FPlayerInformation;
class UCppWidgetMenu;
class ACppChessGameMode;
class UCppWidgetInformation;

UCLASS()
class MULIPLAYERCHESSGAME_API ACppChessController : public APlayerController
{
	GENERATED_BODY()


public:
	ACppChessController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chess UI", meta = (AllowPrivateAccess = "true"))
		ACppChessGameMode* _chessGameMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		TSubclassOf<UCppWidgetMenu> _widgetMenuClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Player UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		TSubclassOf<UCppWidgetInformation> _widgetPlayerInformationClass;

private:
	UCppWidgetMenu* _widgetMenu;
	UCppWidgetInformation* _widgetPlayerInformation;


private:
	void E_ShowPauseMenu();
	void E_SwitchCamera();


private:
	void SetGameModeReference();
	void SetGameMenuReference();
	void SetGamePlayerInformationUIReference();
	void ShowGameMenu(EGameMenuTypes menuType, bool isNeedShowMenu, bool isPlayGame);
};
