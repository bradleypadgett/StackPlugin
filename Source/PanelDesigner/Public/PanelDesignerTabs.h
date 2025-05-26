#pragma once
#include "CoreMinimal.h"



class FName;

struct FPanelDesignerTabs
{
	// Tab identifiers
	static const FName DesignerGraphID;
	static const FName SelectionID;
	static const FName VariablesID;
	static const FName PaletteID;
	static const FName PreviewID;

private:
	FPanelDesignerTabs() {}
};