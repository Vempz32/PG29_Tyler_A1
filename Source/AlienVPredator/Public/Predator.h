// Copyright Rohit VFS 2023-2024

#pragma once

#include "CoreMinimal.h"
#include "LivingOrganism.h"
#include "DamageInterface.h"
#include "Predator.generated.h"

/**
 * 
 */
class AAlien;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPredatorShootEvent, AAlien*, TargetAlien);

UCLASS()
class ALIENVPREDATOR_API APredator : public ALivingOrganism , public IDamageInterface
{
	GENERATED_BODY()

public:

	void TakeLivingDamage_Implementation() override;

	UPROPERTY(BlueprintAssignable, Category = "Predator")
	FOnPredatorShootEvent OnShoot;  

	virtual void Tick(float DeltaTime) override;

private:

	void CheckForCloseAliens(); 
	void ShootAt(AAlien* Target); 
	float LastShootTime = 0.0f;  
	
};
