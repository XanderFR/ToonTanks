// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	/*HitComp component doing the hitting
	OtherActor actor that got hit
	OtherComp other component that got hit
	NormalImpulse physics vector representing the magnitude and direction of that impulse
	Hit information about the hit
	*/

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat") //set this from within blueprint
	class UParticleSystem* HitParticles; //smoke from impact

	UPROPERTY(VisibleAnywhere, Category = "Combat") //access to properties and blueprint
	class UParticleSystemComponent* TrailParticles; //the trail behind the missiles; attachment component to projectile 

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase *HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UMatineeCameraShake> HitCameraShakeClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
