#pragma once
#include "CoreMinimal.h"



class UStack;
class UStackSystem;

namespace FStackEditorUtilities
{
	const FGuid AddStackToSystem(UStackSystem& StackSystem, UStack& Stack);

	FName GetUniqueName(FName BaseName, const TSet<FName>& ExistingNames);

}