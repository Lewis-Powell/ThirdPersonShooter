// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUDScreen = CreateWidget(this, HUDScreenClass);
	if (HUDScreen)
	{
		HUDScreen->AddToViewport();
	}
}


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (HUDScreen)
	{
		HUDScreen->RemoveFromViewport();
	}
	UE_LOG(LogTemp, Warning, TEXT("We have finished."));
	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			if (HUDScreen)
			{
				HUDScreen->RemoveFromViewport();
			}
			LoseScreen->AddToViewport();
		}
	}
	

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}