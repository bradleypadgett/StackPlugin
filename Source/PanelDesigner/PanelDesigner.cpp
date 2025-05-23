#include "PanelDesigner.h"
#include "Modules/ModuleManager.h"
#include "PanelDesignerDefinition.h"
#include "AssetDefinitionRegistry.h"
#include "AssetDefinition.h"



IMPLEMENT_MODULE(FPanelDesignerModule, PanelDesigner)

TStrongObjectPtr<UPanelDesignerDefinition> DesignerDefinitionInstance;

void FPanelDesignerModule::StartupModule()
{
    UAssetDefinitionRegistry* Registry = UAssetDefinitionRegistry::Get();

    // Unregister Epic's default UAssetDefinition_Blueprint
    for (UAssetDefinition* Def : Registry->GetAllAssetDefinitions())
    {
        if (Def && Def->GetClass() == UAssetDefinition_Blueprint::StaticClass())
        {
            Registry->UnregisterAssetDefinition(Def);
            UE_LOG(LogTemp, Warning, TEXT("💣 Unregistered Epic's UAssetDefinition_Blueprint"));
        }
    }

    // Register custom definition AFTER clearing the original
    DesignerDefinitionInstance = TStrongObjectPtr<UPanelDesignerDefinition>(
        NewObject<UPanelDesignerDefinition>(GetTransientPackage())
    );
    Registry->RegisterAssetDefinition(DesignerDefinitionInstance.Get());
    UE_LOG(LogTemp, Warning, TEXT("✅ Registered custom PanelDesignerDefinition"));

    // Log all definitions currently associated with UBlueprint. Just to double check
    UClass* BlueprintClass = UBlueprint::StaticClass();
    UE_LOG(LogTemp, Warning, TEXT("✏️ Logging all registered asset definitions for UBlueprint:"));

    for (UAssetDefinition* Def : Registry->GetAllAssetDefinitions())
    {
        if (Def && Def->GetAssetClass().Get() == BlueprintClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("🔍 %s (Class: %s)"),
                *Def->GetName(),
                *Def->GetClass()->GetName());
        }
    }
}

void FPanelDesignerModule::ShutdownModule()
{
}


