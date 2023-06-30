import ImGui
from linalg import *
from c import *


# with 'f' has bug when it is in functions (STORE_NAME does not work!!)
with open("ImGui.pyi", "w") as f:
    f.write('from c import void_p\n')
    f.write('from linalg import vec2, vec3, vec4\n')
    f.write('\n')
    # write functions
    for name, value in ImGui.__dict__.items():
        if hasattr(value, "__signature__"):
            f.write(f'def {value.__signature__}:\n')
            doc = value.__doc__
            if doc:
                f.write(f'    """{doc}"""\n')
            else:
                f.write(f'    pass\n')
            f.write("\n")
    f.write("\n")
    # first write enums
    for name, value in ImGui.__dict__.items():
        if name.startswith("ImGui") and type(value) is int:
            f.write(f"{name} = {value}\n")


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