#include "DetailsPanelCustomizationEditor.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "FCustomizeToolActorDetails.h"

IMPLEMENT_MODULE(FDetailsPanelCustomizationEditorModule, DetailsPanelCustomizationEditor)

void FDetailsPanelCustomizationEditorModule::StartupModule()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

    PropertyModule.RegisterCustomClassLayout("ToolBaseActor",
        FOnGetDetailCustomizationInstance::CreateStatic(&FCustomizeToolActorDetails::MakeInstance));
}

void FDetailsPanelCustomizationEditorModule::ShutdownModule()
{
    if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
    {
        FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
        PropertyModule.UnregisterCustomClassLayout("ToolBaseActor");
    }
}

