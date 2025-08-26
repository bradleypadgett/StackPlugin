#include "StackFramework.h"
#include "Modules/ModuleManager.h"
#include "Widgets/StackStyle.h"



IMPLEMENT_MODULE(FStackFrameworkModule, StackFramework)

void FStackFrameworkModule::StartupModule()
{
    FStackStyle::Register();
}

void FStackFrameworkModule::ShutdownModule()
{
    FStackStyle::Shutdown();
}

TSharedPtr<FStackSystemManager> FStackFrameworkModule::GetSystemManager(UStackSystem* InSystem)
{
    if (!InSystem) return nullptr;

    if (TWeakPtr<FStackSystemManager>* Found = SystemToManagerMap.Find(InSystem))
    {
        TSharedPtr<FStackSystemManager> Pinned = Found->Pin();
        if (Pinned.IsValid())
        {
            return Pinned;
        }
        else
        {
            // Clean up expired entry
            SystemToManagerMap.Remove(InSystem);
        }
    }
    return nullptr;
}

void FStackFrameworkModule::RegisterSystemManager(UStackSystem* InSystem, TSharedPtr<FStackSystemManager> InManager)
{
    if (InSystem && InManager.IsValid())
    {
        SystemToManagerMap.Add(InSystem, InManager);
    }
}

void FStackFrameworkModule::UnregisterSystemManager(UStackSystem* InSystem)
{
    if (InSystem)
    {
        SystemToManagerMap.Remove(InSystem);
    }
}