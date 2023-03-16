// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Find the distance to the Tank
    if (InFireRange()) 
    {
        RotateTurret(Tank->GetActorLocation()); //rotate the turret
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction(); //super function of base pawn gets called for sound and vfx
    Destroy(); //destroys the tower
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); //access Tank

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true); //2 second timer, fire every 2 seconds
}

void ATower::CheckFireCondition()
{
    if (Tank == nullptr)
    {
        return;
    }
    if (InFireRange() && Tank->bAlive)
    {
        Fire();
    }
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation()); //distance between tank and tower turret
        if (Distance <= FireRange) //Check to see if the Tank is in range
        {
            return true;
        }
    }

    return false;
}