import ImGui
from linalg import *
from c import *

count = 0

v1 = float_()
v2 = float_()
v1.write_float(0.5)
v2.write_float(0.4)
v = bool_()
v.write_bool(True)


v3 = bool_()
v3.write_bool(True)

def update():
    ImGui.NewFrame()

    if v3.read_bool():
        ImGui.ShowDemoWindow(v3.addr())
    print(v3.read_bool())

    ImGui.Begin("Hello, world!")
    ImGui.Text("This is some useful text.")
    cyan = vec4(1, 1, 0, 1)
    ImGui.TextColored(cyan, f"count: {count}")
    if ImGui.Button("Click me"):
        global count
        count += 1

    ImGui.SliderFloat("slider1", v1.addr(), 0.0, 1.0)
    ImGui.SliderFloat("slider2", v2.addr(), 0.0, 1.0)

    ImGui.SmallButton("small button")

    ImGui.Checkbox("checkbox", v.addr())
    ImGui.End()

    ImGui.Render()