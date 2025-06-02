#pragma once



class FStackBlueprintEditor;

/*
*  Static helper class for registering [Designer] & [Graph] toolbar buttons.
*/
class FStackBlueprintToolbar
{
public:

	static TSharedPtr<FExtender> RegisterToolbar(UBlueprint* InBlueprint, TSharedPtr<FStackBlueprintEditor> InEditor);
};