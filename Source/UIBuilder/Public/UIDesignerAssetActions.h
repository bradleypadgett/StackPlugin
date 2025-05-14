#pragma once
#include "AssetTypeActions_Base.h"



class FUIDesignerAssetActions : public FAssetTypeActions_Base
{

public:

	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "Blueprint", "Blueprint"); }
	virtual FColor GetTypeColor() const override { return FColor(0, 96, 128); }
	virtual UClass* GetSupportedClass() const override { return AActor::StaticClass(); }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Blueprint; }

	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> ToolkitHost) override;

	virtual bool AssetsActivatedOverride(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType) override;

};