// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"
#include "ModdingPlus.generated.h"

class FModdingPlusModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	//virtual void StartupModule() override;
	//virtual void ShutdownModule() override;
};

UCLASS()
class UModdingPlus : public UObject
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintPure, Category = "ModdingPlus")
    static bool GetAllFilesFromFolder(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);
    
    UFUNCTION(BlueprintPure, Category = "ModdingPlus", meta = (Keywords = "LoadTxt"))
    static bool LoadTxt(FString FileNameA, FString& SaveTextA);
};