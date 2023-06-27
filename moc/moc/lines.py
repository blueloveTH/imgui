class Lines:
    def __init__(self):
        self.lines = []
        self.depth = 0
    def add(self, line):
        self.lines.append(' '*4*self.depth + line)
    def __str__(self):
        return '\n'.join(self.lines)
    def begin(self):
        self.depth += 1
    def end(self):
        self.depth -= 1
    def __len__(self):
        return len(self.lines)