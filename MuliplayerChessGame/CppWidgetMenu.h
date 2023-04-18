// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CppWidgetMenu.generated.h"

// Forward Declare
enum class EGameMenuTypes : uint8;
class UButton;
class ACppChessGameMode;
class UTextBlock;
class UCanvasPanel;
class UImage;
class UBorder;

UCLASS()
class MULIPLAYERCHESSGAME_API UCppWidgetMenu : public UUserWidget
{
	GENERATED_BODY()


protected:
	void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UButton* _Button1; // Play, Resume, MainMenu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UButton* _Button2; // Help, GiveUp, 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UButton* _Button3; // Restart, 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UButton* _Button4; // Quit, 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _textButton1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _textButton2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _textButton3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _textButton4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess UI", meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _textTitle;

private:
	ACppChessGameMode* _chessGameMode;

private:
	UFUNCTION()
		void button1Click();
	UFUNCTION()
		void button2Click();
	UFUNCTION()
		void button3Click();
	UFUNCTION()
		void button4Click();


	void QuitGame();
	void MainMenu();
	void HelpSupport();
	void GiveUpGame();
	void PlayGame();
	void ResumeGame();
	void PauseGame();
	void RestartGame();


private:
	void SetButtonVisibility(bool button1 = false, bool button2 = false, bool button3 = false, bool button4 = false);


public:
	void SetShowMenuStyle(EGameMenuTypes menuType, bool isNeedShowMenu, bool isPlayGame);

public:
	FORCEINLINE void SetGameModeBase(ACppChessGameMode* gameMode) { this->_chessGameMode = gameMode; }
};
