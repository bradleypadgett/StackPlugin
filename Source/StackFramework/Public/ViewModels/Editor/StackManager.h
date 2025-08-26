#pragma once



//class FStackScriptManager;
class FStackHandleManager;
class UStackEditorData;
class IStackSource;
class UStack;

// TO~DO - mayyybe add viewmodel manager for all these viewmodels
class FStackManager : public TSharedFromThis<FStackManager>
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnHandleRemoved);

	FOnHandleRemoved& OnHandleRemoved();

public:
	FStackManager();
	~FStackManager();

	void Initialize(TScriptInterface<IStackSource> InStackSource);
	void Initialize(UStack& InStack);

	UStackEditorData& GetStackEditorData() const;
	IStackSource* GetStackSource() const;

	TSharedPtr<FStackHandleManager> GetHandleManager(const FStackHandleManager& InHandleManager) const;
	//TSharedRef<FStackScriptManager> GetScriptManager();

	void Reset();

private:

	UPROPERTY()
	TScriptInterface<IStackSource> StackSource;

	TWeakObjectPtr<UStack> StackWeak;

	TSharedPtr<FStackHandleManager> HandleManager;
	//TSharedRef<FStackScriptManager> ScriptManager;

private:
	FOnHandleRemoved OnHandleRemovedDelegate;

};
