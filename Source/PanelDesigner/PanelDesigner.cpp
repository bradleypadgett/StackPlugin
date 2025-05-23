#include "PanelDesigner.h"
#include "Modules/ModuleManager.h"
#include "PanelDesignerDefinition.h"
#include "AssetDefinitionRegistry.h"
#include "AssetDefinition.h"



IMPLEMENT_MODULE(FPanelDesignerModule, PanelDesigner)

TStrongObjectPtr<UPanelDesignerDefinition> DesignerDefinitionInstance;

// Unregister's Epic's default blueprint definition and replaces with PanelDesigner's
void FPanelDesignerModule::StartupModule()
{
    UAssetDefinitionRegistry* Registry = UAssetDefinitionRegistry::Get();

    for (UAssetDefinition* Def : Registry->GetAllAssetDefinitions())
    {
        if (Def && Def->GetClass() == UAssetDefinition_Blueprint::StaticClass())
        {
            Registry->UnregisterAssetDefinition(Def);
        }
    }
    DesignerDefinitionInstance = TStrongObjectPtr<UPanelDesignerDefinition>(NewObject<UPanelDesignerDefinition>(GetTransientPackage()));
    Registry->RegisterAssetDefinition(DesignerDefinitionInstance.Get());
}