#include "CoreMinimal.h"
#include "Nodes/K2Node_AddButton.h"
#include "K2Node_CallFunction.h"
#include "UIBuilderSubsystem.h"
#include "KismetCompiler.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "K2Node_AddButton"

// Create input pins
void UK2Node_AddButton::AllocateDefaultPins()
{
    // Create execution input pin
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, FName(), nullptr, TEXT("In"));

    // Create Label input pin (string)
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, FName(), nullptr, TEXT("Label"));

    // Create execution output pin
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, FName(), nullptr, TEXT("Out"));
}


// Node Title
FText UK2Node_AddButton::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return LOCTEXT("AddButtonNodeTitle", "Add UI Button");
}

// Tooltip
FText UK2Node_AddButton::GetTooltipText() const
{
    return LOCTEXT("AddButtonNodeTooltip", "Adds a Button to the UI Builder");
}

// Actually do the work at compile time
void UK2Node_AddButton::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    UEdGraphPin* ExecPin = FindPin(TEXT("In"));
    UEdGraphPin* LabelPin = FindPin(TEXT("Label"));
    UEdGraphPin* ThenPin = FindPin(TEXT("Out"));

    if (!ExecPin || !ThenPin || !LabelPin)
    {
        CompilerContext.MessageLog.Error(*FString::Printf(TEXT("Missing pins in @@")), this);
        return;
    }

    FString LabelValue = "DefaultLabel";
    if (LabelPin->DefaultValue.Len() > 0)
    {
        LabelValue = LabelPin->DefaultValue;
    }

    if (UUIBuilderSubsystem* Subsystem = GEditor->GetEditorSubsystem<UUIBuilderSubsystem>())
    {
        Subsystem->AddButton(LabelValue);
    }

    // No graph wiring, no intermediate nodes, it's just executed at compile time!

    BreakAllNodeLinks();
}




// Makes it show up in the right-click Blueprint menu
void UK2Node_AddButton::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    UClass* ActionKey = GetClass();
    if (ActionRegistrar.IsOpenForRegistration(ActionKey))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
        ActionRegistrar.AddBlueprintAction(GetClass(), NodeSpawner);
    }
}

// What category it shows under
FText UK2Node_AddButton::GetMenuCategory() const
{
    return LOCTEXT("UIBuilderCategory", "UI Builder");
}

#undef LOCTEXT_NAMESPACE
