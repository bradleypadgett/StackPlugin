#include "StackDesigner.h"
#include "Modules/ModuleManager.h"
#include "StackBlueprintDefinition.h"
#include "AssetDefinitionRegistry.h"
#include "AssetDefinition.h"
#include "UObject/ReferenceChainSearch.h"
#include "Engine/Blueprint.h"
#include "Editor.h"




IMPLEMENT_MODULE(FStackDesignerModule, StackDesigner)

TStrongObjectPtr<UStackBlueprintDefinition> DesignerDefinitionInstance;

// Unregister's Epic's default blueprint definition and replaces with StackDesigner's
void FStackDesignerModule::StartupModule()
{
    UAssetDefinitionRegistry* Registry = UAssetDefinitionRegistry::Get();

    for (UAssetDefinition* Def : Registry->GetAllAssetDefinitions())
    {
        if (Def && Def->GetClass() == UAssetDefinition_Blueprint::StaticClass())
        {
            Registry->UnregisterAssetDefinition(Def);
        }
    }
    DesignerDefinitionInstance = TStrongObjectPtr<UStackBlueprintDefinition>(NewObject<UStackBlueprintDefinition>(GetTransientPackage()));
    Registry->RegisterAssetDefinition(DesignerDefinitionInstance.Get());

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("StackDesigner.DebugRefs"),
		TEXT("Shows reference chains for the first Blueprint currently being edited."),
		FConsoleCommandDelegate::CreateLambda([]()
			{
				TArray<UObject*> EditedAssets = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->GetAllEditedAssets();

				for (UObject* Asset : EditedAssets)
				{
					if (UBlueprint* BP = Cast<UBlueprint>(Asset))
					{
						UE_LOG(LogTemp, Warning, TEXT("Running FReferenceChainSearch on %s..."), *BP->GetName());
						FReferenceChainSearch Search(BP, EReferenceChainSearchMode::PrintResults);
						return;
					}
				}

				UE_LOG(LogTemp, Warning, TEXT("No Blueprint assets currently open."));
			}),
		ECVF_Default
	);
}