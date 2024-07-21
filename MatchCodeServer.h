#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MatchCodeServer.generated.h"

UCLASS()
class YOURPROJECTNAME_API UMatchCodeServer : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "MatchCode")
  static void CreateMatchCode(const FString& ServerAddress, int32 Port, FString& MatchCode);

  UFUNCTION(BlueprintCallable, Category = "MatchCode")
  static void JoinMatchCode(const FString& ServerAddress, int32 Port, const FString& MatchCode, FString& IPAddress);
};
