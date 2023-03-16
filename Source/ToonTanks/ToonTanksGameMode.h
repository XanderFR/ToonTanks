// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent) //give functionality in blueprints
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent) //whether we won or lost through blueprints
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f; //time delay before player can start moving

	void HandleGameStart(); //function to start timer

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount(); //determines number of towers in the world

};
