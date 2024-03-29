
#include "AC_HealthComponent.h"

// Sets default values for this component's properties
UAC_HealthComponent::UAC_HealthComponent()
{
    PrimaryComponentTick.bCanEverTick = true; // Tick every frame
}

// Called when the game starts
void UAC_HealthComponent::BeginPlay()
{
    Super::BeginPlay();

    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UAC_HealthComponent::TakeDamage);
}

// Called every frame
void UAC_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_HealthComponent::Heal(float healAmount)
{
    CurrentHealth += healAmount;

    CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}

void UAC_HealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    CurrentHealth -= Damage;

    // UE_LOG(LogTemp, Warning, TEXT("HP Left : %f"), CurrentHealth);

    if (CurrentHealth <= 0)
    {
        CurrentHealth = 0;
        Die();
    }
}

void UAC_HealthComponent::Die()
{
    // Simulate Actor Physics
    if (GetOwner()->FindComponentByClass<USkeletalMeshComponent>())
    {
        UPrimitiveComponent* PhysicsActorBody;
        PhysicsActorBody = Cast<UPrimitiveComponent>(GetOwner()->FindComponentByClass<USkeletalMeshComponent>());
        PhysicsActorBody->SetSimulatePhysics(true);
    }

    // Disable Capsule Collision
    if (GetOwner()->FindComponentByClass<UCapsuleComponent>())
    {
        UE_LOG(LogTemp, Warning, TEXT("Disable capsule collision"));

        GetOwner()->FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    // Disable input if player is dead
    APawn* Actor = Cast<APawn>(GetOwner());
    if (Actor && Actor->IsPlayerControlled())
    {
        Actor->DisableInput(nullptr);
    }

    // Get AI brain component and stop logic [had to do it in Blueprint, since it's not working / refuse to compile in C++]
    //AAIController *AIController = Cast<AAIController>(GetOwner()->GetInstigatorController());
    //if (AIController)
    //{
	//	AIController->BrainComponent->StopLogic("Dead");
	//}
    
    // Disable Widget [had to do it in Blueprint since "UWidgetComponent" provoke LINKER error when compiling]
    //if (GetOwner()->FindComponentByClass<UWidgetComponent>())
    //{
    //    GetOwner()->FindComponentByClass<UWidgetComponent>()->SetVisibility(false);
    //}
}
