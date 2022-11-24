// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
#include "AIController.h"


UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}


EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController)
	{
		AShooterCharacter* AIShooter = Cast<AShooterCharacter>(AIController->GetPawn());
		if (AIShooter)
		{
			AIShooter->Shoot();
			return EBTNodeResult::Succeeded;
		}
	}

	

	return EBTNodeResult::Failed;
}