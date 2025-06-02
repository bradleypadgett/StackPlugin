#pragma once
#include "Modules/ModuleManager.h"



class UStackBlueprintDefinition;

class FStackDesignerModule : public IModuleInterface
{
public:

    virtual void StartupModule() override;

    TStrongObjectPtr<UStackBlueprintDefinition> DesignerDefinitionInstance;
};