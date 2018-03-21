// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterWithCamera.h"

// Sets default values
APlayerCharacterWithCamera::APlayerCharacterWithCamera()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our mesh
	PlayerBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerCube"));
	PlayerBox->SetupAttachment(RootComponent);

	//Create our camera components
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-70.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = ZoomedOutCameraDistance;
	OurCameraSpringArm->bEnableCameraLag = false;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;
	OurCameraSpringArm->bInheritPitch = false;
	OurCameraSpringArm->bInheritYaw = false;
	OurCameraSpringArm->bInheritRoll = false;

	//Create our camera
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerCharacterWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
	//Show system cursor
	PcMouse = GetWorld()->GetFirstPlayerController();
	PcMouse->bShowMouseCursor = true;
	PcMouse->bEnableClickEvents = true;
	PcMouse->bEnableMouseOverEvents = true;
}

// Called every frame
void APlayerCharacterWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Zoom in if ZoomIn button is down, zoom back out if it's not
	{
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		OurCamera->FieldOfView = FMath::Lerp<float>(FOVZoomedOut, FOVZoomedIn, ZoomFactor);
		OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(ZoomedOutCameraDistance, ZoomedInCameraDistance, ZoomFactor);
	}

	//Rotate our actor's yaw based on cursor location
	//Trace cursor location via a ray from the cursor to the ground.
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		FHitResult TraceResult(ForceInit);
		if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, TraceResult))
		{
			FVector direction(TraceResult.ImpactPoint - GetActorLocation());
			direction.Z = 0;
			SetActorRotation(direction.Rotation());
		}
	}

	//Handle movement based on our "MoveX" and "MoveY" axes
	{
		//Do this if the player is walking
		if (!MovementInput.IsZero() && !bSprinting)
		{
			//Scale our movement input axis values by 100 units per second
			//MovementInput = MovementInput.GetSafeNormal() * MovementSpeed;
			//FVector NewLocation = GetActorLocation();
			//NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			//NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			//SetActorLocation(NewLocation);
			

		}
		//Do this if the player is sprinting
		if (!MovementInput.IsZero() && bSprinting)
		{
			/* BAD CODE
			MovementInput = MovementInput.GetSafeNormal() * SprintSpeed;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
			*/
			AddMovementInput(GetActorForwardVector(), SprintSpeed);
		}
	}
	{
		if (bFireProjectile)
		{
			RayCast();
		}
	}
}

// Called to bind functionality to input
void APlayerCharacterWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayerCharacterWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APlayerCharacterWithCamera::ZoomOut);
	InputComponent->BindAction("FireProjectile", IE_Pressed, this, &APlayerCharacterWithCamera::ShootingProjectile);
	InputComponent->BindAction("FireProjectile", IE_Released, this, &APlayerCharacterWithCamera::NotShootingProjectile);
	InputComponent->BindAction("Sprinting", IE_Pressed, this, &APlayerCharacterWithCamera::IsSprinting);
	InputComponent->BindAction("Sprinting", IE_Released, this, &APlayerCharacterWithCamera::IsNotSprinting);

	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacterWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacterWithCamera::MoveRight);

	InputComponent->BindAxis("MouseY", this, &APlayerCharacterWithCamera::MouseY);
	InputComponent->BindAxis("MouseX", this, &APlayerCharacterWithCamera::MouseX);
}

//Input functions
void APlayerCharacterWithCamera::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
	//MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayerCharacterWithCamera::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
	//MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayerCharacterWithCamera::MouseY(float AxisValue)
{
	MouseLoc.Y = AxisValue;
}

void APlayerCharacterWithCamera::MouseX(float AxisValue)
{
	MouseLoc.X = AxisValue;
}

void APlayerCharacterWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APlayerCharacterWithCamera::ZoomOut()
{
	bZoomingIn = false;
}

void APlayerCharacterWithCamera::ShootingProjectile()
{
	bFireProjectile = true;
}

void APlayerCharacterWithCamera::NotShootingProjectile()
{
	bFireProjectile = false;
}

void APlayerCharacterWithCamera::IsSprinting()
{
	bSprinting = true;
}

void APlayerCharacterWithCamera::IsNotSprinting()
{
	bSprinting = false;
}


void APlayerCharacterWithCamera::RayCast()
{
	{
		FHitResult* HitResult = new FHitResult();

		FVector OrigoToPlayer = GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();

		FVector PlayerToEndtrace = (ForwardVector * WindLength);

		PlayerToEndtrace = PlayerToEndtrace.RotateAngleAxis(45.f, FVector::UpVector);

		FCollisionQueryParams* CQP = new FCollisionQueryParams{ "Fish", false };

		GetWorld()->DebugDrawTraceTag = CQP->TraceTag;
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true);
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, OrigoToPlayer, OrigoToPlayer + PlayerToEndtrace, ECC_Visibility, *CQP))
		{
			/*if (HitResult != NULL)
			{

			}*/
		}
	}
	{
		FHitResult* HitResult = new FHitResult();

		FVector OrigoToPlayer = GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();

		FVector PlayerToEndtrace = (ForwardVector * WindLength);

		PlayerToEndtrace = PlayerToEndtrace.RotateAngleAxis(-45.f, FVector::UpVector);

		FCollisionQueryParams* CQP = new FCollisionQueryParams{ "Fish", false };

		GetWorld()->DebugDrawTraceTag = CQP->TraceTag;
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true);
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, OrigoToPlayer, OrigoToPlayer + PlayerToEndtrace, ECC_Visibility, *CQP))
		{
			/*if (HitResult != NULL)
			{

			}*/
		}
	}
}