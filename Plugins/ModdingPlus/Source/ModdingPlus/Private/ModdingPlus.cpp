// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ModdingPlus.h"

#define LOCTEXT_NAMESPACE "FModdingPlusModule"

/**
void FModdingPlusModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FModdingPlusModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
*/

bool UModdingPlus::GetAllFilesFromFolder(TArray<FString>& Files, FString RootFolderFullPath, FString Ext)
 {
     if(RootFolderFullPath.Len() < 1) return false;
     
     // FPaths::NormalizeDirectoryName(RootFolderFullPath);
     
     //RootFolderFullPath = FPaths::ConvertRelativePathToFull(RootFolderFullPath);
     
     IFileManager& FileManager = IFileManager::Get();
     
     FString RelativePath = FPaths::GameContentDir();
     FString FullPath = FileManager.ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
     
     if(Ext == "") 
     {
         Ext = "*.*";
     }
     else
     {
         Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
     }
     
     FString FinalPath = FullPath + "/" + RootFolderFullPath + "/" + Ext;
     FileManager.FindFiles(Files, *FinalPath, true, false);
     return true;                  
 }
 
 bool UModdingPlus::LoadTxt(FString FileNameA, FString& SaveTextA)
{
     return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::GameContentDir() + FileNameA));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FModdingPlusModule, ModdingPlus)

