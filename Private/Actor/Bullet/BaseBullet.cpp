// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Bullet/BaseBullet.h"

#include "Chaos/KinematicTargets.h"
#include "Character/FPSActionLogicCharacter.h"
#include "Character/FPSUILogicCharacter.h"
#include "Components/SphereComponent.h"
#include "Controller/FPSUILogicController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseBullet::ABaseBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bReplicates = true;
	SetReplicatingMovement(true);

	BulletCollision = CreateDefaultSubobject<USphereComponent>("BulletCollision");
	
}

// Called when the game starts or when spawned
void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();

	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseBullet::BulletOverlap);
	
	BulletVelocity = GetActorForwardVector() * BulletSpeed;
	CurrentPos = GetActorLocation();

	FTimerHandle BulletDestroyTimerHandle;
	GetWorldTimerManager().SetTimer(
		BulletDestroyTimerHandle,
		this,
		&ABaseBullet::DestroyBullet,
		10.f,
		false
	);

	if (Shotter)
		ShotterController = Cast<AFPSUILogicController>(Shotter->GetController());

}

void ABaseBullet::SetBulletDamage(float HeadDamage, float BodyDamage, float ArmDamage, float HandDamage,
	float LegDamage, float FootDamage)
{
	BulletDamageMap.Add(FName("Head")) = HeadDamage;
	BulletDamageMap.Add(FName("Body")) = BodyDamage;
	BulletDamageMap.Add(FName("Arm")) = ArmDamage;
	BulletDamageMap.Add(FName("Hand")) = HandDamage;
	BulletDamageMap.Add(FName("Leg")) = LegDamage;
	BulletDamageMap.Add(FName("Foot")) = FootDamage;
}

void ABaseBullet::BulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

TArray<FHitResult> ABaseBullet::SortActors(TArray<FHitResult>& OutHits, FVector StartLocation)
{
	if (OutHits.Num() <= 1)
		return OutHits;

	FHitResult Pivot =  OutHits[0];
	
	TArray<FHitResult> Left;
	TArray<FHitResult> Right;
	TArray<FHitResult> Equal;

	for (FHitResult Hit : OutHits)
	{
		if (FVector::Distance(Hit.GetActor()->GetActorLocation(), StartLocation) < FVector::Distance(Pivot.GetActor()->GetActorLocation(), StartLocation))
		{
			// 피벗 보다 작음
			Left.Add(Hit);
		}
		else if (FVector::Distance(Hit.GetActor()->GetActorLocation(), StartLocation) > FVector::Distance(Pivot.GetActor()->GetActorLocation(), StartLocation))
		{
			// 피벗 보다 큼
			Right.Add(Hit);
		}
		else
		{
			// 피벗과 같음
			Equal.Add(Hit);
		}
	}
	
	SortActors(Left, StartLocation);
	Left.Append(Equal);
	Left.Append(SortActors(Right, StartLocation));
	
	
	return Left;
}

// Called every frame
void ABaseBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentPos = GetActorLocation();

	NextPos = CurrentPos + BulletVelocity * DeltaTime;

	//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("현재 총알 지점 : %s, 다음 총알 지점 : %s"), *GetActorLocation().ToString(), *NextPos.ToString()), true, true, FLinearColor(0.0, 0.66, 1.0), DeltaTime);

	// --- 플레이어 등 감지 시작 ---
	TArray<TEnumAsByte<EObjectTypeQuery>> BulletHitObjectTypes;
	BulletHitObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel4));
	BulletHitObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel5));
	BulletHitObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel6));
	BulletHitObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel7));

	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	BulletHitObjectTypes.Add(WorldStatic);
	
	TArray<AActor*> IgnoreActorArr;
		
	TArray<FHitResult> OutHits;
	
	if (
		UKismetSystemLibrary::LineTraceMultiForObjects(
			GetWorld(),
			CurrentPos,
			NextPos,
			BulletHitObjectTypes,
			false,
			IgnoreActorArr,
			EDrawDebugTrace::None,
			OutHits,
			true
		)		
	)
	{
		//SortActors(OutHits, CurrentPos);	// 멀티 트레이스는 정렬이 되어 나온다였다... GenericPhysicsInterface.h의 static bool RaycastMulti 참고
		
		for (FHitResult OutHit : OutHits)
		{
			// 라인 트레이스에 탐지된 것이 있고
			AFPSUILogicCharacter* HitPlayer = Cast<AFPSUILogicCharacter>(OutHit.Actor);
		
			if (HitPlayer && HitPlayer->GetCharacterTeamNum() != ShotterController->GetPlayerAccountInfo().GetPartyIndex())
			{
				// 탐지된 것이 플레이어블 캐릭터며 캐릭터의 팀이 슈터의 팀과 다르고
				for (FName ComponentTag : OutHit.Component->ComponentTags)
				{
					float* Damage = BulletDamageMap.Find(ComponentTag);
					if (Damage)
					{
						// 탐지된 것의 태그가 신체 부위에 해당하는 것이면
						const float DamageValue = *Damage;

						if (ShotterController)
						{
							ComponentTag == FName("Head") ? HitPlayer->CharacterState.GetDamage(DamageValue, GetActorLocation() , ShotterController, ShotWeaponTexture, true) : HitPlayer->CharacterState.GetDamage(DamageValue, GetActorLocation(), ShotterController, ShotWeaponTexture, false);
						}
					
						break;
					}
				}

				DestroyBullet();
				break;
			}
		}
	}
	
	// 탐지된 것이 없으면
	SetActorLocation(NextPos);
	BulletVelocity.Z -= Gravity * FiscalMultiplier;
	

	
}

void ABaseBullet::DestroyBullet()
{
	Destroy();
}

