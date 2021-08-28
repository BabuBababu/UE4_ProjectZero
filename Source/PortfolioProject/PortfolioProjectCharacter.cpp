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
#include "Components/TimelineComponent.h"
#include "TimerManager.h"
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
	//WeaponBack->AttachToComponent(PlayerSkeletalMesh,FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponBack"));
	//WeaponRight->AttachToComponent(PlayerSkeletalMesh,FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponRight"));
	WeaponBack->SetupAttachment(PlayerSkeletalMesh,TEXT("WeaponBack"));
	WeaponRight->SetupAttachment(PlayerSkeletalMesh,TEXT("WeaponRight"));
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	WidgetScene->SetupAttachment(Camera);
	HUDWidget->SetupAttachment(RootComponent);
	OrderWidget->SetupAttachment(RootComponent);
	
	//Camera->AttachToComponent(SpringArm,FAttachmentTransformRules::KeepWorldTransform);
	//WidgetScene->AttachToComponent(Camera,FAttachmentTransformRules::KeepWorldTransform);
	//HUDWidget->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);
	//OrderWidget->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);
	
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
	//static ConstructorHelpers::FClassFinder<UUserWidget> HUD_Player_UIAdd(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_Player_UI"));
	//HUD_Player_UIWidgetClass = HUD_Player_UIAdd.Class;
	
	static ConstructorHelpers::FClassFinder<UUserWidget> G36CAdd(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_G36C"));
	G36CWidgetClass = G36CAdd.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> RO635Add(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_RO635"));
	RO635WidgetClass = RO635Add.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget> CommanderAdd(TEXT("/Game/Movable/Charactor/HUD/BP_Widget_Commander"));
	CommanderWidgetClass = CommanderAdd.Class;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WA2000Gun(TEXT("/Game/Movable/WeaponAsset/WA2000Gun/WA2000_GUN.WA2000_GUN"));
	WA2000Class = WA2000Gun.Object;
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
	UE_LOG(LogTemp, Warning, TEXT("Function"));
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
	 //위젯 생성
	if(CrossHairWidgetClass != nullptr)
	  	{
	 	 CrossHairUI = CreateWidget<UUserWidget>(PlayerController,CrossHairWidgetClass);
	  	 UE_LOG(LogTemp, Warning, TEXT("sucess crosswiget"));
	  	}
	if(EscMenuWidgetClass != nullptr)
	 	{
		 EscMenuUI = CreateWidget<UUserWidget>(PlayerController,EscMenuWidgetClass);
	 	 UE_LOG(LogTemp, Warning, TEXT("sucess escwiget"));
	 	}
	if(MissionFailWidgetClass != nullptr)
		{
		   MissionFailUI = CreateWidget<UUserWidget>(PlayerController,MissionFailWidgetClass);
	   	 UE_LOG(LogTemp, Warning, TEXT("sucess missionfailwiget"));
		}
	if(HurtWidgetClass != nullptr)
	{
		HurtUI = CreateWidget<UUserWidget>(PlayerController,HurtWidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("sucess Hurtwiget"));
	}
	// if(HUD_Player_UIWidgetClass != nullptr)
	// {
	// 	HUD_Player_UI = CreateWidget<UUserWidget>(PlayerController,HUD_Player_UIWidgetClass);
	// 	UE_LOG(LogTemp, Warning, TEXT("sucess HudUIwiget"));
	// }
	
	
	if(G36CWidgetClass != nullptr)
	{
		G36CUI = CreateWidget<UUserWidget>(PlayerController,G36CWidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("sucess G36Cwiget"));
	}
	if(RO635WidgetClass != nullptr)
	{
		RO635UI = CreateWidget<UUserWidget>(PlayerController,RO635WidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("sucess RO635wiget"));
	}
	if(CommanderWidgetClass != nullptr)
	{
		CommanderUI = CreateWidget<UUserWidget>(PlayerController,CommanderWidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("sucess commanderwiget"));
	}
	
	EscMenuUI->AddToViewport();
	MissionFailUI->AddToViewport(10);
	HurtUI->AddToViewport();
	G36CUI->AddToViewport();
	RO635UI->AddToViewport();
	CommanderUI->AddToViewport();
	
	EscMenuUI->SetVisibility(ESlateVisibility::Hidden);
	MissionFailUI->SetVisibility(ESlateVisibility::Hidden);
	HurtUI->SetVisibility(ESlateVisibility::Hidden);

	HUDWidget->SetWidgetSpace(EWidgetSpace::Screen);
	UpdateHealth();
	
	GetWorld()->GetTimerManager().SetTimer(SkillTimer,this,&APortfolioProjectCharacter::SetSkill1Time,1.0f,true);
	GetWorld()->GetTimerManager().SetTimer(SkillTimer4,this,&APortfolioProjectCharacter::SetSkill4Time,1.0f,true);

	if (CurrentLevelName != "LobbyBase")
	{
		G36CUI->SetVisibility(ESlateVisibility::Visible);
		RO635UI->SetVisibility(ESlateVisibility::Visible);
		CommanderUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		G36CUI->SetVisibility(ESlateVisibility::Hidden);
		RO635UI->SetVisibility(ESlateVisibility::Hidden);
		CommanderUI->SetVisibility(ESlateVisibility::Hidden);
	}

}

void APortfolioProjectCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CameraCurveTimeline.TickTimeline(DeltaSeconds);
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

void APortfolioProjectCharacter::EquipRifle()
{
	//UCharacterMovementComponent *MovementPtr =  Cast<UCharacterMovementComponent>(this->GetCharacterMovement());
	if(RifleEquipped)
	{
		RifleEquipped = false;
		GetCharacterMovement()->MaxWalkSpeed= 300.f;
		GetCharacterMovement()->MaxWalkSpeedCrouched= 100.f;
		WeaponBack->SetStaticMesh(WA2000Class);
		WeaponRight->SetStaticMesh(nullptr);
		
		
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

void APortfolioProjectCharacter::SetSkill1Time()
{
	Skill1Time = FMath::Clamp(Skill1Time-1.0f,0.f,1.f);
}

void APortfolioProjectCharacter::SetSkill4Time()
{
	Skill4Time = FMath::Clamp(Skill1Time-1.0f,0.f,1.f);
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
