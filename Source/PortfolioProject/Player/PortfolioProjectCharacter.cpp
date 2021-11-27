// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Animation/AnimMontage.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "TimerManager.h"
#include "particles/ParticleSystem.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/UI/PlayerUIWidget.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/DoubleHitEnemy.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Player/MyLineTrace.h"
#include "DrawDebugHelpers.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Monster/OneHitEnemy.h"
#include "/UE4_Project_Zero/Source/PortfolioProject/Player/MyPlayerController.h"
#include "GameFramework/Controller.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Math/TransformCalculus3D.h"

//////////////////////////////////////////////////////////////////////////
// APortfolioProjectCharacter

APortfolioProjectCharacter::APortfolioProjectCharacter()
{
	// 컴포넌트 초기화
	PrimaryActorTick.bCanEverTick=true;
	
	
	RootComponent = GetCapsuleComponent();
	
	WeaponBack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponBack"));
	WeaponRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponRight"));
	PlayerSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletalMesh"));
	SpringArm= CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera= CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	WidgetScene= CreateDefaultSubobject<USceneComponent>(TEXT("WidgetScene"));
	HUDWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HUDWidget"));
	OrderWidget= CreateDefaultSubobject<UWidgetComponent>(TEXT("OrderWidget"));

	PlayerSkeletalMesh->SetupAttachment(RootComponent);
	WeaponBack->SetupAttachment(PlayerSkeletalMesh,TEXT("WeaponBack"));
	WeaponRight->SetupAttachment(PlayerSkeletalMesh,TEXT("WeaponRight"));
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	WidgetScene->SetupAttachment(Camera);
	HUDWidget->SetupAttachment(RootComponent);
	OrderWidget->SetupAttachment(RootComponent);
	
	
	// 콜리전 캡슐 사이즈 초기화
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// 컨트롤러 회전 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	SpringArm->bUsePawnControlRotation = true;

	//HUD,Order 위젯 위치 초기화
	HUDWidget->SetRelativeLocation(FVector(18.454441f,45.500065f,35.0f));
	HUDWidget->SetRelativeRotation(FRotator(0.0f,-180.0f,0.0f));
	HUDWidget->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
	OrderWidget->SetRelativeLocation(FVector(-22.0f,0.000142f,131.0f));
	OrderWidget->SetRelativeRotation(FRotator(0.0f,-180.0f,0.0f));
	OrderWidget->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
	HUDWidget->SetPivot(FVector2D(0.0,0.5));
	
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>
		(GetCharacterMovement());

	

	static ConstructorHelpers::FClassFinder<UUserWidget> MissionFailAdd(TEXT("/Game/Movable/GameAsset/BP_MissionFailWidget"));
	MissionFailWidgetClass = MissionFailAdd.Class;
	
	
	static ConstructorHelpers::FClassFinder<UUserWidget> CrossHairAdd(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_Crosshair"));
	CrossHairWidgetClass = CrossHairAdd.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> EscMenuAdd(TEXT("/Game/Movable/GameAsset/BP_ESC_Widget"));
	EscMenuWidgetClass = EscMenuAdd.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> HurtAdd(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_Hurt"));
	HurtWidgetClass = HurtAdd.Class;
		
	static ConstructorHelpers::FClassFinder<UUserWidget> G36CAdd(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_G36C"));
	G36CWidgetClass = G36CAdd.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> RO635Add(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_RO635"));
	RO635WidgetClass = RO635Add.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> CommanderAdd(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_Commander"));
	CommanderWidgetClass = CommanderAdd.Class;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WA2000Gun(TEXT("/Game/Movable/WeaponAsset/WA2000Gun/WA2000_GUN.WA2000_GUN"));
	WA2000Class = WA2000Gun.Object;

	//WA2000 몽타주
	FireMontage = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Game/Movable/CharactorAsset/Wa2000/WA2000_Animation/firing_rifle_Montage")).Object;
	ReloadingMontage = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Game/Movable/CharactorAsset/Wa2000/WA2000_Animation/Reloading_Montage")).Object;
	Skill1Montage = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("/Game/Movable/CharactorAsset/Wa2000/WA2000_Animation/Fire_Skill_Montage")).Object;

	//WA2000 사운드
	AttackVoiceSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Movable/CharactorAsset/Wa2000/WA2000_Sound/WA2000_ATTACK_JP_Cue")).Object;
	ReloadingSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Movable/GameAsset/Sound/MP7_Reload_Cue")).Object;
	FireSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Movable/WeaponAsset/ArbitraryStudio/Weapons/rifle_sound_Cue")).Object;
	Skill1Sound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Movable/CharactorAsset/Wa2000/WA2000_Sound/WA2000_SKILL_JP_Cue")).Object;

	//파티클 시스템 , character클래스에 category=particle 이런식으로 추가하고 변수 받는것이 확장성에 좋음 이 밑의 코드는 default로 미리 지정해놓은 에셋들.
	static ConstructorHelpers::FObjectFinder<UParticleSystem> OnShoot_ParticleAdd(TEXT("/Game/Movable/WeaponAsset/WeaponEffects/P_AssaultRifle_MF"));
	OnShoot_Particle = OnShoot_ParticleAdd.Object;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Skill1_1_ParticleAdd(TEXT("/Game/Movable/WeaponAsset/WeaponEffects/P_AssaultRifle_IH_2"));
	Skill1_1_Particle =Skill1_1_ParticleAdd.Object;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Skill1_2_ParticleAdd(TEXT("/Game/Movable/WeaponAsset/WeaponEffects/P_AssaultRifle_MF_2"));
	Skill1_2_Particle = Skill1_2_ParticleAdd.Object;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Heal_ParticleAdd(TEXT("/Game/StarterContent/Particles/P_Sparks.P_Sparks"));
	Heal_Particle = Heal_ParticleAdd.Object;

	//플레이어에 대한 AIperception용 
	SetStimulus();
}
//////////////////////////////////////////////////////////////////////////
// Input


void APortfolioProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APortfolioProjectCharacter::Jump);
	PlayerInputComponent->BindAction("EquipRifle", IE_Pressed, this, &APortfolioProjectCharacter::EquipRifle);
	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &APortfolioProjectCharacter::FAiming);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &APortfolioProjectCharacter::FAimingOff);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APortfolioProjectCharacter::Fire);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APortfolioProjectCharacter::Interact);
	PlayerInputComponent->BindAction("Reloading", IE_Pressed, this, &APortfolioProjectCharacter::Reloading);
	PlayerInputComponent->BindAction("SKillShot1", IE_Pressed, this, &APortfolioProjectCharacter::SKillShot1);
	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &APortfolioProjectCharacter::Heal);
	//아군 명령키
	PlayerInputComponent->BindAction("AttackForwad", IE_Pressed, this, &APortfolioProjectCharacter::AttackForwad);
	PlayerInputComponent->BindAction("FallBack", IE_Pressed, this, &APortfolioProjectCharacter::FallBack);
	PlayerInputComponent->BindAction("WaitHere", IE_Pressed, this, &APortfolioProjectCharacter::WaitHere);
	PlayerInputComponent->BindAction("FollowMe", IE_Pressed, this, &APortfolioProjectCharacter::FollowMe);
	//이동 조작
	PlayerInputComponent->BindAxis("MoveForward", this, &APortfolioProjectCharacter::FMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APortfolioProjectCharacter::FMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APortfolioProjectCharacter::FTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &APortfolioProjectCharacter::FLookUp);

}

void APortfolioProjectCharacter::FOVTimelineProgress(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Function"));
	Camera->SetFieldOfView(value);
}


void APortfolioProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* const PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	FString CurrentLevelName = GetWorld()->GetMapName();
	
	
	CurrentHP = MaxHP;
	Skill1Time = 0;
	Skill4Time = 0;
	
	//위젯클래스 담고 생성
	if(PlayerUIManager == nullptr)
	{
		PlayerUIManager=NewObject<UMyUIManager>();
		PlayerUIManager->Init();
		PlayerUIManager->SetContoller(PlayerController);
		UE_LOG(LogTemp, Warning, TEXT("sucess PlayerUIManager"));
	}
	 PlayerUIManager->UITClassArray.Add(MissionFailWidgetClass);
	 PlayerUIManager->UITClassArray.Add(EscMenuWidgetClass);
	 PlayerUIManager->UITClassArray.Add(G36CWidgetClass);
	 PlayerUIManager->UITClassArray.Add(RO635WidgetClass);
	 PlayerUIManager->UITClassArray.Add(CommanderWidgetClass);
	PlayerUIManager->AddUI();
	
	 //위젯 생성
	if(CrossHairWidgetClass != nullptr)
	  	{
	 	 CrossHairUI = CreateWidget<UUserWidget>(PlayerController,CrossHairWidgetClass);
	  	 UE_LOG(LogTemp, Warning, TEXT("sucess crosswiget"));
	  	}
	if(HurtWidgetClass != nullptr)
	{
		HurtUI = CreateWidget<UUserWidget>(PlayerController,HurtWidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("sucess Hurtwiget"));
	}
	
	 // if(EscMenuWidgetClass != nullptr)
	 //  	{
	 // 	 EscMenuUI = CreateWidget<UUserWidget>(PlayerController,EscMenuWidgetClass);
	 //  	 UE_LOG(LogTemp, Warning, TEXT("sucess escwiget"));
	 //  	}
	 // if(MissionFailWidgetClass != nullptr)
	 // 	{
	 // 	   MissionFailUI = CreateWidget<UUserWidget>(PlayerController,MissionFailWidgetClass);
	 //    	 UE_LOG(LogTemp, Warning, TEXT("sucess missionfailwiget"));
	 // 	}
	 //
	 // if(G36CWidgetClass != nullptr)
	 // {
	 // 	G36CUI = CreateWidget<UUserWidget>(PlayerController,G36CWidgetClass);
	 // 	UE_LOG(LogTemp, Warning, TEXT("sucess G36Cwiget"));
	 // }
	 // if(RO635WidgetClass != nullptr)
	 // {
	 // 	RO635UI = CreateWidget<UUserWidget>(PlayerController,RO635WidgetClass);
	 // 	UE_LOG(LogTemp, Warning, TEXT("sucess RO635wiget"));
	 // }
	 // if(CommanderWidgetClass != nullptr)
	 // {
	 // 	CommanderUI = CreateWidget<UUserWidget>(PlayerController,CommanderWidgetClass);
	 // 	UE_LOG(LogTemp, Warning, TEXT("sucess commanderwiget"));
	 // }
	 //
	//PlayerUIManager->AllAddToViewPort();
	
	 // EscMenuUI->AddToViewport();
	 // MissionFailUI->AddToViewport(10);
	 // G36CUI->AddToViewport();
	 // RO635UI->AddToViewport();
	 // CommanderUI->AddToViewport();

	
	HurtUI->AddToViewport();
	//EscMenuUI->SetVisibility(ESlateVisibility::Hidden);
	//MissionFailUI->SetVisibility(ESlateVisibility::Hidden);
	HurtUI->SetVisibility(ESlateVisibility::Hidden);

	HUDWidget->SetWidgetSpace(EWidgetSpace::Screen);
	UpdateHealth();
	
	GetWorld()->GetTimerManager().SetTimer(SkillTimer,this,&APortfolioProjectCharacter::SetSkill1Time,1.0f,true);
	GetWorld()->GetTimerManager().SetTimer(SkillTimer4,this,&APortfolioProjectCharacter::SetSkill4Time,1.0f,true);

	if (CurrentLevelName != "LobbyBase")
	{
		//G36CUI->SetVisibility(ESlateVisibility::Visible);
		//RO635UI->SetVisibility(ESlateVisibility::Visible);
		//CommanderUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		//G36CUI->SetVisibility(ESlateVisibility::Hidden);
		//RO635UI->SetVisibility(ESlateVisibility::Hidden);
		//CommanderUI->SetVisibility(ESlateVisibility::Hidden);
	}

	if(LineTrace == nullptr)
	{
		LineTrace=NewObject<UMyLineTrace>();
	}

}

void APortfolioProjectCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CameraCurveTimeline.TickTimeline(DeltaSeconds);
	UAnimInstance* AnimInstance =PlayerSkeletalMesh->GetAnimInstance();
	if(ReloadNow==true && !AnimInstance->Montage_IsPlaying(ReloadingMontage))
	{
		ReloadNow = false;
		GetMovementComponent()->MovementState.bCanJump = true;
	}
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

void APortfolioProjectCharacter::UpdateHealth()
{
	 if(HUDWidget != nullptr)
	 {
	 	UUserWidget *hudwidget1 = HUDWidget->GetUserWidgetObject();
	 	UProgressBar *healthbar1 = dynamic_cast<UProgressBar *>(hudwidget1->GetWidgetFromName(FName("HealthBar")));
	 	if(IsValid(healthbar1))
	 	{
	 		//UE_LOG(LogTemp, Warning, TEXT("HealthBarTest"));
	 		healthbar1->SetPercent(CurrentHP/MaxHP);
	 	}
	 	
	 }
}

void APortfolioProjectCharacter::TakenDamaged(float damage)
{
	CurrentHP = CurrentHP - damage;
	UpdateHealth();
	GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%f"),this->CurrentHP));
}

void APortfolioProjectCharacter::EquipRifle()
{
	//UCharacterMovementComponent *MovementPtr =  Cast<UCharacterMovementComponent>(this->GetCharacterMovement());
	if(RifleEquipped)
	{
		if(!ReloadNow&& !Aiming)
			{
				
				RifleEquipped = false;
				GetCharacterMovement()->MaxWalkSpeed= 300.f;
				GetCharacterMovement()->MaxWalkSpeedCrouched= 100.f;
				WeaponBack->SetStaticMesh(WA2000Class);
				WeaponRight->SetStaticMesh(nullptr);
			}
	}
	else
	{
		RifleEquipped = true;
		GetCharacterMovement()->MaxWalkSpeed= 600.f;
		GetCharacterMovement()->MaxWalkSpeedCrouched= 200.f;
		WeaponBack->SetStaticMesh(nullptr);
		WeaponRight->SetStaticMesh(WA2000Class);
	}
}

void APortfolioProjectCharacter::FAiming()
{
	if(RifleEquipped)
	{
		Aiming = true;
		GetCharacterMovement()->MaxWalkSpeed= 300.f;
		GetCharacterMovement()->MaxWalkSpeedCrouched= 100.f;
		CrossHairUI->AddToViewport();
		//FOV
		if(CameraCurveFloat)
		{
			UE_LOG(LogTemp, Warning, TEXT("FOVTest"));
			FOnTimelineFloat TimelineProgress;
			TimelineProgress.BindUFunction(this,FName("FOVTimelineProgress"));
			CameraCurveTimeline.AddInterpFloat(CameraCurveFloat,TimelineProgress);
			CameraCurveTimeline.PlayFromStart();
			//CameraCurveTimeline.SetLooping(false);
		}
	}
}

void APortfolioProjectCharacter::FAimingOff()
{
	if(RifleEquipped)
	{
		Aiming = false;
		ComboSound10 = 0;
		GetCharacterMovement()->MaxWalkSpeed= 600.f;
		GetCharacterMovement()->MaxWalkSpeedCrouched= 200.f;
		CrossHairUI->RemoveFromParent();
		//FOV
		if(CameraCurveFloat)
		{
			FOnTimelineFloat TimelineProgress;
			TimelineProgress.BindUFunction(this,FName("FOVTimelineProgress"));
			CameraCurveTimeline.AddInterpFloat(CameraCurveFloat,TimelineProgress);
			CameraCurveTimeline.Reverse();
			//CameraCurveTimeline.SetLooping(false);
		}
	}
}

void APortfolioProjectCharacter::Fire()
{
	UAnimInstance* AnimInstance =PlayerSkeletalMesh->GetAnimInstance();
	UUserWidget* Hudwidget = HUDWidget->GetUserWidgetObject();
	UPlayerUIWidget* Hudwidgetcasted = Cast<UPlayerUIWidget>(Hudwidget);
	//UWidgetBlueprintGeneratedClass* WidgetAnim = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
		
	//UFunction *AmmoRedFlashFunc = dynamic_cast<UFunction *>(Hudwidget->GetWidgetFromName(FName("Ammo red flash")));
	//AMyPlayerController* const PlayerController = Cast<AMyPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	
	if(RifleEquipped && !IsActingSkill)
	{
		if(CurrentAmmo>0)
		{
			if(!AnimInstance->Montage_IsPlaying(ReloadingMontage))
			{
				AnimInstance->Montage_Play(FireMontage);
				CurrentAmmo = CurrentAmmo-1;
				if(Aiming)
				{
					ComboSound10 = ComboSound10+1;
					if(ComboSound10 >= 10 && FMath::RandRange(0,1))
					{
						//UE_LOG(LogTemp, Warning, TEXT("sound"));
						UGameplayStatics::PlaySoundAtLocation(this,AttackVoiceSound,AActor::GetActorLocation());
						ComboSound10 = 0;
					}
				}
				
			}
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("WidgetAnim is Cool"));
			Hudwidgetcasted->PlayAnimationByName(TEXT("NoAmmoAnimation"),0.f,1,EUMGSequencePlayMode::Forward,2.f);
			
		}
	}
}

void APortfolioProjectCharacter::Interact()
{
	//나중에
}

void APortfolioProjectCharacter::Reloading()
{
	UAnimInstance* AnimInstance =PlayerSkeletalMesh->GetAnimInstance();
	if(CurrentAmmo<15)
	{
		ReloadNow = true;
		GetMovementComponent()->MovementState.bCanJump = false;
		AnimInstance->Montage_Play(ReloadingMontage);
		
		UGameplayStatics::PlaySoundAtLocation(this,ReloadingSound,GetActorLocation());
		ReloadingAmmo = 15-CurrentAmmo;
		CurrentAmmo = ReloadingAmmo + CurrentAmmo;
		SaveAmmo = SaveAmmo - ReloadingAmmo;
	}
	
	
}

void APortfolioProjectCharacter::SKillShot1()
{
	UAnimInstance* AnimInstance =PlayerSkeletalMesh->GetAnimInstance();
	UUserWidget* Hudwidget = HUDWidget->GetUserWidgetObject();
	UPlayerUIWidget* Hudwidgetcasted = Cast<UPlayerUIWidget>(Hudwidget);
	FTimerHandle WaitHandle;
	float WaitTime = 2.f;
	if(!IsActingSkill && RifleEquipped && Skill1Time == 0.0f)
	{
		if (CurrentAmmo >2)
		{
			if(!AnimInstance->Montage_IsPlaying(ReloadingMontage))
			{
				if(!IsActingSkill)
				{
					IsActingSkill = true;
					Hudwidgetcasted->PlayAnimationByName(TEXT("Skill1TimeAnimation"),0.f,1,EUMGSequencePlayMode::Forward,1.f);
					Skill1Time = 2.f;
					GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, 3.0f,ECameraShakePlaySpace::CameraLocal,FRotator::ZeroRotator);
					AnimInstance->Montage_Play(Skill1Montage);
					UGameplayStatics::SpawnEmitterAttached(Skill1_1_Particle,WeaponRight,FName("Muzzle"),FVector(0.f,0.f,0.f), FRotator(0.f,0.f,0.f),FVector(1), EAttachLocation::SnapToTarget,true,EPSCPoolMethod::None,true);
					UGameplayStatics::SpawnEmitterAttached(Skill1_2_Particle,WeaponRight,FName("Muzzle"),FVector(0.f,0.f,0.f), FRotator(0.f,0.f,0.f),FVector(1), EAttachLocation::SnapToTarget,true,EPSCPoolMethod::None,true);



					//라인트레이싱
					if(LineTrace != nullptr)
					{
						UE_LOG(LogTemp, Warning, TEXT("NotNull"));
						LineTrace->OnFire(this);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("No,noHit"));
					}
					CurrentAmmo -= 3;
					
					GetWorld()->GetTimerManager().SetTimer(WaitHandle,FTimerDelegate::CreateLambda([&]
					{	//delay
						IsActingSkill = false;
						ComboSound10 = 0;
						if(FMath::RandRange(0,1) && FMath::RandRange(0,1)) // 1/4확률로 음성사운드
						{
							UGameplayStatics::PlaySoundAtLocation(this,Skill1Sound,GetActorLocation());
						}
					}), WaitTime,false);
					
					

				}
			}
		}
		else
		{
			Hudwidgetcasted->PlayAnimationByName(TEXT("NoAmmoAnimation"),0.f,1,EUMGSequencePlayMode::Forward,2.f);
		}
		
	}
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

void APortfolioProjectCharacter::Death()
{
	IsDead = true;
	GetMovementComponent()->MovementState.bCanJump = false;
}

void APortfolioProjectCharacter::SetSkill1Time()
{
	Skill1Time = FMath::Clamp(Skill1Time-1.0f,0.f,2.f);
}

void APortfolioProjectCharacter::SetSkill4Time()
{
	Skill4Time = FMath::Clamp(Skill1Time-1.0f,0.f,10.f);
}

void APortfolioProjectCharacter::OnShoot()
{
	
	
	//UE_LOG(LogTemp, Warning, TEXT("YesPArticle"));
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, 1.0f,ECameraShakePlaySpace::CameraLocal,FRotator::ZeroRotator);
	UGameplayStatics::SpawnEmitterAttached(OnShoot_Particle,WeaponRight,FName("Muzzle"),FVector(0.f,0.f,0.f), FRotator(0.f,0.f,0.f),FVector(1), EAttachLocation::SnapToTarget,true,EPSCPoolMethod::None,true);
	UGameplayStatics::PlaySoundAtLocation(this,FireSound,GetActorLocation());

	//라인트레이싱
	if(LineTrace != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NotNull"));
		LineTrace->OnFire(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No,noHit"));
	}
	
}

void APortfolioProjectCharacter::SetStimulus()
{
	//몬스터용 Stimulus
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}


void APortfolioProjectCharacter::FMoveForward(float Value)
{
	if(!IsActingSkill)
	{
		MoveForward = Value;
		if ((Controller != nullptr) && (MoveForward != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, MoveForward);
		}
	}
}

void APortfolioProjectCharacter::FMoveRight(float Value)
{
	if(!IsActingSkill)
	{
		MoveRight = Value;
		if ( (Controller != nullptr) && (MoveRight != 0.0f) )
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
	
			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, MoveRight);
		}
	}
}
