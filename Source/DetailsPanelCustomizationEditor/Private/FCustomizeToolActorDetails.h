#pragma once

#include "CoreMinimal.h"                       // General Unreal types
#include "IDetailCustomization.h"              // Detail customization interface
#include "Templates/SharedPointer.h"           // Needed for TSharedRef

class IDetailLayoutBuilder;

/**
 * Global editor customization class for Blueprints that implement ICustomizeDetailsPanel.
 */
class FCustomizeToolActorDetails : public IDetailCustomization
{
public:
	// Factory function Unreal calls when using this customization
	static TSharedRef<IDetailCustomization> MakeInstance();

	// This is where we override the Details panel layout
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};