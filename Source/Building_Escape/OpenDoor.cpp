// Copyright Ali Eren Acar 2021

#include "OpenDoor.h"


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
	targetYaw += InitialYaw;
	CloseYaw = InitialYaw - CloseYaw;
	
	
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


if(PressurePlate->IsOverlappingActor(ActorThatOpen))
	OpenDoor(DeltaTime);




// 	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
// 	FRotator OpenDoor(0.f,CurrentYaw,0.f);
// 	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw,targetYaw,DeltaTime,2);
// 	GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoor::OpenDoor(float DeltaTime){

	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);
	CurrentYaw = FMath::Lerp(CurrentYaw,targetYaw,DeltaTime*0.5f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw=CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

}
