// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank) //if the tank dies
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController) //if tank connected to player controller
        {
            // Tank->DisableInput(Tank->GetTankPlayerController()); //disable player controller input
            // Tank->GetTankPlayerController()->bShowMouseCursor = false; //make sure mouse cursor is not shown
            ToonTanksPlayerController->SetPlayerEnabledState(false); //disable input and stop showing cursor
        }
        GameOver(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)) //if the tower dies
    {
        DestroyedTower->HandleDestruction(); //destroy the tower
        --TargetTowers;  //reduce tower count
        if (TargetTowers == 0) //if there are no more towers left in the world
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); //represents player tank
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0)); //sets the value of toon tank player controller

    StartGame();

    if (ToonTanksPlayerController) //if tank and playercontroller are connected
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false); //tank can't move

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true //at the end of the time delay true get plugged into callback function above
        );
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay, //time delay
            false //if timer loops
        );
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    /*
    this = the game world context object
    ATower::StaticClass = the actor class
    Towers = output for the function, holds pointer for all actors of specified class*/
    return Towers.Num(); //return number of tower pointers in the array
}
