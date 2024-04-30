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

    def nearest_neighbor_tsp(self, start):
        visited = set()
        current_vertex = start
        total_distance = 0

        while len(visited) < len(self.graph):
            next_vertex = None
            min_distance = float('inf')

            for neighbor, distance in self.get_neighbors(current_vertex).items():
                if neighbor not in visited and distance < min_distance:
                    next_vertex = neighbor
                    min_distance = distance

            if next_vertex is None:
                break

            total_distance += min_distance
            visited.add(current_vertex)
            current_vertex = next_vertex

        return total_distance

    def shortest_path_any_start(self):
        min_total_distance = float('inf')

        for start_vertex in self.graph.keys():
            total_distance = self.nearest_neighbor_tsp(start_vertex)
            min_total_distance = min(min_total_distance, total_distance)

        return min_total_distance

g = Graph()
filename = "input.txt"

with open(filename, "r") as file:
    for line in file:
        source_target, weight = line.split("=")
        source, target = source_target.strip().split(" to ")
        g.add_edge(source.strip(), target.strip(), int(weight.strip()))
        g.add_edge(target.strip(), source.strip(), int(weight.strip()))

shortest_total_distance = g.shortest_path_any_start()
print("Shortest total distance:", shortest_total_distance)
