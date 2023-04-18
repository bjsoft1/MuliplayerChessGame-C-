// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessPlayer.h"
#include "Components/BillBoardComponent.h"
#include "Camera/CameraComponent.h"
//------------------------------
#include "EnumClass.h"

ACppChessPlayer::ACppChessPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->_billBoardRoot = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoardRoot"));
	this->_billBoardRoot->SetupAttachment(AActor::RootComponent);
	this->_billBoardRoot->SetVisibility(false);
	this->_billBoardRoot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	this->_billBoardRoot->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	AActor::RootComponent = this->_billBoardRoot;

	this->_billBoardBlack = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoardBlack"));
	this->_billBoardBlack->SetupAttachment(this->_billBoardRoot);
	this->_billBoardBlack->SetVisibility(false);
	this->_billBoardBlack->SetRelativeLocation(FVector(0.0f, -500.0f, 700.0f));
	this->_billBoardBlack->SetRelativeRotation(FRotator(0.0f, 300.0f, 90.0f));
	
	this->_billBoardWhite = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoardWhite"));
	this->_billBoardWhite->SetupAttachment(this->_billBoardRoot);
	this->_billBoardWhite->SetVisibility(false);
	this->_billBoardWhite->SetRelativeLocation(FVector(0.0f, 500.0f, 700.0f));
	this->_billBoardWhite->SetRelativeRotation(FRotator(0.0f, 300.0f, -90.0f));

	this->_billBoardCamera = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoardCamera"));
	this->_billBoardCamera->SetupAttachment(this->_billBoardRoot);
	this->_billBoardCamera->SetVisibility(false);
	this->_billBoardCamera->SetRelativeLocation(FVector(-500.0f, 0.0f, 1.0f));
	this->_billBoardCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	this->_rootCamere = CreateDefaultSubobject<UCameraComponent>(TEXT("RootCamera"));
	this->_rootCamere->SetupAttachment(this->_billBoardCamera);
	this->_rootCamere->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	this->_rootCamere->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	FPlayerInformation chessPlayer1;
	FPlayerInformation chessPlayer2;
	chessPlayer1.captures = 0;
	chessPlayer1.isCheck = false;
	chessPlayer1.isLegalMoves = true;
	chessPlayer1.moveCount = 0;
	chessPlayer1.iswatcher = false;
	chessPlayer1.playerIndex = 0;
	chessPlayer1.playerName = "Bijay Adhikari";
	chessPlayer1.playerType = EPlayerColors::White;
	this->_chessPlayerInformations1 = &chessPlayer1;

	chessPlayer2.captures = 0;
	chessPlayer2.isCheck = false;
	chessPlayer2.isLegalMoves = true;
	chessPlayer2.moveCount = 0;
	chessPlayer2.iswatcher = false;
	chessPlayer2.playerIndex = 1;
	chessPlayer2.playerName = "Bijay Adhikari";
	chessPlayer2.playerType = EPlayerColors::Black;
	this->_chessPlayerInformations2 = &chessPlayer2;
}
void ACppChessPlayer::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	this->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	this->_billBoardRoot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	this->_billBoardRoot->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	this->_billBoardBlack->SetRelativeLocation(FVector(0.0f, -500.0f, 700.0f), true);
	this->_billBoardBlack->SetRelativeRotation(FRotator(-60.0f, 90.0f, 0.0f), true);

	this->_billBoardWhite->SetRelativeLocation(FVector(0.0f, 500.0f, 700.0f), true);
	this->_billBoardWhite->SetRelativeRotation(FRotator(-60.0f, -90.0f, 0.0f), true);

	this->_billBoardCamera->SetRelativeLocation(FVector(-1000.0f, 0.0f, 200.0f));
	this->_billBoardCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	this->_rootCamere->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	this->_rootCamere->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}
void ACppChessPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->_isMovingCamera)
		this->SetLocationRotation(DeltaTime);
}
void ACppChessPlayer::SetLocationRotation(float DeltaTime)
{
	const FVector oldLocation = this->_billBoardCamera->GetRelativeLocation();
	const FRotator oldRotator = this->_billBoardCamera->GetRelativeRotation();
	float interpValue = 2.0f;
	if (this->_activeColor == EPlayerColors::White)
	{
		const FVector whiteLocation = this->_billBoardWhite->GetRelativeLocation();
		const FRotator whiteRotation = this->_billBoardWhite->GetRelativeRotation();

		const FVector newLocation = FVector(
			FMath::FInterpTo(oldLocation.X, whiteLocation.X, DeltaTime, interpValue),
			FMath::FInterpTo(oldLocation.Y, whiteLocation.Y, DeltaTime, interpValue),
			FMath::FInterpTo(oldLocation.Z, whiteLocation.Z, DeltaTime, interpValue)
		);
		const FRotator newRotator = FRotator(
			FMath::FInterpTo(oldRotator.Pitch, whiteRotation.Pitch, DeltaTime, interpValue),
			FMath::FInterpTo(oldRotator.Yaw, whiteRotation.Yaw, DeltaTime, interpValue),
			FMath::FInterpTo(oldRotator.Roll, whiteRotation.Roll, DeltaTime, interpValue)
		);
		if (newLocation == whiteLocation && newRotator == whiteRotation)
			this->_isMovingCamera = false;
		this->_billBoardCamera->SetRelativeLocation(newLocation);
		this->_billBoardCamera->SetRelativeRotation(newRotator);
	}
	else
	{
		const FVector blackLocation = this->_billBoardWhite->GetRelativeLocation();
		const FRotator blackRotation = this->_billBoardWhite->GetRelativeRotation();

		const FVector newLocation = FVector(
			FMath::FInterpTo(oldLocation.X, blackLocation.X, DeltaTime, interpValue),
			FMath::FInterpTo(oldLocation.Y, blackLocation.Y, DeltaTime, interpValue),
			FMath::FInterpTo(oldLocation.Z, blackLocation.Z, DeltaTime, interpValue)
		);
		const FRotator newRotator = FRotator(
			FMath::FInterpTo(oldRotator.Pitch, blackRotation.Pitch, DeltaTime, interpValue),
			FMath::FInterpTo(oldRotator.Yaw, blackRotation.Yaw, DeltaTime, interpValue),
			FMath::FInterpTo(oldRotator.Roll, blackRotation.Roll, DeltaTime, interpValue)
		);
		if (newLocation == oldLocation && newRotator == oldRotator)
			this->_isMovingCamera = false;
		this->_billBoardCamera->SetRelativeLocation(newLocation);
		this->_billBoardCamera->SetRelativeRotation(newRotator);
	}
}
void ACppChessPlayer::SetPlayerCamera(EPlayerColors colorType)
{
	this->SetActivePlayerColor(colorType);
	this->_isMovingCamera = true;
	//this->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
	//this->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	//this->RootComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//this->RootComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}
FPlayerInformation* ACppChessPlayer::GetPlayerInformation(int index)
{
	if (index == this->_chessPlayerInformations1->playerIndex)
		return this->_chessPlayerInformations1;
		
	return this->_chessPlayerInformations2;
}
FPlayerInformation* ACppChessPlayer::GetPlayerInformation(EPlayerColors colorType)
{
	if (colorType == _chessPlayerInformations1->playerType)
		return this->_chessPlayerInformations1;

	return this->_chessPlayerInformations2;
}
int ACppChessPlayer::GetActivePlayerIndex()
{
	if (this->_activeColor == this->_chessPlayerInformations1->playerType)
		return this->_chessPlayerInformations1->playerIndex;

	return this->_chessPlayerInformations2->playerIndex;
}
FPlayerInformation* ACppChessPlayer::GetActivePlayerInformation()
{
	if (this->_activeColor == this->_chessPlayerInformations1->playerType)
		return this->_chessPlayerInformations1;

	return this->_chessPlayerInformations2;
}
