#pragma once

enum class EngineState
{
	Edit,
	Play,
};

enum class SceneState
{
	Initialize,
	Update,
	Terminate
};

enum class ShapeType
{
	Rectangle,
	Circle,
	Convex
};

enum class TileType
{
	Conventional,
	Isometric
};

enum class ScriptLanguage // only acceptable language(s) at the moment
{
	Chaiscript,
	CSharp,
	Javascript,
	Lua,
	Python
};

enum class AnchorResize
{
	Left,
	Top,
	Right,
	Bottom,
	LeftTop,
	LeftBottom,
	RightTop,
	RightBottom,
};

enum class AnchorPosition
{
	Left,
	LeftTop,
	LeftBottom,
	Top,
	Right,
	RightTop,
	RightBottom,
	Bottom,
};

enum class PortSideAnchor
{
	Left,
	Top,
	Width,
	Height
};

enum class ExplorerTab
{
	Events,
	Scenes,
	Assets
	// @TODO determine
};

enum class ModifierTab // @TODO update
{
	Tab1,
	Tab2,
	Tab3
};

enum class AuxiliaryTab // @TODO update
{
	Console,
	Warnings,
	Errors,
};