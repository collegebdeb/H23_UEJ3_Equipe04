#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "AC_HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class H23_UEJ3_EQUIPE04_API UAC_HealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAC_HealthComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Component")
        float MaxHealth = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Component")
        float CurrentHealth = 100;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
        void Heal(float healAmount);

    UFUNCTION(BlueprintCallable)
        void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void Die();
};