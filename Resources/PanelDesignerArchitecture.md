# 🏗 PanelDesigner Plugin Architecture 🏗

This document outlines the PanelDesigner plugin's architecture, which re-integrates AActor's Blueprint Editor to create a custom graph-based Slate/UMG UI editing system.

---

## ♻️ Editor Ownership & Lifecycle ♻️

```
UPanelDesignerSubsystem (global singleton)
└── injects →
    UPanelDesignerBlueprintExtension (per open Blueprint)
    ├── stores →
    │   - CurrentMode ("PanelDesignerMode" or "BlueprintMode")
    │   - Pointer to UPanelDesignerGraph (created if missing)
    └── ensures →
        - Graph is created if not found in FunctionGraphs
        - Graph is outered to the Blueprint
        - Graph is added to Blueprint->FunctionGraphs for persistence
```

---

## 🧠 Blueprint Editor Override 🧠

```
FPanelDesignerAssetActions (registered in StartupModule)
└── overrides →
    OpenAssetEditor() if BP->GeneratedClass inherits AActor
    └── opens →
        FPanelDesignerBlueprintEditor (subclass of FBlueprintEditor)
        └── calls →
            InitPanelDesignerEditor(...)

FPanelDesignerBlueprintEditor
└── adds →
    - "BlueprintMode" → FReplicatedBlueprintEditorMode (1:1 copy of Epic’s layout)
    - "PanelDesignerMode" → FPanelDesignerMode (custom layout)
    - Calls SetCurrentMode(...) after adding both
```

---

## 🧩 Application Modes 🧩

```
FReplicatedBlueprintEditorMode
└── reimplements →
    Epic’s default Blueprint editor layout (tabs, docking, stacks)
    (Used when plugin is enabled to simulate default behavior)

FPanelDesignerMode
└── sets →
    TabLayout to use custom layout
    Registers only plugin-specific tabs (Graph, Variables, etc.)
```

---

## 🌊 Tab Registration Flow 🌊

```
FPanelDesignerTabs (global helper class)
└── provides →
    static RegisterAll(...) method to add custom tabs
    (e.g., Graph, Selection, Preview, Variables)

SPanelDesignerGraphEditor
└── builds →
    - Graph tab's SGraphEditor content

SPanelDesignerSelectionPanel (optional)
└── builds →
    - Selection panel (Niagara-style stack)

SPanelDesignerPreviewPanel (optional)
└── builds →
    - Visual layout preview

SPanelDesignerVariablePanel (optional)
└── builds →
    - Variable list or controls
```

---

## 💾 Saved Data Structure 💾

```
UBlueprint (owning asset)
└── stores →
    UPanelDesignerGraph (outered and stored in FunctionGraphs)

UPanelDesignerBlueprintExtension (transient)
└── stores →
    - CurrentMode
    - Transient editor UI state
    - Graph pointer (persisted via Blueprint)
```

---

## 📚 Class Index 📚

### 🧰 Integration & Extension

- **UPanelDesignerSubsystem** — Injects the BlueprintExtension.
- **UPanelDesignerBlueprintExtension** — Stores transient UI state and Blueprint mode toggle.
- **FPanelDesignerAssetActions** — Overrides asset opening for AActors.

### 📋 Blueprint Editor & Modes

- **FPanelDesignerBlueprintEditor** — Subclass of `FBlueprintEditor`, adds application modes.
- **FReplicatedBlueprintEditorMode** — Reimplements the full default Blueprint layout.
- **FPanelDesignerMode** — Custom application mode for PanelDesigner tabs.

### 🗂️ Tabs

- **FPanelDesignerTabs** — Static helper for registering tabs.
- **SPanelDesignerGraphEditor** — Graph tab content (uses SGraphEditor).
- **SPanelDesignerSelectionPanel** — Stack-style selection view.
- **SPanelDesignerPreviewPanel** — Optional layout preview panel.
- **SPanelDesignerVariablePanel** — Optional Blueprint-like variable list.

---

## 🔌 Plugin Integration Notes 🔌

- Plugin overrides only `AActor`-based Blueprints.
- `FPanelDesignerBlueprintEditor` replaces the default editor instance only for actors.
- `FReplicatedBlueprintEditorMode` ensures consistency with the default tab layout.
- Turning off the plugin returns to Epic’s default behavior — no data is lost.
- Layout customization uses `FTabManager::NewLayout()` just like Epic’s tools.
- All tabs are registered explicitly in each mode’s `RegisterTabFactories()`.