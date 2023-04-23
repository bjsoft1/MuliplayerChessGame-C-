// Fill out your copyright notice in the Description page of Project Settings.


#include "CppChessPlayer.h"
#include "Components/BillBoardComponent.h"
#include "Camera/CameraComponent.h"
//------------------------------
#include "EnumClass.h"
#include "CppWidgetInformation.h"

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

	this->_chessPlayerInformations1.captures = 0;
	this->_chessPlayerInformations1.isCheck = false;
	this->_chessPlayerInformations1.isLegalMoves = true;
	this->_chessPlayerInformations1.moveCount = 0;
	this->_chessPlayerInformations1.iswatcher = false;
	this->_chessPlayerInformations1.playerIndex = 0;
	this->_chessPlayerInformations1.playerName = "Bijay Adhikari";
	this->_chessPlayerInformations1.playerType = EPlayerColors::White;

	this->_chessPlayerInformations2.captures = 0;
	this->_chessPlayerInformations2.isCheck = false;
	this->_chessPlayerInformations2.isLegalMoves = true;
	this->_chessPlayerInformations2.moveCount = 0;
	this->_chessPlayerInformations2.iswatcher = false;
	this->_chessPlayerInformations2.playerIndex = 1;
	this->_chessPlayerInformations2.playerName = "Amit Shrestha";
	this->_chessPlayerInformations2.playerType = EPlayerColors::Black;
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

	if (this->_widgetInformation)
	{	
		UE_LOG(LogTemp, Warning, TEXT("%s"), &this->_chessPlayerInformations1.playerName);

		// Set Player Name
		this->_widgetInformation->SetPlayerName(this->_chessPlayerInformations1.playerType, this->_chessPlayerInformations1.playerName);
		this->_widgetInformation->SetPlayerName(this->_chessPlayerInformations2.playerType, this->_chessPlayerInformations2.playerName);

		// Set Default Color
		this->_widgetInformation->SetPlayerColor();

		// Set Default Indicator
		this->_widgetInformation->SetPlayerBorderIndicator(EPlayerColors::White);

		// Set Default Capture Count
		this->_widgetInformation->SetPlayerCapturesCount(EPlayerColors::White, 0);
		this->_widgetInformation->SetPlayerCapturesCount(EPlayerColors::Black, 0);

		// Set Default Check Status
		this->_widgetInformation->SetPlayerCheckStatus(EPlayerColors::White, false);
		this->_widgetInformation->SetPlayerCheckStatus(EPlayerColors::Black, false);

		// Set Profile Picture
		//this->_widgetInformation->SetPlayerImage(_chessPlayerInformations1.playerType, _chessPlayerInformations1.profilePicture);
		//this->_widgetInformation->SetPlayerImage(_chessPlayerInformations2.playerType, _chessPlayerInformations2.profilePicture);
	}
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
		const FVector BlackLocation = this->_billBoardBlack->GetRelativeLocation();
		const FRotator BlackRotation = this->_billBoardBlack->GetRelativeRotation();

		const FVector newLocation = FVector(
			FMath::FInterpTo(oldLocation.X, BlackLocation.X, DeltaTime, interpValue),
			FMath::FInterpTo(oldLocation.Y, BlackLocation.Y, DeltaTime, interpValue),
			FMath::FInterpTo(oldLocation.Z, BlackLocation.Z, DeltaTime, interpValue)
		);
		const FRotator newRotator = FRotator(
			FMath::FInterpTo(oldRotator.Pitch, BlackRotation.Pitch, DeltaTime, interpValue),
			FMath::FInterpTo(oldRotator.Yaw, BlackRotation.Yaw, DeltaTime, interpValue),
			FMath::FInterpTo(oldRotator.Roll, BlackRotation.Roll, DeltaTime, interpValue)
		);
		if (newLocation == BlackLocation && newRotator == BlackRotation)
			this->_isMovingCamera = false;
		this->_billBoardCamera->SetRelativeLocation(newLocation);
		this->_billBoardCamera->SetRelativeRotation(newRotator);
	}
}
void ACppChessPlayer::SetPlayerCamera(EPlayerColors colorType)
{
	this->_activeColor = colorType;
	this->_isMovingCamera = true;
}
FPlayerInformation ACppChessPlayer::GetPlayerInformation(int index)
{
	if (index == this->_chessPlayerInformations1.playerIndex)
		return this->_chessPlayerInformations1;
		
	return this->_chessPlayerInformations2;
}
FPlayerInformation ACppChessPlayer::GetPlayerInformation(EPlayerColors colorType)
{
	if (colorType == _chessPlayerInformations1.playerType)
		return this->_chessPlayerInformations1;

	return this->_chessPlayerInformations2;
}
int ACppChessPlayer::GetActivePlayerIndex()
{
	if (this->_activeColor == this->_chessPlayerInformations1.playerType)
		return this->_chessPlayerInformations1.playerIndex;

	return this->_chessPlayerInformations2.playerIndex;
}
FPlayerInformation ACppChessPlayer::GetActivePlayerInformation()
{
	if (this->_activeColor == this->_chessPlayerInformations1.playerType)
		return this->_chessPlayerInformations1;

	return this->_chessPlayerInformations2;
}
void ACppChessPlayer::SetPlayerMoveCount(EPlayerColors colorType, bool isReset)
{
	if (colorType == this->_chessPlayerInformations1.playerType)
	{
		if (isReset)
			this->_chessPlayerInformations1.moveCount = 0;
		else
			this->_chessPlayerInformations1.moveCount++;
		if (this->_widgetInformation)
			this->_widgetInformation->SetPlayerMoveCount(colorType, this->_chessPlayerInformations1.moveCount);
	}
	else
	{
		if (isReset)
			this->_chessPlayerInformations2.moveCount = 0;
		else
			this->_chessPlayerInformations2.moveCount++;

		if (this->_widgetInformation)
			this->_widgetInformation->SetPlayerMoveCount(colorType, this->_chessPlayerInformations2.moveCount);
	}
}
int ACppChessPlayer::GetPlayerMoveCount(EPlayerColors colorType)
{
	if (colorType == this->_chessPlayerInformations1.playerType)
		return this->_chessPlayerInformations1.moveCount;
	else
		return this->_chessPlayerInformations2.moveCount;
}
void ACppChessPlayer::SetPlayerCaptureCount(EPlayerColors colorType)
{
	if (colorType == this->_chessPlayerInformations1.playerType)
	{
		this->_chessPlayerInformations1.captures++;
		if (this->_widgetInformation)
			this->_widgetInformation->SetPlayerCapturesCount(colorType, this->_chessPlayerInformations1.captures);
	}
	else
	{
		this->_chessPlayerInformations2.captures++;
		if (this->_widgetInformation)
			this->_widgetInformation->SetPlayerCapturesCount(colorType, this->_chessPlayerInformations2.captures);
	}
}
int ACppChessPlayer::GetPlayerCaptureCount(EPlayerColors colorType)
{
	if (colorType == this->_chessPlayerInformations1.playerType)
		return this->_chessPlayerInformations1.captures;
	else
		return this->_chessPlayerInformations2.captures;
}
void ACppChessPlayer::SetPlayerCheckFlag(EPlayerColors colorType, bool isCheckFlag)
{
	if (colorType == this->_chessPlayerInformations1.playerType)
		this->_chessPlayerInformations1.isCheck = isCheckFlag;
	else
		this->_chessPlayerInformations2.isCheck = isCheckFlag;
	
	if (this->_widgetInformation)
		this->_widgetInformation->SetPlayerCheckStatus(colorType, isCheckFlag);
}
void ACppChessPlayer::SetPlayerIndicator()
{
	if (this->_widgetInformation)
		this->_widgetInformation->SetPlayerBorderIndicator(this->_activeColor);
}
bool ACppChessPlayer::GetPlayerCheckFlag(EPlayerColors colorType)
{
	if (colorType == this->_chessPlayerInformations1.playerType)
		return this->_chessPlayerInformations1.isCheck;
	else
		return this->_chessPlayerInformations2.isCheck;
}
