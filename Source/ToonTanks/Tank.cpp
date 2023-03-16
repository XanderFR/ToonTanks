// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move); //this points to tank instance in the game
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false,
            HitResult);

        RotateTurret(HitResult.ImpactPoint); //rotate tank turret towards cursor
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction(); //get visual and sound fx
    SetActorHiddenInGame(true); //hide tank rather than destroy it
    SetActorTickEnabled(false); //disable tick functionality so it exists in world, player still possess it but no see it or move around
    bAlive = false;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController()); //reference to player controller
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector; //prepare a zero vector
    //X = Value * DeltaTime * Speed
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); //modify x value, make smooth movement
    AddActorLocalOffset(DeltaLocation, true); //move tank based on vector values; true associated with sweeping(collison)
}

void ATank::Turn(float Value) 
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    //Yaw - Value * DeltaTime * TurnRate
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true); //turn tank, sweeping enabled
}