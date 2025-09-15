// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/BaseProjectile.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicatingMovement(true);
	SetReplicates(true);
	
	Collision = CreateDefaultSubobject<UCapsuleComponent>("ProjectileCollision");
	RootComponent = Collision;
	Collision->SetSimulatePhysics(true);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	ProjectileMesh->SetupAttachment(RootComponent);

	Collision->SetLinearDamping(0.01f);
	Collision->SetAngularDamping(0.1f);
	
	Collision->SetSimulatePhysics(true);
	Collision->SetNotifyRigidBodyCollision(true);
}

void ABaseProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ABaseProjectile, OwnerPlayer, COND_None, REPNOTIFY_Always);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		ProjectileActionTimerHandle,
		this,
		&ABaseProjectile::ProjectileAction,
		ProjectileActionCoolTime,
		false
	);

	if (Collision)
		Collision->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnCapsuleHit);
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::SetProjectileOwner(AFPSUILogicController* NewOwnerController)
{
	OwnerPlayer = NewOwnerController;
}

void ABaseProjectile::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!Collision)
		return;
	
	Collision->SetLinearDamping(Collision->GetLinearDamping() * LinearDampingMultiplier);
	Collision->SetAngularDamping(Collision->GetAngularDamping() * AngularDampingMultiplier);

	// UKismetSystemLibrary::PrintString(
	// 	this,
	// 	FString::Printf(TEXT("LinearDamping : %lf, AngularDamping : %lf"), Collision->GetLinearDamping(), Collision->GetAngularDamping())
	// );
}

AFPSUILogicController* ABaseProjectile::GetProjectileOwner()
{
	return OwnerPlayer;
}

void ABaseProjectile::ProjectileAction()
{
	if (!HasAuthority())
		return;
}

void ABaseProjectile::DetectedPlayer(TArray<FHitResult>& HitResults, FVector StartLoc, FVector EndLoc, float Radius)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> DetectedObjectTypes;
	TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	DetectedObjectTypes.Add(Pawn);
	
	TArray<AActor*> IgnoreActorArr;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		StartLoc,
		EndLoc,
		Radius,
		DetectedObjectTypes,
		false,
		IgnoreActorArr,
		EDrawDebugTrace::ForDuration,
		HitResults,
		false
	);

}

void ABaseProjectile::DestroyProjectile()
{
	Destroy();
}

void ABaseProjectile::ServerMeshSetHiddenInGame_Implementation(bool bIsHidden)
{
	MultiMeshSetHiddenInGame(bIsHidden);
}

void ABaseProjectile::MultiMeshSetHiddenInGame_Implementation(bool bIsHidden)
{
	ProjectileMesh->SetVisibility(bIsHidden);
	TArray<USceneComponent*> ChildrenComponent;
	ProjectileMesh->GetChildrenComponents(true, ChildrenComponent);

	for (USceneComponent* Child : ChildrenComponent)
	{
		Child->SetVisibility(bIsHidden);
	}
}




