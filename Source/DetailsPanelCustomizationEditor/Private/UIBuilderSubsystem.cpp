#include "UIBuilderSubsystem.h"
#include "Graph/UIBuilderGraphHolder.h"
#include "Graph/UIBuilderGraph.h"
#include "Graph/UIBuilderGraphSchema.h"
#include "Graph/UIBuilderGraphEditor.h"
#include "Graph/UIBuilderEditor.h"
#include "Graph/UIBuilderEditorExtension.h"
#include "Graph/UIBuilderBlueprintExtension.h"
#include "BlueprintEditorTabs.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "UObject/SavePackage.h"
#include "BlueprintEditor.h"
#include "Editor/EditorEngine.h"
#include "Editor.h"



void UUIBuilderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
    {
        AssetEditorSubsystem->OnAssetEditorOpened().AddUObject(this, &UUIBuilderSubsystem::OnBlueprintEditorOpened);
        UE_LOG(LogTemp, Warning, TEXT("UIBuilderSubsystem: Initialized and bound to OnAssetEditorOpened."));
    }
}

void UUIBuilderSubsystem::Deinitialize()
{
    if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
    {
        AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);
    }

    Super::Deinitialize();
}

/*
 * Called whenever a Blueprint editor window finishes opening.
 */
void UUIBuilderSubsystem::OnBlueprintEditorOpened(UObject* Asset)
{
    if (UBlueprint* BlueprintAsset = Cast<UBlueprint>(Asset))
    {
        IAssetEditorInstance* RawEditor = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()
            ->FindEditorForAsset(BlueprintAsset, false);

        if (!RawEditor)
        {
            UE_LOG(LogTemp, Warning, TEXT("⚠️ UIBuilderSubsystem: Could not find active editor for Blueprint %s"), *BlueprintAsset->GetName());
            return;
        }

        FBlueprintEditor* Editor = static_cast<FBlueprintEditor*>(RawEditor);

        if (ActiveEditors.Contains(Editor))
        {
            UE_LOG(LogTemp, Warning, TEXT("⚠️ UIBuilderSubsystem: Editor already registered inside Blueprint."));
            return;
        }

        ActiveEditors.Add(Editor);

        UE_LOG(LogTemp, Warning, TEXT("✅ UIBuilderSubsystem: Registering extension into Blueprint: %s"), *BlueprintAsset->GetName());

        FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda(
            [Editor](float)
            {
                if (!Editor) return false;

                TSharedRef<FUIBuilderEditorExtension> Extension = FUIBuilderEditorExtension::CreateEditorExtension(Editor);
                Extension->ExtendBlueprintEditor();

                return false;
            }
        ));
    }
}