### 🏠 PanelDesigner Stack UI Integration | Milestone II

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

### 🌱 Phase I | General Functionality

🪛 *Core Input Rendering*

* FunctionInput provides the ViewModel, PropertyRow drives rendering, and the widgets render actual input content and name

📌 *Input Behaviors*

* Extends the core inputs with conditional behavior and external binding. They hook directly into FunctionInput

📍 *Output / Metadata Rows*

* Support grouped parameters and output sections

🎯 *Parameter Panel Support*

* Enables parameter collection, editing UI, and issue displays

#### NiagaraEditorWidgets/ | StackFramework/Widgets/

1. **🌸 SNiagaraStackFunctionInputValue** 🪛 (SStackFunctionInputValue)
   
   * Actual slider/input widget. Supports inline, dropdown, and expression editing modes.

2. **🌸 SNiagaraStackFunctionInputName** 🪛 (SStackFunctionInputName)
   
   * Label for stack row input. Inline renaming, edit condition toggles, and namespace menus.

3. **🌸 SNiagaraStackInlineDynamicInput** 🎯 (SStackInlineDynamicInput)
   
   * Shows compact inline input editor in row. Handles graph-based dynamic input formatting and display.🎯

4. **🌸 SNiagaraStackIssueIcon** 🎯 (SStackIssueIcon)
   
   * Small icon indicator for status/validation. Shows error/warning/info icon with tooltip.

5. **🌸 SNiagaraParameterPanel** 🎯 (StackParameterPanel)
   
   * Actual panel widget displaying parameters.

#### NiagaraEditor/ | StackFramework/

1. **🌹 NiagaraStackFunctionInput** 🪛 (StackFunctionInput)
   
   * Represents a single editable input.

2. **🌼 NiagaraStackFunctionInputBinder** 📌 (StackFunctionInputBinder)
   
   * Links stack input to runtime parameter.

3. **🌹 NiagaraStackFunctionInputCondition** 📌 (StackFunctionInputCondition)
   
   * Tracks edit conditions - bool-driven.

4. **🌹 NiagaraStackModuleItemLinkedInputCollection** 📍 (StackModuleItemLinkedInputCollection)
   
   * Grouped inputs bound to dynamic graph inputs.

5. **🌹 NiagaraStackModuleItemOutput** 📍 (StackModuleItemOutput)
   
   * Output definition for a module.

6. **🌹 NiagaraStackModuleItemOutputCollection** 📍 (StackModuleItemOutputCollection)
   
   * Groups output pins of a module item.

7. **🌹 NiagaraStackInputCategory** 📍 (StackInputCategory)
   
   * Label row separating input sections.

8. **🌻 NiagaraParameterBindingCustomization** 📍 (StackParameterBindingCustomization)
   
   * Customizes bindings between stack input and parameters.

9. **🪻 NiagaraParameterEditMode** 🎯 (StackParameterEditMode)
   
   * Controls whether the user can edit just the value, or also name/type/add/remove. 

10. **🪻 NiagaraParameterViewModel** 🎯 (StackParameterViewModel)
    
    * Used for parameter binding/editing support inside stack rows.

11. **🌷 SNiagaraParameterMenu** 🎯 (SStackParameterMenu)
    
    * *Base + derived widgets for parameter selection UIs — dropdowns that add variables to graphs or stacks.

12. **🌷 NiagaraParameterPanelTypes** 🎯 (StackParameterPanelTypes) [**Header Only**]
    
    * What it does: Defines data for parameter list entries (used in parameter panels).

13. **🪻 NiagaraParameterPanelViewModel** 🎯 (StackParameterPanelViewModel)
    
    * ViewModel for grouped parameters. Kinda like a parameter Details panel.

14. **🌼 NiagaraStackErrorItem** 🎯 (StackParameterPanelViewModel)
    
    * Implements stack entries for errors, warnings, and fix buttons shown inline in the stack (with dismiss/fix support).

15. **🌹 SNiagaraStackErrorItem** 🎯 (SStackErrorItem)
    
    * Displays errors within stack rows. Supports error, warning, info display and fix/link buttons.

---

### 🪴 Phase II | Stack Group and Input UX

🪛 *Property Display*

* Utilities support property rendering

📌 *Notes / Comments*

* Extends the core inputs with conditional behavior and external binding. They hook directly into FunctionInput

📍 *Script / Parameter Hierarchy*

* Support grouped parameters and output sections

🎯 *Group UX / Palette*

* Enables parameter collection, editing UI, inline summaries, and issue displays

#### NiagaraEditorWidgets/ | StackFramework/Widgets/

6. **🌸 NiagaraStackPropertyRowUtilities** 🪛 (StackPropertyRowUtilities)
   
   * Utilities for handling Niagara-specific reflection tools.

7. **💎 SNiagaraStackNote** 📌 (StackNote)
   
   * Comment-like rows. Editable notes with header/body, color, and inline display toggle.

8. **🌸 SNiagaraStackItemGroupAddButton** 🎯 (StackItemGroupAddButton)
   
   * Add button for group containers. Supports labeled or icon-only buttons with add menu or direct add.

9. **🌸 SNiagaraStackItemGroupAddMenu** 🎯 (StackItemGroupAddMenu)
   
   * Menu logic for group add actions. Displays filterable, categorized addable items via action selector.

10. **🌸 SNiagaraStackValueCollection** 🎯 (StackValueCollection)
    
    * Renders multiple grouped inputs. Displays a sectioned, interactive value selector for grouped parameters.

11. **💎 SNiagaraOverviewInlineParameterBox** 🎯 (StackInlineParameterBox)
    
    * Condensed parameter value editor (overview embedded use).

12. **💎 SNiagaraSummaryViewToggle** 🎯 (StackSummaryViewToggle)
    
    * Allows collapsing entries into a summary view (future generalization candidate).

#### NiagaraEditor/ | StackFramework/

16. **🌹 NiagaraStackItemPropertyHeaderValueShared** 🪛 (StackItemPropertyHeaderValueShared)
    
    * Shared visual logic for item headers.

17. **🌹 NiagaraStackPropertyRow** 🪛 (StackPropertyRow)
    
    * Editable property row wrapper.

18. **🌹 NiagaraStackNote** 📌 (StackNote)
    
    * Colored comment rows in stack..

19. **🌹 NiagaraStackCommentCollection** 📌 (StackCommentCollection)
    
    * Collects inline comment items.

20. **🌹 NiagaraStackScriptItemGroup** 📍 (StackScriptItemGroup)
    
    * Groups together script-based items.

21. **🌹 NiagaraStackScriptHierarchyRoot** 📍 (StackScriptHierarchyRoot)
    
    * Creates top-level script stack entries.

22. **💮 NiagaraScriptParametersHierarchyViewModel** 📍 (StackScriptParametersHierarchyViewModel)
    
    * Organizes parameters in a tree. Used in overview or detail editor.

23. **💮 NiagaraUserParametersHierarchyViewModel** 📍 (StackUserParametersHierarchyViewModel)
    
    * Organizes parameters in a tree. Used in overview or detail editor.

24. **🌷 SItemSelector** 🎯 (SItemSelector) [**Header Only**]
    
    * Generic multi-item selector UI with checkboxes or pickers.

25. **🌹 INiagaraStackItemGroupAddUtilities** 🎯 (IStackItemGroupAddUtilities) [**Header Only**]
    
    * Defines an interface + helpers for stack groups that let users add new entries (like modules or items) via a "+" dropdown.

26. **🌷 SNiagaraActionMenuExpander** 🎯 (SStackActionMenuExpander) [**Header Only**]
    
    * Custom expander arrow used in SGraphActionMenu entries.

27. **🌹 NiagaraStackValueCollection** 🎯 (StackValueCollection)
    
    * Displays grouped input values.

28. **🌹 NiagaraStackSummaryViewInputCollection** 🎯 (StackSummaryViewInputCollection)
    
    * Grouped input shown in summary view.

29. **💮 NiagaraSummaryViewViewModel** 🎯 (StackSummaryViewModel)
    
    * Drives the collapsed 'Summary View' in Niagara's stack UI.

30. **🪻 NiagaraUserParameterPanelViewModel** 🎯 (StackUserParameterViewModel)
    
    * Organizes user-defined parameters in a tree.

31. **🌷 SNiagaraParameterPanelPaletteItem** 🎯 (StackParameterPanelPaletteItem)
    
    * Could support a drag-and-drop menu to add modules.

32. **🪻 TNiagaraViewModelManager** 🎯 (TStackViewModelManager) [**Header Only**]
    
    * Template for tracking which ViewModel is observing which object.

---

### 🌲 Phase III | Editor Embeds and Visual Overlays

🪛 *Clipboard / Logging / Utilities*

* Copy/paste behavior, polishing UX

📌 *Overview Graph UI / Curve Visuals*

* Builds the actual visual structure and nodes of the system-level overview graph. The node factory must exist to support rendering

📍 *UObject / Detail Embeds*

* UObject-based inline customization (e.g., curves, data channels, custom struct arrays)

🎯 *Optional Tooling / Asset Enhancements*

* Broader UX, utilities, and polish :')

#### NiagaraEditorWidgets/ | StackFramework/Widgets/

13. **💎 SNiagaraOverviewGraph** 📌 (SStackGraph)
    
    * Graph node view inside stack views.

14. **💎 SNiagaraOverviewGraphTitleBar** 📌 (SStackGraphTitleBar)
    
    * Dynamic title bar with status, warnings, and metadata display.

15. **💎 NiagaraOverviewGraphNodeFactory** 📌 (StackGraphNodeFactory)
    
    * Registers graph node factories tied to stack-driven editors.

16. **💎 NiagaraCurveOverview** 📌 (SStackCurve)
    
    * Preview of curve layouts.

17. **🪨 NiagaraDataInterfaceCurveDetails** 📍 (StackCurveDataDetails)
    
    * Displays editable curve data linked to stack entries.

18. **🪨 NiagaraDetailSourcedArrayBuilder** 📍 (StackArrayBuilderUtilities)
    
    * Builds dynamic arrays in detail panels.

19. **🪨 NiagaraDataChannelDetails** 📍 (StackDataChannelDetails)
    
    * Data channel entry customization.

#### NiagaraEditor/ | StackFramework/

33. **🌼 NiagaraClipboard** 🪛 (StackClipboard)
    
    * Clipboard helpers for copy/paste of stack entries.

34. **🌹 NiagaraStackClipboardUtilities** 🪛 (StackClipboardUtilities)
    
    * Copy/paste for stack entries.

35. **🪻 NiagaraMessageLogViewModel** 🪛 (StackMessageLogViewModel)
    
    * ViewModel for per-system or stack logging.

36. **🌼 NiagaraNotificationWidgetProvider** 🪛 (StackNotificationWidgetProvider)
    
    * Displays notifications in stack.

37. **🌹 NiagaraStackObject** 📍 (StackObject)
    
    * Displays a UObject or UStruct inside the stack as a collapsible property editor (like a mini details panel).

38. **🌻 NiagaraStackObjectPropertyCustomization** 📍 (StackObjectPropertyCustomization)
    
    * Customizes how UObjects appear inside stack entries.

39. **🌹 NiagaraStackObjectShared** 📍 (StackObjectShared) [**Header Only**]
    
    * Filter or modify how the stack's detail panel nodes are rendered (e.g., hide/show properties).

40. **🌹 NiagaraStackObjectIssueGenerator** 📍 (StackObjectIssueGenerator)
    
    * Allows attaching issues/warnings to a reflected object in the stack (e.g., “Platform not supported”).

41. **🌼 NiagaraSystemDetailsCustomization** 📍 (StackDetailsCustomization)
    
    * Helps when customizing the Details view of the entire stack asset. May remove.

42. **🌷 SNiagaraFilterBox** 📍 (SStackFilterBox)
    
    * Text filter input box

43. **🪻 NiagaraCollectionParameterViewModel** 🎯 (StackCollectionParameterViewModel)
    
    * Handles editing parameter collections.

44. **🪻 NiagaraParameterCollectionViewModel** 🎯 (StackParameterCollectionViewModel)
    
    * High-level ViewModel for Niagara collections.

45. **🪻 NiagaraEmitterHandleViewModel** 🎯 (StackEmitterHandleViewModel)
    
    * ViewModel for emitter handles inside systems.

46. **🌷 SNiagaraColorEditor** 🎯 (SStackColorEditor)
    
    * Color picker widget.

47. **🌼 NiagaraSpawnShortcut** 🎯 (StackSpawnShortcut) [**Header Only**]
    
    * Defines a shortcut (key binding + name) for spawning modules.

48. **🌺 NiagaraStackEntryEnumerable** 🎯 (StackEntryEnumerable)
    
    * Helpful for advanced filtering of entries. Future-proofing utility.

49. **🌺 NiagaraStackQuery** 🎯 (StackQuery)
    
    * Useful for rule-based filtering/search. May remove.