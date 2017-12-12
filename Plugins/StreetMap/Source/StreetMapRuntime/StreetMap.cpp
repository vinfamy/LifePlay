// Copyright 2017 Mike Fricker. All Rights Reserved.

#include "StreetMapRuntime.h"
#include "StreetMap.h"
#include "EditorFramework/AssetImportData.h"
#include "PolygonTools.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Public/StaticMeshResources.h"
#include "PhysicsEngine/BodySetup.h"


UStreetMap::UStreetMap()
{
#if WITH_EDITORONLY_DATA
	if( !HasAnyFlags( RF_ClassDefaultObject ) )
	{
		AssetImportData = NewObject<UAssetImportData>( this, TEXT( "AssetImportData" ) );
	}
#endif
}


void UStreetMap::GetAssetRegistryTags( TArray<FAssetRegistryTag>& OutTags ) const
{
#if WITH_EDITORONLY_DATA
	if( AssetImportData )
	{
		OutTags.Add( FAssetRegistryTag( SourceFileTagName(), AssetImportData->GetSourceData().ToJson(), FAssetRegistryTag::TT_Hidden ) );
	}
#endif

	Super::GetAssetRegistryTags( OutTags );
}


FStreetMapBuilding UStreetMap::FindBuilding(const FVector2D Point)
{
    FStreetMapBuilding emptyBuilding;
    for (const auto &element : Buildings)
    {
        if (FPolygonTools::IsPointInsidePolygon(element.BuildingPoints, Point))
        {
            return element;
        }
    }
    return emptyBuilding;
}

TArray<FStreetMapBuilding> UStreetMap::SearchByBuildingName(FString SearchTerm, FString Amenity) const
{
    TArray<FStreetMapBuilding> Results;
    if (SearchTerm.Len() > 0)
    {
        for (const auto &element : Buildings)
        {
            if (element.BuildingName.Contains(SearchTerm))
            {
                Results.Add(element);
            }
        }
    }
    else
    {
        Results = Buildings;
    }
    
    if (Amenity.Len() > 0)
    {
        Results = FilterByAmenity(Amenity, Results);
    }
  
    return Results;
}

TArray<FStreetMapBuilding> UStreetMap::SearchByAmenity(FString Amenity) const
{
    TArray<FStreetMapBuilding> Results = FilterByAmenity(Amenity, Buildings);
    
    return Results; 
}

TArray<FStreetMapBuilding> UStreetMap::FilterByAmenity(FString Amenity, TArray<FStreetMapBuilding> SmallBuildings) const
{
    TArray<FStreetMapBuilding> Results;
    for (const auto &element : SmallBuildings)
    {
        if (element.Amenity == Amenity)
        {
            Results.Add(element);
        }
        else if (element.Building == Amenity)
        {
            Results.Add(element);
        }
        else if (Amenity == "residential")
        {
            if (element.Building == "apartments" || element.Building == "flats" || element.Building == "house")
            {
                Results.Add(element);
            }
        }
        else if (Amenity == "office")
        {
             if (element.Building == "commercial" || element.Building == "tower")
            {
                Results.Add(element);
            }           
        }
        else if (Amenity == "sports_centre")
        {
            if (element.Amenity == "gym" || element.Building == "fitness_centre")
            {
                Results.Add(element);
            }        
        }
    }
    
    return Results; 
}