from clang.cindex import *
from .lines import Lines

def gen_enums(tu):
    enums = []
    for c in tu.cursor.get_children():
        if c.kind == CursorKind.ENUM_DECL:
            enums.append(c)

    lines = Lines()
    for e in enums:
        children = list(e.get_children())
        if len(children) == 0:
            continue
        lines.add(f'# {e.spelling}')
        for c in children:
            if c.kind == CursorKind.ENUM_CONSTANT_DECL:
                lines.add(f'{c.spelling} = {c.enum_value}')
        lines.add('')
    return str(lines)