// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

USTRUCT(BlueprintType)
struct FSpawnPositionProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spawning Props")
	int MinSpawn; 
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spawning Props")
	int MaxSpawn; 
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spawning Props")
	float Radius; 
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spawning Props")
	float MinScale; 
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Spawning Props")
	float MaxScale;

	FSpawnPositionProperties()
	{
		MinSpawn = 1;
		MaxSpawn = 1;
		MinScale = 1;
		MaxScale = 1;
		Radius = 500;
	}
};

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, const FSpawnPositionProperties& Properties);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, const FSpawnPositionProperties& Properties);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

private:
	void PositionNavMeshBoundsVolume();

	bool FindEmptyLocation(FVector& OutLocation, float Radius);
	
	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, const FSpawnPositionProperties& Properties);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;
	
};
