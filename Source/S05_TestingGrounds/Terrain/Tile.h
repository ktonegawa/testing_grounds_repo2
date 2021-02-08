// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

    UFUNCTION(BlueprintCallable, Category = "Character")
    void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpaw, float Radius = 500);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // To delete all invalid props
	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    FVector GetEmptyLocation(float Radius);

    void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint);
    
    TArray<AActor*> SpawnedActors;

    bool CastSphere(FVector Location, float Radius);
	
};
