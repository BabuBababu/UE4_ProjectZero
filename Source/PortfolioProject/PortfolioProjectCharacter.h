// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PlayerUIWidget.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "PortfolioProjectCharacter.generated.h"

class UCurveFloat;
class UAnimMontage;
class USoundBase;
class UMatineeCameraShake;
class UParticleSystem;

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

	FTimerHandle SkillTimer;
	FTimerHandle SkillTimer4;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MouseSensitivity = 10.0; //마우스 감도
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void FMoveForward(float Value);
	void FMoveRight(float Value);
	void FTurn(float Rate);
	void FLookUp(float Rate);

	void UpdateHealth();
	void EquipRifle();
	void FAiming();
	void FAimingOff();
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

	void SetSkill1Time();
	void SetSkill4Time();
	
	
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
	bool IsDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHurted = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ComboSound10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsActingSkill = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Skill1Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Skill4Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SelectedRO635 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SelectedG36C= false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ForEnemySendG36CIsDead= false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ForEnemySendRO635IsDead= false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ForEnemySendCommanderIsDead= false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ReloadNow= false;
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
	bool OrderFollow= false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stage2ObjectCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OpenedESC= false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForEnemySendG36CLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForEnemySendRO635Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForEnemySendCommanderLocation;

	//카메라 FOV용타임라인
	FTimeline CameraCurveTimeline;
	UPROPERTY(EditAnywhere,Category="Timeline")
	UCurveFloat* CameraCurveFloat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* FireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ReloadingMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Skill1Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* AttackVoiceSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ReloadingSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Skill1Sound;

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
	TSubclassOf<class UPlayerUIWidget> HUD_Player_UIWidgetClass;
	//동료 위젯클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> G36CWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> RO635WidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> CommanderWidgetClass;
	
	//카메라 쉐이크
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMatineeCameraShake> CameraShake;

	//파티클 시스템
	UPROPERTY(EditAnywhere,Category="Shot Particle Effect")
	UParticleSystem* OnShoot_Particle;
	UPROPERTY(EditAnywhere,Category="Skill1 Particle Effects")
	UParticleSystem* Skill1_1_Particle;
	UPROPERTY(EditAnywhere,Category="Skill1 Particle Effects")
	UParticleSystem* Skill1_2_Particle;
	UPROPERTY(EditAnywhere,Category="Skill4 Particle Effects")
	UParticleSystem* Heal_Particle;

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
	UPlayerUIWidget* HUD_Player_UI;
	//동료 인스턴스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* G36CUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* RO635UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* CommanderUI;

	//플레이어 메쉬
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* WA2000Class;
public:
	//FOV타임라인용 함수
	UFUNCTION()
	void FOVTimelineProgress(float value);
	//커스텀 이벤트
	UFUNCTION(BlueprintCallable)
	void OnShoot();
};

