### 🏗️ PanelDesigner Stack UI Integration | Milestone I

---

#### NiagaraEditorWidgets

| NiagaraEditorWidgets/*     | StackFramework/*              |
| -------------------------- | ----------------------------- |
| 💎 : /*/                   | /Widgets/                     |
| 🌸 : /Stack/               | /Widgets/                     |
| 🪨 : /DetailCustomization/ | /Widgets/DetailCustomization/ |

#### NiagaraEditor

| NiagaraEditor/*                   | StackFramework/*      |
| --------------------------------- | --------------------- |
| 🌼 : /*/                          | /*/                   |
| 🪷 : /Config/                     | /Config/              |
| 🌻 : /Customizations/*            | /Customizations/      |
| 💐 : /Toolkits/*                  | /Toolkits/            |
| 🥀 : /TypeEditorUtilities/        | /TypeEditorUtilities/ |
| 🪻 : /ViewModels/                 | /ViewModels/Editor/   |
| 💮 : /ViewModels/HierarchyEditor/ | /ViewModels/Editor/   |
| 🌹 : /ViewModels/Stack            | /ViewModels/          |
| 🌷 : /Widgets/*                   | /Widgets/Editor/      |
| 🌺 : /Internal/                   | /*                    |

Order to create classes: [`🪛` / `📌` / `📍` / `🎯`] Simultaneously in that order.

- Both lists in each Phase, in practice, are treated as one unit.

⚠️ : As I implement classes these will be a `To-do later` so I can move forward.

---

### 🌱 Phase I | Minimum Visual Stack (MVP)

To get *something visual and placeable* working in the editor~

```
SStackNode
└── SStackView
    └── SStackList
        └── SStackEntry
            └── SStackRow
                └── SStackItem
```

#### NiagaraEditorWidgets/ | StackFramework/Widgets/

1. **💎 SNiagaraOverviewStackNode** 🪛 (SStackNode) ✅
   
   * Container node in graph (inherits `SGraphNode`).
   * ⚠️ Emitter thumbnail, summary view toggle, isolate toggle, pins, etc.
   * ⚠️ Inject SStackView

2. **💎 SNiagaraOverviewStack** 📌 (SStackView) ✅
   
   * Renders the list of entries inside the graph node.
   * ⚠️ Selection support, drag/drop handling
   * ⚠️ Tick refresh / filtering
   * ⚠️ Enable checkbox / delete button

3. **💎 SNiagaraStackEntryWidget** 📌 (SStackEntry) ✅
   
   * Renders a single entry widget from data.
   * ⚠️ Rename support / icon rendering
   * ⚠️ Indentation (sidebar line)
   * ⚠️ Enabled state / interaction hooks

4. **💎 SNiagaraStack** 📌 (SStackList) ✅
   
   * Core ListView/TreeView rendering and layout.
   * ⚠️ Collapse/expand entries with editor data hooks
   * ⚠️ Entry filtering with categories or search
   * ⚠️ Scroll-to-entry with tab syncing
   * ⚠️ Drag/reorder

5. **🌸 SNiagaraStackTableRow** 📌 (SStackRow) ✅
   
   * Concrete row implementation for rendering per-entry UI.
   * ⚠️ Render icons, names, collapse buttons

6. **🌸 SNiagaraStackItem** 📌 (SStackItem) ✅
   
   * Visual wrapper for stack entry content, used in SStackRow
   * ⚠️ Toggles, icons, spacing, interactive entry UI

#### NiagaraEditor/ | StackFramework/

1. **🌹 NiagaraStackEntry** 🪛 (StackEntry) ✅
   
   * Base class for *all* stack ViewModels.
   * ⚠️ Add support for filtering, selection, and structure change notifications
   * ⚠️ Implement virtual functions like `GetDisplayName()`, `GetCanExpand()`, `GetStackRowStyle()`, etc.
   * ⚠️ Support stack issues, validation, rename, delete, copy/paste

2. **🌹 NiagaraStackRoot** 🪛 (StackViewModel) ✅
   
   * Stack container viewmodel, represents section - 'Particle Spawn' / 'System Settings'.
   * ⚠️ Add logic to `RefreshChildrenInternal` that creates subgroups

3. **🌼 NiagaraOverviewNode** 🪛 (StackNode) ✅
   
   * Base stack node.

4. **🪻 NiagaraOverviewGraphViewModel** 📍 (StackGraphViewModel) ✅
   
   * Handles layout and contents of overview graph.
   * ⚠️ Hook up real selection tracking between graph and system
   * ⚠️ Support for view settings + zoom state
   * ⚠️ Node paste, duplicate, rename, delete logic
   * ⚠️ Allow toggling data-only usage (`bIsForDataProcessingOnly`)

5. **🪻 NiagaraSystemViewModel** 📍 (StackEditorViewModel) ✅
   
   * Master ViewModel for editor. Template for hooking up tabs (i.e. palette)
   * ⚠️ Expose selection viewmodel, pinned items, and toolkit hooks
   * ⚠️ Implement stack refresh/dirty logic and `ResetStack()`
   * ⚠️ Wire up compile/request hooks if needed
   * ⚠️ Add delegates for structure change, undo callbacks

6. **🪻 NiagaraSystemSelectionViewModel** 📍 (StackSelectionViewModel) ✅
   
   * Handles stack entry selections / to the Details Panel.
   * ⚠️ Hook up to Details panel

7. **🌼 NiagaraStackEditorData** 🎯 (StackEditorData) ✅
   
   * Editor-only state like expansion/collapse per entry.
   * ⚠️ Persist UI state between editor sessions
   * ⚠️ Display names / Notes & Dismissed Issues for error display
   * ⚠️ Inline display mode

8. **🌹 NiagaraStackGraphUtilities** 🎯 (StackGraphUtilities) ✅
   
   * ⚠️ Helpers for spawning stack entries.
   * ⚠️ Copy/paste , Drag/Drop , Undo/Redo support
   * ⚠️ Support spawning from Palette 'Create from template'
   * ⚠️ ID generation , Graph traversal/context , type filtering

---

### 🪴 Phase II | Core Functional Rows

Hooking up actual module-style rows and grouping behavior~

#### NiagaraEditorWidgets/ | StackFramework/Widgets/

7. **🌸 SNiagaraStackModuleItem** 🪛 (SStackModuleItem)
   
   * Handles editable functional modules (core editing row).

8. **🌸 SNiagaraStackItemGroup** 📌 (SStackItemGroup)
   
   * Nestable group rows with expand/collapse.

9. **💎 NiagaraStackCommandContext** 🎯 (StackCommandContext)
   
   * Cut/copy/paste/rename command logic for stack entries.

10. **💎 SNiagaraParameterDropTarget** 🎯 (SStackParameterDropTarget)
    
    * Drag/drop handler for parameter reordering or injection.

#### NiagaraEditor/ | StackFramework/

9. **🌹 NiagaraStackItem** 🪛 (StackItem)
   
   * ViewModel for stack items.

10. **🌹 NiagaraStackModuleItem** 🪛 (StackModuleItem)
    
    * ViewModel for stack rows like “Scale Color” or other modules.

11. **🌹 NiagaraStackItemGroup** 📌 (StackItemGroup)
    
    * ViewModel for adding group rows.

12. **🌹 NiagaraStackSystemPropertiesItem** 📌 (StackPropertiesItem)
    
    * Stack item for editable system properties.

13. **🌹 NiagaraStackSystemSettingsGroup** 📌 (StackSettingsGroup)
    
    * Stack group for system-level settings.

14. **🥀 NiagaraBoolTypeEditorUtilities** 📍 (StackBoolTypeEditorUtilities)
    
    * Helpers for editing/displaying "bool" properties in stack rows.

15. **🪻 NiagaraParameterCollectionAssetViewModel** 📍 (ParameterCollectionAssetViewModel)
    
    * ViewModel for collection asset editor.

16. **🪻 NiagaraParameterDefinitionsPanelViewModel** 📍 (ParameterDefinitionsPanelViewModel)
    
    * Controls param defs panel.

17. **🌼 SNiagaraGraphPinNumeric** 📍 (SStackGraphPinNumeric)
    
    * Slate widget for numeric pins.

18. **🌷 SNiagaraNumericDropDown** 📍 (SStackNumericDropDown) [**Header Only**]
    
    * Templated dropdown for numeric input with optional pill icons and descriptions.

19. **🌼 NiagaraObjectSelection** 📍 (StackObjectSelection) [**Header Only**]
    
    * Tracks selected UObjects and notifies listeners (e.g., for syncing panels).

20. **🌹 NiagaraStackSelection** 📍 (StackSelection)
    
    * Enables stack ↔ details panel selection sync.

---

### 🌲 Phase III | Utilities, Style, and Polish

Transitioning into interactivity and functionality~

#### NiagaraEditorWidgets/ | StackFramework/Widgets/

11. **💎 NiagaraEditorWidgetsStyle** 🪛 (StackStyle) ✅
    
    * Used for icon styling, category color brushes, etc.

12. **💎 NiagaraEditorWidgetsModule** 🪛 (StackStyleModule) ✅
    
    * Custom Slate styling and brushes for stack UI.

13. **💎 NiagaraEditorWidgetsUtilities** 🪛 (StackUtilities) ✅
    
    * Shared layout helpers, icon names, drag-drop rules, etc.

14. **🌸 SNiagaraStackIndent** 📌 (SStackIndent)
    
    * Draws nesting guides between rows.

15. **🌸 SNiagaraStackItemFooter** 📌 (SStackItemFooter)
    
    * Shows footers like advanced toggle/tooltips.

16. **🌸 SNiagaraStackInheritanceIcon** 📌 (SStackInheritanceIcon)
    
    * Icon indicating inherited vs overridden properties.

17. **🪨 SNiagaraNamePropertySelector** 🎯 (SStackNamePropertySelector)
    
    * A widget for name selection/assignment.

18. **🪨 NiagaraDataInterfaceDetails** 🎯 (StackDataInterfaceDetails)
    
    * For general-purpose data-driven stack detail layouts.

#### NiagaraEditor/ | StackFramework/

21. **🌷 NiagaraEditorStyle.h** 🪛 (StackEditorStyle) ✅
    
    * Registers brushes/colors/fonts.

22. **🌷 NiagaraEditorUtilities.h** 🪛 (StackEditorUtilities)
    
    * Wide set of editor helpers.

23. **🌷 SDynamicLayoutBox** 🪛 (SStackLayoutBox)
    
    * Custom layout widget.

24. **🌷 SNiagaraSelectedObjectsDetails** 📍 (SelectedObjectsDetails)
    
    * View-side details panel wrapper, should pair with the selection ViewModels.

25. **🌷 SNiagaraSelectedAssetDetails** 📍 (SStackSelectedAssetDetails)
    
    * Details panel for selected assets.

26. **🪻 NiagaraCurveSelectionViewModel** 📍 (StackCurveSelectionViewModel)
    
    - Tracks curve editor selection.