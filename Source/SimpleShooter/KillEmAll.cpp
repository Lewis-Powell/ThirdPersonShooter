// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAll.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAll::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		//Game over for player
		EndGame(false);

	}

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (Controller->IsAlive())
		{
			return;
		}
	}

	EndGame(true);

	//for loop
	// is not dead
	//early return if any AI is alive
	//if we can get through we need to end game

	UE_LOG(LogTemp, Warning, TEXT("Pawn Killed"));
}


void AKillEmAll::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
		/*if (bIsPlayerWinner)
		{
			Controller->GameHasEnded(nullptr, bIsPlayerController);
		}
		else
		{
			Controller->GameHasEnded(nullptr, !bIsPlayerController);
		}*/
	}
}