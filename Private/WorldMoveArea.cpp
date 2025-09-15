// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldMoveArea.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AWorldMoveArea::AWorldMoveArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Cube 생성 및 루트로 변경
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	SetRootComponent(Cube);

	// 불러온 메쉬를 Cube에 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CubeMesh.Succeeded())
	{
		Cube->SetStaticMesh(CubeMesh.Object);
	}

	// 크기 변경
	Cube->SetRelativeScale3D(FVector(6, 6, 1));

	// 메테리얼 생성
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BaseMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	// 머터리얼에 성공적으로 들어왔으면 설정험
	if (BaseMaterial.Succeeded()) {
		CubeMaterial = BaseMaterial.Object;
		Cube->SetMaterial(0, CubeMaterial);
	}

	// 콜리전 생성
	DetectedCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	// Cube큐브에 부착
	DetectedCollision->SetupAttachment(Cube);
	// 콜리전 박스 크기 설정
	DetectedCollision->SetBoxExtent(FVector(49, 48, 32));
	// 위치 설정
	DetectedCollision->SetRelativeLocation(FVector(0, 0, 30));
	// 콜리전 프로파일 설정
	DetectedCollision->SetCollisionProfileName(FName("DetectedPawn"));

	// 오버랩 이벤트 가능하게 변경
	DetectedCollision->SetGenerateOverlapEvents(true);
	
	// 택스트 렌더러 설정
	MoveAreaTextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	MoveAreaTextRender->SetupAttachment(Cube);
	MoveAreaTextRender->SetRelativeLocation(FVector(0, 0, 500));
	MoveAreaTextRender->SetHorizontalAlignment(EHTA_Center);
	MoveAreaTextRender->SetYScale(8);


}

// Called when the game starts or when spawned
void AWorldMoveArea::BeginPlay()
{
	Super::BeginPlay();
	DetectedCollision->OnComponentBeginOverlap.RemoveDynamic(this, &AWorldMoveArea::OnBoxBeginOverlap);
	DetectedCollision->OnComponentBeginOverlap.AddDynamic(this, &AWorldMoveArea::OnBoxBeginOverlap);

	DetectedCollision->OnComponentEndOverlap.RemoveDynamic(this, &AWorldMoveArea::OnBoxEndOverlap);
	DetectedCollision->OnComponentEndOverlap.AddDynamic(this, &AWorldMoveArea::OnBoxEndOverlap);
}

// Called every frame
void AWorldMoveArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AWorldMoveArea::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*FString ActorName = OtherActor->GetName();
	UE_LOG(LogTemp, Display, TEXT("%s"), *ActorName);*/
	if (OtherActor && OtherActor != this)
	{

		FString ActorName2 = OtherActor->GetName();

		// 디버그 로그
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s BeginOverlap"), *ActorName2));

		PlayerBeginOverlap(OtherActor);

		//if (HasAuthority()) {
		//	FString ActorName2 = OtherActor->GetName();
		//	UE_LOG(LogTemp, Warning, TEXT("%s�� �ڽ��� �����߽��ϴ�!"), *ActorName2);

		//	// ȭ�鿡 ǥ�� (����� �뵵)
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s BeginOverlap"), *ActorName2));

		//	PlayerBeginOverlap(OtherActor);
		//}
		
	}
}

void AWorldMoveArea::PlayerBeginOverlap(AActor* OtherActor)
{
	ABaseCharacter* player = static_cast<ABaseCharacter*>(OtherActor);
	PlayerArr.Add(player);



	PrintPlayerArr();
	
}

void AWorldMoveArea::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		FString ActorName = OtherActor->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s EndOverlap"), *ActorName));

		PlayerEndOverlap(OtherActor);

	}
}

void AWorldMoveArea::PlayerEndOverlap(AActor* OtherActor)
{
	ABaseCharacter* player = static_cast<ABaseCharacter*>(OtherActor);
	if (player != nullptr) {
		PlayerArr.Remove(player);
	}

	PrintPlayerArr();
}

void AWorldMoveArea::PrintPlayerArr()
{
	for (ABaseCharacter* object : PlayerArr) {
		FString PlayerName = object->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%s"), *PlayerName));
	}

	FText FormatText;
	if (PlayerArr.Num() == 0) {
		FormatText = FText::FromString(TextRenderText);
	}
	else {
		FormatText = FText::Format(
			FText::FromString(TEXT("{0}\n{1}")),
			FText::FromString(TextRenderText),
			FText::AsNumber(PlayerArr.Num())
		);
	}

	MoveAreaTextRender->SetText(FormatText);
	
	if (PlayerArr.Num() >= 3)
	{
		GameStartCountdown();
	}

}

void AWorldMoveArea::SetMoveAreaTextRenderText_Implementation(const FString& text)
{
	FText FormatText = FText::Format(
		FText::FromString(TEXT("{0}\n{1}")),
		FText::FromString(TextRenderText),
		FText::FromString(text)
	);

	MoveAreaTextRender->SetText(FormatText);
}




