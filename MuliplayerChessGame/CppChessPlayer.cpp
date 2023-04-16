// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessPlayer.h"
//#include "Components/BillBoardComponent.h"
#include "Camera/CameraComponent.h"
//------------------------------
#include "EnumClass.h"

ACppChessPlayer::ACppChessPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//this->_billBoardBlack = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoardBlack"));
	//this->_billBoardBlack->SetupAttachment(AActor::RootComponent);
	//this->_billBoardBlack->SetVisibility(false);
	//this->_billBoardBlack->SetRelativeLocation(FVector(-250.0f, 0.0f, 0.0f));
	//this->_billBoardBlack->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	//
	//
	//this->_billBoardWhite = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoardWhite"));
	//this->_billBoardWhite->SetupAttachment(AActor::RootComponent);
	//this->_billBoardWhite->SetVisibility(false);
	//this->_billBoardWhite->SetRelativeLocation(FVector(250.0f, 0.0f, 0.0f));
	//this->_billBoardWhite->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

	this->_rootCamere = CreateDefaultSubobject<UCameraComponent>(TEXT("RootCamera"));
	this->_rootCamere->SetupAttachment(AActor::RootComponent);
	this->_rootCamere->SetRelativeLocation(FVector(-500.0f, 0.0f, 1.0f));
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
	
}
void ACppChessPlayer::SetLocationRotation()
{
	const FVector oldLocation = this->_rootCamere->GetRelativeLocation();
	const FRotator oldRotator = this->_rootCamere->GetRelativeRotation();
	float interpValue = 2.5f;
	if (this->_activeColor == EPlayerColors::White)
	{
		const FVector newLocation = FVector(
			FMath::FInterpTo(oldLocation.X, this->_whiteLocation.X, GetWorld()->GetDeltaSeconds(), interpValue),
			FMath::FInterpTo(oldLocation.Y, this->_whiteLocation.Y, GetWorld()->GetDeltaSeconds(), interpValue),
			FMath::FInterpTo(oldLocation.Z, this->_whiteLocation.Z, GetWorld()->GetDeltaSeconds(), interpValue)
		);
		const FRotator newRotator = FRotator(
			FMath::FInterpTo(oldRotator.Pitch, this->_whiteRotation.Pitch, GetWorld()->GetDeltaSeconds(), interpValue),
			FMath::FInterpTo(oldRotator.Yaw, this->_whiteRotation.Yaw, GetWorld()->GetDeltaSeconds(), interpValue),
			FMath::FInterpTo(oldRotator.Roll, this->_whiteRotation.Roll, GetWorld()->GetDeltaSeconds(), interpValue)
		);
		if (newLocation == oldLocation && newRotator == oldRotator)
			this->_isMovingCamera = false;
		this->_rootCamere->SetRelativeLocation(newLocation);
		this->_rootCamere->SetRelativeRotation(newRotator);
	}
	else
	{
		const FVector newLocation = FVector(
			FMath::FInterpTo(oldLocation.X, this->_blackLocation.X, GetWorld()->GetDeltaSeconds(), interpValue),
			FMath::FInterpTo(oldLocation.Y, this->_blackLocation.Y, GetWorld()->GetDeltaSeconds(), interpValue),
			FMath::FInterpTo(oldLocation.Z, this->_blackLocation.Z, GetWorld()->GetDeltaSeconds(), interpValue)
		);
		const FRotator newRotator = FRotator(
			FMath::FInterpTo(oldRotator.Pitch, this->_blackRotation.Pitch, GetWorld()->GetDeltaSeconds(), interpValue),
			FMath::FInterpTo(oldRotator.Yaw, this->_blackRotation.Yaw, GetWorld()->GetDeltaSeconds(), interpValue),
			FMath::FInterpTo(oldRotator.Roll, this->_blackRotation.Roll, GetWorld()->GetDeltaSeconds(), interpValue)
		);
		if (newLocation == oldLocation && newRotator == oldRotator)
			this->_isMovingCamera = false;
		this->_rootCamere->SetRelativeLocation(newLocation);
		this->_rootCamere->SetRelativeRotation(newRotator); 
	}
}
void ACppChessPlayer::SetPlayerCamera(EPlayerColors colorType)
{
	this->SetActivePlayerColor(colorType);
	this->_isMovingCamera = true;
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
void ACppChessPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->_isMovingCamera)
		this->SetLocationRotation();
}
