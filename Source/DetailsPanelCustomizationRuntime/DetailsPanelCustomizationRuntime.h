#pragma once

#include "Modules/ModuleManager.h"

class FDetailsPanelCustomizationRuntimeModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
