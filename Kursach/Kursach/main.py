from g2 import KruskalAlgorithm

filename ='test.txt'

kruskal_algorithm = KruskalAlgorithm(filename)

kruskal_algorithm.printMST(kruskal_algorithm.kruskal())

kruskal_algorithm.matrix_to_adjacency_list()

kruskal_algorithm.graph_to_incidence_matrix()

kruskal_algorithm.BFS(0)

kruskal_algorithm.DFS(0)