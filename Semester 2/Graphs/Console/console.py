
from Domain.graph import GraphException, Graph
from File.writeSpecial import writeSpecial
from Service.service import Service
from File.readFile import readFromFile
from File.writeFile2 import writeToFile2
from Generator.graphGenerator import generateGraph

class Console:

    def __init__(self, service, graph, validation):
        self._service = service
        self._graph = graph
        self._validation = validation
        self._filePath = None

    def displayNumberOfVertices(self):
        print("The number of vertices is: ", len(self._graph.getVertices()))

    def displayTheVertices(self):
        if len(self._graph.getVertices()) == 0:
            print("There's no graph!")
        else:
            print("The vertices are: \n")
            vertices = self._graph.parseVertices()
            for vertex in vertices:
                print(vertex, "\n")

    def getInDegree(self):
        vertex = int(input("Type in the vertex: "))
        if self._graph.checkExistence(vertex):
            print("\nThe in degree of the vertex is: ", self._service.getInDegree(vertex))
        else:
            print("The given vertex doesn't exist!")

    def getOutDegree(self):
        vertex = int(input("Type in the vertex: "))
        if self._graph.checkExistence(vertex):
            print("\nThe out degree of the vertex is: ", self._service.getOutDegree(vertex))
        else:
            print("The given vertex doesn't exist!")

    def displayInboundVertices(self):
        vertex = int(input("Type in the vertex: "))
        if len(self._service.getInbounds()) == 0:
            print("There's no graph!")
        elif self._graph.checkExistence(vertex):
            print("The inbound vertices are: \n")
            vertices = self._service.getInboundVertices(vertex)
            for vertex in vertices:
                print(vertex, "\n")
        else:
            print("The given vertex doesn't exist!")

    def displayOutboundVertices(self):
        vertex = int(input("Type in the vertex: "))
        if len(self._service.getOutbounds()) == 0:
            print("There's no graph!")
        elif self._graph.checkExistence(vertex):
            print("The outbound vertices are: \n")
            vertices = self._service.getOutboundVertices(vertex)
            for vertex in vertices:
                print(vertex, "\n")
        else:
            print("The given vertex doesn't exist!")

    def edgeBetweenVertices(self):
        firstVertex = int(input("Type in the first vertex: "))
        secondVertex = int(input("\nType in the second vertex: "))
        if firstVertex == secondVertex:
            raise GraphException("Invalid input!")
        self._validation.verticesExist(firstVertex, secondVertex)
        if self._service.checkExistenceEdge(firstVertex, secondVertex):
            print("\nThere exists an edge between the two vertices!")
        else:
            print("\nThere doesn't exist an edge between the two vertices!")

    def getCost(self):
        firstVertex = int(input("Type in the first vertex: "))
        secondVertex = int(input("\nType in the second vertex: "))
        if self._graph.checkExistence(firstVertex) and self._graph.checkExistence(secondVertex):
            if self._service.checkExistenceEdge(firstVertex, secondVertex):
                print("\nThe cost of the edge is: ", self._service.getCostPerEdge(firstVertex, secondVertex))
            else:
                print("\nThere doesn't exist an edge between the two vertices!")
        else:
            print("\nOne of the two vertices doesn't exist!")

    def modifyCostEdge(self):
        if len(self._graph.getVertices()) == 0:
            print("There's no graph!")
        else:
            firstVertex = int(input("Type in the first vertex: "))
            secondVertex = int(input("\nType in the second vertex: "))
            if firstVertex == secondVertex:
                raise GraphException("Invalid input!")
            self._validation.verticesExist(firstVertex, secondVertex)
            if self._service.checkExistenceEdge(firstVertex, secondVertex) is False:
                print("\nThere doesn't exist an edge between the two vertices!")
            else:
                cost = int(input("\nType in the new cost: "))
                self._service.modifyCostEdge(firstVertex, secondVertex, cost)
                print("\nThe cost has been changed successfully!")

    def addVertex(self):
        newVertex = int(input("Type in the new vertex: "))
        self._service.addVertex(newVertex)
        print("\nThe vertex has been added successfully!")

    def removeVertex(self):
        vertex = int(input("Type in the vertex you would like to remove: "))
        self._service.removeVertex(vertex)
        print("\nThe vertex has been removed successfully!")

    def addEdge(self):
        firstVertex = int(input("Type in the first vertex: "))
        secondVertex = int(input("\nType in the second vertex: "))
        if firstVertex == secondVertex:
            raise GraphException("Invalid input!")
        self._validation.verticesExist(firstVertex, secondVertex)
        if self._service.checkExistenceEdge(firstVertex, secondVertex):
            print("\nThe edge already exists!")
        else:
            cost = int(input("\nType in the cost: "))
            self._service.addEdge(firstVertex, secondVertex, cost)
            print("\nThe edge has been added successfully!")

    def removeEdge(self):
        firstVertex = int(input("Type in the first vertex: "))
        secondVertex = int(input("\nType in the second vertex: "))
        if firstVertex == secondVertex:
            raise GraphException("Invalid input!")
        self._validation.verticesExist(firstVertex, secondVertex)
        if self._service.checkExistenceEdge(firstVertex, secondVertex) is False:
            print("The edge doesn't exist!")
        else:
            self._service.removeEdge(firstVertex, secondVertex)
            print("The edge has been removed successfully!")

    def copyGraph(self):
        self._service.copyGraph()
        writeSpecial(self._filePath, self._graph, self._service)
        print("The graph has been copied successfully!")

    def readGraph(self):
        filePath = input("Type in the name of the file: ")
        readFromFile(filePath, self._graph, self._service)
        print("The graph has been read successfully!")

    def displayGraphOnScreen(self):
        self.readGraph()

        vertices = self._graph.getVertices()
        if not vertices:
            print("The graph is empty!")
            return

        print("Vertices:")
        for vertex in vertices:
            print(vertex)

        print("\nEdges:")
        for vertex in vertices:
            outbounds = self._service.getOutboundVertices(vertex)
            for outbound in outbounds:
                cost = self._service.getCostPerEdge(vertex, outbound)
                print(f"{vertex} -> {outbound} with cost {cost}")

    def saveModifiedGraph(self, filePath=None):
        if filePath:
            self._filePath = filePath
        writeSpecial(self._filePath, self._graph, self._service)
        print("The modified graph has been saved successfully!")

    def generateGraph(self):
        numberOfVertices = int(input("Type in the number of vertices: "))
        numberOfEdges = int(input("Type in the number of edges: "))
        filePath = input("Type in the name of the file to save the graph: ")
        generateGraph(self._graph, self._service, numberOfVertices, numberOfEdges)
        writeToFile2(filePath, self._graph, self._service)
        print("The graph has been generated and saved successfully!")

    def find_strongly_connected_components(self):
        try:
            sccs = self._service.findStronglyConnectedComponents()
            print("Strongly Connected Components: ")
            for component in sccs:
                print(component, "\n")
        except Exception as e:
            print(f"Error: {e}")

    def getLowestCost(self):
        startVertex = int(input("Type in the starting vertex: "))
        endVertex = int(input("Type in the ending vertex: "))
        try:
            cost,path = self._service.lowestCostWalk(startVertex, endVertex)
            if path:
                print(f"The lowest cost from {startVertex} to {endVertex} is: {cost} and the path is: {path}")
            else:
                print(f"No path exists between {startVertex} and {endVertex}.")
        except Exception as e:
            print(f"Error: {e}")


    def getCountMinCostWalks(self):
        startVertex = int(input("Type in the starting vertex: "))
        endVertex = int(input("Type in the ending vertex: "))
        try:
            count = self._service.countMinCostWalks(startVertex, endVertex)
            if count:
                print(f"The number of walks with minimum cost from {startVertex} to {endVertex} is: {count}")
            else:
                print(f"No path exists between {startVertex} and {endVertex}.")
        except Exception as e:
            print(f"Error: {e}")

    def Menu(self):
        print("1. Display the number of vertices.")
        print("2. Display the vertices.")
        print("3. Display the in degree of a vertex.")
        print("4. Display the out degree of a vertex.")
        print("5. Display the inbound vertices of a vertex.")
        print("6. Display the outbound vertices of a vertex.")
        print("7. Check if there's an edge between two vertices.")
        print("8. Display the cost of an edge.")
        print("9. Modify the cost of an edge.")
        print("10. Add a vertex.")
        print("11. Remove a vertex.")
        print("12. Add an edge.")
        print("13. Remove an edge.")
        print("14. Copy the graph.")
        print("15. Read the graph from a file.")
        print("16. Find strongly connected components.")
        print("17. Display the graph on the screen.")
        print("18. Find the shortest path between two vertices.")
        print("19. Get lowest cost.")
        print("20. Display the minimum spanning tree.")
        print("21. Min cost walks count.")
        print("22. Find minimum cost path between two vertices.")
        print("23. Exit.")

    def findShortestPath(self):
        startVertex = int(input("Type in the starting vertex: "))
        endVertex = int(input("Type in the ending vertex: "))
        try:
            path = self._service.bfsShortestPath(startVertex, endVertex)
            if path:
                print(f"The shortest path from {startVertex} to {endVertex} is: {path}")
            else:
                print(f"No path exists between {startVertex} and {endVertex}.")
        except Exception as e:
            print(f"Error: {e}")

    def displayMinimumSpanningTree(self):
        try:
            mst, total_cost = self._service.minimumSpanningTreeKruskal()
            print("Minimum Spanning Tree using Kruskal's algorithm:")
            for u, v, cost in mst:
                print(f"{u} - {v} with cost {cost}")
            print(f"Total cost of MST: {total_cost}")
        except Exception as e:
            print(f"Error computing MST: {e}")

    def findMinimumCostPath(self):
        try:
            startVertex = int(input("Type in the starting vertex: "))
            endVertex = int(input("Type in the ending vertex: "))

            if startVertex == endVertex:
                print(f"Start and end vertices are the same. Cost: 0, Path: [{startVertex}]")
                return

            cost, path, has_negative_cycle = self._service.findMinimumCostPath(startVertex, endVertex)

            if has_negative_cycle:
                print(
                    f"Warning: There is a negative cost cycle that affects the path from {startVertex} to {endVertex}.")
                print("The minimum cost is negative infinity (unbounded).")
            elif cost is None:
                print(f"No path exists from vertex {startVertex} to vertex {endVertex}.")
            else:
                print(f"Minimum cost path from {startVertex} to {endVertex}:")
                print(f"Cost: {cost}")
                print(f"Path: {' -> '.join(map(str, path))}")

                if len(path) > 1:
                    print("Edge costs:")
                    for i in range(len(path) - 1):
                        edge_cost = self._service.getCostPerEdge(path[i], path[i + 1])
                        print(f"  {path[i]} -> {path[i + 1]}: {edge_cost}")

        except ValueError:
            print("Invalid input! Please enter valid integers for vertices.")
        except GraphException as e:
            print(f"Graph error: {e}")
        except Exception as e:
            print(f"An error occurred: {e}")

    def start(self):
        done = False
        self._filePath = input("Type in the name of the file to save the modified graph: ")
        self.saveModifiedGraph(self._filePath)
        commands = {
            0: self.Menu,
            1: self.displayNumberOfVertices,
            2: self.displayTheVertices,
            3: self.getInDegree,
            4: self.getOutDegree,
            5: self.displayInboundVertices,
            6: self.displayOutboundVertices,
            7: self.edgeBetweenVertices,
            8: self.getCost,
            9: self.modifyCostEdge,
            10: self.addVertex,
            11: self.removeVertex,
            12: self.addEdge,
            13: self.removeEdge,
            14: self.copyGraph,
            15: self.readGraph,
            16: self.find_strongly_connected_components,
            17: self.displayGraphOnScreen,
            18: self.findShortestPath,
            19: self.getLowestCost,
            20: self.displayMinimumSpanningTree,
            21: self.getCountMinCostWalks,
            22: self.findMinimumCostPath

        }
        while not done:
            command = int(input("Type in the command: "))
            if command in commands:
                try:
                    commands[command]()
                    self.saveModifiedGraph()
                except ValueError as ve:
                    print(ve)
                except GraphException as ge:
                    print(ge)
            elif command == 23:
                print("Goodbye!")
                done = True
            else:
                print("Invalid command!")