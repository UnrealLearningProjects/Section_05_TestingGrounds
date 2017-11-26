// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds_CharacterCPP.h"
#include "Camera/CameraComponent.h"
#include "Weapons/WeaponBaseCPP.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Weapons/Udemy_TestingGroundsProjectile.h"

// Sets default values
ATestingGrounds_CharacterCPP::ATestingGrounds_CharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FP_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FP_Camera->SetupAttachment(GetCapsuleComponent());
	FP_Camera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FP_Camera->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	FP_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterFP_Mesh"));
	FP_Mesh->SetOnlyOwnerSee(true);
	FP_Mesh->SetupAttachment(FP_Camera);
	FP_Mesh->bCastDynamicShadow = false;
	FP_Mesh->CastShadow = false;
	FP_Mesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FP_Mesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void ATestingGrounds_CharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	
	if (GunBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun Blueprint missing"));
		return;
	}
	Gun = GetWorld()->SpawnActor<AWeaponBaseCPP>(GunBlueprint);
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	Gun->AttachToComponent(FP_Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	Gun->AnimInstance = FP_Mesh->GetAnimInstance();

	if (InputComponent != NULL)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &ATestingGrounds_CharacterCPP::PullTrigger);
	}

}

// Called every frame
void ATestingGrounds_CharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestingGrounds_CharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATestingGrounds_CharacterCPP::PullTrigger()
{
	Gun->OnFire();
}

