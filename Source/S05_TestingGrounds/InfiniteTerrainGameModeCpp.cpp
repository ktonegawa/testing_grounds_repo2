// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameModeCpp.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameModeCpp::AInfiniteTerrainGameModeCpp()
{
    NaveMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrainGameModeCpp::PopulateBoundsVolumePool()
{
    TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
    //auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
    while (VolumeIterator)
    {
        //AActor* FoundActor = *VolumeIterator;
        AddToPool(*VolumeIterator);
        ++VolumeIterator; // go to next item in iterator
    }
}

void AInfiniteTerrainGameModeCpp::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
    UE_LOG(LogTemp, Warning, TEXT("FoundActor: %s"), *VolumeToAdd->GetName());
    NaveMeshBoundsVolumePool->Add(VolumeToAdd);
}