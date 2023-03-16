// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if (bPlayerEnabled)
    {
        GetPawn()->EnableInput(this); //gets the pawn the player controller is possessing; enable input
    }
    else
    {
        GetPawn()->DisableInput(this); //disable input
    }
    bShowMouseCursor = bPlayerEnabled; //controlls visibility of mouse cursor
}
