#include "UIBuilderBlueprintExtension.h"
#include "UIDesignerTabs.h"
#include "Graph/UIBuilderGraph.h"
#include "EdGraph/EdGraph.h"
#include "UIDesignerBlueprintEditor.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "BlueprintEditor.h"
#include "GraphEditor.h"



void UUIBuilderBlueprintExtension::PostInitProperties()
{
    Super::PostInitProperties();

    OwningBlueprint = GetTypedOuter<UBlueprint>();
    if (OwningBlueprint)
    {
        EnsureUIBuilderGraph();
    }
}

FName UUIBuilderBlueprintExtension::GetCurrentMode(FUIDesignerBlueprintEditor* InBlueprintEditor) const
{
    IAssetEditorInstance* EditorInst = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(OwningBlueprint, false);
    if (FUIDesignerBlueprintEditor* Editor = static_cast<FUIDesignerBlueprintEditor*>(EditorInst))
    {
        FName Mode = Editor->GetCurrentMode();
        return Mode;
    }
    UE_LOG(LogTemp, Warning, TEXT("❌ No editor found in GetCurrentMode()"));
    return NAME_None;
}

void UUIBuilderBlueprintExtension::SetCurrentMode(FUIDesignerBlueprintEditor* InBlueprintEditor, FName InMode)
{
    UE_LOG(LogTemp, Warning, TEXT("SetCurrentMode activated!! Current Mode is %s"), *CurrentMode.ToString());
    if (CurrentMode != InMode)
    {
        IAssetEditorInstance* EditorInst = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(OwningBlueprint, false);
        if (FUIDesignerBlueprintEditor* Editor = static_cast<FUIDesignerBlueprintEditor*>(EditorInst))
        {

            UE_LOG(LogTemp, Warning, TEXT("🧠 Extension is trying to set active mode to: %s"), *InMode.ToString());

            CurrentMode = InMode;
            Editor->SetCurrentMode(InMode);


            return;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("❌ Extension is trying to set the same mode: %s"), *InMode.ToString());
}



// Creates and serializes UIBuilderGraph into owning blueprint if it doesn't have one
void UUIBuilderBlueprintExtension::EnsureUIBuilderGraph()
{
    if (UIBuilderGraph) return;

    for (UEdGraph* Graph : OwningBlueprint->FunctionGraphs)
    {
        if (UUIBuilderGraph* Found = Cast<UUIBuilderGraph>(Graph))
        {
            UIBuilderGraph = Found;
            return;
        }
    }

    UIBuilderGraph = NewObject<UUIBuilderGraph>(OwningBlueprint, TEXT("UIBuilderGraph"));
    OwningBlueprint->FunctionGraphs.Add(UIBuilderGraph);
    OwningBlueprint->Modify();

}