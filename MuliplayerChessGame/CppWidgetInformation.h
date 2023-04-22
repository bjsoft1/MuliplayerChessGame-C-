// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CppWidgetInformation.generated.h"

enum class EPlayerColors : uint8;
class UTextBlock;
class UBorder;
class UImage;


UCLASS()
class MULIPLAYERCHESSGAME_API UCppWidgetInformation : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    void NativeConstruct() override;

private:
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
    //    class UEditableTextBox* myTextBox;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txWhite;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txBlack;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txPlayerName_White;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txPlayerName_Black;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txPlayerMoveCount_White;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txPlayerMoveCount_Black;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txCaptures_White;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txCaptures_Black;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txCheckStatus_White;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UTextBlock* _txCheckStatus_Black;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UBorder* _brIndicator_White;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UBorder* _brIndicator_Black;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UImage* _imgProfile_Black;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess Widget", meta = (BindWidget, AllowPrivateAccess = "true"))
        UImage* _imgProfile_White;

public:
    void SetPlayerColor();
    void SetPlayerName(EPlayerColors colorType, FString playerName);
    void SetPlayerCapturesCount(EPlayerColors colorType, int captureCount);
    void SetPlayerCheckStatus(EPlayerColors colorType, bool isCheck);
    void SetPlayerMoveCount(EPlayerColors colorType, int moveCount);
    void SetPlayerBorderIndicator(EPlayerColors colorType);
    void SetPlayerImage(EPlayerColors colorType, UTexture2D* image);

};
