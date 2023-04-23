//#include "CoreMinimal.h"
//#include "Engine/Texture2D.h"
#include "EnumClass.Generated.h"

class UTexture2D;

UENUM(BlueprintType)
enum class EPlayerColors : uint8
{
	White UMETA(DisplayName = "White"),
	Black UMETA(DisplayName = "Black"),
};
UENUM(BlueprintType)
enum class EChessPieceTypes : uint8
{
	King UMETA(DisplayName = "King"), // Raja
	Queen UMETA(DisplayName = "Queen"), // Mantri
	Bishop UMETA(DisplayName = "Bishop"), // Uta
	Knight UMETA(DisplayName = "Knight"), // Ghoda
	Rook UMETA(DisplayName = "Rook"), // Hatti
	Pawn UMETA(DisplayName = "Pawn"), // Piuso
};
UENUM(BlueprintType)
enum class EGameMenuTypes : uint8
{
	None UMETA(DisplayName = "None"),
	StartMenu UMETA(DisplayName = "StartMenu"),
	PauseMenu UMETA(DisplayName = "PauseMenu"),
	PauseMenuAfterGiveUp UMETA(DisplayName = "PauseMenuAfterGiveUp"),
	LoseMenu UMETA(DisplayName = "LoseMenu"),
	WinnerMenu UMETA(DisplayName = "WinnerMenu"),
};
UENUM(BlueprintType)
enum class EMaterialTypes : uint8
{
	BlackBoard UMETA(DisplayName = "BlackBoard"),
	WhiteBoard UMETA(DisplayName = "WhiteBoard"),
	BlackPiece UMETA(DisplayName = "BlackPiece"),
	WhitePiece UMETA(DisplayName = "WhitePiece"),
	MarkerAttack UMETA(DisplayName = "MarkerAttack"),
	MarkerPiece UMETA(DisplayName = "MarkerPiece"),
	MarkerHighlight UMETA(DisplayName = "MarkerHighlight"),
	MarkerSelected UMETA(DisplayName = "MarkerSelected"),
};
