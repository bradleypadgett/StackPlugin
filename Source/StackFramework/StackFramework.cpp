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