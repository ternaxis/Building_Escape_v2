// Copyright Ali Eren Acar 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/LightComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/Light.h"
#include "Engine/SpotLight.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;


private:
float InitialYaw;
float CurrentYaw;

UPROPERTY(EditAnywhere)
float OpenAngle=90.f; 

UPROPERTY(EditAnywhere)
ATriggerVolume* PressurePlate;

UPROPERTY(EditAnywhere)
AActor* ActorThatOpen;

UPROPERTY(EditAnywhere)
ASpotLight* SpotLight;


float DoorLastOpened=0.f;

UPROPERTY(EditAnywhere)
float DoorCloseDelay=2.f;

UPROPERTY(EditAnywhere)
float DoorOpenSpeed=0.8f;

UPROPERTY(EditAnywhere)
float DoorCloseSpeed=2.0f;

UPROPERTY(EditAnywhere)
float CurrentIntensity=0.f;

		
};
