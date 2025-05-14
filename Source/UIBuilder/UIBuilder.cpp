#include "UIBuilder.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "UIDesignerAssetActions.h"



static TSharedPtr<IAssetTypeActions> AssetAction;

IMPLEMENT_MODULE(FUIBuilderModule, UIBuilder)

void FUIBuilderModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	AssetAction = MakeShareable(new FUIDesignerAssetActions());
	AssetTools.RegisterAssetTypeActions(AssetAction.ToSharedRef());
}

void FUIBuilderModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools") && AssetAction.IsValid())
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.UnregisterAssetTypeActions(AssetAction.ToSharedRef());
	}
	AssetAction.Reset();
}



