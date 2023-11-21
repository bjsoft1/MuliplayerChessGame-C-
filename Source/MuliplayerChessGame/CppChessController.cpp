// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessController.h"
//-------------------------
#include "CppWidgetMenu.h"
#include "CppChessGameMode.h"
#include "CppWidgetInformation.h"
#include "EnumClass.h"

ACppChessController::ACppChessController()
{
	APlayerController::bShowMouseCursor = true;
	APlayerController::bEnableClickEvents = true;
	APlayerController::bEnableTouchEvents = true;
}
void ACppChessController::BeginPlay()
{
	Super::BeginPlay();

	this->SetGameModeReference();
	this->SetGameMenuReference();
	this->SetGamePlayerInformationUIReference();
}
void ACppChessController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent == nullptr) return;

	InputComponent->BindAction("EscPress", IE_Pressed, this, &ACppChessController::E_ShowPauseMenu);
}
void ACppChessController::E_ShowPauseMenu()
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();
	if (this->_chessGameMode)
		this->ShowGameMenu(this->_chessGameMode->GetGameMenuTypes(), true, true);
}
void ACppChessController::E_SwitchCamera()
{
	if (!this->_chessGameMode)
		this->SetGameModeReference();

	if (this->_chessGameMode)
	{

	}
}
void ACppChessController::SetGameModeReference()
{
	if (this->_chessGameMode)
		return;

	AGameModeBase* gameModeBase = GetWorld()->GetAuthGameMode();
	if (gameModeBase)
		this->_chessGameMode = Cast<ACppChessGameMode>(gameModeBase);
}
void ACppChessController::SetGameMenuReference()
{
	if (this->_widgetMenu)
		return;
	else if (!this->_widgetMenuClass)
		return;

	this->_widgetMenu = CreateWidget<UCppWidgetMenu>(this, this->_widgetMenuClass);
	if (this->_widgetMenu)
	{
		this->_widgetMenu->SetGameModeBase(this->_chessGameMode);
		this->ShowGameMenu(this->_chessGameMode->GetGameMenuTypes(), this->_chessGameMode->GetIsNeedShowMenu(), this->_chessGameMode->GetIsPlayGame());
		this->_chessGameMode->PlayGame(false);
	}
	this->_chessGameMode->PlayGame();
}
void ACppChessController::SetGamePlayerInformationUIReference()
{
	if (this->_widgetPlayerInformation)
		return;
	else if (!this->_widgetPlayerInformationClass)
		return;

	this->_widgetPlayerInformation = CreateWidget<UCppWidgetInformation>(this, this->_widgetPlayerInformationClass);
	if (this->_widgetPlayerInformation)
	{
		this->_widgetPlayerInformation->AddToViewport(0);
		if (!this->_chessGameMode)
			this->SetGameModeReference();
		if (this->_chessGameMode)
			this->_chessGameMode->SetWidgetInformationForPlayerClass(_widgetPlayerInformation);
	}
} 
void ACppChessController::ShowGameMenu(EGameMenuTypes menuType, bool isNeedShowMenu, bool isPlayGame)
{
	if (!this->_widgetMenu)
		this->SetGameMenuReference();

	if (this->_widgetMenu)
		this->_widgetMenu->SetShowMenuStyle(menuType, isNeedShowMenu, isPlayGame);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString("00001"));
}