#include "Graph/UIBuilderBlueprintExtension.h"
#include "Graph/UIBuilderGraphHolder.h"
#include "Graph/UIBuilderGraph.h"
#include "Graph/UIBuilderGraphSchema.h"
#include "Graph/UIBuilderGraphEditor.h"
#include "Graph/UIBuilderEditor.h"
#include "Graph/UIBuilderEditorExtension.h"
#include "UIBuilderSubsystem.h"
#include "BlueprintEditorTabs.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "UObject/SavePackage.h"
#include "BlueprintEditor.h"
#include "Editor/EditorEngine.h"
#include "Editor.h"

/*
bool UUIBuilderSubsystem::InjectGraphHolderInstance(UBlueprint* BlueprintAsset)
{
   if (!BlueprintAsset)
    {
        UE_LOG(LogTemp, Warning, TEXT("❌ InjectGraphHolderInstance: Invalid BlueprintAsset"));
        return false;
    }

    // 🔄 Get or create your BlueprintExtension
   UBlueprintExtensionContainer* Extensions = Blueprint->GetExtensionContainer();
   UUIBuilderBlueprintExtension* Extension = Extensions->FindExtension<UUIBuilderBlueprintExtension>();

   if (!Extension)
   {
       Extension = NewObject<UUIBuilderBlueprintExtension>(Extensions);
       Extensions->AddExtension(Extension);
   }

    // ✅ Already has one? Great.
    if (Extension->GraphHolder)
    {
        if (!Extension->GraphHolder->UIBuilderGraph)
        {
            Extension->GraphHolder->UIBuilderGraph = NewObject<UUIBuilderGraph>(Extension->GraphHolder, TEXT("UIBuilderGraph"));
            Extension->GraphHolder->UIBuilderGraph->Schema = UUIBuilderGraphSchema::StaticClass();
        }

        UE_LOG(LogTemp, Warning, TEXT("✅ Found existing GraphHolder via BlueprintExtension: %s"), *Extension->GraphHolder->GetName());
        return true;
    }

    // ❌ Otherwise, create a new one
    UUIBuilderGraphHolder* NewHolder = NewObject<UUIBuilderGraphHolder>(
        BlueprintAsset,
        UUIBuilderGraphHolder::StaticClass(),
        TEXT("UIBuilderGraph_Holder"),
        RF_Public | RF_Transactional
    );

    NewHolder->UIBuilderGraph = NewObject<UUIBuilderGraph>(NewHolder, TEXT("UIBuilderGraph"), RF_Transactional);
    NewHolder->UIBuilderGraph->Schema = UUIBuilderGraphSchema::StaticClass();

    Extension->GraphHolder = NewHolder;

    UE_LOG(LogTemp, Warning, TEXT("✅ Created and attached new GraphHolder via BlueprintExtension: %s"), *NewHolder->GetName());
    return true;
}
*/