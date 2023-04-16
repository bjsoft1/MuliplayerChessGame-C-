// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessSquare.h"
//-------------------------
#include "EnumClass.h"
#include "CppChessPiece.h"

// Sets default values
ACppChessSquare::ACppChessSquare()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->_squareBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SquareBoard"));
	this->_markerBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MarkerBoard"));
	this->_markerBoard->SetupAttachment(AActor::RootComponent);
	this->_squareBoard->SetupAttachment(AActor::RootComponent);
	
	this->_squareBoard->SetRelativeLocation(FVector(0.0f, 0.0f, -1.2f));
	this->_markerBoard->SetVisibility(false);
}

// Called when the game starts or when spawned
void ACppChessSquare::BeginPlay()
{
	Super::BeginPlay();
}

void ACppChessSquare::SetBoardSquareMaterial()
{

}
void ACppChessSquare::SetHighlightMaterial(UMaterialInstance* materialInstance, bool isVisible)
{
	this->_markerBoard->SetMaterial(0 ,materialInstance);
	this->_markerBoard->SetVisibility(isVisible);
}