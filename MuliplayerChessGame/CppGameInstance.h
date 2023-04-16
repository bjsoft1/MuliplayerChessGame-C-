// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CppGameInstance.generated.h"

enum class EGameMenuTypes : uint8;


UCLASS()
class MULIPLAYERCHESSGAME_API UCppGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCppGameInstance();

private:
	 EGameMenuTypes _currentMenu;
	 bool _isNeedShowMenu;


public:
	FORCEINLINE void SetActiveMenuType(EGameMenuTypes menuType, bool isNeedShow)
	{
		this->_currentMenu = menuType;
		this->_isNeedShowMenu = isNeedShow;
	}
	FORCEINLINE EGameMenuTypes GetActiveMenuType() const { return this->_currentMenu; }
	//FORCEINLINE bool GetIsNeedShowMenu() const { return this->_isNeedShowMenu; }
	FORCEINLINE bool GetIsNeedShowMenu() const { return this->_isNeedShowMenu; }
};
