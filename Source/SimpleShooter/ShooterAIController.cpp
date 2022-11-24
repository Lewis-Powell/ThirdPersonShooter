// Fill out your copyright notice in the Description page of Project Settings.



#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

AShooterAIController::AShooterAIController()
{

}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();


	
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		//APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//SetFocus(PlayerPawn);
		//GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


bool AShooterAIController::IsAlive() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		return ControlledCharacter->isAlive();
	}

	//might need to return false
	return true;
}