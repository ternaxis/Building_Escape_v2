// Copyright Ali Eren Acar 2021


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"



#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandle();
	InputCheck();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	if(PhysicsHandle->GrabbedComponent){
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}

}


void UGrabber::InputCheck(){

InputGrab = GetOwner()-> FindComponentByClass<UInputComponent>();

	if(InputGrab){
		UE_LOG(LogTemp, Error, TEXT("Input handle is found!"),*GetOwner()->GetName());
		InputGrab->BindAction("Grab",IE_Pressed, this, &UGrabber::Grab);
		InputGrab->BindAction("Grab",IE_Released, this, &UGrabber::Release);
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("Input handle is MISSING!"),*GetOwner()->GetName());
	}

}

void UGrabber::FindPhysicsHandle(){

PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();

	if(PhysicsHandle==nullptr){
		UE_LOG(LogTemp, Error, TEXT("Physics handle is not found! Corrupted object is: %s"),*GetOwner()->GetName());
	}

}

void UGrabber::Grab(){

	

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	if(HitResult.GetActor())
	PhysicsHandle->GrabComponentAtLocation(
		ComponentToGrab,
		NAME_None,
		GetLineTraceEnd()
	);
}

void UGrabber::Release(){
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const{

		FHitResult Hit;

		FCollisionQueryParams TraceParams(FName(TEXT(" ")),false,GetOwner());

		bool isHit = GetWorld()->LineTraceSingleByObjectType(
			OUT Hit,
			GetPlayersWorldPosition(),
			GetLineTraceEnd(),
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
		);

		return Hit;

}

FVector UGrabber::GetLineTraceEnd() const{
	
	FVector Location;
	FRotator Rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT Location,
		OUT Rotation
		);
	
		return Location + Rotation.Vector() * reach;

}

FVector UGrabber::GetPlayersWorldPosition() const{
	

	FVector Location;
	FRotator Rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT Location,
		OUT Rotation
		);

		return Location;

}

