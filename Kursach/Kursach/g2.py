from collections import deque
class KruskalAlgorithm:
    def __init__(self, filename):
        self.graph, self.vertices = self.read_matrix(filename)
        self.edges = self.get_edges()
        self.adjacency_list = self.matrix_to_adjacency_list()
        self.parent = {}
        self.rank = {}


    def read_matrix(self, filename):
        graph = []
        vertices = set()
        with open(filename, 'r') as file:
            lines = file.readlines()
            edges = lines[0].split()
            for line in lines[1:]:
                graph.append(list(map(int, line.split())))
        for edge in edges:
            vertices.update(edge)
        return graph, sorted(list(vertices))

    def get_edges(self):
        edges = []
        for i in range(len(self.graph)):
            for j in range(i + 1, len(self.graph)):
                if self.graph[i][j] != 0:
                    edges.append((i, j, self.graph[i][j]))
        edges = self.insertion_sort(edges)
        return edges

    def insertion_sort(self, edges):
        for i in range(1, len(edges)):
            key = edges[i]
            j = i - 1
            while j >= 0 and key[2] < edges[j][2]:
                edges[j + 1] = edges[j]
                j -= 1
            edges[j + 1] = key
        return edges

    def find(self, vertex):
        if self.parent[vertex] != vertex:
            self.parent[vertex] = self.find(self.parent[vertex])
        return self.parent[vertex]

    def union(self, root1, root2):
        if self.rank[root1] > self.rank[root2]:
            self.parent[root2] = root1
        elif self.rank[root1] < self.rank[root2]:
            self.parent[root1] = root2
        else:
            self.parent[root1] = root2
            self.rank[root2] += 1

    def kruskal(self):
        result = []
        for vertex in range(len(self.graph)):
            self.parent[vertex] = vertex
            self.rank[vertex] = 0
        for edge in self.edges:
            root1 = self.find(edge[0])
            root2 = self.find(edge[1])
            if root1 != root2:
                result.append(edge)
                self.union(root1, root2)
        return result

    def matrix_to_adjacency_list(self):
        adjacency_list = {vertex: [] for vertex in range(len(self.graph))}
        for i in range(len(self.graph)):
            for j in range(len(self.graph[i])):
                if self.graph[i][j] != 0:
                    adjacency_list[i].append((j, self.graph[i][j]))
        return adjacency_list

    def graph_to_incidence_matrix(self):
        num_vertices = len(self.graph)
        num_edges = len(self.edges)
        incidence_matrix = [[0] * num_edges for _ in range(num_vertices)]

        for idx, edge in enumerate(self.edges):
            incidence_matrix[edge[0]][idx] = 1
            incidence_matrix[edge[1]][idx] = 1

        print()
        print("Incidence Matrix:")
        for row in incidence_matrix:
            print(row)

    def printMST(self, min_spanning_tree):
        total_weight = 0
        for edge in min_spanning_tree:
            print(self.vertices[edge[0]],self.vertices[edge[1]])
            total_weight += edge[2]
        print(total_weight)

    def BFS(self, start_vertex):
        visited = set()
        queue = deque([start_vertex])
        result = []
        print()
        print("Adjacency List:")
        for vertex, neighbors in self.adjacency_list.items():
            print(f"{self.vertices[vertex]}: {[(self.vertices[neighbor], weight) for neighbor, weight in neighbors]}")
        while queue:
            current_vertex = queue.popleft()
            if current_vertex not in visited:
                result.append(self.vertices[current_vertex])  # Append the character representation
                visited.add(current_vertex)
                queue.extend(neighbor for neighbor, _ in self.adjacency_list[current_vertex])
        print()
        print("BFS", result)

    def DFS(self, start_vertex):
        visited = set()
        stack = [start_vertex]
        result = []

        while stack:
            current_vertex = stack.pop()
            if current_vertex not in visited:
                result.append(self.vertices[current_vertex])  # Append the character representation
                visited.add(current_vertex)
                stack.extend(neighbor for neighbor, _ in self.adjacency_list[current_vertex])

        print()
        print("DFS", result)
        return result