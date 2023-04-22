// Fill out your copyright notice in the Description page of Project Settings.


#include "CppWidgetInformation.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include <Components/Image.h>
//--------------------------
#include "EnumClass.h"

void UCppWidgetInformation::NativeConstruct()
{
    this->SetPlayerColor();
    this->SetPlayerCheckStatus(EPlayerColors::White, false);
    this->SetPlayerCheckStatus(EPlayerColors::Black, false);
    this->SetPlayerMoveCount(EPlayerColors::White, 0);
    this->SetPlayerMoveCount(EPlayerColors::Black, 0);
    this->SetPlayerCapturesCount(EPlayerColors::White, 0);
    this->SetPlayerCapturesCount(EPlayerColors::Black, 0);
}
void UCppWidgetInformation::SetPlayerCheckStatus(EPlayerColors colorType, bool isCheck)
{
    FString checkStatus = FString(isCheck ? "Check" : "");
    if (colorType == EPlayerColors::White)
    {
        if (this->_txCheckStatus_White)
        {
            this->_txCheckStatus_White->SetText(FText::FromString(checkStatus));
            if (isCheck)
                this->_txCheckStatus_Black->SetText(FText::FromString(""));
        }
    }
    else
    {
        if (this->_txCheckStatus_Black)
        {
            this->_txCheckStatus_Black->SetText(FText::FromString(checkStatus));
            if (isCheck)
                this->_txCheckStatus_White->SetText(FText::FromString(""));
        }
    }
}
void UCppWidgetInformation::SetPlayerMoveCount(EPlayerColors colorType, int moveCount)
{
    if (colorType == EPlayerColors::White)
    {
        this->_txPlayerMoveCount_White->SetText(FText::AsNumber(moveCount));
    }
    else
    {
        this->_txPlayerMoveCount_Black->SetText(FText::AsNumber(moveCount));
    }
}
void UCppWidgetInformation::SetPlayerBorderIndicator(EPlayerColors colorType)
{
    if (colorType == EPlayerColors::White)
    {
        this->_brIndicator_White->SetRenderOpacity(1.0f);
        this->_brIndicator_Black->SetRenderOpacity(0.0f);
    }
    else
    {
        this->_brIndicator_White->SetRenderOpacity(0.0f);
        this->_brIndicator_Black->SetRenderOpacity(1.0f);
    }
}
void UCppWidgetInformation::SetPlayerImage(EPlayerColors colorType, UTexture2D* image)
{
    if (image)
    {
        if (colorType == EPlayerColors::White)
            this->_imgProfile_White->SetBrushFromTexture(image);
        else
            this->_imgProfile_Black->SetBrushFromTexture(image);
    }

}
void UCppWidgetInformation::SetPlayerCapturesCount(EPlayerColors colorType, int moveCount)
{
    if (colorType == EPlayerColors::White)
    {
        if (this->_txCaptures_White)
        {
            this->_txCaptures_White->SetText(FText::AsNumber(moveCount));
        }
    }
    else
    {
        if (this->_txCaptures_Black)
        {
            this->_txCaptures_Black->SetText(FText::AsNumber(moveCount));
        }
    }
}
void UCppWidgetInformation::SetPlayerColor()
{
    if (this->_txWhite && this->_txBlack)
    {
        this->_txWhite->SetText(FText::FromString("White"));
        this->_txBlack->SetText(FText::FromString("Black"));
    }
}
void UCppWidgetInformation::SetPlayerName(EPlayerColors colorType, FString playerName)
{
    UE_LOG(LogTemp, Warning, TEXT("%s"), &playerName);
    this->_brIndicator_Black->SetRenderOpacity(1.0f);
    this->_brIndicator_White->SetRenderOpacity(1.0f);
    if (colorType == EPlayerColors::White)
    {
        if (this->_txPlayerName_White)
        {
            this->_txPlayerName_White->SetText(FText::FromString(playerName));
        }
    }
    else
    {
        if (this->_txPlayerName_Black)
        {
            this->_txPlayerName_Black->SetText(FText::FromString(playerName));
        }
    }
}