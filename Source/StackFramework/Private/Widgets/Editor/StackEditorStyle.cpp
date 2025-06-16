#include "Widgets/Editor/StackEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Brushes/SlateColorBrush.h"



TSharedPtr<FSlateStyleSet> FStackEditorStyle::StyleInstance = nullptr;

void FStackEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = MakeShareable(new FSlateStyleSet("StackEditorStyle"));
		StyleInstance->Set("StackEditor.GroupBackground", new FSlateColorBrush(FLinearColor(0.08f, 0.08f, 0.1f, 1.f)));
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FStackEditorStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		StyleInstance.Reset();
	}
}

const ISlateStyle& FStackEditorStyle::Get()
{
	return *StyleInstance;
}

FName FStackEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("StackEditorStyle"));
	return StyleSetName;
}