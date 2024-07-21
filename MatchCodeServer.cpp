#include "MatchCodeServer.h"
#include "Http.h"

void UMatchCodeServer::CreateMatchCode(const FString& ServerAddress, int32 Port, FString& MatchCode)
{
  FHttpModule* Http = &FHttpModule::Get();
  if (!Http) return;

  TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
  Request->OnProcessRequestComplete().BindLambda([&MatchCode](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
  {
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
      TSharedPtr<FJsonObject> JsonObject;
      TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

      if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
      {
        MatchCode = JsonObject->GetStringField("matchCode");
      }
    }
  });

  FString URL = FString::Printf(TEXT("http://%s:%d/create"), *ServerAddress, Port);
  Request->SetURL(URL);
  Request->SetVerb("POST");
  Request->SetHeader("Content-Type", "application/json");
  Request->ProcessRequest();
}

void UMatchCodeServer::JoinMatchCode(const FString& ServerAddress, int32 Port, const FString& MatchCode, FString& IPAddress)
{
  FHttpModule* Http = &FHttpModule::Get();
  if (!Http) return;

  TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
  Request->OnProcessRequestComplete().BindLambda([&IPAddress](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
  {
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
      TSharedPtr<FJsonObject> JsonObject;
      TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

      if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
      {
        IPAddress = JsonObject->GetStringField("ip");
      }
    }
  });

  FString PostData = FString::Printf(TEXT("{\"matchCode\":\"%s\"}"), *MatchCode);
  FString URL = FString::Printf(TEXT("http://%s:%d/join"), *ServerAddress, Port);
  Request->SetURL(URL);
  Request->SetVerb("POST");
  Request->SetHeader("Content-Type", "application/json");
  Request->SetContentAsString(PostData);
  Request->ProcessRequest();
}
