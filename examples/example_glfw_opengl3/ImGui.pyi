from c import *
from linalg import vec2, vec3, vec4

def GetCursorStartPos() -> vec2:
    """initial cursor position in window coordinates"""

def IsAnyItemHovered() -> bool:
    """is any item hovered?"""

def SetScrollHereX(center_x_ratio=0.5):
    """adjust scrolling amount to make current cursor position visible. center_x_ratio=0.0: left, 0.5: center, 1.0: right. When using to make a "default/current item" visible, consider using SetItemDefaultFocus() instead."""

def SliderInt4(label: str, v: int_p, v_min, v_max, format='%d', flags=0) -> bool:
    pass

def GetClipboardText() -> str:
    pass

def EndFrame():
    """ends the Dear ImGui frame. automatically called by Render(). If you don't need to render data (skipping rendering) you may call EndFrame() without Render()... but you'll have wasted CPU already! If you don't need to render, better to not create any windows and not call NewFrame() at all!"""

def GetCursorScreenPos() -> vec2:
    """cursor position in absolute screen coordinates (0..io.DisplaySize) or natural OS coordinates when using multiple viewport. useful to work with ImDrawList API."""

def IsAnyItemActive() -> bool:
    """is any item active?"""

def SetClipboardText(text: str) -> None:
    pass

def Render():
    """ends the Dear ImGui frame, finalize the draw data. You can then get call GetDrawData()."""

def SetCursorScreenPos(pos: vec2):
    """cursor position in absolute screen coordinates (0..io.DisplaySize) or natural OS coordinates when using multiple viewport. useful to work with ImDrawList API."""

def IsAnyItemFocused() -> bool:
    """is any item focused?"""

def SetScrollHereY(center_y_ratio=0.5):
    """adjust scrolling amount to make current cursor position visible. center_y_ratio=0.0: top, 0.5: center, 1.0: bottom. When using to make a "default/current item" visible, consider using SetItemDefaultFocus() instead."""

def GetDrawData() -> void_p:
    """valid after Render() and until the next call to NewFrame(). this is what you have to render."""

def AlignTextToFramePadding():
    """vertically align/lower upcoming text to FramePadding.y so that it will aligns to upcoming widgets (call if you have text on a line before regular widgets)"""

def GetItemRectMin() -> vec2:
    """get upper-left bounding rectangle of the last item (screen space)"""

def InputText(label: str, buf: char_p, buf_size: int, flags=0):
    pass

def GetTextLineHeight() -> float:
    """~ FontSize"""

def GetItemRectMax() -> vec2:
    """get lower-right bounding rectangle of the last item (screen space)"""

def SetScrollFromPosX(local_x: float, center_x_ratio=0.5):
    """adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position."""

def InputTextMultiline(label: str, buf: char_p, buf_size: int, size: vec2 = None, flags=0):
    pass

def ShowDemoWindow(p_open: bool_p = None):
    """create Demo window. demonstrate most ImGui features. call this to learn about the library! try to make it always available in your application!"""

def GetTextLineHeightWithSpacing() -> float:
    """~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)"""

def GetItemRectSize() -> vec2:
    """get size of last item"""

def GetVersion() -> str:
    """get the compiled version string e.g. "1.80 WIP" (essentially the value for IMGUI_VERSION from the compiled version of imgui.cpp)"""

def GetFrameHeight() -> float:
    """~ FontSize + style.FramePadding.y * 2"""

def SetItemAllowOverlap():
    """allow last item to be overlapped by a subsequent item. sometimes useful with invisible buttons, selectables, etc. to catch unused area."""

def SetScrollFromPosY(local_y: float, center_y_ratio=0.5):
    """adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position."""

def InputTextWithHint(label: str, hint: str, buf: char_p, buf_size: int, flags=0):
    pass

def StyleColorsDark():
    """new, recommended style (default)"""

def GetFrameHeightWithSpacing() -> float:
    """~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)"""

def GetMainViewport() -> void_p:
    pass

def StyleColorsLight():
    """best used with borders and a custom, thicker font"""

def PushID(x):
    pass

def GetBackgroundDrawList() -> void_p:
    """get background draw list for the current active window."""

def PushFont(font: void_p):
    """use None as a shortcut to push default font"""

def InputFloat(label: str, v: float_p, step=0.0, step_fast=0.0, format='%.3f', flags=0):
    pass

def StyleColorsClassic():
    """classic imgui style"""

def unknown(*args, **kwargs):
    pass

def GetForegroundDrawList() -> void_p:
    """get foreground draw list for the current active window."""

def PopFont():
    pass

def InputFloat2(label: str, v: float_p, format='%.3f', flags=0) -> bool:
    pass

def Text(s: str):
    pass

def IsRectVisible(size: vec2) -> bool:
    """test if rectangle (of given size, starting from cursor position) is visible / not clipped."""

def InputFloat3(label: str, v: float_p, format='%.3f', flags=0) -> bool:
    pass

def Begin(name: str, p_open: bool_p = None, flags=0) -> bool:
    """- Begin() = push window to the stack and start appending to it. End() = pop window from the stack.
- Passing 'bool* p_open != NULL' shows a window-closing widget in the upper-right corner of the window,
    which clicking will set the boolean to false when clicked.
- You may append multiple times to the same window during the same frame by calling Begin()/End() pairs multiple times.
    Some information such as 'flags' or 'p_open' will only be considered by the first call to Begin().
- Begin() return false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting
    anything to the window. Always call a matching End() for each Begin() call, regardless of its return value!
    [Important: due to legacy reason, this is inconsistent with most other functions such as BeginMenu/EndMenu,
    BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding BeginXXX function
    returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]
- Note that the bottom of window stack always contains a window called 'Debug'."""

def TextColored(col: vec4, s: str):
    pass

def GetTime() -> float:
    """get global imgui time. incremented by io.DeltaTime every frame."""

def InputFloat4(label: str, v: float_p, format='%.3f', flags=0) -> bool:
    pass

def End():
    pass

def TextDisabled(s: str):
    pass

def GetFrameCount() -> int:
    """get global imgui frame count. incremented by 1 every frame."""

def PushStyleColor(idx: int, col: vec4):
    """modify a style color. always use this if you modify the style after NewFrame()."""

def InputInt(label: str, v: int_p, step=1, step_fast=100, flags=0):
    pass

def TextWrapped(s: str):
    pass

def GetDrawListSharedData() -> void_p:
    """you may use this when creating your own ImDrawList instances."""

def PopStyleColor(count=1):
    pass

def InputInt2(label: str, v: int_p, flags=0) -> bool:
    pass

def GetStyleColorName(idx: int) -> str:
    """get a string corresponding to the enum value (for display, saving, etc.)."""

def InputInt3(label: str, v: int_p, flags=0) -> bool:
    pass

def BeginChild(str_id: str, size=None, border=False, flags=0):
    """- Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window. Child windows can embed their own child.
- For each independent axis of 'size': ==0.0f: use remaining host window size / >0.0f: fixed size / <0.0f: use remaining window size minus abs(size) / Each axis can use a different mode, e.g. ImVec2(0,400).
- BeginChild() returns false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting anything to the window.
    Always call a matching EndChild() for each BeginChild() call, regardless of its return value.
    [Important: due to legacy reason, this is inconsistent with most other functions such as BeginMenu/EndMenu,
    BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding BeginXXX function
    returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]"""

def LabelText(label: str, s: str):
    pass

def PushStyleVar(idx: int, val: vec2):
    """modify a style ImVec2 variable. always use this if you modify the style after NewFrame()."""

def InputInt4(label: str, v: int_p, flags=0) -> bool:
    pass

def EndChild():
    pass

def BulletText(s: str):
    pass

def SetStateStorage(storage: void_p):
    """replace current window storage with our own (if you want to manipulate it yourself, typically clear subsection of it)"""

def PopStyleVar(count=1):
    pass

def BeginTooltip() -> bool:
    """begin/append a tooltip window. to create full-featured tooltip (with any kind of items)."""

def IsWindowAppearing() -> bool:
    pass

def SeparatorText(label: str):
    pass

def GetStateStorage() -> void_p:
    pass

def EndTooltip():
    """end/append tooltip window"""

def IsWindowCollapsed() -> bool:
    pass

def Button(label: str, size=None) -> bool:
    """button"""

def BeginChildFrame(id: int, size: vec2, flags: int = 0) -> bool:
    """helper to create a child window / scrolling region that looks like a normal widget frame"""

def PushTabStop(tab_stop: bool):
    """== tab stop enable. Allow focusing using TAB/Shift-TAB, enabled by default but you can disable it for certain widgets"""

def IsWindowFocused(flags=0) -> bool:
    """is current window focused? or its root/child, depending on flags. see flags for options."""

def SmallButton(label: str) -> bool:
    """button with FramePadding=(0,0) to easily embed within text"""

def EndChildFrame():
    """always call EndChildFrame() regardless of BeginChildFrame() return values (which indicates a collapsed/clipped window)"""

def PopTabStop():
    pass

def SetTooltip(text: str):
    """set a text-only tooltip, typically use with ImGui::IsItemHovered(). override any previous call to SetTooltip()."""

def IsWindowHovered(flags=0) -> bool:
    """is current window hovered (and typically: not blocked by a popup/modal)? see flags for options. NB: If you are trying to check whether your mouse should be dispatched to imgui or to your app, you should use the 'io.WantCaptureMouse' boolean for that! Please read the FAQ!"""

def InvisibleButton(str_id: str, size: vec2, flags=0) -> bool:
    """flexible button behavior without the visuals, frequently useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)"""

def BeginItemTooltip() -> bool:
    """begin/append a tooltip window. to create full-featured tooltip (with any kind of items)."""

def GetWindowDrawList() -> void_p:
    """get draw list associated to the current window, to append your own drawing primitives"""

def ArrowButton(str_id: str, dir: int) -> bool:
    """square button with an arrow shape"""

def PushButtonRepeat(repeat: bool):
    """in 'repeat' mode, Button*() functions return repeated true in a typematic manner (using io.KeyRepeatDelay/io.KeyRepeatRate setting). Note that you can call IsItemActive() after any Button() to tell if the button is held in the current frame."""

def SetItemTooltip(text: str):
    """set a text-only tooltip, typically use with ImGui::IsItemHovered(). override any previous call to SetTooltip()."""

def GetWindowPos() -> vec2:
    """get current window position in screen space (useful if you want to do your own drawing via the DrawList API)"""

def CalcTextSize(text: str, hide_text_after_double_hash=False, wrap_width=-1.0) -> vec2:
    """calculate text size. text can be multi-line. optionally ignore text after double-space (for e.g. for logging to file, etc.)"""

def PopButtonRepeat():
    pass

def BeginPopup(str_id: str, flags: int = 0) -> bool:
    """return true if the popup is open, and you can start outputting to it."""

def GetWindowSize() -> vec2:
    """get current window size"""

def Checkbox(label: str, v: bool_p) -> bool:
    pass

def IsKeyDown(key: int) -> bool:
    """is key being held."""

def BeginPopupModal(name: str, p_open=None, flags: int = 0) -> bool:
    """return true if the modal is open, and you can start outputting to it."""

def GetWindowWidth() -> float:
    """get current window width (shortcut for GetWindowSize().x)"""

def IsKeyPressed(key: int, repeat=True) -> bool:
    """was key pressed (went from !Down to Down)? if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate"""

def PushItemWidth(item_width: float):
    """push width of items for common large "item+label" widgets. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side)."""

def EndPopup():
    """only call EndPopup() if BeginPopupXXX() returns true!"""

def GetWindowHeight() -> float:
    """get current window height (shortcut for GetWindowSize().y)"""

def CheckboxFlags(label: str, flags: int_p, flags_value: int) -> bool:
    pass

def IsKeyReleased(key: int) -> bool:
    """was key released (went from Down to !Down)?"""

def PopItemWidth():
    pass

def SetNextItemWidth(item_width: float):
    """set width of the _next_ common large "item+label" widget. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side)"""

def OpenPopup(str_id: str, popup_flags: int = 0):
    """call to mark popup as open (don't call every frame!)."""

def RadioButton(label: str, active: bool) -> bool:
    """use with e.g. if (RadioButton("one", my_value==1)) { my_value = 1; }"""

def CalcItemWidth() -> float:
    """width of item given pushed settings and current cursor position. NOT necessarily the width of last item unlike most 'Item' functions."""

def OpenPopupOnItemClick(str_id: str = None, popup_flags: int = 1):
    """helper to open popup when clicked on last item. Default to ImGuiPopupFlags_MouseButtonRight == 1. (note: actually triggers on the mouse _released_ event to be consistent with popup behaviors)"""

def GetKeyPressedAmount(key: int, repeat_delay: float, rate: float) -> int:
    """uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate"""

def CloseCurrentPopup():
    """manually close the popup we have begin-ed into."""

def SetNextWindowPos(pos: vec2, cond=0, pivot=None):
    """set next window position. call before Begin(). use pivot=(0.5f,0.5f) to center on given point, etc."""

def GetKeyName(key: int) -> str:
    """[DEBUG] returns English name of the key. Those names a provided for debugging purpose and are not meant to be saved persistently not compared."""

def PushTextWrapPos(wrap_local_pos_x: float = 0.0):
    """push word-wrapping position for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window (or column); > 0.0f: wrap at 'wrap_pos_x' position in window local space"""

def BeginPopupContextItem(str_id: str = None, popup_flags: int = 1) -> bool:
    """open+begin popup when clicked on last item. Use str_id==None to associate the popup to previous item. If you want to use that on a non-interactive item such as Text() you need to pass in an explicit ID here. read comments in .cpp!"""

def SetNextWindowSize(size: vec2, cond=0):
    """set next window size. set axis to 0.0f to force an auto-fit on this axis. call before Begin()"""

def ProgressBar(fraction: float, size: vec2=None, overlay: str=None):
    pass

def PopTextWrapPos():
    pass

def BeginPopupContextWindow(str_id: str = None, popup_flags: int = 1) -> bool:
    """open+begin popup when clicked on current window."""

def Bullet():
    """draw a small circle + keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses"""

def SetNextFrameWantCaptureKeyboard(want_capture_keyboard: bool):
    """Override io.WantCaptureKeyboard flag next frame (said flag is left for your application to handle, typically when true it instructs your app to ignore inputs). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting "io.WantCaptureKeyboard = want_capture_keyboard"; after the next NewFrame() call."""

def GetFont() -> void_p:
    """get current font"""

def BeginPopupContextVoid(str_id: str = None, popup_flags: int = 1) -> bool:
    """open+begin popup when clicked in void (where there are no windows)."""

def GetFontSize() -> float:
    """get current font size (= height in pixels) of current font with current scale applied"""

def IsPopupOpen(str_id: str, flags: int = 0) -> bool:
    """return true if the popup is open."""

def SetNextWindowSizeConstraints(size_min: vec2, size_max: vec2):
    """set next window size limits. use -1,-1 on either X/Y axis to preserve the current size. Sizes will be rounded down. Use callback to apply non-trivial programmatic constraints."""

def IsMouseDown(button: int) -> bool:
    """is mouse button held?"""

def GetFontTexUvWhitePixel() -> vec2:
    """get UV coordinate for a while pixel, useful to draw custom shapes via the ImDrawList API"""

def SetNextWindowContentSize(size: vec2):
    """set next window content size (~ scrollable client area, which enforce the range of scrollbars). Not including window decorations (title bar, menu bar, etc.) nor WindowPadding. set an axis to 0.0f to leave it automatic. call before Begin()"""

def IsMouseClicked(button: int, repeat=False) -> bool:
    """did mouse button clicked? (went from !Down to Down). Same as GetMouseClickedCount() == 1."""

def GetStyleColorVec4(idx: int) -> vec4:
    """retrieve style color as stored in ImGuiStyle structure. use to feed back into PushStyleColor(), otherwise use GetColorU32() to get style color with style alpha baked in."""

def BeginDisabled(disabled: bool = True):
    """- Disable all user interactions and dim items visuals (applying style.DisabledAlpha over current colors)
- Those can be nested but it cannot be used to enable an already disabled section (a single BeginDisabled(true) in the stack is enough to keep everything disabled)
- BeginDisabled(false) essentially does nothing useful but is provided to facilitate use of boolean expressions. If you can avoid calling BeginDisabled(False)/EndDisabled() best to avoid it."""

def IsMouseReleased(button: int) -> bool:
    """did mouse button released? (went from Down to !Down)"""

def Separator():
    """separator, generally horizontal. inside a menu bar or in horizontal layout mode, this becomes a vertical separator."""

def EndDisabled():
    pass

def SetNextWindowCollapsed(collapsed: bool, cond=0):
    """set next window collapsed state. call before Begin()"""

def IsMouseDoubleClicked(button: int) -> bool:
    """did mouse button double-clicked? Same as GetMouseClickedCount() == 2. (note that a double-click will also report IsMouseClicked() == true)"""

def SetNextWindowFocus():
    """set next window to be focused / top-most. call before Begin()"""

def Image(user_texture_id: void_p, size: vec2, uv0: vec2 = None, uv1: vec2 = None, tint_col: vec4 = None, border_col: vec4 = None):
    """Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples"""

def GetMouseClickedCount(button: int) -> int:
    """return the number of successive mouse-clicks at the time where a click happen (otherwise 0)."""

def SameLine(offset_from_start_x=0.0, spacing=-1.0):
    """call between widgets or groups to layout them horizontally. X position given in window coordinates."""

def SetNextWindowScroll(scroll: vec2):
    """set next window scrolling value (use < 0.0f to not affect a given axis)."""

def ImageButton(str_id: str, user_texture_id: void_p, size: vec2, uv0: vec2 = None, uv1: vec2 = None, bg_col: vec4 = None, tint_col: vec4 = None) -> bool:
    """Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples"""

def NewLine():
    """undo a SameLine() or force a new line when in a horizontal-layout context."""

def PushClipRect(clip_rect_min: vec2, clip_rect_max: vec2, intersect_with_current_clip_rect: bool):
    pass

def Spacing():
    """add vertical spacing."""

def PopClipRect():
    pass

def SetNextWindowBgAlpha(alpha: float):
    """set next window background alpha."""

def BeginCombo(label: str, preview_value: str, flags=0) -> bool:
    """The BeginCombo()/EndCombo() api allows you to manage your contents and selection state however you want it, by creating e.g. Selectable() items."""

def IsMouseHoveringRect(r_min: vec2, r_max: vec2, clip=True) -> bool:
    """is mouse hovering given bounding rect (in screen space). clipped by current clipping settings, but disregarding of other consideration of focus/window ordering/popup-block."""

def Dummy(size: vec2):
    """add a dummy item of given size. unlike InvisibleButton(), Dummy() won't take the mouse click or be navigable into."""

def SetItemDefaultFocus():
    """make last item the default focused item of a window."""

def GetContentRegionAvail() -> vec2:
    """== GetContentRegionMax() - GetCursorPos()"""

def EndCombo():
    """only call EndCombo() if BeginCombo() returns true!"""

def SetKeyboardFocusHere(offset: int = 0):
    """focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget. Use -1 to access previous widget."""

def GetContentRegionMax() -> vec2:
    """current content boundaries (typically window boundaries including scrolling, or current column boundaries), in windows coordinates"""

def IsMousePosValid(mouse_pos: vec2 = None) -> bool:
    """by convention we use (-FLT_MAX,-FLT_MAX) to denote that there is no mouse available"""

def Indent(indent_w=0.0):
    """move content position toward the right, by indent_w, or style.IndentSpacing if indent_w <= 0"""

def IsItemHovered(flags: int = 0) -> bool:
    """is the last item hovered? (and usable, aka not blocked by a popup, etc.). See ImGuiHoveredFlags for more options."""

def GetWindowContentRegionMin() -> vec2:
    """content boundaries min (roughly (0,0)-Scroll), in window coordinates"""

def IsAnyMouseDown() -> bool:
    """[WILL OBSOLETE] is any mouse button held? This was designed for backends, but prefer having backend maintain a mask of held mouse buttons, because upcoming input queue system will make this invalid."""

def Unindent(indent_w=0.0):
    """move content position back to the left, by indent_w, or style.IndentSpacing if indent_w <= 0"""

def IsItemActive() -> bool:
    """is the last item active? (e.g. button being held, text field being edited. This will continuously return true while holding mouse button on an item. Items that don't interact will always return false)"""

def GetWindowContentRegionMax() -> vec2:
    """content boundaries max (roughly (0,0)+Size-Scroll) where Size can be override with SetNextWindowContentSize(), in window coordinates"""

def Combo(label: str, current_item: int_p, items: list[str], popup_max_height_in_items=-1):
    """The old Combo() api are helpers over BeginCombo()/EndCombo() which are kept available for convenience purpose. This is analogous to how ListBox are created."""

def GetMousePos() -> vec2:
    """shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls"""

def BeginGroup():
    """lock horizontal starting position"""

def IsItemFocused() -> bool:
    """is the last item focused for keyboard/gamepad navigation?"""

def GetScrollX():
    """get scrolling amount [0 .. GetScrollMaxX()]"""

def GetMousePosOnOpeningCurrentPopup() -> vec2:
    """retrieve mouse position at the time of opening popup we have BeginPopup() into (helper to avoid user backing that value themselves)"""

def EndGroup():
    """unlock horizontal starting position + capture the whole group bounding box into one "item" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)"""

def GetScrollY():
    """get scrolling amount [0 .. GetScrollMaxY()]"""

def CreateContext():
    pass

def GetCursorPos() -> vec2:
    """cursor position in window coordinates (relative to window position)"""

def IsItemClicked(mouse_button: int = 0) -> bool:
    """is the last item hovered and mouse clicked on? (**)  == IsMouseClicked(mouse_button) && IsItemHovered()Important. (**) this is NOT equivalent to the behavior of e.g. Button(). Read comments in function definition."""

def SliderFloat(label: str, v: float_p, v_min, v_max, format='%.3f', flags=0) -> bool:
    pass

def IsMouseDragging(button: int, lock_threshold=-1.0) -> bool:
    """is mouse dragging? (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)"""

def GetCursorPosX() -> float:
    pass

def IsItemVisible() -> bool:
    """is the last item visible? (items may be out of sight because of clipping/scrolling)"""

def SetScrollX(scroll_x: float):
    """set scrolling amount [0 .. GetScrollMaxX()]"""

def SliderFloat2(label: str, v: float_p, v_min, v_max, format='%.3f', flags=0) -> bool:
    pass

def GetMouseDragDelta(button: int=0, lock_threshold=-1.0) -> vec2:
    """return the delta from the initial clicking position while the mouse button is pressed or was just released. This is locked and return 0.0f until the mouse moves past a distance threshold at least once (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)"""

def DestroyContext(ctx: void_p = None):
    pass

def GetCursorPosY() -> float:
    pass

def IsItemEdited() -> bool:
    """did the last item modify its underlying value this frame? or was pressed? This is generally the same as the "bool" return value of many widgets."""

def SliderFloat3(label: str, v: float_p, v_min, v_max, format='%.3f', flags=0) -> bool:
    pass

def ResetMouseDragDelta(button: int=0) -> None:
    """reset the dragging state when the mouse has been dragging (0=left, 1=right, 2=middle)"""

def GetCurrentContext() -> void_p:
    pass

def IsItemActivated() -> bool:
    """was the last item just made active (item was previously inactive)."""

def SetScrollY(scroll_y: float):
    """set scrolling amount [0 .. GetScrollMaxY()]"""

def SliderFloat4(label: str, v: float_p, v_min, v_max, format='%.3f', flags=0) -> bool:
    pass

def GetMouseCursor() -> int:
    """get desired cursor type, reset in end frame. valid before Render(). if you use software rendering by setting io.MouseDrawCursor ImGui will render those for you"""

def SetCurrentContext(ctx: void_p):
    pass

def SetCursorPos(local_pos: vec2):
    """cursor position in window coordinates (relative to window position)"""

def IsItemDeactivated() -> bool:
    """was the last item just made inactive (item was previously active). Useful for Undo/Redo patterns with widgets that require continuous editing."""

def GetScrollMaxX():
    """get maximum scrolling amount ~~ ContentSize.x - WindowSize.x - DecorationsSize.x"""

def SliderInt(label: str, v: int_p, v_min, v_max, format='%d', flags=0) -> bool:
    pass

def SetMouseCursor(type: int) -> None:
    """set desired cursor type"""

def GetIO() -> void_p:
    """access the IO structure (mouse/keyboard/gamepad inputs, time, various configuration options/flags)"""

def SetCursorPosX(local_x: float):
    pass

def IsItemDeactivatedAfterEdit() -> bool:
    """was the last item just made inactive and made a value change when it was active? (e.g. Slider/Drag moved). Useful for Undo/Redo patterns with widgets that require continuous editing. Note that you may get false positives (some widgets such as Combo()/ListBox()/Selectable() will return true even when clicking an already selected item)."""

def GetScrollMaxY():
    """get maximum scrolling amount ~~ ContentSize.y - WindowSize.y - DecorationsSize.y"""

def SliderInt2(label: str, v: int_p, v_min, v_max, format='%d', flags=0) -> bool:
    pass

def GetStyle() -> void_p:
    """access the Style structure (colors, sizes). Always use PushStyleCol(), PushStyleVar() to modify style mid-frame!"""

def SetCursorPosY(local_y: float):
    pass

def IsItemToggledOpen() -> bool:
    """was the last item open state toggled? set by TreeNode()."""

def SliderInt3(label: str, v: int_p, v_min, v_max, format='%d', flags=0) -> bool:
    pass

def SetNextFrameWantCaptureMouse(want_capture_mouse: bool):
    """set next window ala Begin() to be focused / hovered for input handling without navigation"""

def NewFrame():
    """start a new Dear ImGui frame, you can submit any command from this point until Render()/EndFrame()."""


ImGuiKey_GamepadL1 = 627
ImGuiCol_TabActive = 35
ImGuiCond_Always = 1
ImGuiSelectableFlags_AllowDoubleClick = 4
ImGuiHoveredFlags_RootWindow = 2
ImGuiKey_F2 = 573
ImGuiNavInput_FocusPrev = 12
ImGuiColorEditFlags_NoAlpha = 2
ImGuiTableFlags_NoHostExtendX = 65536
ImGuiKey_Home = 519
ImGuiKey_GamepadR1 = 628
ImGuiCol_TabUnfocused = 36
ImGuiCond_Once = 2
ImGuiSelectableFlags_Disabled = 8
ImGuiHoveredFlags_AnyWindow = 4
ImGuiKey_F3 = 574
ImGuiNavInput_FocusNext = 13
ImGuiColorEditFlags_NoPicker = 4
ImGuiTableFlags_NoHostExtendY = 131072
ImGuiKey_End = 520
ImGuiKey_GamepadL2 = 629
ImGuiCol_TabUnfocusedActive = 37
ImGuiCond_FirstUseEver = 4
ImGuiSelectableFlags_AllowItemOverlap = 16
ImGuiHoveredFlags_NoPopupHierarchy = 8
ImGuiKey_F4 = 575
ImGuiNavInput_TweakSlow = 14
ImGuiColorEditFlags_NoOptions = 8
ImGuiInputTextFlags_None = 0
ImGuiTableFlags_NoKeepColumnsVisible = 262144
ImGuiKey_Insert = 521
ImGuiKey_GamepadR2 = 630
ImGuiCol_PlotLines = 38
ImGuiCond_Appearing = 8
ImGuiComboFlags_None = 0
ImGuiHoveredFlags_AllowWhenBlockedByPopup = 32
ImGuiKey_F5 = 576
ImGuiNavInput_TweakFast = 15
ImGuiColorEditFlags_NoSmallPreview = 16
ImGuiInputTextFlags_CharsDecimal = 1
ImGuiTableFlags_PreciseWidths = 524288
ImGuiKey_Delete = 522
ImGuiKey_GamepadL3 = 631
ImGuiCol_PlotLinesHovered = 39
ImGuiComboFlags_PopupAlignLeft = 1
ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 128
ImGuiKey_F6 = 577
ImGuiNavInput_COUNT = 16
ImGuiColorEditFlags_NoInputs = 32
ImGuiInputTextFlags_CharsHexadecimal = 2
ImGuiTableFlags_NoClip = 1048576
ImGuiKey_Backspace = 523
ImGuiKey_GamepadR3 = 632
ImGuiCol_PlotHistogram = 40
ImGuiComboFlags_HeightSmall = 2
ImGuiHoveredFlags_AllowWhenOverlapped = 256
ImGuiKey_F7 = 578
ImGuiConfigFlags_None = 0
ImGuiColorEditFlags_NoTooltip = 64
ImGuiInputTextFlags_CharsUppercase = 4
ImGuiTableFlags_PadOuterX = 2097152
ImGuiKey_Space = 524
ImGuiKey_GamepadLStickLeft = 633
ImGuiCol_PlotHistogramHovered = 41
ImGuiComboFlags_HeightRegular = 4
ImGuiHoveredFlags_AllowWhenDisabled = 512
ImGuiKey_F8 = 579
ImGuiConfigFlags_NavEnableKeyboard = 1
ImGuiColorEditFlags_NoLabel = 128
ImGuiInputTextFlags_CharsNoBlank = 8
ImGuiTableFlags_NoPadOuterX = 4194304
ImGuiKey_Enter = 525
ImGuiKey_GamepadLStickRight = 634
ImGuiCol_TableHeaderBg = 42
ImGuiComboFlags_HeightLarge = 8
ImGuiHoveredFlags_NoNavOverride = 1024
ImGuiKey_F9 = 580
ImGuiConfigFlags_NavEnableGamepad = 2
ImGuiColorEditFlags_NoSidePreview = 256
ImGuiInputTextFlags_AutoSelectAll = 16
ImGuiTableFlags_NoPadInnerX = 8388608
ImGuiKey_Escape = 526
ImGuiKey_GamepadLStickUp = 635
ImGuiCol_TableBorderStrong = 43
ImGuiComboFlags_HeightLargest = 16
ImGuiHoveredFlags_RectOnly = 416
ImGuiKey_F10 = 581
ImGuiConfigFlags_NavEnableSetMousePos = 4
ImGuiColorEditFlags_NoDragDrop = 512
ImGuiInputTextFlags_EnterReturnsTrue = 32
ImGuiTableFlags_ScrollX = 16777216
ImGuiKey_LeftCtrl = 527
ImGuiKey_GamepadLStickDown = 636
ImGuiCol_TableBorderLight = 44
ImGuiComboFlags_NoArrowButton = 32
ImGuiHoveredFlags_RootAndChildWindows = 3
ImGuiKey_F11 = 582
ImGuiConfigFlags_NavNoCaptureKeyboard = 8
ImGuiColorEditFlags_NoBorder = 1024
ImGuiInputTextFlags_CallbackCompletion = 64
ImGuiTableFlags_ScrollY = 33554432
ImGuiKey_LeftShift = 528
ImGuiKey_GamepadRStickLeft = 637
ImGuiCol_TableRowBg = 45
ImGuiComboFlags_NoPreview = 64
ImGuiHoveredFlags_ForTooltip = 2048
ImGuiKey_F12 = 583
ImGuiConfigFlags_NoMouse = 16
ImGuiColorEditFlags_AlphaBar = 65536
ImGuiInputTextFlags_CallbackHistory = 128
ImGuiTableFlags_SortMulti = 67108864
ImGuiKey_LeftAlt = 529
ImGuiKey_GamepadRStickRight = 638
ImGuiCol_TableRowBgAlt = 46
ImGuiComboFlags_HeightMask_ = 30
ImGuiHoveredFlags_Stationary = 4096
ImGuiKey_Apostrophe = 584
ImGuiConfigFlags_NoMouseCursorChange = 32
ImGuiColorEditFlags_AlphaPreview = 131072
ImGuiInputTextFlags_CallbackAlways = 256
ImGuiTableFlags_SortTristate = 134217728
ImGuiKey_LeftSuper = 530
ImGuiKey_GamepadRStickUp = 639
ImGuiCol_TextSelectedBg = 47
ImGuiTabBarFlags_None = 0
ImGuiHoveredFlags_DelayNone = 8192
ImGuiKey_Comma = 585
ImGuiConfigFlags_IsSRGB = 1048576
ImGuiColorEditFlags_AlphaPreviewHalf = 262144
ImGuiInputTextFlags_CallbackCharFilter = 512
ImGuiTableFlags_SizingMask_ = 57344
ImGuiKey_RightCtrl = 531
ImGuiKey_GamepadRStickDown = 640
ImGuiCol_DragDropTarget = 48
ImGuiTabBarFlags_Reorderable = 1
ImGuiHoveredFlags_DelayShort = 16384
ImGuiKey_Minus = 586
ImGuiConfigFlags_IsTouchScreen = 2097152
ImGuiColorEditFlags_HDR = 524288
ImGuiInputTextFlags_AllowTabInput = 1024
ImGuiTableColumnFlags_None = 0
ImGuiKey_RightShift = 532
ImGuiKey_MouseLeft = 641
ImGuiCol_NavHighlight = 49
ImGuiTabBarFlags_AutoSelectNewTabs = 2
ImGuiHoveredFlags_DelayNormal = 32768
ImGuiKey_Period = 587
ImGuiBackendFlags_None = 0
ImGuiColorEditFlags_DisplayRGB = 1048576
ImGuiInputTextFlags_CtrlEnterForNewLine = 2048
ImGuiTableColumnFlags_Disabled = 1
ImGuiKey_RightAlt = 533
ImGuiKey_MouseRight = 642
ImGuiCol_NavWindowingHighlight = 50
ImGuiTabBarFlags_TabListPopupButton = 4
ImGuiHoveredFlags_NoSharedDelay = 65536
ImGuiKey_Slash = 588
ImGuiBackendFlags_HasGamepad = 1
ImGuiColorEditFlags_DisplayHSV = 2097152
ImGuiInputTextFlags_NoHorizontalScroll = 4096
ImGuiTableColumnFlags_DefaultHide = 2
ImGuiKey_RightSuper = 534
ImGuiKey_MouseMiddle = 643
ImGuiCol_NavWindowingDimBg = 51
ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 8
ImGuiDragDropFlags_None = 0
ImGuiKey_Semicolon = 589
ImGuiBackendFlags_HasMouseCursors = 2
ImGuiColorEditFlags_DisplayHex = 4194304
ImGuiInputTextFlags_AlwaysOverwrite = 8192
ImGuiTableColumnFlags_DefaultSort = 4
ImGuiKey_Menu = 535
ImGuiKey_MouseX1 = 644
ImGuiCol_ModalWindowDimBg = 52
ImGuiTabBarFlags_NoTabListScrollingButtons = 16
ImGuiDragDropFlags_SourceNoPreviewTooltip = 1
ImGuiKey_Equal = 590
ImGuiBackendFlags_HasSetMousePos = 4
ImGuiColorEditFlags_Uint8 = 8388608
ImGuiInputTextFlags_ReadOnly = 16384
ImGuiTableColumnFlags_WidthStretch = 8
ImGuiKey_0 = 536
ImGuiKey_MouseX2 = 645
ImGuiCol_COUNT = 53
ImGuiTabBarFlags_NoTooltip = 32
ImGuiDragDropFlags_SourceNoDisableHover = 2
ImGuiKey_LeftBracket = 591
ImGuiBackendFlags_RendererHasVtxOffset = 8
ImGuiColorEditFlags_Float = 16777216
ImGuiInputTextFlags_Password = 32768
ImGuiTableColumnFlags_WidthFixed = 16
ImGuiKey_1 = 537
ImGuiKey_MouseWheelX = 646
ImGuiStyleVar_Alpha = 0
ImGuiTabBarFlags_FittingPolicyResizeDown = 64
ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 4
ImGuiKey_Backslash = 592
ImGuiCol_Text = 0
ImGuiColorEditFlags_PickerHueBar = 33554432
ImGuiInputTextFlags_NoUndoRedo = 65536
ImGuiTableColumnFlags_NoResize = 32
ImGuiKey_2 = 538
ImGuiKey_MouseWheelY = 647
ImGuiStyleVar_DisabledAlpha = 1
ImGuiTabBarFlags_FittingPolicyScroll = 128
ImGuiDragDropFlags_SourceAllowNullID = 8
ImGuiKey_RightBracket = 593
ImGuiCol_TextDisabled = 1
ImGuiColorEditFlags_PickerHueWheel = 67108864
ImGuiInputTextFlags_CharsScientific = 131072
ImGuiTableColumnFlags_NoReorder = 64
ImGuiKey_3 = 539
ImGuiKey_ReservedForModCtrl = 648
ImGuiStyleVar_WindowPadding = 2
ImGuiTabBarFlags_FittingPolicyMask_ = 192
ImGuiDragDropFlags_SourceExtern = 16
ImGuiKey_GraveAccent = 594
ImGuiCol_WindowBg = 2
ImGuiColorEditFlags_InputRGB = 134217728
ImGuiInputTextFlags_CallbackResize = 262144
ImGuiTableColumnFlags_NoHide = 128
ImGuiKey_4 = 540
ImGuiKey_ReservedForModShift = 649
ImGuiStyleVar_WindowRounding = 3
ImGuiTabBarFlags_FittingPolicyDefault_ = 64
ImGuiDragDropFlags_SourceAutoExpirePayload = 32
ImGuiKey_CapsLock = 595
ImGuiCol_ChildBg = 3
ImGuiColorEditFlags_InputHSV = 268435456
ImGuiInputTextFlags_CallbackEdit = 524288
ImGuiTableColumnFlags_NoClip = 256
ImGuiKey_5 = 541
ImGuiKey_ReservedForModAlt = 650
ImGuiStyleVar_WindowBorderSize = 4
ImGuiTabItemFlags_None = 0
ImGuiDragDropFlags_AcceptBeforeDelivery = 1024
ImGuiKey_ScrollLock = 596
ImGuiCol_PopupBg = 4
ImGuiColorEditFlags_DefaultOptions_ = 177209344
ImGuiInputTextFlags_EscapeClearsAll = 1048576
ImGuiTableColumnFlags_NoSort = 512
ImGuiKey_6 = 542
ImGuiKey_ReservedForModSuper = 651
ImGuiStyleVar_WindowMinSize = 5
ImGuiTabItemFlags_UnsavedDocument = 1
ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 2048
ImGuiKey_NumLock = 597
ImGuiCol_Border = 5
ImGuiColorEditFlags_DisplayMask_ = 7340032
ImGuiTreeNodeFlags_None = 0
ImGuiTableColumnFlags_NoSortAscending = 1024
ImGuiKey_7 = 543
ImGuiKey_COUNT = 652
ImGuiStyleVar_WindowTitleAlign = 6
ImGuiTabItemFlags_SetSelected = 2
ImGuiDragDropFlags_AcceptNoPreviewTooltip = 4096
ImGuiKey_PrintScreen = 598
ImGuiCol_BorderShadow = 6
ImGuiColorEditFlags_DataTypeMask_ = 25165824
ImGuiTreeNodeFlags_Selected = 1
ImGuiTableColumnFlags_NoSortDescending = 2048
ImGuiKey_8 = 544
ImGuiMod_None = 0
ImGuiStyleVar_ChildRounding = 7
ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 4
ImGuiDragDropFlags_AcceptPeekOnly = 3072
ImGuiKey_Pause = 599
ImGuiCol_FrameBg = 7
ImGuiColorEditFlags_PickerMask_ = 100663296
ImGuiTreeNodeFlags_Framed = 2
ImGuiTableColumnFlags_NoHeaderLabel = 4096
ImGuiKey_9 = 545
ImGuiMod_Ctrl = 4096
ImGuiStyleVar_ChildBorderSize = 8
ImGuiViewportFlags_None = 0
ImGuiTabItemFlags_NoPushId = 8
ImGuiDataType_S8 = 0
ImGuiKey_Keypad0 = 600
ImGuiCol_FrameBgHovered = 8
ImGuiColorEditFlags_InputMask_ = 402653184
ImGuiTreeNodeFlags_AllowItemOverlap = 4
ImGuiTableColumnFlags_NoHeaderWidth = 8192
ImGuiKey_A = 546
ImGuiMod_Shift = 8192
ImGuiStyleVar_PopupRounding = 9
ImGuiViewportFlags_IsPlatformWindow = 1
ImGuiTabItemFlags_NoTooltip = 16
ImGuiDataType_U8 = 1
ImGuiKey_Keypad1 = 601
ImGuiCol_FrameBgActive = 9
ImGuiSliderFlags_None = 0
ImGuiTreeNodeFlags_NoTreePushOnOpen = 8
ImGuiTableColumnFlags_PreferSortAscending = 16384
ImGuiKey_B = 547
ImGuiMod_Alt = 16384
ImGuiStyleVar_PopupBorderSize = 10
ImGuiViewportFlags_IsPlatformMonitor = 2
ImGuiTabItemFlags_NoReorder = 32
ImGuiDataType_S16 = 2
ImGuiKey_Keypad2 = 602
ImGuiCol_TitleBg = 10
ImGuiSliderFlags_AlwaysClamp = 16
ImGuiTreeNodeFlags_NoAutoOpenOnLog = 16
ImGuiTableColumnFlags_PreferSortDescending = 32768
ImGuiKey_C = 548
ImGuiMod_Super = 32768
ImGuiStyleVar_FramePadding = 11
ImGuiViewportFlags_OwnedByApp = 4
ImGuiTabItemFlags_Leading = 64
ImGuiDataType_U16 = 3
ImGuiKey_Keypad3 = 603
ImGuiCol_TitleBgActive = 11
ImGuiSliderFlags_Logarithmic = 32
ImGuiTreeNodeFlags_DefaultOpen = 32
ImGuiTableColumnFlags_IndentEnable = 65536
ImGuiKey_D = 549
ImGuiMod_Shortcut = 2048
ImGuiStyleVar_FrameRounding = 12
ImGuiTabItemFlags_Trailing = 128
ImGuiDataType_S32 = 4
ImGuiKey_Keypad4 = 604
ImGuiCol_TitleBgCollapsed = 12
ImGuiSliderFlags_NoRoundToFormat = 64
ImGuiTreeNodeFlags_OpenOnDoubleClick = 64
ImGuiTableColumnFlags_IndentDisable = 131072
ImGuiKey_E = 550
ImGuiMod_Mask_ = 63488
ImGuiStyleVar_FrameBorderSize = 13
ImGuiTableFlags_None = 0
ImGuiDataType_U32 = 5
ImGuiKey_Keypad5 = 605
ImGuiCol_MenuBarBg = 13
ImGuiSliderFlags_NoInput = 128
ImGuiTreeNodeFlags_OpenOnArrow = 128
ImGuiTableColumnFlags_IsEnabled = 16777216
ImGuiKey_F = 551
ImGuiKey_NamedKey_BEGIN = 512
ImGuiStyleVar_ItemSpacing = 14
ImGuiTableFlags_Resizable = 1
ImGuiDataType_S64 = 6
ImGuiKey_Keypad6 = 606
ImGuiCol_ScrollbarBg = 14
ImGuiSliderFlags_InvalidMask_ = 1879048207
ImGuiTreeNodeFlags_Leaf = 256
ImGuiTableColumnFlags_IsVisible = 33554432
ImGuiKey_G = 552
ImGuiKey_NamedKey_END = 652
ImGuiStyleVar_ItemInnerSpacing = 15
ImGuiTableFlags_Reorderable = 2
ImGuiDataType_U64 = 7
ImGuiKey_Keypad7 = 607
ImGuiCol_ScrollbarGrab = 15
ImGuiMouseButton_Left = 0
ImGuiTreeNodeFlags_Bullet = 512
ImGuiTableColumnFlags_IsSorted = 67108864
ImGuiKey_H = 553
ImGuiKey_NamedKey_COUNT = 140
ImGuiStyleVar_IndentSpacing = 16
ImGuiTableFlags_Hideable = 4
ImGuiDataType_Float = 8
ImGuiKey_Keypad8 = 608
ImGuiCol_ScrollbarGrabHovered = 16
ImGuiMouseButton_Right = 1
ImGuiTreeNodeFlags_FramePadding = 1024
ImGuiTableColumnFlags_IsHovered = 134217728
ImGuiKey_I = 554
ImGuiKey_KeysData_SIZE = 652
ImGuiStyleVar_CellPadding = 17
ImGuiTableFlags_Sortable = 8
ImGuiDataType_Double = 9
ImGuiKey_Keypad9 = 609
ImGuiCol_ScrollbarGrabActive = 17
ImGuiMouseButton_Middle = 2
ImGuiTreeNodeFlags_SpanAvailWidth = 2048
ImGuiTableColumnFlags_WidthMask_ = 24
ImGuiKey_J = 555
ImGuiKey_KeysData_OFFSET = 0
ImGuiStyleVar_ScrollbarSize = 18
ImGuiTableFlags_NoSavedSettings = 16
ImGuiDataType_COUNT = 10
ImGuiKey_KeypadDecimal = 610
ImGuiCol_CheckMark = 18
ImGuiMouseButton_COUNT = 5
ImGuiTreeNodeFlags_SpanFullWidth = 4096
ImGuiTableColumnFlags_IndentMask_ = 196608
ImGuiKey_K = 556
ImGuiKey_ModCtrl = 4096
ImGuiStyleVar_ScrollbarRounding = 19
ImGuiTableFlags_ContextMenuInBody = 32
ImGuiDir_None = -1
ImGuiKey_KeypadDivide = 611
ImGuiCol_SliderGrab = 19
ImGuiMouseCursor_None = -1
ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 8192
ImGuiTableColumnFlags_StatusMask_ = 251658240
ImGuiKey_L = 557
ImGuiKey_ModShift = 8192
ImGuiStyleVar_GrabMinSize = 20
ImGuiTableFlags_RowBg = 64
ImGuiDir_Left = 0
ImGuiKey_KeypadMultiply = 612
ImGuiCol_SliderGrabActive = 20
ImGuiMouseCursor_Arrow = 0
ImGuiTreeNodeFlags_CollapsingHeader = 26
ImGuiTableColumnFlags_NoDirectResize_ = 1073741824
ImGuiKey_M = 558
ImGuiKey_ModAlt = 16384
ImGuiStyleVar_GrabRounding = 21
ImGuiTableFlags_BordersInnerH = 128
ImGuiDir_Right = 1
ImGuiKey_KeypadSubtract = 613
ImGuiCol_Button = 21
ImGuiMouseCursor_TextInput = 1
ImGuiPopupFlags_None = 0
ImGuiTableRowFlags_None = 0
ImGuiKey_N = 559
ImGuiKey_ModSuper = 32768
ImGuiStyleVar_TabRounding = 22
ImGuiModFlags_None = 0
ImGuiTableFlags_BordersOuterH = 256
ImGuiDir_Up = 2
ImGuiKey_KeypadAdd = 614
ImGuiCol_ButtonHovered = 22
ImGuiMouseCursor_ResizeAll = 2
ImGuiPopupFlags_MouseButtonLeft = 0
ImGuiTableRowFlags_Headers = 1
ImGuiKey_O = 560
ImGuiKey_KeyPadEnter = 615
ImGuiStyleVar_ButtonTextAlign = 23
ImGuiModFlags_Ctrl = 4096
ImGuiTableFlags_BordersInnerV = 512
ImGuiDir_Down = 3
ImGuiKey_KeypadEnter = 615
ImGuiCol_ButtonActive = 23
ImGuiMouseCursor_ResizeNS = 3
ImGuiPopupFlags_MouseButtonRight = 1
ImGuiTableBgTarget_None = 0
ImGuiKey_P = 561
ImGuiNavInput_Activate = 0
ImGuiStyleVar_SelectableTextAlign = 24
ImGuiModFlags_Shift = 8192
ImGuiTableFlags_BordersOuterV = 1024
ImGuiDir_COUNT = 4
ImGuiKey_KeypadEqual = 616
ImGuiCol_Header = 24
ImGuiMouseCursor_ResizeEW = 4
ImGuiPopupFlags_MouseButtonMiddle = 2
ImGuiTableBgTarget_RowBg0 = 1
ImGuiKey_Q = 562
ImGuiNavInput_Cancel = 1
ImGuiStyleVar_SeparatorTextBorderSize = 25
ImGuiModFlags_Alt = 16384
ImGuiTableFlags_BordersH = 384
ImGuiSortDirection_None = 0
ImGuiKey_GamepadStart = 617
ImGuiCol_HeaderHovered = 25
ImGuiMouseCursor_ResizeNESW = 5
ImGuiPopupFlags_MouseButtonMask_ = 31
ImGuiTableBgTarget_RowBg1 = 2
ImGuiKey_R = 563
ImGuiNavInput_Input = 2
ImGuiStyleVar_SeparatorTextAlign = 26
ImGuiModFlags_Super = 32768
ImGuiTableFlags_BordersV = 1536
ImGuiSortDirection_Ascending = 1
ImGuiKey_GamepadBack = 618
ImGuiCol_HeaderActive = 26
ImGuiMouseCursor_ResizeNWSE = 6
ImGuiPopupFlags_MouseButtonDefault_ = 1
ImGuiTableBgTarget_CellBg = 3
ImGuiKey_S = 564
ImGuiNavInput_Menu = 3
ImGuiStyleVar_SeparatorTextPadding = 27
ImGuiTableFlags_BordersInner = 640
ImGuiSortDirection_Descending = 2
ImGuiKey_GamepadFaceLeft = 619
ImGuiCol_Separator = 27
ImGuiMouseCursor_Hand = 7
ImGuiPopupFlags_NoOpenOverExistingPopup = 32
ImGuiFocusedFlags_None = 0
ImGuiKey_T = 565
ImGuiNavInput_DpadLeft = 4
ImGuiStyleVar_COUNT = 28
ImGuiTableFlags_BordersOuter = 1280
ImGuiKey_None = 0
ImGuiKey_GamepadFaceRight = 620
ImGuiCol_SeparatorHovered = 28
ImGuiMouseCursor_NotAllowed = 8
ImGuiPopupFlags_NoOpenOverItems = 64
ImGuiFocusedFlags_ChildWindows = 1
ImGuiKey_U = 566
ImGuiNavInput_DpadRight = 5
ImGuiButtonFlags_None = 0
ImGuiTableFlags_Borders = 1920
ImGuiKey_Tab = 512
ImGuiKey_GamepadFaceUp = 621
ImGuiCol_SeparatorActive = 29
ImGuiMouseCursor_COUNT = 9
ImGuiPopupFlags_AnyPopupId = 128
ImGuiFocusedFlags_RootWindow = 2
ImGuiKey_V = 567
ImGuiNavInput_DpadUp = 6
ImGuiButtonFlags_MouseButtonLeft = 1
ImGuiTableFlags_NoBordersInBody = 2048
ImGuiKey_LeftArrow = 513
ImGuiKey_GamepadFaceDown = 622
ImGuiCol_ResizeGrip = 30
ImGuiMouseSource_Mouse = 0
ImGuiPopupFlags_AnyPopupLevel = 256
ImGuiFocusedFlags_AnyWindow = 4
ImGuiKey_W = 568
ImGuiNavInput_DpadDown = 7
ImGuiButtonFlags_MouseButtonRight = 2
ImGuiTableFlags_NoBordersInBodyUntilResize = 4096
ImGuiKey_RightArrow = 514
ImGuiKey_GamepadDpadLeft = 623
ImGuiCol_ResizeGripHovered = 31
ImGuiMouseSource_TouchScreen = 1
ImGuiPopupFlags_AnyPopup = 384
ImGuiFocusedFlags_NoPopupHierarchy = 8
ImGuiKey_X = 569
ImGuiNavInput_LStickLeft = 8
ImGuiButtonFlags_MouseButtonMiddle = 4
ImGuiTableFlags_SizingFixedFit = 8192
ImGuiKey_UpArrow = 515
ImGuiKey_GamepadDpadRight = 624
ImGuiCol_ResizeGripActive = 32
ImGuiMouseSource_Pen = 2
ImGuiSelectableFlags_None = 0
ImGuiFocusedFlags_RootAndChildWindows = 3
ImGuiKey_Y = 570
ImGuiNavInput_LStickRight = 9
ImGuiButtonFlags_MouseButtonMask_ = 7
ImGuiTableFlags_SizingFixedSame = 16384
ImGuiKey_DownArrow = 516
ImGuiKey_GamepadDpadUp = 625
ImGuiCol_Tab = 33
ImGuiMouseSource_COUNT = 3
ImGuiSelectableFlags_DontClosePopups = 1
ImGuiHoveredFlags_None = 0
ImGuiKey_Z = 571
ImGuiNavInput_LStickUp = 10
ImGuiButtonFlags_MouseButtonDefault_ = 1
ImGuiTableFlags_SizingStretchProp = 24576
ImGuiKey_PageUp = 517
ImGuiKey_GamepadDpadDown = 626
ImGuiCol_TabHovered = 34
ImGuiCond_None = 0
ImGuiSelectableFlags_SpanAllColumns = 2
ImGuiHoveredFlags_ChildWindows = 1
ImGuiKey_F1 = 572
ImGuiNavInput_LStickDown = 11
ImGuiColorEditFlags_None = 0
ImGuiTableFlags_SizingStretchSame = 32768
ImGuiKey_PageDown = 518
