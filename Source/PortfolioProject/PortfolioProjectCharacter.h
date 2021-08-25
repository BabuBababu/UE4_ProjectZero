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
	void FMoveForward(float Value);
	void FMoveRight(float Value);
	void FTurn(float Rate);
	void FLookUp(float Rate);
	void EquipRifle();
	void FAiming();
	void Fire();
	void Interact();
	void Reloading();
	void SKillShot1();
	void Heal();
	void FollowMe();
	void AttackForwad();
	void WaitHere();
	void FallBack();
	void ESCMenu();
public:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool RifleEquipped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Aiming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PressKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 350.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmmo = 15;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SaveAmmo = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ReloadingAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHurted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ComboSound10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsActingSkill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Skill1Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Skill4Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SelectedRO635;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SelectedG36C;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ForEnemySendG36CIsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ForEnemySendRO635IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ForEnemySendCommanderIsDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForPlayerG36CCurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForPlayerG36CMaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForPlayerRO635CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForPlayerRO635MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForPlayerCommanderCurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForPlayerCommanderMaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OrderFollow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stage2ObjectCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OpenedESC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForEnemySendG36CLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForEnemySendRO635Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForEnemySendCommanderLocation;
	
	
	

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> CrossHairWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MissionFailWidget;
};

