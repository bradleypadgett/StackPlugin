#pragma once



class FName;

struct FStackBlueprintTabs
{
	// Tab identifiers
	static const FName DesignerGraphID;
	static const FName SelectionID;
	static const FName VariablesID;
	static const FName PaletteID;
	static const FName PreviewID;

private:
	FStackBlueprintTabs() {}
};