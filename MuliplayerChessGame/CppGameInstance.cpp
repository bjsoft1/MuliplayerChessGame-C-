// Fill out your copyright notice in the Description page of Project Settings.


#include "CppGameInstance.h"
//--------------------------
#include "EnumClass.h"

UCppGameInstance::UCppGameInstance()
{
	this->_currentMenu = EGameMenuTypes::StartMenu;
	this->_isNeedShowMenu = true;
	this->_isPlayingGame = false;
	//this->_currentMenu = EGameMenuTypes::PauseMenu;
	//this->_isNeedShowMenu = false;
	//this->_isPlayingGame = true;
}
