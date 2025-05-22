#include "UIBuilderSubsystem.h"
#include "UIDesignerTabs.h"
#include "UIDesignerMode.h"
#include "UIBuilderBlueprintExtension.h"
#include "Blueprint/BlueprintExtension.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "AssetEditorModeManager.h"
#include "EditorModeManager.h"
#include "BlueprintEditor.h"
#include "UIDesignerBlueprintEditor.h"
#include "Editor/EditorEngine.h"
#include "Editor.h"

//TODO : Phase out subsystem completely! At this point I need to move/adjust the wacky toolbar widget injection to integrate into the proper FToolBarExtender extension

void UUIBuilderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
    {
        // Injects blueprint extension if it doesn't exist and adds [Designer]/[Graph] toolbar buttons before layout is finalized
        //AssetEditorSubsystem->OnEditorOpeningPreWidgets().AddUObject(this, &UUIBuilderSubsystem::OnEditorPreWidgets);
        //AssetEditorSubsystem->OnAssetOpenedInEditor().AddUObject(this, &UUIBuilderSubsystem::OnAssetOpened);
        //AssetEditorSubsystem->OnAssetEditorOpened().AddUObject(this, &UUIBuilderSubsystem::OnEditorBlueprintOpened);

        FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
    }
}

void UUIBuilderSubsystem::Deinitialize()
{
    if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()) AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);

    Super::Deinitialize();
}
/*
void UUIBuilderSubsystem::OnEditorPreWidgets(const TArray<UObject*>& Assets, IAssetEditorInstance* Instance)
{
    for (UObject* Asset : Assets)
    {
        if (UBlueprint* BP = Cast<UBlueprint>(Asset))
        {
            UE_LOG(LogTemp, Warning, TEXT("🔹[OnEditorPreWidgets] Asset is a Blueprint!"));

            if (!BP->GeneratedClass || !BP->GeneratedClass->IsChildOf(AActor::StaticClass()))
                continue; // skip non-AActor BPs

            UE_LOG(LogTemp, Warning, TEXT("🔹[OnEditorPreWidgets] AActor Blueprint: %s"), *BP->GetName());

            if (Instance->GetEditorName() != FUIDesignerBlueprintEditor::GetEditorAppName()) {

                FUIDesignerBlueprintEditor* Editor = static_cast<FUIDesignerBlueprintEditor*>(Instance);
                FUIDesignerTabs::InjectModeSwitcherToolbar(Editor, EnsureExtension(BP));

                //FUIDesignerBlueprintEditor* Editor = static_cast<FUIDesignerBlueprintEditor*>(Instance);
                //FUIDesignerTabs::InjectModeSwitcherToolbar(Editor, Extension);


                
                TArray<UBlueprint*> Blueprints = { BP };

                TSharedRef<FUIDesignerBlueprintEditor> CustomEditor = MakeShareable(new FUIDesignerBlueprintEditor());
                FUIDesignerTabs::InjectModeSwitcherToolbar(&CustomEditor.Get(), Extension);
                CustomEditor->InitBlueprintEditor(EToolkitMode::Standalone, nullptr, Blueprints, false);
                CustomEditor->InitUIDesignerMode(EToolkitMode::Standalone, nullptr, BP);
                

            }
        }
    }
}*/

/*
void UUIBuilderSubsystem::OnAssetOpened(UObject* Asset, IAssetEditorInstance* EditorInstance)
{
    UE_LOG(LogTemp, Warning, TEXT("🔷[OnAssetOpened] Asset Opened!"));
    if (UBlueprint* BP = Cast<UBlueprint>(Asset))
    {
        UE_LOG(LogTemp, Warning, TEXT("🔷[OnAssetOpened] Asset is a Blueprint!"));
        if (!BP->GeneratedClass || !BP->GeneratedClass->IsChildOf(AActor::StaticClass())) return;
        // now we know its an AActor

        UE_LOG(LogTemp, Warning, TEXT("🔷[OnAssetOpened] AActor Blueprint opened: %s"), *BP->GetName());

        //EnsureExtension(BP);

        TArray<UBlueprint*> Blueprints = { BP };

        //TSharedRef<FUIDesignerBlueprintEditor> CustomEditor = MakeShareable(new FUIDesignerBlueprintEditor());

        UE_LOG(LogTemp, Warning, TEXT("🔷[OnAssetOpened] Asset Editor name:\n📝[OnAssetOpened] %s"), *EditorInstance->GetEditorName().ToString());
        if (EditorInstance->GetEditorName() != FUIDesignerBlueprintEditor::GetEditorAppName()) {

            //TSharedRef<FUIDesignerBlueprintEditor> CustomEditor = MakeShareable(new FUIDesignerBlueprintEditor());
            //FUIDesignerTabs::InjectModeSwitcherToolbar(&CustomEditor.Get(), Extension);
            //CustomEditor->InitBlueprintEditor(EToolkitMode::Standalone, nullptr, Blueprints, false);
            //CustomEditor->InitUIDesignerMode(EToolkitMode::Standalone, nullptr, BP);

            return;
        }


        //GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->CloseAllEditorsForAsset(Asset);

        UE_LOG(LogTemp, Warning, TEXT("🔷[OnAssetOpened] Launching our custom editor"));

        //GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetOpened(Asset, &CustomEditor.Get());
        //GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->CloseOtherEditors(Asset, &CustomEditor.Get());
        return;
    }
}

void UUIBuilderSubsystem::OnEditorBlueprintOpened(UObject* Asset)
{
    UE_LOG(LogTemp, Warning, TEXT("🔵[OnEditorBlueprintOpened] Initializing Asset"));
    if (UBlueprint* BP = Cast<UBlueprint>(Asset))
    {
        UE_LOG(LogTemp, Warning, TEXT("🔵[OnEditorBlueprintOpened] Initializing Blueprint Asset"));
        if (!BP->GeneratedClass || !BP->GeneratedClass->IsChildOf(AActor::StaticClass())) return;
        // now we know its an AActor
        UE_LOG(LogTemp, Warning, TEXT("🔵[OnEditorBlueprintOpened] Initializing AActor Blueprint opened: %s"), *BP->GetName());

        IAssetEditorInstance* Editor = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(BP, false);
        TArray<UBlueprint*> Blueprints = { BP };

        if (Editor->GetEditorName() == FUIDesignerBlueprintEditor::GetEditorAppName())
        {
            UE_LOG(LogTemp, Warning, TEXT("🚨WE GOT TO THE END🚨"));
            FUIDesignerBlueprintEditor* EditorLocal = static_cast<FUIDesignerBlueprintEditor*>(Editor);


            //FUIDesignerTabs::InjectModeSwitcherToolbar(EditorLocal, Extension);
            //EditorLocal->InitBlueprintEditor(EToolkitMode::Standalone, nullptr, Blueprints, false);
            //EditorLocal->InitUIDesignerMode(EToolkitMode::Standalone, nullptr, BP);
            //EditorLocal->BringToolkitToFront();

            return;
        }

        //GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetOpened(Asset, &CustomEditor.Get());

        TSharedRef<FUIDesignerBlueprintEditor> CustomEditor = MakeShareable(new FUIDesignerBlueprintEditor());
 


        FUIDesignerTabs::InjectModeSwitcherToolbar(&CustomEditor.Get(), EnsureExtension(BP));
        CustomEditor->InitBlueprintEditor(EToolkitMode::Standalone, nullptr, Blueprints, false);
        CustomEditor->InitUIDesignerMode(EToolkitMode::Standalone, nullptr, BP);

        //CustomEditor->GetEditorModeManager().get
        GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetOpened(Asset, &CustomEditor.Get());
        GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->CloseOtherEditors(Asset, &CustomEditor.Get());
        return;
    }
}*/
/*
UUIBuilderBlueprintExtension* UUIBuilderSubsystem::EnsureExtension(UBlueprint* BP)
{
    for (const TObjectPtr<UBlueprintExtension>& FoundExtension : BP->GetExtensions())
    {
        if (UUIBuilderBlueprintExtension* TargetExtension = Cast<UUIBuilderBlueprintExtension>(FoundExtension)) return TargetExtension;
    }

    UUIBuilderBlueprintExtension* NewExtension = NewObject<UUIBuilderBlueprintExtension>(BP);
    BP->AddExtension(NewExtension);
    return NewExtension;
}*/
