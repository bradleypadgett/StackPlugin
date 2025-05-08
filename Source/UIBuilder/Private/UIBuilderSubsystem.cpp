#include "UIBuilderSubsystem.h"
#include "UIBuilderTabRegistrar.h"
#include "UIBuilderBlueprintExtension.h"
#include "Blueprint/BlueprintExtension.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "BlueprintEditor.h"
#include "Editor/EditorEngine.h"
#include "Editor.h"



void UUIBuilderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
    {
        // Injects blueprint extension if it doesn't exist and adds [Designer]/[Graph] toolbar buttons before layout is finalized
        AssetEditorSubsystem->OnEditorOpeningPreWidgets().AddUObject(this, &UUIBuilderSubsystem::OnEditorPreWidgets);

        FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
    }
}

void UUIBuilderSubsystem::Deinitialize()
{
    if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()) AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);

    Super::Deinitialize();
}

void UUIBuilderSubsystem::OnEditorPreWidgets(const TArray<UObject*>& Assets, IAssetEditorInstance* Instance)
{
    // Blueprint editors should only have one asset, but looping just for catchin' edge cases
    if (FBlueprintEditor* BlueprintEditor = static_cast<FBlueprintEditor*>(Instance); BlueprintEditor)
    {
        for (UObject* Asset : Assets)
        {
            // Makes sure each asset is an AActor
            UBlueprint* BP = Cast<UBlueprint>(Asset);
            if (BP && BP->GeneratedClass && BP->GeneratedClass->IsChildOf(AActor::StaticClass()))
            {
                // Checks for blueprint extension and adds one if it doesn't exist
                UUIBuilderBlueprintExtension* Extension = nullptr;
                bool bFoundExtension = false;
                for (const TObjectPtr<UBlueprintExtension>& CheckExtension : BP->GetExtensions())
                {
                    if (Cast<UUIBuilderBlueprintExtension>(CheckExtension))
                    {
                        bFoundExtension = true;
                        Extension = Cast<UUIBuilderBlueprintExtension>(CheckExtension.Get());
                        break;
                    }
                }
                if (!bFoundExtension) {
                    Extension = NewObject<UUIBuilderBlueprintExtension>(BP);
                    BP->AddExtension(Cast<UBlueprintExtension>(Extension));
                }
                // Then injects the [Designer]/[Graph] toolbar buttons into the AActor!
                FUIBuilderTabRegistrar::InjectModeSwitcherToolbar(BlueprintEditor, Extension);
            }
        }
    }
}