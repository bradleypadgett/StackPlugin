#pragma once
#include "Modules/ModuleManager.h"



class FStackEditorModule : public IModuleInterface
{
public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};