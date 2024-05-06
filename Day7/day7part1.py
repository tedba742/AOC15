import re

class Operation:
    ERR = 0
    AND = 1
    OR = 2
    NOT = 3
    LSHIFT = 4
    RSHIFT = 5
    STORE = 6

def is_number(s):
    return s.isdigit()

def string_to_operation(s):
    if s == "AND":
        return Operation.AND
    elif s == "OR":
        return Operation.OR
    elif s == "LSHIFT":
        return Operation.LSHIFT
    elif s == "RSHIFT":
        return Operation.RSHIFT
    elif s == "NOT":
        return Operation.NOT
    else:
        return Operation.ERR

class Gate:
    def __init__(self, op=Operation.ERR, lhs="", rhs="", memoized=False, val=0):
        self.op = op
        self.lhs = lhs
        self.rhs = rhs
        self.memoized = memoized
        self.val = val

class LogicCircuit:
    def __init__(self):
        self.circuit = {}

    def evaluate(self, wire):
        if is_number(wire):
            return int(wire)
        else:
            return self.find_output(wire)

    def find_output(self, wire):
        if wire not in self.circuit:
            print(f"Unknown wire '{wire}'")
            return 0

        g = self.circuit[wire]
        if g.memoized:
            return g.val
        else:
            result = 0
            if g.op == Operation.STORE:
                result = self.evaluate(g.lhs)
            elif g.op == Operation.AND:
                result = self.evaluate(g.lhs) & self.evaluate(g.rhs)
            elif g.op == Operation.OR:
                result = self.evaluate(g.lhs) | self.evaluate(g.rhs)
            elif g.op == Operation.LSHIFT:
                result = self.evaluate(g.lhs) << self.evaluate(g.rhs)
            elif g.op == Operation.RSHIFT:
                result = self.evaluate(g.lhs) >> self.evaluate(g.rhs)
            elif g.op == Operation.NOT:
                result = ~self.evaluate(g.lhs)
            
            g.memoized = True
            g.val = result
            return result

    def dump(self):
        for wire, gate in self.circuit.items():
            print(f"{wire}: {self.find_output(wire)}")

    def reset(self):
        for gate in self.circuit.values():
            gate.memoized = False

    def size(self):
        return len(self.circuit)

    def add(self, wire, g):
        self.circuit[wire] = g

    def find_gate(self, wire):
        return self.circuit[wire]

def main():
    circuit = LogicCircuit()
    file_path = "input.txt"  # Update this with the path to your input file

    with open(file_path, "r") as file:
        assign_op = re.compile(r"(\w+) -> (\w+)")
        not_op = re.compile(r"NOT (\w+) -> (\w+)")
        binary_op = re.compile(r"(\w+) (AND|OR|LSHIFT|RSHIFT) (\w+) -> (\w+)")

        for command in file:
            command = command.strip()  # Remove leading/trailing whitespace
            if not command:
                continue  # Skip empty lines

            if match := re.match(assign_op, command):
                g = Gate(Operation.STORE, match.group(1))
                circuit.add(match.group(2), g)
            elif match := re.match(not_op, command):
                g = Gate(Operation.NOT, match.group(1))
                circuit.add(match.group(2), g)
            elif match := re.match(binary_op, command):
                op = string_to_operation(match.group(2))
                g = Gate(op, match.group(1), match.group(3))
                circuit.add(match.group(4), g)
            else:
                print("Unknown gate:", command)

    print("There are a total of", circuit.size(), "gates.")

    a = circuit.find_output("a")
    print("Initial value of a:", a)

    circuit.reset()
    b = Gate(Operation.STORE, str(a), memoized=True, val=a)
    circuit.add("b", b)

    a = circuit.find_output("a")
    print("New value of a:", a)

if __name__ == "__main__":
    main()
