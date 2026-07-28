#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LunarAttributeSet.generated.h"

#define LUNAR_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class LUNARST_API ULunarAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ULunarAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
	FGameplayAttributeData Health;

	LUNAR_ATTRIBUTE_ACCESSORS(ULunarAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
	FGameplayAttributeData MaxHealth;

	LUNAR_ATTRIBUTE_ACCESSORS(ULunarAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Astral Energy")
	FGameplayAttributeData AstralEnergy;

	LUNAR_ATTRIBUTE_ACCESSORS(ULunarAttributeSet, AstralEnergy)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Astral Energy")
	FGameplayAttributeData MaxAstralEnergy;

	LUNAR_ATTRIBUTE_ACCESSORS(ULunarAttributeSet, MaxAstralEnergy)
};