// Fill out your copyright notice in the Description page of Project Settings.


#include "CppWidgetMenu.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
//------------------------
#include "CppChessGameMode.h"
#include "EnumClass.h"


void UCppWidgetMenu::NativeConstruct()
{
	if (this->_Button1)
		this->_Button1->OnClicked.AddDynamic(this, &UCppWidgetMenu::button1Click);
	if (this->_Button2)
		this->_Button2->OnClicked.AddDynamic(this, &UCppWidgetMenu::button2Click);
	if (this->_Button3)
		this->_Button3->OnClicked.AddDynamic(this, &UCppWidgetMenu::button3Click);
	if (this->_Button4)
		this->_Button4->OnClicked.AddDynamic(this, &UCppWidgetMenu::button4Click);
}
void UCppWidgetMenu::button1Click()
{
	FString buttonText = this->_textButton1->Text.ToString();
	if (buttonText == "Play Game")
		this->PlayGame();
	else if (buttonText == "Resume Game")
		this->ResumeGame();
	else if (buttonText == "Main Menu")
		this->MainMenu();
}
void UCppWidgetMenu::button2Click()
{
	FString buttonText = this->_textButton2->Text.ToString();
	if (buttonText == "Help & Support")
		this->HelpSupport();
	else if (buttonText == "Give Up")
		this->GiveUpGame();
}
void UCppWidgetMenu::button3Click()
{
	FString buttonText = this->_textButton3->Text.ToString();
	if (buttonText == "Restart Game")
		this->RestartGame();
}
void UCppWidgetMenu::button4Click()
{
	FString buttonText = this->_textButton4->Text.ToString();
	if (buttonText == "Quit Game")
		this->QuitGame();
}
void UCppWidgetMenu::QuitGame()
{
	// this is force close command // This command for exit force With UnrealEngine.
//exit(0);

	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
void UCppWidgetMenu::MainMenu()
{
	////UE_LOG(LogTemp, Warning, TEXT("H000000-25"));
	this->SetShowMenuStyle(EGameMenuTypes::StartMenu, true, false);
	UGameplayStatics::OpenLevel(GetWorld(), FName("GameLevel"), true);
}
void UCppWidgetMenu::HelpSupport()
{
	// TODO:
}
void UCppWidgetMenu::GiveUpGame()
{
	// TODO:
	this->SetShowMenuStyle(EGameMenuTypes::PauseMenuAfterGiveUp, false, false);
}
void UCppWidgetMenu::PlayGame()
{
	this->SetShowMenuStyle(EGameMenuTypes::PauseMenu, false, true);
	UGameplayStatics::OpenLevel(GetWorld(), FName("GameLevel"), false);
}
void UCppWidgetMenu::ResumeGame()
{
	this->SetShowMenuStyle(EGameMenuTypes::PauseMenu , false, true);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
void UCppWidgetMenu::PauseGame()
{
	this->SetShowMenuStyle(EGameMenuTypes::PauseMenu, true, true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
void UCppWidgetMenu::RestartGame()
{
	// TODO: Reset All UserInfromation
	this->SetShowMenuStyle(EGameMenuTypes::PauseMenu, false, true);
	UGameplayStatics::OpenLevel(GetWorld(), FName("GameLevel"), false);
}
void UCppWidgetMenu::SetButtonVisibility(bool button1, bool button2, bool button3, bool button4)
{
	this->_Button1->SetVisibility(button1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	this->_Button2->SetVisibility(button2 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	this->_Button3->SetVisibility(button3 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	this->_Button4->SetVisibility(button4 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
void UCppWidgetMenu::SetShowMenuStyle(EGameMenuTypes menuType, bool isNeedShowMenu, bool isPlayGame)
{
	if (this->_chessGameMode)
		this->_chessGameMode->SetGameMenuTypes(menuType, isNeedShowMenu, isPlayGame);
	////UE_LOG(LogTemp, Warning, TEXT("H000000-12"));
	if (this->IsInViewport())
		this->RemoveFromViewport();

	if (!isNeedShowMenu)
		return;
	
	switch (menuType)
	{
	case EGameMenuTypes::None:
	{
		if (this->IsInViewport())
			this->RemoveFromViewport();
		this->SetButtonVisibility();
		break;
	}
	case EGameMenuTypes::StartMenu:
	{
		if (!this->IsInViewport())
			this->AddToViewport(1);
		this->_textTitle->SetText(FText::FromString("Main Menu"));
		this->_textTitle->SetVisibility(ESlateVisibility::Visible);
		this->_textButton1->SetText(FText::FromString("Play Game"));
		this->_textButton2->SetText(FText::FromString("Help & Support"));
		this->_textButton3->SetText(FText::FromString(""));
		this->_textButton4->SetText(FText::FromString("Quit Game"));
		this->SetButtonVisibility(true, true, false, true);
		break;
	}
	case EGameMenuTypes::PauseMenu:
	{
		if (!this->IsInViewport())
			this->AddToViewport(1);
		this->_textTitle->SetText(FText::FromString("Pause Game"));
		this->_textTitle->SetVisibility(ESlateVisibility::Visible);
		this->_textButton1->SetText(FText::FromString("Resume Game"));
		this->_textButton2->SetText(FText::FromString("Give Up"));
		this->_textButton3->SetText(FText::FromString(""));
		this->_textButton4->SetText(FText::FromString("Quit Game"));
		this->SetButtonVisibility(true, true, false, true);
		break;
	}
	case EGameMenuTypes::PauseMenuAfterGiveUp:
	{
		if (!this->IsInViewport())
			this->AddToViewport(1);
		this->_textTitle->SetText(FText::FromString("Pause Game"));
		this->_textTitle->SetVisibility(ESlateVisibility::Visible);
		this->_textButton1->SetText(FText::FromString("Main Menu"));
		this->_textButton2->SetText(FText::FromString(""));
		this->_textButton3->SetText(FText::FromString("Restart Game"));
		this->_textButton4->SetText(FText::FromString("Quit Game"));
		this->SetButtonVisibility(true, false, true, true);
		break;
	}
	case EGameMenuTypes::LoseMenu:
	{
		if (!this->IsInViewport())
			this->AddToViewport(1);
		this->_textTitle->SetText(FText::FromString("You Lose Game"));
		this->_textTitle->SetVisibility(ESlateVisibility::Visible);
		this->_textButton1->SetText(FText::FromString("Main Menu"));
		this->_textButton2->SetText(FText::FromString(""));
		this->_textButton3->SetText(FText::FromString("Restart Game"));
		this->_textButton4->SetText(FText::FromString("Quit Game"));
		this->SetButtonVisibility(true, false, true, true);
		break;
	}
	case EGameMenuTypes::WinnerMenu:
	{
		if (!this->IsInViewport())
			this->AddToViewport(1);
		this->_textTitle->SetText(FText::FromString("You Win Game"));
		this->_textTitle->SetVisibility(ESlateVisibility::Visible);
		this->_textButton1->SetText(FText::FromString("Main Menu"));
		this->_textButton2->SetText(FText::FromString(""));
		this->_textButton3->SetText(FText::FromString("Restart Game"));
		this->_textButton4->SetText(FText::FromString("Quit Game"));
		this->SetButtonVisibility(true, false, true, true);
		break;
	}
	default:
		break;
	}
}
