// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleHitEnemy.h"

// Sets default values
ADoubleHitEnemy::ADoubleHitEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoubleHitEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoubleHitEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

