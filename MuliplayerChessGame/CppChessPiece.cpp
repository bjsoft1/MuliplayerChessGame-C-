// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessPiece.h"
//------------------------
#include "EnumClass.h"
#include "CppChessSquare.h"

ACppChessPiece::ACppChessPiece()
{
	PrimaryActorTick.bCanEverTick = false;
	this->_chessPieceMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChessPieceMeshComponent"));
	this->_chessPieceMeshComponent->SetupAttachment(AActor::RootComponent);
}
void ACppChessPiece::BeginPlay()
{
	Super::BeginPlay();
	
}
void ACppChessPiece::SetPieceMesh(UStaticMesh* mesh)
{
	if (mesh && this->_moveCount == 0)
		this->_chessPieceMeshComponent->SetStaticMesh(mesh);
}
void ACppChessPiece::SetPieceMaterial(UMaterialInstance* materialInstance)
{
	if (materialInstance && this->_moveCount == 0)
		this->_chessPieceMeshComponent->SetMaterial(0, materialInstance);
}


