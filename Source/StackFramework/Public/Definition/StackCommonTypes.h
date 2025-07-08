#pragma once



// Defines different flags to use in conjunction with OnStructureChanged delegates for stack entries and related classes. */
// (Taken directly from NiagaraEditorCommon.h - comments as well)
enum EStackStructureChangedFlags
{
	/** The actual stack structure changed - used to invalidate or refresh previous state, like search results */
	StructureChanged = 1 << 0,
	/** Only filtering changed; we don't need to invalidate or refresh as much state */
	FilteringChanged = 1 << 1
	// add more flags here if needed
};

/** Defines different usages for a Stack script. */
UENUM()
enum class EStackModuleUsage : uint8
{
	Module,       // Most common – reusable building block | Called during preview/compile
	Function,     // Logic-only helper | Called by Modules
	CreateStage,  // Like Spawn – builds layout | Called during Compile
	UpdateStage   // Like Update – runtime reaction/refresh | Called during runtime
};