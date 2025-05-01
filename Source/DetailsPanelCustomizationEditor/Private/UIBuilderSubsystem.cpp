#include "UIBuilderSubsystem.h"
#include "Graph/UIBuilderGraphHolder.h"
#include "Graph/UIBuilderGraph.h"
#include "Graph/UIBuilderGraphSchema.h"
#include "Graph/UIBuilderGraphEditor.h"
#include "Graph/UIBuilderEditor.h"
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
        AssetEditorSubsystem->OnAssetEditorOpened().AddUObject(this, &UUIBuilderSubsystem::RegisterEditorExtension);
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
 * Called whenever an asset editor window finishes opening.
 */
void UUIBuilderSubsystem::RegisterEditorExtension(UObject* Asset)
{
    if (UBlueprint* BlueprintAsset = Cast<UBlueprint>(Asset))
    {
        IAssetEditorInstance* RawEditor = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()
            ->FindEditorForAsset(BlueprintAsset, /*bFocusIfOpen=*/false);

        if (!RawEditor)
        {
            UE_LOG(LogTemp, Warning, TEXT("⚠️ UIBuilderSubsystem: Could not find active editor for Blueprint %s"), *BlueprintAsset->GetName());
            return;
        }

        FBlueprintEditor* Editor = static_cast<FBlueprintEditor*>(RawEditor);

        if (ActiveEditors.Contains(Editor))
        {
            UE_LOG(LogTemp, Warning, TEXT("⚠️ UIBuilderSubsystem: Editor already extended."));
            return;
        }

        ActiveEditors.Add(Editor);

        UE_LOG(LogTemp, Warning, TEXT("✅ UIBuilderSubsystem: Registering extension for Blueprint: %s"), *BlueprintAsset->GetName());

        FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda(
            [Editor](float)
            {
                if (!Editor) return false;

                TSharedRef<FUIBuilderBlueprintExtension> Extension = FUIBuilderBlueprintExtension::Create(Editor);
                Extension->ExtendBlueprintEditor();

                return false; // one-shot
            }
        ));
    }
}

/*
 * Ensures the Blueprint has a UIBuilderGraphHolder and a valid Graph.
 */
void UUIBuilderSubsystem::InjectGraphHolder(UBlueprint* BlueprintAsset)
{
    if (!BlueprintAsset) return;

    if (!EnsureGraphHolderVariable(BlueprintAsset))
    {
        UE_LOG(LogTemp, Warning, TEXT("♻️ UIBuilderSubsystem: GraphHolder already exists — skipping injection."));
        return;
    }

    FKismetEditorUtilities::CompileBlueprint(BlueprintAsset);
    InjectGraphHolderInstance(BlueprintAsset);

    BlueprintAsset->Modify();
    BlueprintAsset->MarkPackageDirty();

    UE_LOG(LogTemp, Warning, TEXT("✅ InjectGraphHolder: Property created, graph holder injected, and Blueprint recompiled."));
}


bool UUIBuilderSubsystem::EnsureGraphHolderVariable(UBlueprint* BlueprintAsset)
{
    if (!BlueprintAsset || !BlueprintAsset->GeneratedClass)
    {
        return false;
    }

    if (StaticFindObjectFast(UUIBuilderGraphHolder::StaticClass(), BlueprintAsset, TEXT("UIBuilderGraph_Holder")))
    {
        return false;
    }
    return true;
}


/*
 * Creates and assigns a UUIBuilderGraphHolder if one doesn't exist yet.
 */
bool UUIBuilderSubsystem::InjectGraphHolderInstance(UBlueprint* BlueprintAsset)
{
    if (!BlueprintAsset)
    {
        UE_LOG(LogTemp, Warning, TEXT("❌ InjectGraphHolderInstance: Invalid BlueprintAsset"));
        return false;
    }

    // Try to find existing graph holder as an inner object
    UObject* Existing = StaticFindObjectFast(UUIBuilderGraphHolder::StaticClass(), BlueprintAsset, TEXT("UIBuilderGraph_Holder"));
    if (UUIBuilderGraphHolder* ExistingHolder = Cast<UUIBuilderGraphHolder>(Existing))
    {
        if (!ExistingHolder->UIBuilderGraph)
        {
            ExistingHolder->UIBuilderGraph = NewObject<UUIBuilderGraph>(ExistingHolder, UUIBuilderGraph::StaticClass(), TEXT("UIBuilderGraph"), RF_Transactional);
            ExistingHolder->UIBuilderGraph->Schema = UUIBuilderGraphSchema::StaticClass();
            UE_LOG(LogTemp, Warning, TEXT("♻️ Graph was missing — created new UIBuilderGraph for existing holder."));
        }

        UE_LOG(LogTemp, Warning, TEXT("✅ Found existing GraphHolder: %s"), *ExistingHolder->GetName());
        return true;
    }

    // Otherwise create a new one
    BlueprintAsset->Modify();

    UUIBuilderGraphHolder* NewHolder = NewObject<UUIBuilderGraphHolder>(
        BlueprintAsset,
        UUIBuilderGraphHolder::StaticClass(),
        TEXT("UIBuilderGraph_Holder"),
        RF_Public | RF_Transactional
    );

    NewHolder->UIBuilderGraph = NewObject<UUIBuilderGraph>(
        NewHolder,
        UUIBuilderGraph::StaticClass(),
        TEXT("UIBuilderGraph"),
        RF_Transactional
    );

    NewHolder->UIBuilderGraph->Schema = UUIBuilderGraphSchema::StaticClass();

    UE_LOG(LogTemp, Warning, TEXT("✅ Created new GraphHolder = %s with Graph = %s"),
        *NewHolder->GetName(),
        *NewHolder->UIBuilderGraph->GetName());

    return true;
}

/*
 * Retries InjectGraphHolderInstance() until successful or retries are exhausted.
 */
void UUIBuilderSubsystem::DeferGraphHolderInjection(UBlueprint* BlueprintAsset, int32 AttemptsRemaining)
{
    if (!BlueprintAsset || AttemptsRemaining <= 0)
    {
        return;
    }

    TWeakObjectPtr<UBlueprint> WeakBlueprint = BlueprintAsset;

    FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this, WeakBlueprint, AttemptsRemaining](float DeltaTime) mutable
        {
            if (!WeakBlueprint.IsValid())
            {
                return false;
            }

            UE_LOG(LogTemp, Warning, TEXT("UIBuilderSubsystem: Retry #%d for Blueprint %s..."), 11 - AttemptsRemaining, *WeakBlueprint->GetName());

            if (InjectGraphHolderInstance(WeakBlueprint.Get()))
            {
                return false;
            }

            --AttemptsRemaining;

            if (AttemptsRemaining <= 0)
            {
                UE_LOG(LogTemp, Warning, TEXT("UIBuilderSubsystem: Exhausted retries injecting GraphHolder for %s."), *WeakBlueprint->GetName());
                return false;
            }

            return true;
        }));
}

/*
 * Looks for GraphHolder and tries to open Graph
 */
UUIBuilderGraph* UUIBuilderSubsystem::GetGraphForBlueprint(UBlueprint* BlueprintAsset) const
{
    if (!BlueprintAsset)
    {
        UE_LOG(LogTemp, Warning, TEXT("❌ GetGraphForBlueprint: Invalid Blueprint"));
        return nullptr;
    }

    // Try to find the existing holder object by name
    UUIBuilderGraphHolder* Holder = Cast<UUIBuilderGraphHolder>(
        StaticFindObjectFast(UUIBuilderGraphHolder::StaticClass(), BlueprintAsset, TEXT("UIBuilderGraph_Holder"))
    );

    if (!Holder)
    {
        UE_LOG(LogTemp, Warning, TEXT("❌ GetGraphForBlueprint: No GraphHolder found on Blueprint %s"), *BlueprintAsset->GetName());
        return nullptr;
    }

    // Try to access the graph on the holder
    if (!Holder->UIBuilderGraph)
    {
        UE_LOG(LogTemp, Warning, TEXT("❌ GetGraphForBlueprint: Holder found, but UIBuilderGraph is null — possibly failed injection?"));
        return nullptr;
    }

    return Holder->UIBuilderGraph;
}