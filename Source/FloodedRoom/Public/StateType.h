UENUM(BlueprintType)
enum StateType {
	Default = 0	UMETA(DisplayName = "Default state"),
	Overlap = 1	UMETA(DisplayName = "Overlap state"),
	Interaction = 2	UMETA(DisplayName = "Interaction state"),
	EndGame = 3	UMETA(DisplayName = "EndGame state"),
};