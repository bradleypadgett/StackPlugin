#pragma once
#include "Modules/ModuleManager.h"



class UStackSystem;
class FStackSystemManager;

class FStackFrameworkModule : public IModuleInterface
{
public:

    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    static FStackFrameworkModule& Get() { return FModuleManager::LoadModuleChecked<FStackFrameworkModule>("StackFramework"); }

	// TO-DO ~ when I wanna support multiple managers per system (like multiple editor instances), change to a template-based manager
    TSharedPtr<FStackSystemManager> GetSystemManager(UStackSystem* InSystem);
    void RegisterSystemManager(UStackSystem* InSystem, TSharedPtr<FStackSystemManager> InManager);
    void UnregisterSystemManager(UStackSystem* InSystem);


private:
    TMap<UStackSystem*, TWeakPtr<FStackSystemManager>> SystemToManagerMap;

};