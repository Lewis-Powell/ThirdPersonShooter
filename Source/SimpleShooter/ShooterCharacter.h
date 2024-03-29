// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure) //BlueprintPure is blueprintcallable with some other stuff
		bool isAlive() const;
	
	UFUNCTION(BlueprintPure) //BlueprintPure is blueprintcallable with some other stuff
		float GetHPPercent() const;

	void Shoot();

private:

	
	///Movement Functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	///Other Functions
	

	//UPROPERTY Variables
	UPROPERTY(EditAnywhere)
		float RotationRightRate = 10.0f;
	UPROPERTY(EditAnywhere)
		float RotationUpRate = 10.0f;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;
	UPROPERTY()
		AGun* Gun;
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
		float Health;

	bool bAlive = true;


	//C++ Variables


};
