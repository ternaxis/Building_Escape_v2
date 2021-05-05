// Copyright Ali Eren Acar 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	float reach=100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputGrab = nullptr;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void InputCheck();
	//Return the first actor within reach with physics body.
	FHitResult GetFirstPhysicsBodyInReach() const;
	//Return line trace end.
	FVector GetLineTraceEnd() const;
	//Return player position.
	FVector GetPlayersWorldPosition() const;
	

};
