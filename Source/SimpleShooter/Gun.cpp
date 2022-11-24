// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
//#include "Sound/SoundBase.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_RootComponet = CreateDefaultSubobject<USceneComponent>(TEXT("m_RootComponent"));
	SetRootComponent(m_RootComponet);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(m_RootComponet);



}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGun::PullTrigger()
{
	//UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"), FVector::ZeroVector, FRotator::ZeroRotator, FVector(1,1,1), EAttachLocation::KeepRelativeOffset, bool false);

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	//UGameplayStatics::PlaySoundAtLocation(this, GunSoundBase)
	
	FHitResult Hit;
	FVector ShotDirection;

	bool bHitResult = GunTrace(Hit, ShotDirection);

	if (bHitResult)
	{
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			FPointDamageEvent DmgEvent = FPointDamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DmgEvent, OwnerController, this);
		}
	}
	

	//UE_LOG(LogTemp, Warning, TEXT("You've Been Shot"));
}

void AGun::ReleaseTrigger()
{
	
}


bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}
	FVector Loc;
	FRotator Rot;
	OwnerController->GetPlayerViewPoint(Loc, Rot);
	//DrawDebugCamera(GetWorld(), Loc, Rot, 90, 2, FColor::White, true);

	FVector End = Loc + Rot.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	ShotDirection = -Rot.Vector();
	return GetWorld()->LineTraceSingleByChannel(Hit, Loc, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
}


AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}
	return OwnerPawn->GetController();
	
}