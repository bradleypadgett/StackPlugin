# Stack | Unreal Engine Plugin

A modular Stack-driven ecosystem in Unreal Engine. Currently in early stages of development.


In development ~
- StackFramework : Public API for defining new Stack nodes. Handles the plumbing for all Stacks and offers helpers for hooking up the System into new editors.
- StackDesigner : Available within all blueprint actors via an integrated 'Designer' editor (similar to widget BPs). Allows users to customize their actors' Details Panel. This is an implementation of the StackFramework API.

Planned modules (both implementations of the StackFramework) ~
- StackEditor : Standalone editor for creating Stack asset types.
- StackNodes : Runtime module for hosting customized Stack K2 Blueprint nodes.