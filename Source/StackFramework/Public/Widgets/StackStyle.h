#pragma once
#include "Styling/SlateStyle.h"



/** Style set for stack-specific widgets (rows, icons, colors, inputs). */
class FStackStyle : public FSlateStyleSet
{
public:
	static void Register();
	static void Unregister();
	static void Shutdown();

	static const FStackStyle& Get();

	static void ReloadTextures();
	static void ReinitializeStyle();

private:
	FStackStyle();

	static TSharedPtr<FStackStyle> StackStyleInstance;

	void InitTextStyles();
	void InitRowStyles();
	void InitIcons();
	void InitDropTarget();
	void InitSizes();

};
