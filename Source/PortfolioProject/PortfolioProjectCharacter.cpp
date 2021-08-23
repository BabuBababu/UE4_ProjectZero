// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// APortfolioProjectCharacter

APortfolioProjectCharacter::APortfolioProjectCharacter()
{
	// 컴포넌트 초기화
	RootComponent = GetCapsuleComponent();
	
	WeaponBack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponBack"));
	WeaponRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponRight"));
	PlayerSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletalMesh"));
	SpringArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera= CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	WidgetScene= CreateDefaultSubobject<USceneComponent>(TEXT("WidgetScene"));

	PlayerSkeletalMesh->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);
	WeaponBack->AttachToComponent(PlayerSkeletalMesh,FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponBack"));
	WeaponRight->AttachToComponent(PlayerSkeletalMesh,FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponRight"));
	SpringArm->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);
	
	Camera->AttachToComponent(SpringArm,FAttachmentTransformRules::KeepWorldTransform);
	WidgetScene->AttachToComponent(Camera,FAttachmentTransformRules::KeepWorldTransform);
	// 콜리전 캡슐 사이즈 초기화
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	SpringArm->bUsePawnControlRotation = true;

	
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>
		(GetCharacterMovement());


}

//////////////////////////////////////////////////////////////////////////
// Input

void APortfolioProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APortfolioProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APortfolioProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APortfolioProjectCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APortfolioProjectCharacter::LookUp);

}


void APortfolioProjectCharacter::Turn(float Rate)
{
	// calculate delta for this frame from the rate information, Rate옆에 상수값 곱해서 감도조절
	AddControllerYawInput(Rate*MouseSensitivity* GetWorld()->GetDeltaSeconds());
}

void APortfolioProjectCharacter::LookUp(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate*MouseSensitivity* GetWorld()->GetDeltaSeconds());
}

void APortfolioProjectCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APortfolioProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
