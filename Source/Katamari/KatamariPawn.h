// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "KatamariPawn.generated.h"

UCLASS()
class KATAMARI_API AKatamariPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AKatamariPawn();

private:

	void InitializeNodule(UStaticMeshComponent* InputMesh, USphereComponent* InputCollider, FVector RelativeLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlapSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlapSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* NoduleStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ball, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// Nodule Static Meshes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh6;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh7;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh8;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh9;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh10;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NoduleMesh11;

	// Nodule Overlap Spheres
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap6;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap7;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap8;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap9;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap10;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nodule, meta = (AllowPrivateAccess = "true"))
	USphereComponent* NoduleOverlap11;

	// Containers for iterative access to nodules
	TArray<UStaticMeshComponent*> NoduleStaticMeshArray;
	TArray<USphereComponent*> NoduleSphereOverlapArray;

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Called to move ball forwards and backwards */
	void MoveForward(float Val);

public:	

	/** Torque to apply when trying to roll ball */
	UPROPERTY(EditAnywhere, Category = Ball)
	float RollTorque;

	UPROPERTY(EditAnywhere, Category = Ball)
	float SphereOverlapRadius;

	UPROPERTY(EditAnywhere, Category = Ball)
	float SphereOverlapSizeIncrease;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns StaticMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetStaticMesh() const { return StaticMesh; }
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};