class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, u, v, weight):
        if u not in self.graph:
            self.graph[u] = {}
        if v not in self.graph:
            self.graph[v] = {}
        self.graph[u][v] = weight
        self.graph[v][u] = weight

    def get_neighbors(self, vertex):
        return self.graph[vertex]

    def longest_path_dfs(self, start, visited, current_length):
        visited.add(start)
        max_length = current_length

        for neighbor, weight in self.get_neighbors(start).items():
            if neighbor not in visited:
                max_length = max(max_length, self.longest_path_dfs(neighbor, visited, current_length + weight))

        visited.remove(start)
        return max_length

    def longest_path(self):
        max_length = float('-inf')

        for vertex in self.graph.keys():
            visited = set()
            max_length = max(max_length, self.longest_path_dfs(vertex, visited, 0))

        return max_length

g = Graph()
filename = "input.txt"

with open(filename, "r") as file:
    for line in file:
        source_target, weight = line.split("=")
        source, target = source_target.strip().split(" to ")
        g.add_edge(source.strip(), target.strip(), int(weight.strip()))
        g.add_edge(target.strip(), source.strip(), int(weight.strip()))

longest_path_length = g.longest_path()
print("Longest path length:", longest_path_length)
