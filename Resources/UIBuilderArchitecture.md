# 🧠 UIBuilder Plugin Architecture Guide

This document outlines the architecture of the UIBuilder plugin, which integrates with the Unreal Blueprint Editor to create a custom graph-based UI editing system.

---

## 🔁 Editor-Only Ownership & Lifecycle

```
UUIBuilderSubsystem (global singleton)
└── injects →
    UUIBuilderBlueprintExtension (per open Blueprint, not saved)
    ├── holds →
    │   UUIBuilderGraph* (pointer only; not serialized)
    │
    ├── ensures →
    │   - Graph is created if missing
    │   - Graph is outered to the Blueprint
    │   - Graph is added to Blueprint->FunctionGraphs (or similar)
    │
    └── tracks →
        - Current tab mode (Designer/Graph)
        - Pinned tab (optional)
        - Other transient settings (non-persistent)
```

---

## 🧱 Graph Data Saved in Blueprint Asset

```
UBlueprint (owning asset)
└── owns →
    UUIBuilderGraph (must be outered to Blueprint)
    └── owns →
        UUIBuilderGraphNode_* (one per node; saved with graph)
```

---

## 🎛️ Tab + UI Layer (Per-Tab Flow)

```
FUIBuilderTabRegistrar (global)
└── registers →
    Custom tabs (Graph, Designer, etc.)
    └── spawns →
        FUIBuilderGraphController (per tab)
        ├── builds →
        │   - SUIBuilderGraphWidget
        │   - SUIBuilderPreviewPanel (optional)
        │   - SUIBuilderVariablePanel (optional)
        │
        └── accesses →
            UUIBuilderBlueprintExtension → to read graph, mode

        uses →
            FUIBuilderNodeFactory (global) → custom SGraphNode widgets
```

---

## 📚 Class Summaries

### Graph System

- **UUIBuilderGraph** (`UEdGraph`) — The actual graph data structure; added to `FunctionGraphs` for saving.
- **UUIBuilderGraphNode_Base** (`UEdGraphNode`) — Serialized node types inside the graph.
- **UUIBuilderGraphSchema** — Defines node wiring rules, pin types, and context actions.
- **FUIBuilderGraphSidebarAction** — Enables node creation via context menu/drag-drop.
- **FUIBuilderNodeFactory** — Creates `SGraphNode_*` widgets to render each node visually.

### Tab System / UI

- **FUIBuilderTabRegistrar** — Registers tabs with the Blueprint Editor.
- **FUIBuilderGraphController** — Manages tab layout, mode switching, and UI logic.
- **SUIBuilderGraphWidget** — Container for rendering the Graph tab’s graph.
- **SUIBuilderPreviewPanel** — Optional preview of layout, using Slate.
- **SUIBuilderVariablePanel** — Optional variable list/editor panel.

### Blueprint Integration

- **UUIBuilderSubsystem** (`UEditorSubsystem`) — Injects the BlueprintExtension on Blueprint open.
- **UUIBuilderBlueprintExtension** — Stores per-blueprint state like mode and graph pointer (not saved).

---

## 🔑 Integration Reminders

- `UUIBuilderBlueprintExtension` is not saved — use it only for transient state.
- The graph must be outered to the Blueprint and added to a serializable list like `FunctionGraphs`.
- Graph nodes (`UUIBuilderGraphNode_*`) are saved automatically inside the graph.
- Inject custom widgets (sliders, curves, etc.) into the Details panel using `IDetailCustomization`.
- Use `CreateDetailView()` and `SetObject()` to show the Details panel inside custom tabs.

---

## ✅ UX Reminders

- Reuse native systems (Details panel, Graph, etc.) whenever possible.
- Only create custom widgets where they improve clarity or workflow.
- Use one `BlueprintExtension` per Blueprint and one `Subsystem` globally.
- Custom tabs shouldn't have an `FApplicationMode` for non-sublassing integration.

---

## 🧱 Runtime Descriptor Pattern (UMG Compatibility)

```
UUIBuilderGraphNode_* (Editor-only)
└── Inherits from UEdGraphNode
└── Used in the Blueprint Editor graph tab
└── Converts to → UUIBuilderNodeDescriptor_* for runtime use

UUIBuilderNodeDescriptor_* (Runtime-safe)
└── Lightweight config object (UObject or UStruct)
└── Lives in UIBuilderRuntime module
└── Holds widget settings (e.g., Min/Max, Label)
└── Used to spawn UMG widgets at runtime
```

> Editor nodes expose a `ToDescriptor()` method that returns the runtime-safe version.  
> This pattern keeps runtime builds clean while reusing node logic in both the editor and UMG menus.
