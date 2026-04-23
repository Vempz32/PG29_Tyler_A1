// Copyright Rohit VFS 2023-2024


#include "Predator.h"
#include "Alien.h"  
#include "Engine/World.h"  
#include "Kismet/GameplayStatics.h"  

void APredator::TakeLivingDamage_Implementation()
{
}

void APredator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckForCloseAliens();
}

void APredator::CheckForCloseAliens()
{
	
	if (GetWorld()->GetTimeSeconds() - LastShootTime < 1.0f) return;

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAlien::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
	
		AAlien* Alien = Cast<AAlien>(Actor);
		if (Alien && FVector::Dist(GetActorLocation(), Alien->GetActorLocation()) < 1000.0f)  
		{
			ShootAt(Alien);
			LastShootTime = GetWorld()->GetTimeSeconds();
			break;
		}
	}
}

void APredator::ShootAt(AAlien* Target)
{
	if (Target)
	{

		IDamageInterface::Execute_TakeLivingDamage(Target);

		OnShoot.Broadcast(Target);
	}
}
