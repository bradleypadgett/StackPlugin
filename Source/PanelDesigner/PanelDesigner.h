#pragma once
#include "Modules/ModuleManager.h"



class UPanelDesignerDefinition;

class FPanelDesignerModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    TStrongObjectPtr<UPanelDesignerDefinition> DesignerDefinitionInstance;

};
