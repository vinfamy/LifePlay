// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ModdingExtraBPLibrary.h"
#include "ModdingExtra.h"
#include "Engine.h"

UModdingExtraBPLibrary::UModdingExtraBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UModdingExtraBPLibrary::ModdingExtraSampleFunction(float Param)
{
	return -1;
}

 bool UModdingExtraBPLibrary::GetAllFilesFromFolder(TArray<FString>& Files, FString RootFolderFullPath, FString Ext)
 {
     if(RootFolderFullPath.Len() < 1) return false;
     
     // FPaths::NormalizeDirectoryName(RootFolderFullPath);
     
     //RootFolderFullPath = FPaths::ConvertRelativePathToFull(RootFolderFullPath);
     
     IFileManager& FileManager = IFileManager::Get();
     
     FString RelativePath = FPaths::ProjectContentDir();
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
     FString FinalPathWithoutExt = FullPath + "/" + RootFolderFullPath + "/";
     
     //FileManager.FindFiles(Files, *FinalPath, true, false);
     FileManager.FindFilesRecursive(Files, *FinalPathWithoutExt, *Ext, true, false, false);
     return true;                  
 }
 
 
  bool UModdingExtraBPLibrary::GetAllSubfolders(TArray<FString>& Folders, FString RootFolderFullPath)
 {
     if(RootFolderFullPath.Len() < 1) return false;
     
     IFileManager& FileManager = IFileManager::Get();
     
     FString RelativePath = FPaths::ProjectContentDir();
     FString FullPath = FileManager.ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
     
     FString FinalPath = FullPath + "/" + RootFolderFullPath + "/";
     
     FileManager.FindFiles(Folders, *FinalPath, false, true);
     return true;                  
 }
 
 
 bool UModdingExtraBPLibrary::LoadTxt(FString FileNameA, FString& SaveTextA)
{
     return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::ProjectContentDir() + FileNameA));
}

bool UModdingExtraBPLibrary::SaveTxt(FString SaveTextB, FString FileNameB)
{
     return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::ProjectContentDir() + FileNameB));
}

 FString UModdingExtraBPLibrary::ContentDirectory()
{
    FString RelativePath = FPaths::ProjectContentDir();
    FString FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
    return FullPath;
}

 bool UModdingExtraBPLibrary::IsPointInsidePolygon( const TArray<FVector2D>& Polygon, const FVector2D Point )
{
	const int NumCorners = Polygon.Num();
	int PreviousCornerIndex = NumCorners - 1;
	bool bIsInside = false;

	for( int CornerIndex = 0; CornerIndex < NumCorners; CornerIndex++ )
	{
		if( ( ( Polygon[ CornerIndex ].Y < Point.Y && Polygon[ PreviousCornerIndex ].Y >= Point.Y ) || ( Polygon[ PreviousCornerIndex ].Y < Point.Y && Polygon[ CornerIndex ].Y >= Point.Y ) ) && 
			( Polygon[ CornerIndex ].X <= Point.X || Polygon[ PreviousCornerIndex ].X <= Point.X ) )
		{
			bIsInside ^= ( Polygon[ CornerIndex ].X + ( Point.Y - Polygon[ CornerIndex ].Y ) / ( Polygon[ PreviousCornerIndex ].Y - Polygon[ CornerIndex ].Y )*( Polygon[ PreviousCornerIndex ].X - Polygon[ CornerIndex ].X ) < Point.X );
		}

		PreviousCornerIndex = CornerIndex;
	}

	return bIsInside;
}

