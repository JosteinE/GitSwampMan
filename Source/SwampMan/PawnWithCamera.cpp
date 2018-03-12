// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnWithCamera.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the Box Collider
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerBoxCollider"));
	RootBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RootBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	RootBox->SetCollisionProfileName("Pawn");
	RootBox->SetSimulatePhysics(false);
	RootBox->SetEnableGravity(false);

	RootComponent = RootBox;

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
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();

	//Show system cursor
	PcMouse = GetWorld()->GetFirstPlayerController();
	PcMouse->bShowMouseCursor = true;
	PcMouse->bEnableClickEvents = true;
	PcMouse->bEnableMouseOverEvents = true;
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*// Handle Player HP. 
	{
		if ()
		{
			PlayerHealth -= 20;
		}
		if (PlayerHealth <= 0)
		{
			Destroy();
		}
	}*/

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
			MovementInput = MovementInput.GetSafeNormal() * MovementSpeed;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
		//Do this if the player is sprinting
		if (!MovementInput.IsZero() && bSprinting)
		{
			MovementInput = MovementInput.GetSafeNormal() * SprintSpeed;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}

	{
		//Gravity
		FVector PlayerPosition = GetActorLocation();
		FVector GravityStrength = FVector(0.0f, 0.0f, -5.0f);
		PlayerPosition += GravityStrength;
		SetActorLocation(PlayerPosition);
	}
}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Hook up events for "ZoomIn"
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);
	InputComponent->BindAction("FireProjectile", IE_Pressed, this, &APawnWithCamera::ShootingProjectile);
	InputComponent->BindAction("FireProjectile", IE_Released, this, &APawnWithCamera::NotShootingProjectile);
	InputComponent->BindAction("Sprinting", IE_Pressed, this, &APawnWithCamera::IsSprinting);
	InputComponent->BindAction("Sprinting", IE_Released, this, &APawnWithCamera::IsNotSprinting);

	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
	
	InputComponent->BindAxis("MouseY", this, &APawnWithCamera::MouseY);
	InputComponent->BindAxis("MouseX", this, &APawnWithCamera::MouseX);
}

//Input functions
void APawnWithCamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MouseY(float AxisValue)
{
	MouseLoc.Y = AxisValue;
}

void APawnWithCamera::MouseX(float AxisValue)
{
	MouseLoc.X = AxisValue;
}

void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}

void APawnWithCamera::ShootingProjectile()
{
	bFireProjectile = true;
}

void APawnWithCamera::NotShootingProjectile()
{
	bFireProjectile = false;
}

void APawnWithCamera::IsSprinting()
{
	bSprinting = true;
}

void APawnWithCamera::IsNotSprinting()
{
	bSprinting = false;
}
