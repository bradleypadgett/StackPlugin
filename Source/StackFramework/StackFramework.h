#pragma once
#include "Modules/ModuleManager.h"



class FStackFrameworkModule : public IModuleInterface
{
public:

    virtual void StartupModule() override;
 
    virtual void ShutdownModule() override;
};