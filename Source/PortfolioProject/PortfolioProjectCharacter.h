// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PortfolioProjectCharacter.generated.h"


UCLASS(config=Game)
class APortfolioProjectCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	APortfolioProjectCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* WeaponBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* WeaponRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	USkeletalMeshComponent* PlayerSkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* WidgetScene;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MouseSensitivity = 10.0; //마우스 감도
protected:


	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Rate);
	void LookUp(float Rate);
public:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
};

