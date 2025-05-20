#pragma once
#include "Modules/ModuleManager.h"



class UIDesignerDefinition;

class FUIBuilderModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    TStrongObjectPtr<UIDesignerDefinition> DesignerDefinitionInstance;

};
