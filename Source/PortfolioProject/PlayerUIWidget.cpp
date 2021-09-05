// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUIWidget.h"
#include "PortfolioProjectCharacter.h"

void UPlayerUIWidget::NativeConstruct()
{
	
	Super::NativeConstruct();
	FillAnimationMap();
	NoAmmoAnimation = GetAnimationByName(TEXT("NoAmmoAnimation"));
	Skill1TimeAnimation = GetAnimationByName(TEXT("Skill1TimeAnimation"));
	Skill4TimeAnimation = GetAnimationByName(TEXT("Skill4TimeAnimation"));
	
	
}

UWidgetAnimation* UPlayerUIWidget::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnim = AnimationMap.Find(AnimationName);
	if(WidgetAnim)
	{
		return *WidgetAnim;
	}
	return nullptr;
}

bool UPlayerUIWidget::PlayAnimationByName(FName AnimationName, float StartAtTime, int32 NumLoopsToPlay,
	EUMGSequencePlayMode::Type PlayMode, float PlaybackSpeed)
{
	//위젯 애니메이션 실행
	UWidgetAnimation* WidgetAnim = GetAnimationByName(AnimationName);
	if(WidgetAnim)
	{
		PlayAnimation(WidgetAnim,StartAtTime,NumLoopsToPlay,PlayMode,PlaybackSpeed);
		return true;
	}
	return false;
}

void UPlayerUIWidget::FillAnimationMap()
{
	//애니메이션 비우기
	AnimationMap.Empty();

	//해당 클래스의 모든 속성중에서 위젯 애니메이션 찾기
	FProperty* Prop = GetClass()->PropertyLink;
	while(Prop != nullptr)
	{
		//객체 특성이라면
		if(Prop->GetClass() == FObjectProperty::StaticClass())
		{
			//위젯 애니메이션이라면
			FObjectProperty* ObjProp = Cast<FObjectProperty>(Prop);
			if(ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				//블루프린트에서 만든 변수 가져오기
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);
				//오브젝트가 위젯 애니메이션이고 무비씬이 존재하면
				UWidgetAnimation* WidgetAnim = Cast<UWidgetAnimation>(Obj);
				if(WidgetAnim != nullptr && WidgetAnim->MovieScene != nullptr)
				{
					//애니메이션을 맵에 넣기
					FName AnimName = WidgetAnim->MovieScene->GetFName();
					AnimationMap.Add(AnimName,WidgetAnim);
				}
			}
		}
	
		//다음
		Prop = Prop->PropertyLinkNext;
	}
}
