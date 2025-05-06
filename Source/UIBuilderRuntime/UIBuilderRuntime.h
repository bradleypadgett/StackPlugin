#pragma once
#include "Modules/ModuleManager.h"



class FUIBuilderRuntimeModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
