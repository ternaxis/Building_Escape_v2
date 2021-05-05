// Copyright Ali Eren Acar 2021

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;
	
	if(!PressurePlate)
	UE_LOG(LogTemp,Warning,TEXT("%s has the open door component on it, but PressurePlate not set!"));
	
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();

	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

if(TotalMassOfActors()> 50.f)
{
	OpenDoor(DeltaTime);
	DoorLastOpened = GetWorld()->GetTimeSeconds();
	CurrentIntensity = FMath::Lerp(CurrentIntensity,50.f,DeltaTime*DoorOpenSpeed);
	SpotLight->GetLightComponent()->SetIntensity(CurrentIntensity);


}else
{ 
	if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay )
	CloseDoor(DeltaTime);
	CurrentIntensity = FMath::Lerp(CurrentIntensity,0.f,DeltaTime*DoorCloseSpeed);
	SpotLight->GetLightComponent()->SetIntensity(CurrentIntensity);

}

//UE_LOG(LogTemp, Warning, TEXT("%f"), DoorLastOpened);



// 	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
// 	FRotator OpenDoor(0.f,CurrentYaw,0.f);
// 	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw,OpenAngle,DeltaTime,2);
// 	GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoor::OpenDoor(float DeltaTime){

	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
	CurrentYaw = FMath::Lerp(CurrentYaw,OpenAngle,DeltaTime*0.8f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	

}

void UOpenDoor::CloseDoor(float DeltaTime){

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
	CurrentYaw = FMath::Lerp(CurrentYaw,InitialYaw,DeltaTime*1.f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

}

float UOpenDoor::TotalMassOfActors() const{
	float TotalMass = 0;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	return TotalMass;
}