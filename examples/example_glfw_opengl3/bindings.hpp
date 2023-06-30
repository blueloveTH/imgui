#pragma once

#include "pocketpy.h"
#include "imgui.h"

namespace pkpy{

inline PyObject* py_var(VM* vm, ImVec2 im_vec){
    Vec2 vec(im_vec.x, im_vec.y);
    return py_var(vm, vec);
}

inline PyObject* py_var(VM* vm, ImVec4 im_vec){
    Vec4 vec(im_vec.x, im_vec.y, im_vec.z, im_vec.w);
    return py_var(vm, vec);
}

template<>
inline ImVec2 py_cast<ImVec2>(VM* vm, PyObject* obj){
    PyVec2 vec = py_cast<PyVec2>(vm, obj);
    return ImVec2(vec.x, vec.y);
}

template<>
inline ImVec4 py_cast<ImVec4>(VM* vm, PyObject* obj){
    PyVec4 vec = py_cast<PyVec4>(vm, obj);
    return ImVec4(vec.x, vec.y, vec.z, vec.w);
}

inline void add_module_imgui(VM* vm){
    PyObject* imgui = vm->new_module("ImGui");

    // struct ImGuiContext;                // Dear ImGui context (opaque structure, unless including imgui_internal.h)
    // NOTE: context is an opaque pointer, so we treat it as void_p
    vm->bind(imgui, "CreateContext()",
        PK_VAR_LAMBDA(ImGui::CreateContext())
        );

    vm->bind(imgui, "DestroyContext(ctx: void_p = None)",
        [](VM* vm, ArgsView args){
            void* ctx = CAST(void*, args[0]);
            ImGui::DestroyContext((ImGuiContext*)ctx);
            return vm->None;
        });

    vm->bind(imgui, "GetCurrentContext() -> void_p",
        PK_VAR_LAMBDA(ImGui::GetCurrentContext())
        );

    vm->bind(imgui, "SetCurrentContext(ctx: void_p)",
        [](VM* vm, ArgsView args){
            ImGui::SetCurrentContext((ImGuiContext*)CAST(void*, args[0]));
            return vm->None;
        });

    
    // Main
    vm->bind(imgui, "GetIO() -> void_p",
        "access the IO structure (mouse/keyboard/gamepad inputs, time, various configuration options/flags)",
        PK_VAR_LAMBDA(&ImGui::GetIO())
        );

    vm->bind(imgui, "GetStyle() -> void_p",
        "access the Style structure (colors, sizes). Always use PushStyleCol(), PushStyleVar() to modify style mid-frame!",
        PK_VAR_LAMBDA(&ImGui::GetStyle())
        );

    vm->bind(imgui, "NewFrame()",
        "start a new Dear ImGui frame, you can submit any command from this point until Render()/EndFrame().",
        PK_ACTION(ImGui::NewFrame())
        );

    vm->bind(imgui, "EndFrame()",
        "ends the Dear ImGui frame. automatically called by Render(). If you don't need to render data (skipping rendering) you may call EndFrame() without Render()... but you'll have wasted CPU already! If you don't need to render, better to not create any windows and not call NewFrame() at all!",
        PK_ACTION(ImGui::EndFrame())
        );

    vm->bind(imgui, "Render()",
        "ends the Dear ImGui frame, finalize the draw data. You can then get call GetDrawData().",
        PK_ACTION(ImGui::Render())
        );

    vm->bind(imgui, "GetDrawData() -> void_p",
        "valid after Render() and until the next call to NewFrame(). this is what you have to render.",
        PK_VAR_LAMBDA(ImGui::GetDrawData())
        );

    // Demo, Debug, Information
    vm->bind(imgui, "ShowDemoWindow(p_open: void_p = None)",
        "create Demo window. demonstrate most ImGui features. call this to learn about the library! try to make it always available in your application!",
        [](VM* vm, ArgsView args){
            bool* p_open = CAST(bool*, args[0]);
            ImGui::ShowDemoWindow(p_open);
            return vm->None;
        });

    vm->bind(imgui, "GetVersion() -> str",
        "get the compiled version string e.g. \"1.80 WIP\" (essentially the value for IMGUI_VERSION from the compiled version of imgui.cpp)",
        PK_VAR_LAMBDA(ImGui::GetVersion())
        );

    // Styles
    vm->bind(imgui, "StyleColorsDark()",
        "new, recommended style (default)",
        PK_ACTION(ImGui::StyleColorsDark())
        );

    vm->bind(imgui, "StyleColorsLight()",
        "best used with borders and a custom, thicker font",
        PK_ACTION(ImGui::StyleColorsLight())
        );

    vm->bind(imgui, "StyleColorsClassic()",
        "classic imgui style",
        PK_ACTION(ImGui::StyleColorsClassic())
        );

    // Windows
    vm->bind(imgui, "Begin(name: str, p_open: void_p = None, flags=0) -> bool",
R"(
- Begin() = push window to the stack and start appending to it. End() = pop window from the stack.
- Passing 'bool* p_open != NULL' shows a window-closing widget in the upper-right corner of the window,
    which clicking will set the boolean to false when clicked.
- You may append multiple times to the same window during the same frame by calling Begin()/End() pairs multiple times.
    Some information such as 'flags' or 'p_open' will only be considered by the first call to Begin().
- Begin() return false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting
    anything to the window. Always call a matching End() for each Begin() call, regardless of its return value!
    [Important: due to legacy reason, this is inconsistent with most other functions such as BeginMenu/EndMenu,
    BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding BeginXXX function
    returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]
- Note that the bottom of window stack always contains a window called 'Debug'.
)",
        [](VM* vm, ArgsView args){
            const char* name = CAST(CString, args[0]);
            bool* p_open = CAST(bool*, args[1]);
            ImGuiWindowFlags flags = CAST(int, args[2]);
            bool open = ImGui::Begin(name, p_open, flags);
            return VAR(open);
        });

    vm->bind(imgui, "End()",
        PK_ACTION(ImGui::End())
        );

    // Child Windows
    vm->bind(imgui, "BeginChild(str_id: str, size=None, border=False, flags=0)",
R"(
- Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window. Child windows can embed their own child.
- For each independent axis of 'size': ==0.0f: use remaining host window size / >0.0f: fixed size / <0.0f: use remaining window size minus abs(size) / Each axis can use a different mode, e.g. ImVec2(0,400).
- BeginChild() returns false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting anything to the window.
    Always call a matching EndChild() for each BeginChild() call, regardless of its return value.
    [Important: due to legacy reason, this is inconsistent with most other functions such as BeginMenu/EndMenu,
    BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding BeginXXX function
    returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]
)",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImVec2 size = CAST(ImVec2, args[1]);
            bool border = CAST(bool, args[2]);
            ImGuiWindowFlags flags = CAST(int, args[3]);
            bool open = ImGui::BeginChild(str_id, size, border, flags);
            return VAR(open);
        });

    vm->bind(imgui, "EndChild()",
        PK_ACTION(ImGui::EndChild())
        );

    // Windows Utilities
    // - 'current window' = the window we are appending into while inside a Begin()/End() block. 'next window' = next window we will Begin() into.
    vm->bind(imgui, "IsWindowAppearing() -> bool",
        PK_VAR_LAMBDA(ImGui::IsWindowAppearing())
        );

    vm->bind(imgui, "IsWindowCollapsed() -> bool",
        PK_VAR_LAMBDA(ImGui::IsWindowCollapsed())
        );

    vm->bind(imgui, "IsWindowFocused(flags=0) -> bool",
        "is current window focused? or its root/child, depending on flags. see flags for options.",
        [](VM* vm, ArgsView args){
            ImGuiFocusedFlags flags = CAST(int, args[0]);
            return VAR(ImGui::IsWindowFocused(flags));
        });

    vm->bind(imgui, "IsWindowHovered(flags=0) -> bool",
        "is current window hovered (and typically: not blocked by a popup/modal)? see flags for options. NB: If you are trying to check whether your mouse should be dispatched to imgui or to your app, you should use the 'io.WantCaptureMouse' boolean for that! Please read the FAQ!",
        [](VM* vm, ArgsView args){
            ImGuiHoveredFlags flags = CAST(int, args[0]);
            return VAR(ImGui::IsWindowHovered(flags));
        });

    vm->bind(imgui, "GetWindowDrawList() -> void_p",
        "get draw list associated to the current window, to append your own drawing primitives",
        PK_VAR_LAMBDA(ImGui::GetWindowDrawList())
        );

    vm->bind(imgui, "GetWindowPos() -> vec2",
        "get current window position in screen space (useful if you want to do your own drawing via the DrawList API)",
        PK_VAR_LAMBDA(ImGui::GetWindowPos())
        );

    vm->bind(imgui, "GetWindowSize() -> vec2",
        "get current window size",
        PK_VAR_LAMBDA(ImGui::GetWindowSize())
        );

    vm->bind(imgui, "GetWindowWidth() -> float",
        "get current window width (shortcut for GetWindowSize().x)",
        PK_VAR_LAMBDA(ImGui::GetWindowWidth())
        );

    vm->bind(imgui, "GetWindowHeight() -> float",
        "get current window height (shortcut for GetWindowSize().y)",
        PK_VAR_LAMBDA(ImGui::GetWindowHeight())
        );

    // Window manipulation
    // - Prefer using SetNextXXX functions (before Begin) rather that SetXXX functions (after Begin).
    // [SKIP: SetXXX functions]
    vm->bind(imgui, "SetNextWindowPos(pos: vec2, cond=0, pivot=None)",
        "set next window position. call before Begin(). use pivot=(0.5f,0.5f) to center on given point, etc.",
        [](VM* vm, ArgsView args){
            ImVec2 pos = CAST(ImVec2, args[0]);
            ImGuiCond cond = CAST(int, args[1]);
            ImVec2 pivot = CAST_DEFAULT(ImVec2, args[2], ImVec2(0, 0));
            ImGui::SetNextWindowPos(pos, cond, pivot);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowSize(size: vec2, cond=0)",
        "set next window size. set axis to 0.0f to force an auto-fit on this axis. call before Begin()",
        [](VM* vm, ArgsView args){
            ImVec2 size = CAST(ImVec2, args[0]);
            ImGuiCond cond = CAST(int, args[1]);
            ImGui::SetNextWindowSize(size, cond);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowSizeConstraints(size_min: vec2, size_max: vec2)",
        "set next window size limits. use -1,-1 on either X/Y axis to preserve the current size. Sizes will be rounded down. Use callback to apply non-trivial programmatic constraints.",
        [](VM* vm, ArgsView args){
            ImVec2 size_min = CAST(ImVec2, args[0]);
            ImVec2 size_max = CAST(ImVec2, args[1]);
            ImGui::SetNextWindowSizeConstraints(size_min, size_max);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowContentSize(size: vec2)",
        "set next window content size (~ scrollable client area, which enforce the range of scrollbars). Not including window decorations (title bar, menu bar, etc.) nor WindowPadding. set an axis to 0.0f to leave it automatic. call before Begin()",
        [](VM* vm, ArgsView args){
            ImVec2 size = CAST(ImVec2, args[0]);
            ImGui::SetNextWindowContentSize(size);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowCollapsed(collapsed: bool, cond=0)",
        "set next window collapsed state. call before Begin()",
        [](VM* vm, ArgsView args){
            bool collapsed = CAST(bool, args[0]);
            ImGuiCond cond = CAST(int, args[1]);
            ImGui::SetNextWindowCollapsed(collapsed, cond);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowFocus()",
        "set next window to be focused / top-most. call before Begin()",
        [](VM* vm, ArgsView args){
            ImGui::SetNextWindowFocus();
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowScroll(scroll: vec2)",
        "set next window scrolling value (use < 0.0f to not affect a given axis).",
        [](VM* vm, ArgsView args){
            ImVec2 scroll = CAST(ImVec2, args[0]);
            ImGui::SetNextWindowScroll(scroll);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowBgAlpha(alpha: float)",
        "set next window background alpha.",
        [](VM* vm, ArgsView args){
            float alpha = CAST_F(args[0]);
            ImGui::SetNextWindowBgAlpha(alpha);
            return vm->None;
        });

    // Content region
    // - Retrieve available space from a given point. GetContentRegionAvail() is frequently useful.
    // - Those functions are bound to be redesigned (they are confusing, incomplete and the Min/Max return values are in local window coordinates which increases confusion)
    vm->bind(imgui, "GetContentRegionAvail() -> vec2",
        "== GetContentRegionMax() - GetCursorPos()",
        PK_VAR_LAMBDA(ImGui::GetContentRegionAvail())
        );

    vm->bind(imgui, "GetContentRegionMax() -> vec2",
        "current content boundaries (typically window boundaries including scrolling, or current column boundaries), in windows coordinates",
        PK_VAR_LAMBDA(ImGui::GetContentRegionMax())
        );

    vm->bind(imgui, "GetWindowContentRegionMin() -> vec2",
        "content boundaries min (roughly (0,0)-Scroll), in window coordinates",
        PK_VAR_LAMBDA(ImGui::GetWindowContentRegionMin())
        );

    vm->bind(imgui, "GetWindowContentRegionMax() -> vec2",
        "content boundaries max (roughly (0,0)+Size-Scroll) where Size can be override with SetNextWindowContentSize(), in window coordinates",
        PK_VAR_LAMBDA(ImGui::GetWindowContentRegionMax())
        );

    // Window Scrolling
    // - Any change of Scroll will be applied at the beginning of next frame in the first call to Begin().
    // - You may instead use SetNextWindowScroll() prior to calling Begin() to avoid this delay, as an alternative to using SetScrollX()/SetScrollY().
    vm->bind(imgui, "GetScrollX()",
        "get scrolling amount [0 .. GetScrollMaxX()]",
        PK_VAR_LAMBDA(ImGui::GetScrollX())
        );

    vm->bind(imgui, "GetScrollY()",
        "get scrolling amount [0 .. GetScrollMaxY()]",
        PK_VAR_LAMBDA(ImGui::GetScrollY())
        );

    vm->bind(imgui, "SetScrollX(scroll_x: float)",
        "set scrolling amount [0 .. GetScrollMaxX()]",
        [](VM* vm, ArgsView args){
            float scroll_x = CAST_F(args[0]);
            ImGui::SetScrollX(scroll_x);
            return vm->None;
        });

    vm->bind(imgui, "SetScrollY(scroll_y: float)",
        "set scrolling amount [0 .. GetScrollMaxY()]",
        [](VM* vm, ArgsView args){
            float scroll_y = CAST_F(args[0]);
            ImGui::SetScrollY(scroll_y);
            return vm->None;
        });

    vm->bind(imgui, "GetScrollMaxX()",
        "get maximum scrolling amount ~~ ContentSize.x - WindowSize.x - DecorationsSize.x",
        PK_VAR_LAMBDA(ImGui::GetScrollMaxX())
        );

    vm->bind(imgui, "GetScrollMaxY()",
        "get maximum scrolling amount ~~ ContentSize.y - WindowSize.y - DecorationsSize.y",
        PK_VAR_LAMBDA(ImGui::GetScrollMaxY())
        );

    vm->bind(imgui, "SetScrollHereX(center_x_ratio=0.5)",
        "adjust scrolling amount to make current cursor position visible. center_x_ratio=0.0: left, 0.5: center, 1.0: right. When using to make a \"default/current item\" visible, consider using SetItemDefaultFocus() instead.",
        [](VM* vm, ArgsView args){
            float center_x_ratio = CAST_F(args[0]);
            ImGui::SetScrollHereX(center_x_ratio);
            return vm->None;
        });

    vm->bind(imgui, "SetScrollHereY(center_y_ratio=0.5)",
        "adjust scrolling amount to make current cursor position visible. center_y_ratio=0.0: top, 0.5: center, 1.0: bottom. When using to make a \"default/current item\" visible, consider using SetItemDefaultFocus() instead.",
        [](VM* vm, ArgsView args){
            float center_y_ratio = CAST_F(args[0]);
            ImGui::SetScrollHereY(center_y_ratio);
            return vm->None;
        });

    vm->bind(imgui, "SetScrollFromPosX(local_x: float, center_x_ratio=0.5)",
        "adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position.",
        [](VM* vm, ArgsView args){
            float local_x = CAST_F(args[0]);
            float center_x_ratio = CAST_F(args[1]);
            ImGui::SetScrollFromPosX(local_x, center_x_ratio);
            return vm->None;
        });

    vm->bind(imgui, "SetScrollFromPosY(local_y: float, center_y_ratio=0.5)",
        "adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position.",
        [](VM* vm, ArgsView args){
            float local_y = CAST_F(args[0]);
            float center_y_ratio = CAST_F(args[1]);
            ImGui::SetScrollFromPosY(local_y, center_y_ratio);
            return vm->None;
        });

    // Parameters stacks (shared)
    vm->bind(imgui, "PushFont(font: void_p)",
        "use None as a shortcut to push default font",
        [](VM* vm, ArgsView args){
            ImFont* font = CAST(ImFont*, args[0]);
            ImGui::PushFont(font);
            return vm->None;
        });

    vm->bind(imgui, "PopFont()",
        PK_ACTION(ImGui::PopFont())
        );

    vm->bind(imgui, "PushStyleColor(idx: int, col: vec4)",
        "modify a style color. always use this if you modify the style after NewFrame().",
        [](VM* vm, ArgsView args){
            ImGuiCol idx = CAST(ImGuiCol, args[0]);
            ImVec4 col = CAST(ImVec4, args[1]);
            ImGui::PushStyleColor(idx, col);
            return vm->None;
        });

    vm->bind(imgui, "PopStyleColor(count=1)",
        [](VM* vm, ArgsView args){
            int count = CAST(int, args[0]);
            ImGui::PopStyleColor(count);
            return vm->None;
        });

    vm->bind(imgui, "PushStyleVar(idx: int, val: float)",
        "modify a style float variable. always use this if you modify the style after NewFrame().",
        [](VM* vm, ArgsView args){
            ImGuiStyleVar idx = CAST(ImGuiStyleVar, args[0]);
            float val = CAST_F(args[1]);
            ImGui::PushStyleVar(idx, val);
            return vm->None;
        });

    vm->bind(imgui, "PushStyleVar(idx: int, val: vec2)",
        "modify a style ImVec2 variable. always use this if you modify the style after NewFrame().",
        [](VM* vm, ArgsView args){
            ImGuiStyleVar idx = CAST(ImGuiStyleVar, args[0]);
            ImVec2 val = CAST(ImVec2, args[1]);
            ImGui::PushStyleVar(idx, val);
            return vm->None;
        });

    vm->bind(imgui, "PopStyleVar(count=1)",
        [](VM* vm, ArgsView args){
            int count = CAST(int, args[0]);
            ImGui::PopStyleVar(count);
            return vm->None;
        });

    vm->bind(imgui, "PushTabStop(tab_stop: bool)",
        "== tab stop enable. Allow focusing using TAB/Shift-TAB, enabled by default but you can disable it for certain widgets",
        [](VM* vm, ArgsView args){
            bool tab_stop = CAST(bool, args[0]);
            ImGui::PushTabStop(tab_stop);
            return vm->None;
        });

    vm->bind(imgui, "PopTabStop()",
        PK_ACTION(ImGui::PopTabStop())
        );

    vm->bind(imgui, "PushButtonRepeat(repeat: bool)",
        "in 'repeat' mode, Button*() functions return repeated true in a typematic manner (using io.KeyRepeatDelay/io.KeyRepeatRate setting). Note that you can call IsItemActive() after any Button() to tell if the button is held in the current frame.",
        [](VM* vm, ArgsView args){
            bool repeat = CAST(bool, args[0]);
            ImGui::PushButtonRepeat(repeat);
            return vm->None;
        });

    vm->bind(imgui, "PopButtonRepeat()",
        PK_ACTION(ImGui::PopButtonRepeat())
        );

    // Parameters stacks (current window)
    vm->bind(imgui, "PushItemWidth(item_width: float)",
        "push width of items for common large \"item+label\" widgets. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side).",
        [](VM* vm, ArgsView args){
            float item_width = CAST_F(args[0]);
            ImGui::PushItemWidth(item_width);
            return vm->None;
        });

    vm->bind(imgui, "PopItemWidth()",
        PK_ACTION(ImGui::PopItemWidth())
        );

    vm->bind(imgui, "SetNextItemWidth(item_width: float)",
        "set width of the _next_ common large \"item+label\" widget. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side)",
        [](VM* vm, ArgsView args){
            float item_width = CAST_F(args[0]);
            ImGui::SetNextItemWidth(item_width);
            return vm->None;
        });

    vm->bind(imgui, "CalcItemWidth() -> float",
        "width of item given pushed settings and current cursor position. NOT necessarily the width of last item unlike most 'Item' functions.",
        PK_VAR_LAMBDA(ImGui::CalcItemWidth())
        );

    vm->bind(imgui, "PushTextWrapPos(wrap_local_pos_x: float = 0.0)",
        "push word-wrapping position for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window (or column); > 0.0f: wrap at 'wrap_pos_x' position in window local space",
        [](VM* vm, ArgsView args){
            float wrap_local_pos_x = CAST_F(args[0]);
            ImGui::PushTextWrapPos(wrap_local_pos_x);
            return vm->None;
        });

    vm->bind(imgui, "PopTextWrapPos()",
        PK_ACTION(ImGui::PopTextWrapPos())
        );

    // Style read access
    // - Use the ShowStyleEditor() function to interactively see/edit the colors.
    vm->bind(imgui, "GetFont() -> void_p",
        "get current font",
        PK_VAR_LAMBDA(ImGui::GetFont())
        );

    vm->bind(imgui, "GetFontSize() -> float",
        "get current font size (= height in pixels) of current font with current scale applied",
        PK_VAR_LAMBDA(ImGui::GetFontSize())
        );

    vm->bind(imgui, "GetFontTexUvWhitePixel() -> vec2",
        "get UV coordinate for a while pixel, useful to draw custom shapes via the ImDrawList API",
        PK_VAR_LAMBDA(ImGui::GetFontTexUvWhitePixel())
        );
    vm->bind(imgui, "GetStyleColorVec4(idx: int) -> vec4",
        "retrieve style color as stored in ImGuiStyle structure. use to feed back into PushStyleColor(), otherwise use GetColorU32() to get style color with style alpha baked in.",
        [](VM* vm, ArgsView args){
            ImGuiCol idx = CAST(ImGuiCol, args[0]);
            ImVec4 v = ImGui::GetStyleColorVec4(idx);
            return VAR(v);
        });

    // Cursor / Layout
    // - By "cursor" we mean the current output position.
    // - The typical widget behavior is to output themselves at the current cursor position, then move the cursor one line down.
    // - You can call SameLine() between widgets to undo the last carriage return and output at the right of the preceding widget.
    // - Attention! We currently have inconsistencies between window-local and absolute positions we will aim to fix with future API:
    //    Window-local coordinates:   SameLine(), GetCursorPos(), SetCursorPos(), GetCursorStartPos(), GetContentRegionMax(), GetWindowContentRegion*(), PushTextWrapPos()
    //    Absolute coordinate:        GetCursorScreenPos(), SetCursorScreenPos(), all ImDrawList:: functions.
    vm->bind(imgui, "Separator()",
        "separator, generally horizontal. inside a menu bar or in horizontal layout mode, this becomes a vertical separator.",
        PK_ACTION(ImGui::Separator())
        );

    vm->bind(imgui, "SameLine(offset_from_start_x=0.0, spacing=-1.0)",
        "call between widgets or groups to layout them horizontally. X position given in window coordinates.",
        [](VM* vm, ArgsView args){
            float offset_from_start_x = CAST_F(args[0]);
            float spacing = CAST_F(args[1]);
            ImGui::SameLine(offset_from_start_x, spacing);
            return vm->None;
        });

    vm->bind(imgui, "NewLine()",
        "undo a SameLine() or force a new line when in a horizontal-layout context.",
        PK_ACTION(ImGui::NewLine())
        );

    vm->bind(imgui, "Spacing()",
        "add vertical spacing.",
        PK_ACTION(ImGui::Spacing())
        );

    vm->bind(imgui, "Dummy(size: vec2)",
        "add a dummy item of given size. unlike InvisibleButton(), Dummy() won't take the mouse click or be navigable into.",
        [](VM* vm, ArgsView args){
            ImVec2 size = CAST(ImVec2, args[0]);
            ImGui::Dummy(size);
            return vm->None;
        });

    vm->bind(imgui, "Indent(indent_w=0.0)",
        "move content position toward the right, by indent_w, or style.IndentSpacing if indent_w <= 0",
        [](VM* vm, ArgsView args){
            float indent_w = CAST_F(args[0]);
            ImGui::Indent(indent_w);
            return vm->None;
        });

    vm->bind(imgui, "Unindent(indent_w=0.0)",
        "move content position back to the left, by indent_w, or style.IndentSpacing if indent_w <= 0",
        [](VM* vm, ArgsView args){
            float indent_w = CAST_F(args[0]);
            ImGui::Unindent(indent_w);
            return vm->None;
        });

    vm->bind(imgui, "BeginGroup()",
        "lock horizontal starting position",
        PK_ACTION(ImGui::BeginGroup())
        );

    vm->bind(imgui, "EndGroup()",
        "unlock horizontal starting position + capture the whole group bounding box into one \"item\" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)",
        PK_ACTION(ImGui::EndGroup())
        );

    vm->bind(imgui, "GetCursorPos() -> vec2",
        "cursor position in window coordinates (relative to window position)",
        PK_VAR_LAMBDA(ImGui::GetCursorPos())
        );

    vm->bind(imgui, "GetCursorPosX() -> float",
        PK_VAR_LAMBDA(ImGui::GetCursorPosX())
        );

    vm->bind(imgui, "GetCursorPosY() -> float",
        PK_VAR_LAMBDA(ImGui::GetCursorPosY())
        );

    vm->bind(imgui, "SetCursorPos(local_pos: vec2)",
        "cursor position in window coordinates (relative to window position)",
        [](VM* vm, ArgsView args){
            ImVec2 local_pos = CAST(ImVec2, args[0]);
            ImGui::SetCursorPos(local_pos);
            return vm->None;
        });

    vm->bind(imgui, "SetCursorPosX(local_x: float)",
        [](VM* vm, ArgsView args){
            float local_x = CAST_F(args[0]);
            ImGui::SetCursorPosX(local_x);
            return vm->None;
        });

    vm->bind(imgui, "SetCursorPosY(local_y: float)",
        [](VM* vm, ArgsView args){
            float local_y = CAST_F(args[0]);
            ImGui::SetCursorPosY(local_y);
            return vm->None;
        });

    vm->bind(imgui, "GetCursorStartPos() -> vec2",
        "initial cursor position in window coordinates",
        PK_VAR_LAMBDA(ImGui::GetCursorStartPos())
        );

    vm->bind(imgui, "GetCursorScreenPos() -> vec2",
        "cursor position in absolute screen coordinates (0..io.DisplaySize) or natural OS coordinates when using multiple viewport. useful to work with ImDrawList API.",
        PK_VAR_LAMBDA(ImGui::GetCursorScreenPos())
        );

    vm->bind(imgui, "SetCursorScreenPos(pos: vec2)",
        "cursor position in absolute screen coordinates (0..io.DisplaySize) or natural OS coordinates when using multiple viewport. useful to work with ImDrawList API.",
        [](VM* vm, ArgsView args){
            ImVec2 pos = CAST(ImVec2, args[0]);
            ImGui::SetCursorScreenPos(pos);
            return vm->None;
        });

    vm->bind(imgui, "AlignTextToFramePadding()",
        "vertically align/lower upcoming text to FramePadding.y so that it will aligns to upcoming widgets (call if you have text on a line before regular widgets)",
        PK_ACTION(ImGui::AlignTextToFramePadding())
        );

    vm->bind(imgui, "GetTextLineHeight() -> float",
        "~ FontSize",
        PK_VAR_LAMBDA(ImGui::GetTextLineHeight())
        );

    vm->bind(imgui, "GetTextLineHeightWithSpacing() -> float",
        "~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)",
        PK_VAR_LAMBDA(ImGui::GetTextLineHeightWithSpacing())
        );

    vm->bind(imgui, "GetFrameHeight() -> float",
        "~ FontSize + style.FramePadding.y * 2",
        PK_VAR_LAMBDA(ImGui::GetFrameHeight())
        );

    vm->bind(imgui, "GetFrameHeightWithSpacing() -> float",
        "~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)",
        PK_VAR_LAMBDA(ImGui::GetFrameHeightWithSpacing())
        );
    
    // ID stack/scopes
    vm->bind(imgui, "PushID(x)",
        [](VM* vm, ArgsView args){
            if(is_non_tagged_type(args[0], vm->tp_str)){
                const char* str_id = _CAST(CString, args[0]);
                ImGui::PushID(str_id);
            }else if(is_int(args[0])){
                int int_id = _CAST(int, args[0]);
                ImGui::PushID(int_id);
            }else if(is_non_tagged_type(args[0], VoidP::_type(vm))){
                void* ptr_id = _CAST(VoidP&, args[0]).ptr;
                ImGui::PushID(ptr_id);
            }else{
                vm->TypeError("expected str, int or void_p");
            }
            return vm->None;
        });

    vm->bind_func<0>(imgui, "PopID", PK_ACTION(ImGui::PopID()));
    
    // Widgets: Text
    vm->bind(imgui, "Text(s: str)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::Text("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "TextColored(col: vec4, s: str)",
        [](VM* vm, ArgsView args){
            ImVec4 col = CAST(ImVec4, args[0]);
            const char* text = CAST(CString, args[1]);
            ImGui::TextColored(col, "%s", text);
            return vm->None;
        });

    vm->bind(imgui, "TextDisabled(s: str)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::TextDisabled("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "TextWrapped(s: str)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::TextWrapped("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "LabelText(label: str, s: str)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            const char* text = CAST(CString, args[1]);
            ImGui::LabelText(label, "%s", text);
            return vm->None;
        });

    vm->bind(imgui, "BulletText(s: str)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::BulletText("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "SeparatorText(label: str)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            ImGui::SeparatorText(label);
            return vm->None;
        });

    // Widgets: Main
    // - Most widgets return true when the value has been changed or when pressed/selected
    // - You may also use one of the many IsItemXXX functions (e.g. IsItemActive, IsItemHovered, etc.) to query widget state.
    vm->bind(imgui, "Button(label: str, size=None) -> bool",
        "button",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            ImVec2 size = CAST_DEFAULT(ImVec2, args[1], ImVec2(0, 0));
            bool ret = ImGui::Button(label, size);
            return VAR(ret);
        });

    vm->bind(imgui, "SmallButton(label: str) -> bool",
        "button with FramePadding=(0,0) to easily embed within text",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            bool ret = ImGui::SmallButton(label);
            return VAR(ret);
        });

    vm->bind(imgui, "InvisibleButton(str_id: str, size: vec2, flags=0) -> bool",
        "flexible button behavior without the visuals, frequently useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImVec2 size = CAST(ImVec2, args[1]);
            ImGuiButtonFlags flags = CAST(ImGuiButtonFlags, args[2]);
            bool ret = ImGui::InvisibleButton(str_id, size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "ArrowButton(str_id: str, dir: int) -> bool",
        "square button with an arrow shape",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiDir dir = CAST(ImGuiDir, args[1]);
            bool ret = ImGui::ArrowButton(str_id, dir);
            return VAR(ret);
        });

    vm->bind(imgui, "Checkbox(label: str, v: void_p) -> bool",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            bool* v = CAST(bool*, args[1]);
            bool ret = ImGui::Checkbox(label, v);
            return VAR(ret);
        });

    vm->bind(imgui, "CheckboxFlags(label: str, flags: void_p, flags_value: int) -> bool",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            int* flags = CAST(int*, args[1]);
            int flags_value = CAST(int, args[2]);
            bool ret = ImGui::CheckboxFlags(label, flags, flags_value);
            return VAR(ret);
        });

    vm->bind(imgui, "RadioButton(label: str, active: bool) -> bool",
        "use with e.g. if (RadioButton(\"one\", my_value==1)) { my_value = 1; }",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            bool active = CAST(bool, args[1]);
            bool ret = ImGui::RadioButton(label, active);
            return VAR(ret);
        });

    vm->bind(imgui, "ProgressBar(fraction: float, size: vec2=None, overlay: str=None)",
        [](VM* vm, ArgsView args){
            float fraction = CAST_F(args[0]);
            ImVec2 size = CAST_DEFAULT(ImVec2, args[1], ImVec2(-FLT_MIN, 0));
            const char* overlay = CAST_DEFAULT(CString, args[2], NULL);
            ImGui::ProgressBar(fraction, size, overlay);
            return vm->None;
        });

    vm->bind(imgui, "Bullet()",
        "draw a small circle + keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses",
        PK_ACTION(ImGui::Bullet())
        );

    // Widgets: Images
    vm->bind(imgui, "Image(user_texture_id: void_p, size: vec2, uv0: vec2 = None, uv1: vec2 = None, tint_col: vec4 = None, border_col: vec4 = None)",
        "Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples",
        [](VM* vm, ArgsView args){
            void* user_texture_id = CAST(void*, args[0]);
            ImVec2 size = CAST(ImVec2, args[1]);
            ImVec2 uv0 = CAST_DEFAULT(ImVec2, args[2], ImVec2(0, 0));
            ImVec2 uv1 = CAST_DEFAULT(ImVec2, args[3], ImVec2(1, 1));
            ImVec4 tint_col = CAST_DEFAULT(ImVec4, args[4], ImVec4(1, 1, 1, 1));
            ImVec4 border_col = CAST_DEFAULT(ImVec4, args[5], ImVec4(0, 0, 0, 0));
            ImGui::Image(user_texture_id, size, uv0, uv1, tint_col, border_col);
            return vm->None;
        });

    vm->bind(imgui, "ImageButton(str_id: str, user_texture_id: void_p, size: vec2, uv0: vec2 = None, uv1: vec2 = None, bg_col: vec4 = None, tint_col: vec4 = None) -> bool",
        "Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            void* user_texture_id = CAST(void*, args[1]);
            ImVec2 size = CAST(ImVec2, args[2]);
            ImVec2 uv0 = CAST_DEFAULT(ImVec2, args[3], ImVec2(0, 0));
            ImVec2 uv1 = CAST_DEFAULT(ImVec2, args[4], ImVec2(1, 1));
            ImVec4 bg_col = CAST_DEFAULT(ImVec4, args[5], ImVec4(0, 0, 0, 0));
            ImVec4 tint_col = CAST_DEFAULT(ImVec4, args[6], ImVec4(1, 1, 1, 1));
            bool ret = ImGui::ImageButton(str_id, user_texture_id, size, uv0, uv1, bg_col, tint_col);
            return VAR(ret);
        });


    // Widgets: Combo Box (Dropdown)
    vm->bind(imgui, "BeginCombo(label: str, preview_value: str, flags=0) -> bool",
        "The BeginCombo()/EndCombo() api allows you to manage your contents and selection state however you want it, by creating e.g. Selectable() items.",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            const char* preview_value = CAST(CString, args[1]);
            ImGuiComboFlags flags = CAST(int, args[2]);
            return VAR(ImGui::BeginCombo(label, preview_value, flags));
        });

    vm->bind(imgui, "EndCombo()",
        "only call EndCombo() if BeginCombo() returns true!",
        PK_ACTION(ImGui::EndCombo()));

    vm->bind(imgui, "Combo(label: str, current_item: void_p, items: list[str], popup_max_height_in_items=-1)",
        "The old Combo() api are helpers over BeginCombo()/EndCombo() which are kept available for convenience purpose. This is analogous to how ListBox are created.",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            int* current_item = CAST(int*, args[1]);
            const List& items = CAST(List&, args[2]);
            std::vector<char> items_separated_by_zeros;
            for(PyObject* obj: items){
                for(char c: CAST(Str&, obj).sv()) items_separated_by_zeros.push_back(c);
                items_separated_by_zeros.push_back('\0');
            }
            items_separated_by_zeros.push_back('\0');
            int popup_max_height_in_items = CAST(int, args[3]);
            bool ret = ImGui::Combo(label, current_item, items_separated_by_zeros.data(), popup_max_height_in_items);
            return VAR(ret);
        });

    // Widgets: Drag Sliders
    // [SKIP]

    // Widgets: Regular Sliders
#define BIND_SLIDER_FLOAT(name)   \
vm->bind(imgui, #name "(label: str, v: void_p, v_min, v_max, format='%.3f', flags=0) -> bool",  \
    [](VM* vm, ArgsView args){  \
        const char* label = CAST(CString, args[0]); \
        float* v = CAST(float*, args[1]);   \
        float v_min = CAST_F(args[2]);  \
        float v_max = CAST_F(args[3]);  \
        const char* format = CAST(CString, args[4]);    \
        ImGuiSliderFlags flags = CAST(int, args[5]);    \
        bool ret = ImGui::name(label, v, v_min, v_max, format, flags);    \
        return VAR(ret);    \
    });

    BIND_SLIDER_FLOAT(SliderFloat)
    BIND_SLIDER_FLOAT(SliderFloat2)
    BIND_SLIDER_FLOAT(SliderFloat3)
    BIND_SLIDER_FLOAT(SliderFloat4)

#undef BIND_SLIDER_FLOAT

#define BIND_SLIDER_INT(name)   \
vm->bind(imgui, #name "(label: str, v: void_p, v_min, v_max, format='%d', flags=0) -> bool",  \
    [](VM* vm, ArgsView args){  \
        const char* label = CAST(CString, args[0]); \
        int* v = CAST(int*, args[1]);   \
        int v_min = CAST(int, args[2]);  \
        int v_max = CAST(int, args[3]);  \
        const char* format = CAST(CString, args[4]);    \
        ImGuiSliderFlags flags = CAST(int, args[5]);    \
        bool ret = ImGui::name(label, v, v_min, v_max, format, flags);    \
        return VAR(ret);    \
    });

    BIND_SLIDER_INT(SliderInt)
    BIND_SLIDER_INT(SliderInt2)
    BIND_SLIDER_INT(SliderInt3)
    BIND_SLIDER_INT(SliderInt4)

#undef BIND_SLIDER_INT

    // Widgets: Input with Keyboard
    IMGUI_API bool          InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool          InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool          InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool          InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0);
    IMGUI_API bool          InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0);
    
    vm->bind(imgui, "InputText(label: str, buf: void_p, buf_size: int, flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            char* buf = CAST(char*, args[1]);
            size_t buf_size = CAST(size_t, args[2]);
            ImGuiInputTextFlags flags = CAST(int, args[3]);
            bool ret = ImGui::InputText(label, buf, buf_size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "InputTextMultiline(label: str, buf: void_p, buf_size: int, size: vec2 = None, flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            char* buf = CAST(char*, args[1]);
            size_t buf_size = CAST(size_t, args[2]);
            ImVec2 size = CAST_DEFAULT(ImVec2, args[3], ImVec2(0, 0));
            ImGuiInputTextFlags flags = CAST(int, args[4]);
            bool ret = ImGui::InputTextMultiline(label, buf, buf_size, size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "InputTextWithHint(label: str, hint: str, buf: void_p, buf_size: int, flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            const char* hint = CAST(CString, args[1]);
            char* buf = CAST(char*, args[2]);
            size_t buf_size = CAST(size_t, args[3]);
            ImGuiInputTextFlags flags = CAST(int, args[4]);
            bool ret = ImGui::InputTextWithHint(label, hint, buf, buf_size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "InputFloat(label: str, v: void_p, step=0.0, step_fast=0.0, format='%.3f', flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            float* v = CAST(float*, args[1]);
            float step = CAST(float, args[2]);
            float step_fast = CAST(float, args[3]);
            const char* format = CAST(CString, args[4]);
            ImGuiInputTextFlags flags = CAST(int, args[5]);
            bool ret = ImGui::InputFloat(label, v, step, step_fast, format, flags);
            return VAR(ret);
        });

#define BIND_INPUT_FLOAT(name)  \
vm->bind(imgui, #name "(label: str, v: void_p, format='%.3f', flags=0) -> bool",  \
    [](VM* vm, ArgsView args){  \
        const char* label = CAST(CString, args[0]); \
        float* v = CAST(float*, args[1]);   \
        const char* format = CAST(CString, args[2]);    \
        ImGuiInputTextFlags flags = CAST(int, args[3]);    \
        bool ret = ImGui::name(label, v, format, flags);    \
        return VAR(ret);    \
    });
    BIND_INPUT_FLOAT(InputFloat2)
    BIND_INPUT_FLOAT(InputFloat3)
    BIND_INPUT_FLOAT(InputFloat4)

#undef BIND_INPUT_FLOAT

    vm->bind(imgui, "InputInt(label: str, v: void_p, step=1, step_fast=100, flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            int* v = CAST(int*, args[1]);
            int step = CAST(int, args[2]);
            int step_fast = CAST(int, args[3]);
            ImGuiInputTextFlags flags = CAST(int, args[4]);
            bool ret = ImGui::InputInt(label, v, step, step_fast, flags);
            return VAR(ret);
        });

#define BIND_INPUT_INT(name)  \
vm->bind(imgui, #name "(label: str, v: void_p, flags=0) -> bool",  \
    [](VM* vm, ArgsView args){  \
        const char* label = CAST(CString, args[0]); \
        int* v = CAST(int*, args[1]);   \
        ImGuiInputTextFlags flags = CAST(int, args[2]);    \
        bool ret = ImGui::name(label, v, flags);    \
        return VAR(ret);    \
    });

    BIND_INPUT_INT(InputInt2)
    BIND_INPUT_INT(InputInt3)
    BIND_INPUT_INT(InputInt4)

#undef BIND_INPUT_INT

    // Widgets: Color Editor/Picker
    // ... (TODO)
    
    // Widgets: Trees
    // ... (TODO)

    // Widgets: Selectables
    // ... (TODO)

    // Widgets: List Boxes
    // ... (TODO)

    // Widgets: Data Plotting
    // ... (TODO)

    // Widgets: Value() Helpers
    // NOT NEEDED

    // Widgets: Menus
    // ... (TODO)

    // Tooltips
    vm->bind(imgui, "BeginTooltip() -> bool",
        "begin/append a tooltip window. to create full-featured tooltip (with any kind of items).",
        PK_VAR_LAMBDA(ImGui::BeginTooltip()));

    vm->bind(imgui, "EndTooltip()",
        "end/append tooltip window",
        PK_ACTION(ImGui::EndTooltip()));

    vm->bind(imgui, "SetTooltip(text: str)",
        "set a text-only tooltip, typically use with ImGui::IsItemHovered(). override any previous call to SetTooltip().",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::SetTooltip("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "BeginItemTooltip() -> bool",
        "begin/append a tooltip window. to create full-featured tooltip (with any kind of items).",
        PK_VAR_LAMBDA(ImGui::BeginTooltip()));

    vm->bind(imgui, "SetItemTooltip(text: str)",
        "set a text-only tooltip, typically use with ImGui::IsItemHovered(). override any previous call to SetTooltip().",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::SetTooltip("%s", text);
            return vm->None;
        });

    // Popups, Modals
    // Popups: begin/end functions
    vm->bind(imgui, "BeginPopup(str_id: str, flags: int = 0) -> bool",
        "return true if the popup is open, and you can start outputting to it.",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiWindowFlags flags = CAST_DEFAULT(ImGuiWindowFlags, args[1], ImGuiWindowFlags(0));
            bool ret = ImGui::BeginPopup(str_id, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "BeginPopupModal(name: str, p_open=None, flags: int = 0) -> bool",
        "return true if the modal is open, and you can start outputting to it.",
        [](VM* vm, ArgsView args){
            const char* name = CAST(CString, args[0]);
            bool* p_open = CAST_DEFAULT(bool*, args[1], NULL);
            ImGuiWindowFlags flags = CAST_DEFAULT(ImGuiWindowFlags, args[2], ImGuiWindowFlags(0));
            bool ret = ImGui::BeginPopupModal(name, p_open, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "EndPopup()",
        "only call EndPopup() if BeginPopupXXX() returns true!",
        [](VM* vm, ArgsView args){
            ImGui::EndPopup();
            return vm->None;
        });

    // Popups: open/close functions
    vm->bind(imgui, "OpenPopup(str_id: str, popup_flags: int = 0)",
        "call to mark popup as open (don't call every frame!).",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            ImGui::OpenPopup(str_id, popup_flags);
            return vm->None;
        });

    vm->bind(imgui, "OpenPopupOnItemClick(str_id: str = None, popup_flags: int = 1)",
        "helper to open popup when clicked on last item. Default to ImGuiPopupFlags_MouseButtonRight == 1. (note: actually triggers on the mouse _released_ event to be consistent with popup behaviors)",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST_DEFAULT(CString, args[0], NULL);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            ImGui::OpenPopupOnItemClick(str_id, popup_flags);
            return vm->None;
        });

    vm->bind(imgui, "CloseCurrentPopup()",
        "manually close the popup we have begin-ed into.",
        PK_ACTION(ImGui::CloseCurrentPopup()));

    // Popups: open+begin combined functions helpers
    vm->bind(imgui, "BeginPopupContextItem(str_id: str = None, popup_flags: int = 1) -> bool",
        "open+begin popup when clicked on last item. Use str_id==None to associate the popup to previous item. If you want to use that on a non-interactive item such as Text() you need to pass in an explicit ID here. read comments in .cpp!",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST_DEFAULT(CString, args[0], NULL);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            bool ret = ImGui::BeginPopupContextItem(str_id, popup_flags);
            return VAR(ret);
        });

    vm->bind(imgui, "BeginPopupContextWindow(str_id: str = None, popup_flags: int = 1) -> bool",
        "open+begin popup when clicked on current window.",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST_DEFAULT(CString, args[0], NULL);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            bool ret = ImGui::BeginPopupContextWindow(str_id, popup_flags);
            return VAR(ret);
        });

    vm->bind(imgui, "BeginPopupContextVoid(str_id: str = None, popup_flags: int = 1) -> bool",
        "open+begin popup when clicked in void (where there are no windows).",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST_DEFAULT(CString, args[0], NULL);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            bool ret = ImGui::BeginPopupContextVoid(str_id, popup_flags);
            return VAR(ret);
        });

    // Popups: query functions
    vm->bind(imgui, "IsPopupOpen(str_id: str, flags: int = 0) -> bool",
        "return true if the popup is open.",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiPopupFlags flags = CAST(int, args[1]);
            bool ret = ImGui::IsPopupOpen(str_id, flags);
            return VAR(ret);
        });

    // Tables
    // ... (TODO)

    // Tab Bars, Tabs
    // ... (TODO)

    // Logging/Capture
    // ... (TODO)

    // Drag and Drop
    // ... (TODO)

    // Disabling [BETA API]
    vm->bind(imgui, "BeginDisabled(disabled: bool = True)",
R"(
- Disable all user interactions and dim items visuals (applying style.DisabledAlpha over current colors)
- Those can be nested but it cannot be used to enable an already disabled section (a single BeginDisabled(true) in the stack is enough to keep everything disabled)
- BeginDisabled(false) essentially does nothing useful but is provided to facilitate use of boolean expressions. If you can avoid calling BeginDisabled(False)/EndDisabled() best to avoid it.
)",
        [](VM* vm, ArgsView args){
            bool disabled = CAST(bool, args[0]);
            ImGui::BeginDisabled(disabled);
            return vm->None;
        });

    vm->bind(imgui, "EndDisabled()",
        PK_ACTION(ImGui::EndDisabled()));

    // Clipping
    vm->bind(imgui, "PushClipRect(clip_rect_min: vec2, clip_rect_max: vec2, intersect_with_current_clip_rect: bool)",
        [](VM* vm, ArgsView args){
            ImVec2 clip_rect_min = CAST(ImVec2, args[0]);
            ImVec2 clip_rect_max = CAST(ImVec2, args[1]);
            bool intersect_with_current_clip_rect = CAST(bool, args[2]);
            ImGui::PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);
            return vm->None;
        });

    vm->bind(imgui, "PopClipRect()",
        PK_ACTION(ImGui::PopClipRect()));

    // Focus, Activation
    vm->bind(imgui, "SetItemDefaultFocus()",
        "make last item the default focused item of a window.",
        PK_ACTION(ImGui::SetItemDefaultFocus()));

    vm->bind(imgui, "SetKeyboardFocusHere(offset: int = 0)",
        "focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget. Use -1 to access previous widget.",
        [](VM* vm, ArgsView args){
            int offset = CAST(int, args[0]);
            ImGui::SetKeyboardFocusHere(offset);
            return vm->None;
        });
    
    // Item/Widgets Utilities and Query Functions
    // - Most of the functions are referring to the previous Item that has been submitted.
    // - See Demo Window under "Widgets->Querying Status" for an interactive visualization of most of those functions.
    vm->bind(imgui, "IsItemHovered(flags: int = 0) -> bool",
        "is the last item hovered? (and usable, aka not blocked by a popup, etc.). See ImGuiHoveredFlags for more options.",
        [](VM* vm, ArgsView args){
            ImGuiHoveredFlags flags = CAST(int, args[0]);
            bool ret = ImGui::IsItemHovered(flags);
            return VAR(ret);
        });

    vm->bind(imgui, "IsItemActive() -> bool",
        "is the last item active? (e.g. button being held, text field being edited. This will continuously return true while holding mouse button on an item. Items that don't interact will always return false)",
        PK_VAR_LAMBDA(ImGui::IsItemActive()));

    vm->bind(imgui, "IsItemFocused() -> bool",
        "is the last item focused for keyboard/gamepad navigation?",
        PK_VAR_LAMBDA(ImGui::IsItemFocused()));

    vm->bind(imgui, "IsItemClicked(mouse_button: int = 0) -> bool",
        "is the last item hovered and mouse clicked on? (**)  == IsMouseClicked(mouse_button) && IsItemHovered()Important. (**) this is NOT equivalent to the behavior of e.g. Button(). Read comments in function definition.",
        [](VM* vm, ArgsView args){
            ImGuiMouseButton mouse_button = CAST(int, args[0]);
            bool ret = ImGui::IsItemClicked(mouse_button);
            return VAR(ret);
        });

    vm->bind(imgui, "IsItemVisible() -> bool",
        "is the last item visible? (items may be out of sight because of clipping/scrolling)",
        PK_VAR_LAMBDA(ImGui::IsItemVisible()));

    vm->bind(imgui, "IsItemEdited() -> bool",
        "did the last item modify its underlying value this frame? or was pressed? This is generally the same as the \"bool\" return value of many widgets.",
        PK_VAR_LAMBDA(ImGui::IsItemEdited()));

    vm->bind(imgui, "IsItemActivated() -> bool",
        "was the last item just made active (item was previously inactive).",
        PK_VAR_LAMBDA(ImGui::IsItemActivated()));

    vm->bind(imgui, "IsItemDeactivated() -> bool",
        "was the last item just made inactive (item was previously active). Useful for Undo/Redo patterns with widgets that require continuous editing.",
        PK_VAR_LAMBDA(ImGui::IsItemDeactivated()));

    vm->bind(imgui, "IsItemDeactivatedAfterEdit() -> bool",
        "was the last item just made inactive and made a value change when it was active? (e.g. Slider/Drag moved). Useful for Undo/Redo patterns with widgets that require continuous editing. Note that you may get false positives (some widgets such as Combo()/ListBox()/Selectable() will return true even when clicking an already selected item).",
        PK_VAR_LAMBDA(ImGui::IsItemDeactivatedAfterEdit()));

    vm->bind(imgui, "IsItemToggledOpen() -> bool",
        "was the last item open state toggled? set by TreeNode().",
        PK_VAR_LAMBDA(ImGui::IsItemToggledOpen()));

    vm->bind(imgui, "IsAnyItemHovered() -> bool",
        "is any item hovered?",
        PK_VAR_LAMBDA(ImGui::IsAnyItemHovered()));

    vm->bind(imgui, "IsAnyItemActive() -> bool",
        "is any item active?",
        PK_VAR_LAMBDA(ImGui::IsAnyItemActive()));

    vm->bind(imgui, "IsAnyItemFocused() -> bool",
        "is any item focused?",
        PK_VAR_LAMBDA(ImGui::IsAnyItemFocused()));

    vm->bind(imgui, "GetItemRectMin() -> vec2",
        "get upper-left bounding rectangle of the last item (screen space)",
        PK_VAR_LAMBDA(ImGui::GetItemRectMin()));

    vm->bind(imgui, "GetItemRectMax() -> vec2",
        "get lower-right bounding rectangle of the last item (screen space)",
        PK_VAR_LAMBDA(ImGui::GetItemRectMax()));

    vm->bind(imgui, "GetItemRectSize() -> vec2",
        "get size of last item",
        PK_VAR_LAMBDA(ImGui::GetItemRectSize()));

    vm->bind(imgui, "SetItemAllowOverlap()",
        "allow last item to be overlapped by a subsequent item. sometimes useful with invisible buttons, selectables, etc. to catch unused area.",
        PK_ACTION(ImGui::SetItemAllowOverlap()));

    // Viewports
    vm->bind(imgui, "GetMainViewport() -> void_p",
        PK_VAR_LAMBDA(ImGui::GetMainViewport()));

    // Background/Foreground Draw Lists
    vm->bind(imgui, "GetBackgroundDrawList() -> void_p",
        "get background draw list for the current active window.",
        [](VM* vm, ArgsView args){
            ImDrawList* ret = ImGui::GetBackgroundDrawList();
            return VAR(ret);
        });

    vm->bind(imgui, "GetForegroundDrawList() -> void_p",
        "get foreground draw list for the current active window.",
        [](VM* vm, ArgsView args){
            ImDrawList* ret = ImGui::GetForegroundDrawList();
            return VAR(ret);
        });

    // Miscellaneous Utilities
    vm->bind(imgui, "IsRectVisible(size: vec2) -> bool",
        "test if rectangle (of given size, starting from cursor position) is visible / not clipped.",
        [](VM* vm, ArgsView args){
            ImVec2 size = CAST(ImVec2, args[0]);
            bool ret = ImGui::IsRectVisible(size);
            return VAR(ret);
        });

    vm->bind(imgui, "GetTime() -> float",
        "get global imgui time. incremented by io.DeltaTime every frame.",
        [](VM* vm, ArgsView args){
            double ret = ImGui::GetTime();
            return VAR(ret);
        });

    vm->bind(imgui, "GetFrameCount() -> int",
        "get global imgui frame count. incremented by 1 every frame.",
        [](VM* vm, ArgsView args){
            int ret = ImGui::GetFrameCount();
            return VAR(ret);
        });

    vm->bind(imgui, "GetDrawListSharedData() -> void_p",
        "you may use this when creating your own ImDrawList instances.",
        [](VM* vm, ArgsView args){
            ImDrawListSharedData* ret = ImGui::GetDrawListSharedData();
            return VAR(ret);
        });

    vm->bind(imgui, "GetStyleColorName(idx: int) -> str",
        "get a string corresponding to the enum value (for display, saving, etc.).",
        [](VM* vm, ArgsView args){
            ImGuiCol idx = CAST(ImGuiCol, args[0]);
            const char* ret = ImGui::GetStyleColorName(idx);
            return VAR(ret);
        });

    vm->bind(imgui, "SetStateStorage(storage: void_p)",
        "replace current window storage with our own (if you want to manipulate it yourself, typically clear subsection of it)",
        [](VM* vm, ArgsView args){
            ImGuiStorage* storage = CAST(ImGuiStorage*, args[0]);
            ImGui::SetStateStorage(storage);
            return vm->None;
        });

    vm->bind(imgui, "GetStateStorage() -> void_p",
        [](VM* vm, ArgsView args){
            ImGuiStorage* ret = ImGui::GetStateStorage();
            return VAR(ret);
        });

    vm->bind(imgui, "BeginChildFrame(id: int, size: vec2, flags: int = 0) -> bool",
        "helper to create a child window / scrolling region that looks like a normal widget frame",
        [](VM* vm, ArgsView args){
            ImGuiID id = CAST(ImGuiID, args[0]);
            ImVec2 size = CAST(ImVec2, args[1]);
            ImGuiWindowFlags flags = CAST_DEFAULT(ImGuiWindowFlags, args[2], ImGuiWindowFlags(0));
            bool ret = ImGui::BeginChildFrame(id, size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "EndChildFrame()",
        "always call EndChildFrame() regardless of BeginChildFrame() return values (which indicates a collapsed/clipped window)",
        [](VM* vm, ArgsView args){
            ImGui::EndChildFrame();
            return vm->None;
        });

    // Text Utilities
    vm->bind(imgui, "CalcTextSize(text: str, hide_text_after_double_hash=False, wrap_width=-1.0) -> vec2",
        "calculate text size. text can be multi-line. optionally ignore text after double-space (for e.g. for logging to file, etc.)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(const char*, args[0]);
            bool hide_text_after_double_hash = CAST_DEFAULT(bool, args[1], false);
            float wrap_width = CAST_DEFAULT(float, args[2], -1.0f);
            ImVec2 ret = ImGui::CalcTextSize(text, nullptr, hide_text_after_double_hash, wrap_width);
            return VAR(ret);
        });

    // Color Utilities
    // ... (TODO)

    // Inputs Utilities: Keyboard/Mouse/Gamepad
    vm->bind(imgui, "IsKeyDown(key: int) -> bool",
        "is key being held.",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            bool ret = ImGui::IsKeyDown((ImGuiKey)key);
            return VAR(ret);
        });

    vm->bind(imgui, "IsKeyPressed(key: int, repeat=True) -> bool",
        "was key pressed (went from !Down to Down)? if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            bool repeat = CAST_DEFAULT(bool, args[1], true);
            bool ret = ImGui::IsKeyPressed((ImGuiKey)key, repeat);
            return VAR(ret);
        });

    vm->bind(imgui, "IsKeyReleased(key: int) -> bool",
        "was key released (went from Down to !Down)?",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            bool ret = ImGui::IsKeyReleased((ImGuiKey)key);
            return VAR(ret);
        });

    vm->bind(imgui, "GetKeyPressedAmount(key: int, repeat_delay: float, rate: float) -> int",
        "uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            float repeat_delay = CAST_F(args[1]);
            float rate = CAST_F(args[2]);
            int ret = ImGui::GetKeyPressedAmount((ImGuiKey)key, repeat_delay, rate);
            return VAR(ret);
        });

    vm->bind(imgui, "GetKeyName(key: int) -> str",
        "[DEBUG] returns English name of the key. Those names a provided for debugging purpose and are not meant to be saved persistently not compared.",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            const char* ret = ImGui::GetKeyName((ImGuiKey)key);
            return VAR(ret);
        });

    vm->bind(imgui, "SetNextFrameWantCaptureKeyboard(want_capture_keyboard: bool)",
        "Override io.WantCaptureKeyboard flag next frame (said flag is left for your application to handle, typically when true it instructs your app to ignore inputs). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting \"io.WantCaptureKeyboard = want_capture_keyboard\"; after the next NewFrame() call.",
        [](VM* vm, ArgsView args){
            bool want_capture_keyboard = CAST(bool, args[0]);
            ImGui::SetNextFrameWantCaptureKeyboard(want_capture_keyboard);
            return vm->None;
        });

    // Inputs Utilities: Mouse specific
    vm->bind(imgui, "IsMouseDown(button: int) -> bool",
        "is mouse button held?",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            bool ret = ImGui::IsMouseDown(button);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseClicked(button: int, repeat=False) -> bool",
        "did mouse button clicked? (went from !Down to Down). Same as GetMouseClickedCount() == 1.",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            bool repeat = CAST(bool, args[1]);
            bool ret = ImGui::IsMouseClicked(button, repeat);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseReleased(button: int) -> bool",
        "did mouse button released? (went from Down to !Down)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            bool ret = ImGui::IsMouseReleased(button);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseDoubleClicked(button: int) -> bool",
        "did mouse button double-clicked? Same as GetMouseClickedCount() == 2. (note that a double-click will also report IsMouseClicked() == true)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            bool ret = ImGui::IsMouseDoubleClicked(button);
            return VAR(ret);
        });

    vm->bind(imgui, "GetMouseClickedCount(button: int) -> int",
        "return the number of successive mouse-clicks at the time where a click happen (otherwise 0).",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            int ret = ImGui::GetMouseClickedCount(button);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseHoveringRect(r_min: vec2, r_max: vec2, clip=True) -> bool",
        "is mouse hovering given bounding rect (in screen space). clipped by current clipping settings, but disregarding of other consideration of focus/window ordering/popup-block.",
        [](VM* vm, ArgsView args){
            ImVec2 r_min = CAST(ImVec2, args[0]);
            ImVec2 r_max = CAST(ImVec2, args[1]);
            bool clip = CAST(bool, args[2]);
            bool ret = ImGui::IsMouseHoveringRect(r_min, r_max, clip);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMousePosValid(mouse_pos: vec2 = None) -> bool",
        "by convention we use (-FLT_MAX,-FLT_MAX) to denote that there is no mouse available",
        [](VM* vm, ArgsView args){
            ImVec2 mouse_pos = CAST(ImVec2, args[0]);
            bool ret = ImGui::IsMousePosValid(&mouse_pos);
            return VAR(ret);
        });

    vm->bind(imgui, "IsAnyMouseDown() -> bool",
        "[WILL OBSOLETE] is any mouse button held? This was designed for backends, but prefer having backend maintain a mask of held mouse buttons, because upcoming input queue system will make this invalid.",
        [](VM* vm, ArgsView args){
            bool ret = ImGui::IsAnyMouseDown();
            return VAR(ret);
        });

    vm->bind(imgui, "GetMousePos() -> vec2",
        "shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls",
        [](VM* vm, ArgsView args){
            ImVec2 ret = ImGui::GetMousePos();
            return VAR(ret);
        });

    vm->bind(imgui, "GetMousePosOnOpeningCurrentPopup() -> vec2",
        "retrieve mouse position at the time of opening popup we have BeginPopup() into (helper to avoid user backing that value themselves)",
        [](VM* vm, ArgsView args){
            ImVec2 ret = ImGui::GetMousePosOnOpeningCurrentPopup();
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseDragging(button: int, lock_threshold=-1.0) -> bool",
        "is mouse dragging? (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            float lock_threshold = CAST_F(args[1]);
            bool ret = ImGui::IsMouseDragging(button, lock_threshold);
            return VAR(ret);
        });

    vm->bind(imgui, "GetMouseDragDelta(button: int=0, lock_threshold=-1.0) -> vec2",
        "return the delta from the initial clicking position while the mouse button is pressed or was just released. This is locked and return 0.0f until the mouse moves past a distance threshold at least once (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            float lock_threshold = CAST_F(args[1]);
            ImVec2 ret = ImGui::GetMouseDragDelta(button, lock_threshold);
            return VAR(ret);
        });

    vm->bind(imgui, "ResetMouseDragDelta(button: int=0) -> None",
        "reset the dragging state when the mouse has been dragging (0=left, 1=right, 2=middle)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            ImGui::ResetMouseDragDelta(button);
            return vm->None;
        });

    vm->bind(imgui, "GetMouseCursor() -> int",
        "get desired cursor type, reset in end frame. valid before Render(). if you use software rendering by setting io.MouseDrawCursor ImGui will render those for you",
        [](VM* vm, ArgsView args){
            ImGuiMouseCursor ret = ImGui::GetMouseCursor();
            return VAR(ret);
        });

    vm->bind(imgui, "SetMouseCursor(type: int) -> None",
        "set desired cursor type",
        [](VM* vm, ArgsView args){
            ImGuiMouseCursor type = CAST(ImGuiMouseCursor, args[0]);
            ImGui::SetMouseCursor(type);
            return vm->None;
        });

    vm->bind(imgui, "SetNextFrameWantCaptureMouse(want_capture_mouse: bool)",
        "set next window ala Begin() to be focused / hovered for input handling without navigation",
        [](VM* vm, ArgsView args){
            bool want_capture_mouse = CAST(bool, args[0]);
            ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse);
            return vm->None;
        });
        
    // Clipboard Utilities
    vm->bind(imgui, "GetClipboardText() -> str",
        [](VM* vm, ArgsView args){
            const char* ret = ImGui::GetClipboardText();
            return VAR(ret);
        });

    vm->bind(imgui, "SetClipboardText(text: str) -> None",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::SetClipboardText(text);
            return vm->None;
        });
    
    
    vm->exec(R"(
# ImGuiInputTextFlags_
ImGuiInputTextFlags_None = 0
ImGuiInputTextFlags_CharsDecimal = 1
ImGuiInputTextFlags_CharsHexadecimal = 2
ImGuiInputTextFlags_CharsUppercase = 4
ImGuiInputTextFlags_CharsNoBlank = 8
ImGuiInputTextFlags_AutoSelectAll = 16
ImGuiInputTextFlags_EnterReturnsTrue = 32
ImGuiInputTextFlags_CallbackCompletion = 64
ImGuiInputTextFlags_CallbackHistory = 128
ImGuiInputTextFlags_CallbackAlways = 256
ImGuiInputTextFlags_CallbackCharFilter = 512
ImGuiInputTextFlags_AllowTabInput = 1024
ImGuiInputTextFlags_CtrlEnterForNewLine = 2048
ImGuiInputTextFlags_NoHorizontalScroll = 4096
ImGuiInputTextFlags_AlwaysOverwrite = 8192
ImGuiInputTextFlags_ReadOnly = 16384
ImGuiInputTextFlags_Password = 32768
ImGuiInputTextFlags_NoUndoRedo = 65536
ImGuiInputTextFlags_CharsScientific = 131072
ImGuiInputTextFlags_CallbackResize = 262144
ImGuiInputTextFlags_CallbackEdit = 524288
ImGuiInputTextFlags_EscapeClearsAll = 1048576

# ImGuiTreeNodeFlags_
ImGuiTreeNodeFlags_None = 0
ImGuiTreeNodeFlags_Selected = 1
ImGuiTreeNodeFlags_Framed = 2
ImGuiTreeNodeFlags_AllowItemOverlap = 4
ImGuiTreeNodeFlags_NoTreePushOnOpen = 8
ImGuiTreeNodeFlags_NoAutoOpenOnLog = 16
ImGuiTreeNodeFlags_DefaultOpen = 32
ImGuiTreeNodeFlags_OpenOnDoubleClick = 64
ImGuiTreeNodeFlags_OpenOnArrow = 128
ImGuiTreeNodeFlags_Leaf = 256
ImGuiTreeNodeFlags_Bullet = 512
ImGuiTreeNodeFlags_FramePadding = 1024
ImGuiTreeNodeFlags_SpanAvailWidth = 2048
ImGuiTreeNodeFlags_SpanFullWidth = 4096
ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 8192
ImGuiTreeNodeFlags_CollapsingHeader = 26

# ImGuiPopupFlags_
ImGuiPopupFlags_None = 0
ImGuiPopupFlags_MouseButtonLeft = 0
ImGuiPopupFlags_MouseButtonRight = 1
ImGuiPopupFlags_MouseButtonMiddle = 2
ImGuiPopupFlags_MouseButtonMask_ = 31
ImGuiPopupFlags_MouseButtonDefault_ = 1
ImGuiPopupFlags_NoOpenOverExistingPopup = 32
ImGuiPopupFlags_NoOpenOverItems = 64
ImGuiPopupFlags_AnyPopupId = 128
ImGuiPopupFlags_AnyPopupLevel = 256
ImGuiPopupFlags_AnyPopup = 384

# ImGuiSelectableFlags_
ImGuiSelectableFlags_None = 0
ImGuiSelectableFlags_DontClosePopups = 1
ImGuiSelectableFlags_SpanAllColumns = 2
ImGuiSelectableFlags_AllowDoubleClick = 4
ImGuiSelectableFlags_Disabled = 8
ImGuiSelectableFlags_AllowItemOverlap = 16

# ImGuiComboFlags_
ImGuiComboFlags_None = 0
ImGuiComboFlags_PopupAlignLeft = 1
ImGuiComboFlags_HeightSmall = 2
ImGuiComboFlags_HeightRegular = 4
ImGuiComboFlags_HeightLarge = 8
ImGuiComboFlags_HeightLargest = 16
ImGuiComboFlags_NoArrowButton = 32
ImGuiComboFlags_NoPreview = 64
ImGuiComboFlags_HeightMask_ = 30

# ImGuiTabBarFlags_
ImGuiTabBarFlags_None = 0
ImGuiTabBarFlags_Reorderable = 1
ImGuiTabBarFlags_AutoSelectNewTabs = 2
ImGuiTabBarFlags_TabListPopupButton = 4
ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 8
ImGuiTabBarFlags_NoTabListScrollingButtons = 16
ImGuiTabBarFlags_NoTooltip = 32
ImGuiTabBarFlags_FittingPolicyResizeDown = 64
ImGuiTabBarFlags_FittingPolicyScroll = 128
ImGuiTabBarFlags_FittingPolicyMask_ = 192
ImGuiTabBarFlags_FittingPolicyDefault_ = 64

# ImGuiTabItemFlags_
ImGuiTabItemFlags_None = 0
ImGuiTabItemFlags_UnsavedDocument = 1
ImGuiTabItemFlags_SetSelected = 2
ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 4
ImGuiTabItemFlags_NoPushId = 8
ImGuiTabItemFlags_NoTooltip = 16
ImGuiTabItemFlags_NoReorder = 32
ImGuiTabItemFlags_Leading = 64
ImGuiTabItemFlags_Trailing = 128

# ImGuiTableFlags_
ImGuiTableFlags_None = 0
ImGuiTableFlags_Resizable = 1
ImGuiTableFlags_Reorderable = 2
ImGuiTableFlags_Hideable = 4
ImGuiTableFlags_Sortable = 8
ImGuiTableFlags_NoSavedSettings = 16
ImGuiTableFlags_ContextMenuInBody = 32
ImGuiTableFlags_RowBg = 64
ImGuiTableFlags_BordersInnerH = 128
ImGuiTableFlags_BordersOuterH = 256
ImGuiTableFlags_BordersInnerV = 512
ImGuiTableFlags_BordersOuterV = 1024
ImGuiTableFlags_BordersH = 384
ImGuiTableFlags_BordersV = 1536
ImGuiTableFlags_BordersInner = 640
ImGuiTableFlags_BordersOuter = 1280
ImGuiTableFlags_Borders = 1920
ImGuiTableFlags_NoBordersInBody = 2048
ImGuiTableFlags_NoBordersInBodyUntilResize = 4096
ImGuiTableFlags_SizingFixedFit = 8192
ImGuiTableFlags_SizingFixedSame = 16384
ImGuiTableFlags_SizingStretchProp = 24576
ImGuiTableFlags_SizingStretchSame = 32768
ImGuiTableFlags_NoHostExtendX = 65536
ImGuiTableFlags_NoHostExtendY = 131072
ImGuiTableFlags_NoKeepColumnsVisible = 262144
ImGuiTableFlags_PreciseWidths = 524288
ImGuiTableFlags_NoClip = 1048576
ImGuiTableFlags_PadOuterX = 2097152
ImGuiTableFlags_NoPadOuterX = 4194304
ImGuiTableFlags_NoPadInnerX = 8388608
ImGuiTableFlags_ScrollX = 16777216
ImGuiTableFlags_ScrollY = 33554432
ImGuiTableFlags_SortMulti = 67108864
ImGuiTableFlags_SortTristate = 134217728
ImGuiTableFlags_SizingMask_ = 57344

# ImGuiTableColumnFlags_
ImGuiTableColumnFlags_None = 0
ImGuiTableColumnFlags_Disabled = 1
ImGuiTableColumnFlags_DefaultHide = 2
ImGuiTableColumnFlags_DefaultSort = 4
ImGuiTableColumnFlags_WidthStretch = 8
ImGuiTableColumnFlags_WidthFixed = 16
ImGuiTableColumnFlags_NoResize = 32
ImGuiTableColumnFlags_NoReorder = 64
ImGuiTableColumnFlags_NoHide = 128
ImGuiTableColumnFlags_NoClip = 256
ImGuiTableColumnFlags_NoSort = 512
ImGuiTableColumnFlags_NoSortAscending = 1024
ImGuiTableColumnFlags_NoSortDescending = 2048
ImGuiTableColumnFlags_NoHeaderLabel = 4096
ImGuiTableColumnFlags_NoHeaderWidth = 8192
ImGuiTableColumnFlags_PreferSortAscending = 16384
ImGuiTableColumnFlags_PreferSortDescending = 32768
ImGuiTableColumnFlags_IndentEnable = 65536
ImGuiTableColumnFlags_IndentDisable = 131072
ImGuiTableColumnFlags_IsEnabled = 16777216
ImGuiTableColumnFlags_IsVisible = 33554432
ImGuiTableColumnFlags_IsSorted = 67108864
ImGuiTableColumnFlags_IsHovered = 134217728
ImGuiTableColumnFlags_WidthMask_ = 24
ImGuiTableColumnFlags_IndentMask_ = 196608
ImGuiTableColumnFlags_StatusMask_ = 251658240
ImGuiTableColumnFlags_NoDirectResize_ = 1073741824

# ImGuiTableRowFlags_
ImGuiTableRowFlags_None = 0
ImGuiTableRowFlags_Headers = 1

# ImGuiTableBgTarget_
ImGuiTableBgTarget_None = 0
ImGuiTableBgTarget_RowBg0 = 1
ImGuiTableBgTarget_RowBg1 = 2
ImGuiTableBgTarget_CellBg = 3

# ImGuiFocusedFlags_
ImGuiFocusedFlags_None = 0
ImGuiFocusedFlags_ChildWindows = 1
ImGuiFocusedFlags_RootWindow = 2
ImGuiFocusedFlags_AnyWindow = 4
ImGuiFocusedFlags_NoPopupHierarchy = 8
ImGuiFocusedFlags_RootAndChildWindows = 3

# ImGuiHoveredFlags_
ImGuiHoveredFlags_None = 0
ImGuiHoveredFlags_ChildWindows = 1
ImGuiHoveredFlags_RootWindow = 2
ImGuiHoveredFlags_AnyWindow = 4
ImGuiHoveredFlags_NoPopupHierarchy = 8
ImGuiHoveredFlags_AllowWhenBlockedByPopup = 32
ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 128
ImGuiHoveredFlags_AllowWhenOverlapped = 256
ImGuiHoveredFlags_AllowWhenDisabled = 512
ImGuiHoveredFlags_NoNavOverride = 1024
ImGuiHoveredFlags_RectOnly = 416
ImGuiHoveredFlags_RootAndChildWindows = 3
ImGuiHoveredFlags_ForTooltip = 2048
ImGuiHoveredFlags_Stationary = 4096
ImGuiHoveredFlags_DelayNone = 8192
ImGuiHoveredFlags_DelayShort = 16384
ImGuiHoveredFlags_DelayNormal = 32768
ImGuiHoveredFlags_NoSharedDelay = 65536

# ImGuiDragDropFlags_
ImGuiDragDropFlags_None = 0
ImGuiDragDropFlags_SourceNoPreviewTooltip = 1
ImGuiDragDropFlags_SourceNoDisableHover = 2
ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 4
ImGuiDragDropFlags_SourceAllowNullID = 8
ImGuiDragDropFlags_SourceExtern = 16
ImGuiDragDropFlags_SourceAutoExpirePayload = 32
ImGuiDragDropFlags_AcceptBeforeDelivery = 1024
ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 2048
ImGuiDragDropFlags_AcceptNoPreviewTooltip = 4096
ImGuiDragDropFlags_AcceptPeekOnly = 3072

# ImGuiDataType_
ImGuiDataType_S8 = 0
ImGuiDataType_U8 = 1
ImGuiDataType_S16 = 2
ImGuiDataType_U16 = 3
ImGuiDataType_S32 = 4
ImGuiDataType_U32 = 5
ImGuiDataType_S64 = 6
ImGuiDataType_U64 = 7
ImGuiDataType_Float = 8
ImGuiDataType_Double = 9
ImGuiDataType_COUNT = 10

# ImGuiDir_
ImGuiDir_None = -1
ImGuiDir_Left = 0
ImGuiDir_Right = 1
ImGuiDir_Up = 2
ImGuiDir_Down = 3
ImGuiDir_COUNT = 4

# ImGuiSortDirection_
ImGuiSortDirection_None = 0
ImGuiSortDirection_Ascending = 1
ImGuiSortDirection_Descending = 2

# ImGuiKey
ImGuiKey_None = 0
ImGuiKey_Tab = 512
ImGuiKey_LeftArrow = 513
ImGuiKey_RightArrow = 514
ImGuiKey_UpArrow = 515
ImGuiKey_DownArrow = 516
ImGuiKey_PageUp = 517
ImGuiKey_PageDown = 518
ImGuiKey_Home = 519
ImGuiKey_End = 520
ImGuiKey_Insert = 521
ImGuiKey_Delete = 522
ImGuiKey_Backspace = 523
ImGuiKey_Space = 524
ImGuiKey_Enter = 525
ImGuiKey_Escape = 526
ImGuiKey_LeftCtrl = 527
ImGuiKey_LeftShift = 528
ImGuiKey_LeftAlt = 529
ImGuiKey_LeftSuper = 530
ImGuiKey_RightCtrl = 531
ImGuiKey_RightShift = 532
ImGuiKey_RightAlt = 533
ImGuiKey_RightSuper = 534
ImGuiKey_Menu = 535
ImGuiKey_0 = 536
ImGuiKey_1 = 537
ImGuiKey_2 = 538
ImGuiKey_3 = 539
ImGuiKey_4 = 540
ImGuiKey_5 = 541
ImGuiKey_6 = 542
ImGuiKey_7 = 543
ImGuiKey_8 = 544
ImGuiKey_9 = 545
ImGuiKey_A = 546
ImGuiKey_B = 547
ImGuiKey_C = 548
ImGuiKey_D = 549
ImGuiKey_E = 550
ImGuiKey_F = 551
ImGuiKey_G = 552
ImGuiKey_H = 553
ImGuiKey_I = 554
ImGuiKey_J = 555
ImGuiKey_K = 556
ImGuiKey_L = 557
ImGuiKey_M = 558
ImGuiKey_N = 559
ImGuiKey_O = 560
ImGuiKey_P = 561
ImGuiKey_Q = 562
ImGuiKey_R = 563
ImGuiKey_S = 564
ImGuiKey_T = 565
ImGuiKey_U = 566
ImGuiKey_V = 567
ImGuiKey_W = 568
ImGuiKey_X = 569
ImGuiKey_Y = 570
ImGuiKey_Z = 571
ImGuiKey_F1 = 572
ImGuiKey_F2 = 573
ImGuiKey_F3 = 574
ImGuiKey_F4 = 575
ImGuiKey_F5 = 576
ImGuiKey_F6 = 577
ImGuiKey_F7 = 578
ImGuiKey_F8 = 579
ImGuiKey_F9 = 580
ImGuiKey_F10 = 581
ImGuiKey_F11 = 582
ImGuiKey_F12 = 583
ImGuiKey_Apostrophe = 584
ImGuiKey_Comma = 585
ImGuiKey_Minus = 586
ImGuiKey_Period = 587
ImGuiKey_Slash = 588
ImGuiKey_Semicolon = 589
ImGuiKey_Equal = 590
ImGuiKey_LeftBracket = 591
ImGuiKey_Backslash = 592
ImGuiKey_RightBracket = 593
ImGuiKey_GraveAccent = 594
ImGuiKey_CapsLock = 595
ImGuiKey_ScrollLock = 596
ImGuiKey_NumLock = 597
ImGuiKey_PrintScreen = 598
ImGuiKey_Pause = 599
ImGuiKey_Keypad0 = 600
ImGuiKey_Keypad1 = 601
ImGuiKey_Keypad2 = 602
ImGuiKey_Keypad3 = 603
ImGuiKey_Keypad4 = 604
ImGuiKey_Keypad5 = 605
ImGuiKey_Keypad6 = 606
ImGuiKey_Keypad7 = 607
ImGuiKey_Keypad8 = 608
ImGuiKey_Keypad9 = 609
ImGuiKey_KeypadDecimal = 610
ImGuiKey_KeypadDivide = 611
ImGuiKey_KeypadMultiply = 612
ImGuiKey_KeypadSubtract = 613
ImGuiKey_KeypadAdd = 614
ImGuiKey_KeypadEnter = 615
ImGuiKey_KeypadEqual = 616
ImGuiKey_GamepadStart = 617
ImGuiKey_GamepadBack = 618
ImGuiKey_GamepadFaceLeft = 619
ImGuiKey_GamepadFaceRight = 620
ImGuiKey_GamepadFaceUp = 621
ImGuiKey_GamepadFaceDown = 622
ImGuiKey_GamepadDpadLeft = 623
ImGuiKey_GamepadDpadRight = 624
ImGuiKey_GamepadDpadUp = 625
ImGuiKey_GamepadDpadDown = 626
ImGuiKey_GamepadL1 = 627
ImGuiKey_GamepadR1 = 628
ImGuiKey_GamepadL2 = 629
ImGuiKey_GamepadR2 = 630
ImGuiKey_GamepadL3 = 631
ImGuiKey_GamepadR3 = 632
ImGuiKey_GamepadLStickLeft = 633
ImGuiKey_GamepadLStickRight = 634
ImGuiKey_GamepadLStickUp = 635
ImGuiKey_GamepadLStickDown = 636
ImGuiKey_GamepadRStickLeft = 637
ImGuiKey_GamepadRStickRight = 638
ImGuiKey_GamepadRStickUp = 639
ImGuiKey_GamepadRStickDown = 640
ImGuiKey_MouseLeft = 641
ImGuiKey_MouseRight = 642
ImGuiKey_MouseMiddle = 643
ImGuiKey_MouseX1 = 644
ImGuiKey_MouseX2 = 645
ImGuiKey_MouseWheelX = 646
ImGuiKey_MouseWheelY = 647
ImGuiKey_ReservedForModCtrl = 648
ImGuiKey_ReservedForModShift = 649
ImGuiKey_ReservedForModAlt = 650
ImGuiKey_ReservedForModSuper = 651
ImGuiKey_COUNT = 652
ImGuiMod_None = 0
ImGuiMod_Ctrl = 4096
ImGuiMod_Shift = 8192
ImGuiMod_Alt = 16384
ImGuiMod_Super = 32768
ImGuiMod_Shortcut = 2048
ImGuiMod_Mask_ = 63488
ImGuiKey_NamedKey_BEGIN = 512
ImGuiKey_NamedKey_END = 652
ImGuiKey_NamedKey_COUNT = 140
ImGuiKey_KeysData_SIZE = 652
ImGuiKey_KeysData_OFFSET = 0
ImGuiKey_ModCtrl = 4096
ImGuiKey_ModShift = 8192
ImGuiKey_ModAlt = 16384
ImGuiKey_ModSuper = 32768
ImGuiKey_KeyPadEnter = 615

# ImGuiNavInput
ImGuiNavInput_Activate = 0
ImGuiNavInput_Cancel = 1
ImGuiNavInput_Input = 2
ImGuiNavInput_Menu = 3
ImGuiNavInput_DpadLeft = 4
ImGuiNavInput_DpadRight = 5
ImGuiNavInput_DpadUp = 6
ImGuiNavInput_DpadDown = 7
ImGuiNavInput_LStickLeft = 8
ImGuiNavInput_LStickRight = 9
ImGuiNavInput_LStickUp = 10
ImGuiNavInput_LStickDown = 11
ImGuiNavInput_FocusPrev = 12
ImGuiNavInput_FocusNext = 13
ImGuiNavInput_TweakSlow = 14
ImGuiNavInput_TweakFast = 15
ImGuiNavInput_COUNT = 16

# ImGuiConfigFlags_
ImGuiConfigFlags_None = 0
ImGuiConfigFlags_NavEnableKeyboard = 1
ImGuiConfigFlags_NavEnableGamepad = 2
ImGuiConfigFlags_NavEnableSetMousePos = 4
ImGuiConfigFlags_NavNoCaptureKeyboard = 8
ImGuiConfigFlags_NoMouse = 16
ImGuiConfigFlags_NoMouseCursorChange = 32
ImGuiConfigFlags_IsSRGB = 1048576
ImGuiConfigFlags_IsTouchScreen = 2097152

# ImGuiBackendFlags_
ImGuiBackendFlags_None = 0
ImGuiBackendFlags_HasGamepad = 1
ImGuiBackendFlags_HasMouseCursors = 2
ImGuiBackendFlags_HasSetMousePos = 4
ImGuiBackendFlags_RendererHasVtxOffset = 8

# ImGuiCol_
ImGuiCol_Text = 0
ImGuiCol_TextDisabled = 1
ImGuiCol_WindowBg = 2
ImGuiCol_ChildBg = 3
ImGuiCol_PopupBg = 4
ImGuiCol_Border = 5
ImGuiCol_BorderShadow = 6
ImGuiCol_FrameBg = 7
ImGuiCol_FrameBgHovered = 8
ImGuiCol_FrameBgActive = 9
ImGuiCol_TitleBg = 10
ImGuiCol_TitleBgActive = 11
ImGuiCol_TitleBgCollapsed = 12
ImGuiCol_MenuBarBg = 13
ImGuiCol_ScrollbarBg = 14
ImGuiCol_ScrollbarGrab = 15
ImGuiCol_ScrollbarGrabHovered = 16
ImGuiCol_ScrollbarGrabActive = 17
ImGuiCol_CheckMark = 18
ImGuiCol_SliderGrab = 19
ImGuiCol_SliderGrabActive = 20
ImGuiCol_Button = 21
ImGuiCol_ButtonHovered = 22
ImGuiCol_ButtonActive = 23
ImGuiCol_Header = 24
ImGuiCol_HeaderHovered = 25
ImGuiCol_HeaderActive = 26
ImGuiCol_Separator = 27
ImGuiCol_SeparatorHovered = 28
ImGuiCol_SeparatorActive = 29
ImGuiCol_ResizeGrip = 30
ImGuiCol_ResizeGripHovered = 31
ImGuiCol_ResizeGripActive = 32
ImGuiCol_Tab = 33
ImGuiCol_TabHovered = 34
ImGuiCol_TabActive = 35
ImGuiCol_TabUnfocused = 36
ImGuiCol_TabUnfocusedActive = 37
ImGuiCol_PlotLines = 38
ImGuiCol_PlotLinesHovered = 39
ImGuiCol_PlotHistogram = 40
ImGuiCol_PlotHistogramHovered = 41
ImGuiCol_TableHeaderBg = 42
ImGuiCol_TableBorderStrong = 43
ImGuiCol_TableBorderLight = 44
ImGuiCol_TableRowBg = 45
ImGuiCol_TableRowBgAlt = 46
ImGuiCol_TextSelectedBg = 47
ImGuiCol_DragDropTarget = 48
ImGuiCol_NavHighlight = 49
ImGuiCol_NavWindowingHighlight = 50
ImGuiCol_NavWindowingDimBg = 51
ImGuiCol_ModalWindowDimBg = 52
ImGuiCol_COUNT = 53

# ImGuiStyleVar_
ImGuiStyleVar_Alpha = 0
ImGuiStyleVar_DisabledAlpha = 1
ImGuiStyleVar_WindowPadding = 2
ImGuiStyleVar_WindowRounding = 3
ImGuiStyleVar_WindowBorderSize = 4
ImGuiStyleVar_WindowMinSize = 5
ImGuiStyleVar_WindowTitleAlign = 6
ImGuiStyleVar_ChildRounding = 7
ImGuiStyleVar_ChildBorderSize = 8
ImGuiStyleVar_PopupRounding = 9
ImGuiStyleVar_PopupBorderSize = 10
ImGuiStyleVar_FramePadding = 11
ImGuiStyleVar_FrameRounding = 12
ImGuiStyleVar_FrameBorderSize = 13
ImGuiStyleVar_ItemSpacing = 14
ImGuiStyleVar_ItemInnerSpacing = 15
ImGuiStyleVar_IndentSpacing = 16
ImGuiStyleVar_CellPadding = 17
ImGuiStyleVar_ScrollbarSize = 18
ImGuiStyleVar_ScrollbarRounding = 19
ImGuiStyleVar_GrabMinSize = 20
ImGuiStyleVar_GrabRounding = 21
ImGuiStyleVar_TabRounding = 22
ImGuiStyleVar_ButtonTextAlign = 23
ImGuiStyleVar_SelectableTextAlign = 24
ImGuiStyleVar_SeparatorTextBorderSize = 25
ImGuiStyleVar_SeparatorTextAlign = 26
ImGuiStyleVar_SeparatorTextPadding = 27
ImGuiStyleVar_COUNT = 28

# ImGuiButtonFlags_
ImGuiButtonFlags_None = 0
ImGuiButtonFlags_MouseButtonLeft = 1
ImGuiButtonFlags_MouseButtonRight = 2
ImGuiButtonFlags_MouseButtonMiddle = 4
ImGuiButtonFlags_MouseButtonMask_ = 7
ImGuiButtonFlags_MouseButtonDefault_ = 1

# ImGuiColorEditFlags_
ImGuiColorEditFlags_None = 0
ImGuiColorEditFlags_NoAlpha = 2
ImGuiColorEditFlags_NoPicker = 4
ImGuiColorEditFlags_NoOptions = 8
ImGuiColorEditFlags_NoSmallPreview = 16
ImGuiColorEditFlags_NoInputs = 32
ImGuiColorEditFlags_NoTooltip = 64
ImGuiColorEditFlags_NoLabel = 128
ImGuiColorEditFlags_NoSidePreview = 256
ImGuiColorEditFlags_NoDragDrop = 512
ImGuiColorEditFlags_NoBorder = 1024
ImGuiColorEditFlags_AlphaBar = 65536
ImGuiColorEditFlags_AlphaPreview = 131072
ImGuiColorEditFlags_AlphaPreviewHalf = 262144
ImGuiColorEditFlags_HDR = 524288
ImGuiColorEditFlags_DisplayRGB = 1048576
ImGuiColorEditFlags_DisplayHSV = 2097152
ImGuiColorEditFlags_DisplayHex = 4194304
ImGuiColorEditFlags_Uint8 = 8388608
ImGuiColorEditFlags_Float = 16777216
ImGuiColorEditFlags_PickerHueBar = 33554432
ImGuiColorEditFlags_PickerHueWheel = 67108864
ImGuiColorEditFlags_InputRGB = 134217728
ImGuiColorEditFlags_InputHSV = 268435456
ImGuiColorEditFlags_DefaultOptions_ = 177209344
ImGuiColorEditFlags_DisplayMask_ = 7340032
ImGuiColorEditFlags_DataTypeMask_ = 25165824
ImGuiColorEditFlags_PickerMask_ = 100663296
ImGuiColorEditFlags_InputMask_ = 402653184

# ImGuiSliderFlags_
ImGuiSliderFlags_None = 0
ImGuiSliderFlags_AlwaysClamp = 16
ImGuiSliderFlags_Logarithmic = 32
ImGuiSliderFlags_NoRoundToFormat = 64
ImGuiSliderFlags_NoInput = 128
ImGuiSliderFlags_InvalidMask_ = 1879048207

# ImGuiMouseButton_
ImGuiMouseButton_Left = 0
ImGuiMouseButton_Right = 1
ImGuiMouseButton_Middle = 2
ImGuiMouseButton_COUNT = 5

# ImGuiMouseCursor_
ImGuiMouseCursor_None = -1
ImGuiMouseCursor_Arrow = 0
ImGuiMouseCursor_TextInput = 1
ImGuiMouseCursor_ResizeAll = 2
ImGuiMouseCursor_ResizeNS = 3
ImGuiMouseCursor_ResizeEW = 4
ImGuiMouseCursor_ResizeNESW = 5
ImGuiMouseCursor_ResizeNWSE = 6
ImGuiMouseCursor_Hand = 7
ImGuiMouseCursor_NotAllowed = 8
ImGuiMouseCursor_COUNT = 9

# ImGuiMouseSource
ImGuiMouseSource_Mouse = 0
ImGuiMouseSource_TouchScreen = 1
ImGuiMouseSource_Pen = 2
ImGuiMouseSource_COUNT = 3

# ImGuiCond_
ImGuiCond_None = 0
ImGuiCond_Always = 1
ImGuiCond_Once = 2
ImGuiCond_FirstUseEver = 4
ImGuiCond_Appearing = 8

# ImDrawFlags_
ImDrawFlags_None = 0
ImDrawFlags_Closed = 1
ImDrawFlags_RoundCornersTopLeft = 16
ImDrawFlags_RoundCornersTopRight = 32
ImDrawFlags_RoundCornersBottomLeft = 64
ImDrawFlags_RoundCornersBottomRight = 128
ImDrawFlags_RoundCornersNone = 256
ImDrawFlags_RoundCornersTop = 48
ImDrawFlags_RoundCornersBottom = 192
ImDrawFlags_RoundCornersLeft = 80
ImDrawFlags_RoundCornersRight = 160
ImDrawFlags_RoundCornersAll = 240
ImDrawFlags_RoundCornersDefault_ = 240
ImDrawFlags_RoundCornersMask_ = 496

# ImDrawListFlags_
ImDrawListFlags_None = 0
ImDrawListFlags_AntiAliasedLines = 1
ImDrawListFlags_AntiAliasedLinesUseTex = 2
ImDrawListFlags_AntiAliasedFill = 4
ImDrawListFlags_AllowVtxOffset = 8

# ImFontAtlasFlags_
ImFontAtlasFlags_None = 0
ImFontAtlasFlags_NoPowerOfTwoHeight = 1
ImFontAtlasFlags_NoMouseCursors = 2
ImFontAtlasFlags_NoBakedLines = 4

# ImGuiViewportFlags_
ImGuiViewportFlags_None = 0
ImGuiViewportFlags_IsPlatformWindow = 1
ImGuiViewportFlags_IsPlatformMonitor = 2
ImGuiViewportFlags_OwnedByApp = 4

# ImDrawCornerFlags_
ImDrawCornerFlags_None = 256
ImDrawCornerFlags_TopLeft = 16
ImDrawCornerFlags_TopRight = 32
ImDrawCornerFlags_BotLeft = 64
ImDrawCornerFlags_BotRight = 128
ImDrawCornerFlags_All = 240
ImDrawCornerFlags_Top = 48
ImDrawCornerFlags_Bot = 192
ImDrawCornerFlags_Left = 80
ImDrawCornerFlags_Right = 160

# ImGuiModFlags_
ImGuiModFlags_None = 0
ImGuiModFlags_Ctrl = 4096
ImGuiModFlags_Shift = 8192
ImGuiModFlags_Alt = 16384
ImGuiModFlags_Super = 32768
    )", "imgui.py", EXEC_MODE, imgui);
}


inline VM* python_init(){
    VM* vm = new VM();
    add_module_imgui(vm);
    return vm;
}

}