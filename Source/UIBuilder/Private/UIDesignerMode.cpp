#include "UIDesignerMode.h"
#include "UIDesignerTabs.h" // your tab registrar
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "BlueprintEditor.h"



static FText GetLocalizedUIDesignerMode(FName InMode)
{
	return FText::FromString("UI Designer");
}

FUIDesignerMode::FUIDesignerMode(TSharedPtr<FBlueprintEditor> InBlueprintEditor) : FApplicationMode("UIDesignerMode", GetLocalizedUIDesignerMode)
{
	// 🔧 Set up your default layout (first-time or reset fallback)
	TabLayout = FTabManager::NewLayout(FName("UIDesigner_Layout_v1"))
		->AddArea(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split(
				FTabManager::NewStack()
				->AddTab("UIDesignerGraph", ETabState::OpenedTab)
			)
		);
}

void FUIDesignerMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	if (const TSharedPtr<FBlueprintEditor> BP = WeakBlueprintEditor.Pin())
	{
		//BP->RegisterModeTabFactories(InTabManager); // ✅ this is what wires up Graph, Components, etc
	}
	//FUIDesignerTabs::RegisterAll(this, InTabManager);
}
