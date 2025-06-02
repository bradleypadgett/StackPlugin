#pragma once
#include "Modules/ModuleManager.h"



class FStackNodesModule : public IModuleInterface
{
public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};