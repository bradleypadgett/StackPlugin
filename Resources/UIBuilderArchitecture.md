# 🏗️ UIBuilder Plugin Architecture Guide

This document outlines the architecture of the UIBuilder plugin, which integrates with the Unreal Blueprint Editor to create a custom graph-based UI editing system.

---

## ♻️ Editor-Only Ownership & Lifecycle

```
UUIBuilderSubsystem (global singleton)
└── injects →
    UUIBuilderBlueprintExtension (per open Blueprint)
    ├── stores →
    │   - CurrentMode (e.g., "Designer" or "Graph")
    │   - Pointer to UUIBuilderGraph (created if missing)
    └── ensures →
        - Graph is created if not found in FunctionGraphs
        - Graph is outered to the Blueprint
        - Graph is added to Blueprint->FunctionGraphs for persistence
```

---

## 🌊 Tab Management Flow

```
UUIBuilderBlueprintExtension (per Blueprint)
└── manages →
    ├── CurrentTabMode (FName)
    ├── Tab layout state (active tab, pinned tab, etc.)
    ├── Reference to UUIBuilderGraph (stored inside Blueprint)
    └── Broadcasts OnModeChanged()

FUIBuilderTabRegistrar (global helper class)
└── registers →
    ├── Tabs with the Blueprint Editor (graph, preview, variables)
    └── Spawner delegates call into the system to build tab content

SUIBuilderGraphEditor
└── builds →
    ├── Graph tab’s SGraphEditor
    └── Custom UIBuilder graph visuals (via mvvm stack)

SUIBuilderSelectionPanel
└── builds →
    └── Mirrors Niagara's property display with selected stack data

SUIBuilderPreviewPanel (optional)
└── builds →
    └── Preview layout based on current graph

SUIBuilderVariablePanel (optional)
└── builds →
    └── Stripped down version of "My Blueprint"
```

---

## 💾 Graph Data Saved (Serialized / Transient)

```
UBlueprint (owning asset)
└── stores →
    └── UUIBuilderGraph (outered to Blueprint)
        └── stores → 
            └── UUIBuilderStackSection (section block)

UUIBuilderBlueprintExtension (transient per Blueprint)
└── stores →
    ├── Graph* pointer (serialized to UBlueprint)
    ├── CurrentTabMode ("Designer", "Graph")
    └── Editor-only toggle flags (panel visibility, UI state, etc.)
```

---

## 🎨 UIBuilder Graph Rendering Flow

```
UIBuilderTabManager (per Blueprint) (behavior)
└── builds →
    └── SUIBuilderGraphEditor (layout)

SUIBuilderGraphEditor
└── creates →
    ├── SGraphEditor (layout + behavior)
    ├── GraphToEdit = UUIBuilderGraph* (data)
    └── Appearance = FGraphAppearanceInfo (behavior)
         configures zooming, overlays, etc.
```

---

## 📚 Class Summaries

#### Blueprint Integration

- **UUIBuilderSubsystem** (`UEditorSubsystem`) — Injects the BlueprintExtension on Blueprint open.
- **UUIBuilderBlueprintExtension** — Stores tab layout state (current mode, toggle flags, graph pointer) 

#### Graph System

- **SUIBuilderGraphEditor** — Tab container for rendering the Graph tab’s graph.
- **UUIBuilderGraph** (`UEdGraph`) — The actual graph data structure; added to `FunctionGraphs` for saving.
- **UUIBuilderGraphSchema** — Defines connnection rules, context actions, and drag/drop validation.
- **FUIBuilderGraphSidebarAction** — Registers palette items, group stack types, handles drag/drop.

#### Tab System / UI

- **FUIBuilderTabRegistrar** — Registers tabs with the Blueprint Editor.
- **FUIBuilderTabManager** — Manages tab layout, mode switching, and UI logic.
- **SUIBuilderSelectionPanel** — Reflects selected stack data in a contextual panel
- **SUIBuilderPreviewPanel** — Optional preview of layout, using Slate.
- **SUIBuilderVariablePanel** — Optional variable list/editor panel.

---

## 🔌 Integration Reminders

- `UUIBuilderBlueprintExtension` is not saved — use it only for transient state.
- The graph must be outered to the Blueprint and serialized in `FunctionGraphs`.
- Inject custom widgets (sliders, curves, etc.) into the Details panel using `IDetailCustomization`.
- Use `CreateDetailView()` and `SetObject()` to show the Details panel inside custom tabs.
- Switching between `Graph` and `Designer` modes controls which tabs are visible. When in `Designer` mode, only the plugin's custom tabs are shown. When in `Graph` mode, the default Blueprint tabs (e.g. Event Graph) are shown.
- Tab registration and management aren't instanced, they're only helper classes.

---

## 🤳 UX Reminders

- Reuse native systems (Details panel, My Blueprint, etc.) whenever possible.
- Only create custom widgets where they improve clarity or workflow.
- Use one `BlueprintExtension` per Blueprint and one `Subsystem` globally.
- Custom tabs won't use an `FApplicationMode` for non-sublassing integration.

---
