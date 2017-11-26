// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestingGrounds_CharacterCPP.generated.h"

UCLASS()
class UDEMY_TESTINGGROUNDS_API ATestingGrounds_CharacterCPP : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ATestingGrounds_CharacterCPP();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AWeaponBaseCPP> GunBlueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UnPossessed() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullTrigger();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FP_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	AWeaponBaseCPP* Gun;

	UPROPERTY(VisibleDefaultsOnly)
	class USkeletalMeshComponent* FP_Mesh;

};
