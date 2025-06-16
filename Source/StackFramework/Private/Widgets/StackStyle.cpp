#include "Widgets/StackStyle.h"
#include "Styling/SlateStyleRegistry.h"



TSharedPtr<FStackStyle> FStackStyle::StackStyleInstance = nullptr;

FStackStyle::FStackStyle()
	: FSlateStyleSet("StackStyle")
{
	InitTextStyles();
	InitRowStyles();
	InitIcons();
	InitDropTarget();
	InitSizes();
}

void FStackStyle::Register()
{
	if (!StackStyleInstance.IsValid())
	{
		StackStyleInstance = MakeShareable(new FStackStyle());
		FSlateStyleRegistry::RegisterSlateStyle(*StackStyleInstance);
	}
}

void FStackStyle::Unregister()
{
	if (StackStyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StackStyleInstance);
		StackStyleInstance.Reset();
	}
}

void FStackStyle::Shutdown()
{
	Unregister();
}

const FStackStyle& FStackStyle::Get()
{
	check(StackStyleInstance.IsValid());
	return *StackStyleInstance;
}

void FStackStyle::ReloadTextures()
{
	if (StackStyleInstance.IsValid())
	{
		StackStyleInstance->ReloadTextures();
	}
}

void FStackStyle::ReinitializeStyle()
{
	Shutdown();
	Register();
}

void FStackStyle::InitTextStyles()
{
	Set("StackEditor.GroupHeaderText", FTextBlockStyle()
		.SetFont(FAppStyle::Get().GetFontStyle("BoldFont"))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FVector2D(1.f, 1.f))
	);

	Set("StackEditor.NodeTitleText", FTextBlockStyle()
		.SetFont(FAppStyle::GetFontStyle("Graph.Node.NodeTitleFont"))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FVector2D(1.f, 1.f)));
}


void FStackStyle::InitRowStyles()
{
	Set("StackEditor.NodeHeader", new FSlateImageBrush(
		FPaths::EngineContentDir() / TEXT("Editor/Slate/Icons/CategoryRow.png"),
		FVector2D(64, 32),
		FLinearColor(0.25f, 1.0f, 0.5f) // green tint
	));
}


void FStackStyle::InitIcons() {}
void FStackStyle::InitDropTarget() {}
void FStackStyle::InitSizes() {}
