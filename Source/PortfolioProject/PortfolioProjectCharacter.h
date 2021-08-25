// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
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
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWidgetComponent* HUDWidget;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWidgetComponent* OrderWidget;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MouseSensitivity = 10.0; //마우스 감도
protected:
	virtual void BeginPlay() override;
	void FMoveForward(float Value);
	void FMoveRight(float Value);
	void FTurn(float Rate);
	void FLookUp(float Rate);

	void UpdateHealth();
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
	//플레이어 위젯클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> CrossHairWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MissionFailWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> EscMenuWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HurtWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HUD_Player_UIWidgetClass;
	//동료 위젯클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> G36CWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> RO635WidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> CommanderWidgetClass;

	//플레이어 인스턴스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* CrossHairUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* MissionFailUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* EscMenuUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* HurtUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* HUD_Player_UI;
	//동료 인스턴스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* G36CUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* RO635UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* CommanderUI;
};

