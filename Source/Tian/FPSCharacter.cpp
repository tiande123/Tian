// Fill out your copyright notice in the Description page of Project Settings.

#include "Tian.h"
#include "FPSCharacter.h"


// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ����һ����һ�˳�����������
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// �������������ӵ������������
	FPSCameraComponent->AttachTo(GetCapsuleComponent());
	// ��������������۾��Ϸ���Զ����
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// �� pawn �����������ת��
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Ϊӵ����Ҵ���һ����һ�˳�ģ�������
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	// ��ģ�ͽ���ӵ����ҿɼ���
	FPSMesh->SetOnlyOwnerSee(true);
	// �� FPS ģ����ӵ� FPS �������
	FPSMesh->AttachTo(FPSCameraComponent);
	// ���ò��ֻ�����Ӱ��������һģ�ʹ��ڵļ���
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	// ӵ������޷�������ͨ�������˳ƣ�����ģ�͡�
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// ��ʾ������Ϣ���롣-1������ֵ���׸�������˵������������»�ˢ�´���Ϣ��
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
	
}

// Called every frame
void AFPSCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput); 
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);
}
// ����Ĭ��ֵ


// ���ú󽫹��ܰ󶨵�����
void AFPSCharacter::MoveForward(float Value)
{
	// ��ȷ�ĸ������ǡ�ǰ����������¼�����ͼ��˷����ƶ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	// ��ȷ�ĸ������ǡ����ҡ�������¼�����ͼ��˷����ƶ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}
void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}
// ����һ����һ�˳�����������



