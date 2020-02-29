// Fill out your copyright notice in the Description page of Project Settings.

#include "KatamariPawn.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "ConstructorHelpers.h"
#include "DynamicObject.h"

// Sets default values
AKatamariPawn::AKatamariPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set up sphere radius
	SphereOverlapRadius = 35.0f;

	SphereOverlapSizeIncrease = 0.0005f;

	// Set up forces
	RollTorque = 35000000.0f;

	// Nodule Setup
	NoduleStaticMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StaticMeshes/SphereMesh.SphereMesh'")).Object;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh0"));
	StaticMesh->SetStaticMesh(NoduleStaticMesh);
	StaticMesh->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetAngularDamping(0.1f);
	StaticMesh->SetLinearDamping(0.1f);
	StaticMesh->BodyInstance.MassScale = 10.5f;	
	StaticMesh->BodyInstance.MaxAngularVelocity = 400.0f;
	StaticMesh->SetNotifyRigidBodyCollision(true);
	RootComponent = StaticMesh;	

	float x = 24.5f;
	float z = 24.5f;

	// Setup nodules
	InitializeNodule(NoduleMesh0, NoduleOverlap0, FVector(-x, 0.0f, z));
	InitializeNodule(NoduleMesh1, NoduleOverlap1, FVector(x, 0.0f, z));
	InitializeNodule(NoduleMesh2, NoduleOverlap2, FVector(-x, 0.0f, -z));
	InitializeNodule(NoduleMesh3, NoduleOverlap3, FVector(x, 0.0f, -z));
	InitializeNodule(NoduleMesh4, NoduleOverlap4, FVector(0.0f, z, x));
	InitializeNodule(NoduleMesh5, NoduleOverlap5, FVector(0.0f, z, -x));
	InitializeNodule(NoduleMesh6, NoduleOverlap6, FVector(0.0f, -z, x));
	InitializeNodule(NoduleMesh7, NoduleOverlap7, FVector(0.0f, -z, -x));
	InitializeNodule(NoduleMesh8, NoduleOverlap8, FVector(z, x, 0.0f));
	InitializeNodule(NoduleMesh9, NoduleOverlap9, FVector(-z, x, 0.0f));
	InitializeNodule(NoduleMesh10, NoduleOverlap10, FVector(z, -x, 0.0f));
	InitializeNodule(NoduleMesh11, NoduleOverlap11, FVector(-z, -x, 0.0f));

	// Create a camera boom attached to the root (ball)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bAbsoluteRotation = true; // Rotation of the ball should not affect rotation of boom
	SpringArm->bEnableCameraLag = false;
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->TargetOffset = FVector(0.0f, 0.0f, 300.0f);

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
	Camera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));

	// Create overlap 
	//OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere0"));
	//OverlapSphere->BodyInstance.SetCollisionProfileName(TEXT("OverlapAll"));
	//OverlapSphere->SetupAttachment(StaticMesh);
	//OverlapSphere->bAbsoluteScale = true;
}

void AKatamariPawn::InitializeNodule(UStaticMeshComponent* InputMesh,  USphereComponent* InputCollider, FVector RelativeLocation)
{
	FString MeshName = "NoduleMesh" + FString::FromInt(NoduleStaticMeshArray.Num());
	InputMesh = CreateDefaultSubobject<UStaticMeshComponent>(*MeshName);
	InputMesh->SetStaticMesh(NoduleStaticMesh);
	InputMesh->SetCollisionProfileName(FName("NoCollision"));
	InputMesh->AttachToComponent(StaticMesh, FAttachmentTransformRules::KeepRelativeTransform);
	InputMesh->SetRelativeLocation(RelativeLocation);
	InputMesh->SetRelativeScale3D(FVector(0.38f, 0.38f, 0.38f));
	NoduleStaticMeshArray.Add(InputMesh);

	FString ColliderName = "NoduleCollider" + FString::FromInt(NoduleSphereOverlapArray.Num());
	InputCollider = CreateDefaultSubobject<USphereComponent>(*ColliderName);
	InputCollider->BodyInstance.SetCollisionProfileName(TEXT("OverlapAll"));
	InputCollider->SetSphereRadius(SphereOverlapRadius);
	InputCollider->SetupAttachment(InputMesh);
	InputCollider->bAbsoluteScale = true;
	InputCollider->OnComponentBeginOverlap.AddDynamic(this, &AKatamariPawn::OnComponentBeginOverlapSphere);
	InputCollider->OnComponentEndOverlap.AddDynamic(this, &AKatamariPawn::OnComponentEndOverlapSphere);
	NoduleSphereOverlapArray.Add(InputCollider);
}

// Called when the game starts or when spawned
void AKatamariPawn::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called every frame
void AKatamariPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKatamariPawn::MoveRight(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	StaticMesh->AddTorque(Torque);
}

void AKatamariPawn::MoveForward(float Val)
{
	const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
	StaticMesh->AddTorque(Torque);
}

// Called to bind functionality to input
void AKatamariPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis("MoveRight", this, &AKatamariPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AKatamariPawn::MoveForward);
}

void AKatamariPawn::OnComponentBeginOverlapSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ADynamicObject::StaticClass()))
	{
		// Find the distance to the outside of the nodule that is grabbing this component.
		FVector ClosestPointOnCollision;
		OtherActor->ActorGetDistanceToCollision(OverlappedComponent->GetComponentLocation(), ECollisionChannel::ECC_Camera, ClosestPointOnCollision);
		FVector DirectionToCollision = (ClosestPointOnCollision - OtherActor->GetActorLocation()).GetSafeNormal();
		float DistanceToCollision = FVector::Dist(OtherActor->GetActorLocation(), ClosestPointOnCollision);

		FVector AmountToMoveActor = DirectionToCollision * (DistanceToCollision / 2.0f);
		OtherActor->SetActorLocation(OtherActor->GetActorLocation() + AmountToMoveActor);

		OtherComp->SetSimulatePhysics(false);
		OtherActor->SetActorEnableCollision(false);
		OtherComp->WeldTo(OverlappedComponent);		

		// TODO: Other overlaps arent scaling BIG ISSUE

		StaticMesh->SetWorldScale3D(StaticMesh->GetComponentScale() + (FVector(1.0f) * SphereOverlapSizeIncrease));
		USphereComponent* Temp = Cast<USphereComponent>(OverlappedComponent);
		Temp->SetSphereRadius(Temp->GetUnscaledSphereRadius() + SphereOverlapSizeIncrease);
	}
}

void AKatamariPawn::OnComponentEndOverlapSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}