// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

#define ECC_Spawn ECC_GameTraceChannel2

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
    //// ############################## start ################################## //
    ////FVector Min(0, -2000, 0);
    ////FVector Max(4000, 2000, 0);
    //// ################################ end ################################ //
    //FVector Min = GetActorTransform().TransformPosition(FVector(0, -2000, 0));
    //FVector Max = GetActorTransform().TransformPosition(FVector(4000, 2000, 0));
    //FBox Bounds(Min, Max);
    //int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
    //for (size_t i = 0; i < NumberToSpawn; i++)
    //{
    //    FVector SpawnPoint = FMath::RandPointInBox(Bounds);
    //    UE_LOG(LogTemp, Warning, TEXT("SpawnPoint: %s"), *SpawnPoint.ToCompactString());
    //    AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
    //    Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    //    // ############################## start ################################## //
    //    //FVector StartTrace = Spawned->GetActorLocation();
    //    //GetWorld()->LineTraceSingleByChannel(*hitResult, SpawnPoint, EndTrace, ECC_Visibility);
    //    //Spawned->SetActorRelativeLocation(SpawnPoint);
    //    //Trying to automatically detect the ground via hitResult
    //    //FTransform Pos1 = GetActorTransform();
    //    //FVector Pos2 = GetActorTransform().TransformPosition(Min);
    //    //UE_LOG(LogTemp, Warning, TEXT("Pos1: %s"), *Pos1.ToString());
    //    //UE_LOG(LogTemp, Warning, TEXT("Pos2: %s"), *Pos2.ToString());
    //    // ################################ end ################################ //
    //    FVector StartTrace = Spawned->GetActorLocation();
    //    //FVector EndTrace = StartTrace - FVector(0, 0, 200);
    //    FVector EndTrace = SpawnPoint - FVector(0, 0, 200);
    //    FHitResult hitResult;
    //    // ############################## start ################################## //
    //    //FHitResult* hitResult2 = new FHitResult();
    //    //DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true, -1, 0, 10);
    //    //DrawDebugLine(GetWorld(), SpawnPoint, SpawnPoint-FVector(0, 0, 200), FColor::Green, true, -1, 0, 10);
    //    //FCollisionQueryParams CollisionParameters;
    //    ////TArray<AActor*> ignoredActors;
    //    ////ignoredActors.Add(Spawned);
    //    ////CollisionParameters.AddIgnoredActors(ignoredActors);
    //    //Spawned->ActorLineTraceSingle(hitResult, SpawnPoint, SpawnPoint - FVector(0, 0, 200), ECC_Visibility, CollisionParameters);
    //    // ################################ end ################################ //
    //    GetWorld()->LineTraceSingleByChannel(hitResult, SpawnPoint, EndTrace, ECC_Visibility);
    //    UE_LOG(LogTemp, Warning, TEXT("HitPoint: %s"), *hitResult.ToString());
    //    // ############################## start ################################## //
    //    //UE_LOG(LogTemp, Warning, TEXT("HitPoint: %s"), *hitResult2->ToString());
    //    //Spawned->SetActorRelativeLocation(hitResult.Location);
    //    //Spawned->SetActorRelativeLocation(hitResult2->Location);
    //    //Spawned->SetActorLocation(hitResult2->Location);
    //    // ################################ end ################################ //
    //    Spawned->SetActorLocation(hitResult.Location);
    //    SpawnedActors.Add(Spawned);
    //    // ############################## start ################################## //
    //    //Spawned->AddActorLocalOffset(FVector(0, 0, -120));
    //    // ################################ end ################################ //
    //}
    int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
    for (size_t i = 0; i < NumberToSpawn; i++)
    {
        FVector SpawnPoint = GetEmptyLocation(Radius);
        PlaceActor(ToSpawn, SpawnPoint);
    }
}

FVector ATile::GetEmptyLocation(float Radius)
{
    FVector Min = GetActorTransform().TransformPosition(FVector(0, -2000, 0));
    FVector Max = GetActorTransform().TransformPosition(FVector(4000, 2000, 0));
    FBox Bounds(Min, Max);

    return FMath::RandPointInBox(Bounds);
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
    AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
    Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    FVector StartTrace = Spawned->GetActorLocation();
    FVector EndTrace = SpawnPoint - FVector(0, 0, 200);
    FHitResult hitResult;
    GetWorld()->LineTraceSingleByChannel(hitResult, SpawnPoint, EndTrace, ECC_Visibility);
    UE_LOG(LogTemp, Warning, TEXT("HitPoint: %s"), *hitResult.ToString());
    Spawned->SetActorLocation(hitResult.Location);
    SpawnedActors.Add(Spawned);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
    //CastSphere(GetActorLocation(), 300);
    //CastSphere(GetActorLocation() + FVector(0, 0, 1000), 300);
    CastSphere(GetActorLocation() + FVector(4000, 0, 0), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CastSphere(FVector Location, float Radius)
{
    FHitResult HitResult;
    bool HasHit = GetWorld()->SweepSingleByChannel(
                            HitResult,
                            Location,
                            Location,
                            FQuat::Identity,
                            ECollisionChannel::ECC_Spawn,
                            FCollisionShape::MakeSphere(Radius));
    FColor ResultColor = HasHit ? FColor::Red : FColor::Green; // this reads "if HasHit then Red, else Green"
    DrawDebugSphere(GetWorld(), Location, Radius, 26, ResultColor, true, -1, 0, 2);
    return HasHit;
}

void ATile::Destroyed()
{
    Super::Destroyed();
    if (SpawnedActors.Num() > 0)
    {
        for (AActor* Actor : SpawnedActors)
        {
            Actor->Destroy();
        }
    }
    
}