#include "UIDesignerAssetActions.h"
#include "UIDesignerBlueprintEditor.h"



void FUIDesignerAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> ToolkitHost)
{
	for (UObject* Obj : InObjects)
	{
		if (UBlueprint* BP = Cast<UBlueprint>(Obj))
		{
			if (BP->GeneratedClass && BP->GeneratedClass->IsChildOf(AActor::StaticClass()))
			{
				TSharedRef<FUIDesignerBlueprintEditor> Editor = MakeShareable(new FUIDesignerBlueprintEditor());
				Editor->InitUIDesignerEditor(EToolkitMode::Standalone, ToolkitHost, BP);
				return;
			}
		}
	}

	// Fallback for any asset that wasn't handled
	for (UObject* Obj : InObjects)
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Obj);
	}
}

bool FUIDesignerAssetActions::AssetsActivatedOverride(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType)
{
	for (UObject* Obj : InObjects)
	{
		if (UBlueprint* BP = Cast<UBlueprint>(Obj))
		{
			if (BP->GeneratedClass && BP->GeneratedClass->IsChildOf(AActor::StaticClass()))
			{
				TSharedRef<FUIDesignerBlueprintEditor> Editor = MakeShareable(new FUIDesignerBlueprintEditor());
				Editor->InitUIDesignerEditor(EToolkitMode::Standalone, nullptr, BP);
				return true; // handled!
			}
		}
	}

	return false; // fallback to default editor
}