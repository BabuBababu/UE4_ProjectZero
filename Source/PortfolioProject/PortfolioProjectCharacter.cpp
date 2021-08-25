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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::EquipRifle);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::FAiming);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::Fire);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::Interact);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::Reloading);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::SKillShot1);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::Heal);
	//아군 명령키
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::AttackForwad);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::FallBack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::WaitHere);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::FollowMe);
	//이동 조작
	PlayerInputComponent->BindAxis("MoveForward", this, &APortfolioProjectCharacter::FMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APortfolioProjectCharacter::FMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APortfolioProjectCharacter::FTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &APortfolioProjectCharacter::FLookUp);

}


void APortfolioProjectCharacter::FTurn(float Rate)
{
	// calculate delta for this frame from the rate information, Rate옆에 상수값 곱해서 감도조절
	AddControllerYawInput(Rate*MouseSensitivity* GetWorld()->GetDeltaSeconds());
}

void APortfolioProjectCharacter::FLookUp(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate*MouseSensitivity* GetWorld()->GetDeltaSeconds());
}

void APortfolioProjectCharacter::EquipRifle()
{
}

void APortfolioProjectCharacter::FAiming()
{
}

void APortfolioProjectCharacter::Fire()
{
}

void APortfolioProjectCharacter::Interact()
{
}

void APortfolioProjectCharacter::Reloading()
{
}

void APortfolioProjectCharacter::SKillShot1()
{
}

void APortfolioProjectCharacter::Heal()
{
}

void APortfolioProjectCharacter::FollowMe()
{
}

void APortfolioProjectCharacter::AttackForwad()
{
}

void APortfolioProjectCharacter::WaitHere()
{
}

void APortfolioProjectCharacter::FallBack()
{
}

void APortfolioProjectCharacter::ESCMenu()
{
}

void APortfolioProjectCharacter::FMoveForward(float Value)
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

void APortfolioProjectCharacter::FMoveRight(float Value)
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
