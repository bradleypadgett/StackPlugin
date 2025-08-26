#include "Widgets/SStackNodeRoot.h"
#include "Widgets/SStackNodeEntries.h"
#include "Editor/StackNode.h"
#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackRootManager.h"
#include "ViewModels/Editor/StackHandleManager.h"
#include "ViewModels/Editor/StackSelectionManager.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/StackStyle.h"
#include "Providers/Editor/StackSystemProvider.h"
#include "StackFramework/StackFramework.h"
#include "StackSystem.h"



#define LOCTEXT_NAMESPACE "SStackNodeRoot"

void SStackNodeRoot::Construct(const FArguments& InArgs, UStackNode* InNode)
{
	Node = InNode;
	GraphNode = InNode;
	RootManager = nullptr;
	SelectionManager = nullptr;
	if (Node->GetOwningSystem())
	{
		FStackFrameworkModule& EditorModule = FStackFrameworkModule::Get();
		TSharedPtr<FStackSystemManager> SystemManager = EditorModule.GetSystemManager(Node->GetOwningSystem());
		if (SystemManager.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("SystemManager is valid"));

			if (Node->GetHandleID().IsValid() == false)
			{
				RootManager = SystemManager->GetSystemStackRootManager();
			}
			else
			{
				HandleManagerWeak = SystemManager->GetHandleManagerFromID(Node->GetHandleID());
				if (HandleManagerWeak.IsValid())
				{
					RootManager = HandleManagerWeak.Pin()->GetStackRootManager();
				}
			}

			SelectionManager = SystemManager->GetSelectionManager();
		}
	}

	if (!RootManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("SStackNodeRoot: Missing Manager."));
		return;
	}

	if (!SelectionManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("SStackNodeRoot: Missing SelectionManager."));
		return;
	}


	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

void SStackNodeRoot::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{

}



void SStackNodeRoot::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					CreateTitleWidget(NodeTitle)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					CreateNodeContentArea()
				]
		];
}

TSharedRef<SWidget> SStackNodeRoot::CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle)
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(STextBlock)
				.Text(FText::FromString("Stack Node"))
				.TextStyle(FAppStyle::Get(), "Graph.Node.NodeTitle")
		];
}

TSharedRef<SWidget> SStackNodeRoot::CreateNodeContentArea()
{
	return CreateNodeStack();
}

TSharedRef<SWidget> SStackNodeRoot::CreateNodeStack()
{
	return SNew(SStackNodeEntries, *RootManager, *SelectionManager);
}

#undef LOCTEXT_NAMESPACE