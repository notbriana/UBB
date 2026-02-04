import copy
from Domain.graph import GraphException
from collections import deque
import sys
from collections import defaultdict


class Service:

    def __init__(self, graph):
        self._graph = graph
        self._inbounds = {}
        self._outbounds = {}
        self._cost = {}

    def getInbounds(self):
        return self._inbounds

    def setInbounds(self, key, newValue):
        self._inbounds[key] = newValue

    def getOutbounds(self):
        return self._outbounds

    def setOutbounds(self, key, newValue):
        self._outbounds[key] = newValue

    def getCost(self):
        return self._cost

    def setCost(self, key, newValue):
        self._cost[key] = newValue

    def copyGraph(self):
        return copy.deepcopy(self._graph), copy.deepcopy(self)

    def initializeGraph(self, numberOfVertices):
        self._inbounds.clear()
        self._outbounds.clear()
        self._cost.clear()
        self._graph.initializeVertices(numberOfVertices)
        self.initializeCosts()
        self.initializeVerticesIn()
        self.initializeVerticesOut()

    def initializeCosts(self):
        for i in range(0, self._graph.getEdges()):
            self._cost[i] = []

    def initializeVerticesIn(self):
        for i in range(len(self._graph.getVertices())):
            self._inbounds[i] = []

    def initializeVerticesOut(self):
        for i in range(len(self._graph.getVertices())):
            self._outbounds[i] = []

    def getInboundVertices(self, vertex):
        return self._inbounds[vertex]

    def getOutboundVertices(self, vertex):
        return self._outbounds[vertex]

    def addVertex(self, newVertex):
        self._graph.addVertex(newVertex)
        self._outbounds[newVertex] = []
        self._inbounds[newVertex] = []

    def removeVertex(self, vertex):
        self._graph.removeVertex(vertex)
        for existentVertex in self._inbounds:
            if vertex in self._inbounds[existentVertex]:
                self._inbounds[existentVertex].remove(vertex)
            elif vertex in self._outbounds[existentVertex]:
                self._outbounds[existentVertex].remove(vertex)

        del self._inbounds[vertex]
        del self._outbounds[vertex]

    def addEdge(self, firstVertex, secondVertex, cost):
        if self._graph.checkExistence(firstVertex) and self._graph.checkExistence(secondVertex):
            if secondVertex in self._outbounds[firstVertex]:
                raise GraphException("The edge already exists.")
            else:
                self._inbounds[secondVertex].append(firstVertex)
                self._outbounds[firstVertex].append(secondVertex)
                finalKey = str(firstVertex) + '-' + str(secondVertex)
                self._cost[finalKey] = cost
                self._graph.setEdges(self._graph.getEdges() + 1)
        else:
            raise GraphException("One of the two vertices doesn't exist!")

    def removeEdge(self, firstVertex, secondVertex):
        if self._graph.checkExistence(firstVertex) and self._graph.checkExistence(secondVertex):
            if secondVertex not in self._outbounds[firstVertex]:
                raise GraphException("The edge doesn't exist.")
            else:
                self._inbounds[secondVertex].remove(firstVertex)
                self._outbounds[firstVertex].remove(secondVertex)
                finalKey = str(firstVertex) + '-' + str(secondVertex)
                del self._cost[finalKey]
                self._graph.setEdges(self._graph.getEdges() - 1)

    def addCost(self, firstEdge, secondEdge, cost):
        finalKey = str(firstEdge) + '-' + str(secondEdge)
        self._cost[finalKey] = cost

    def addVertexToInbounds(self, firstVertex, secondVertex):
        self._inbounds[secondVertex].append(firstVertex)

    def addVertexToOutbounds(self, firstVertex, secondVertex):
        self._outbounds[firstVertex].append(secondVertex)

    def parseOutboundVertices(self, vertex):
        vertices = self.getOutboundVertices(vertex)
        for vertex in vertices:
            yield vertex

    def parseInboundVertices(self, vertex):
        vertices = self.getInboundVertices(vertex)
        for vertex in vertices:
            yield vertex

    def getInDegree(self, vertex):
        return len(self.getInboundVertices(vertex))

    def getOutDegree(self, vertex):
        return len(self.getOutboundVertices(vertex))

    def getCost(self):
        for key in self._cost.keys():
            yield key

    def checkExistenceEdge(self, firstEdge, secondEdge):
        outboundVertices = self.getOutboundVertices(firstEdge)
        for vertex in outboundVertices:
            if vertex == secondEdge:
                return True
        return False

    def modifyCost(self, key, newCost):
        self._cost[key] = newCost

    def modifyCostEdge(self, firstVertex, secondVertex, newCost):
        finalKey = str(firstVertex) + '-' + str(secondVertex)
        keys = self.getCost()
        for key in keys:
            if key == finalKey:
                self.modifyCost(key, newCost)

    def getCostPerEdge(self, firstVertex, secondVertex):
        finalKey = str(firstVertex) + '-' + str(secondVertex)
        return self._cost[finalKey]

    def getEdges(self):
        edges = []
        for vertex in self._graph.getVertices():
            for outbound in self._outbounds[vertex]:
                cost = self._cost[f"{vertex}-{outbound}"]
                edges.append((vertex, outbound, cost))
        return edges

    def bfsShortestPath(self, startVertex, endVertex):
        if startVertex not in self._graph.getVertices() or endVertex not in self._graph.getVertices():
            raise GraphException("One of the two vertices doesn't exist!")

        queue = deque([startVertex])
        visited = set()
        parent = {startVertex: None}

        while queue:
            current = queue.popleft()
            if current == endVertex:
                path = []
                while current is not None:
                    path.append(current)
                    current = parent[current]
                path.reverse()
                return path, len(path) - 1
            visited.add(current)
            for neighbor in self.getOutboundVertices(current):
                if neighbor not in visited and neighbor not in parent:
                    queue.append(neighbor)
                    parent[neighbor] = current
        return None, -1

    def findStronglyConnectedComponents(self):
        def dfs(vertex, visited, graph, stack=None, component=None):
            visited.add(vertex)
            if component is not None:
                component.append(vertex)
            for neighbor in graph[vertex]:
                if neighbor not in visited:
                    dfs(neighbor, visited, graph, stack, component)
            if stack is not None:
                stack.append(vertex)

        def transposeGraph():
            transposed = {v: [] for v in self._graph.getVertices()}
            for vertex in self._graph.getVertices():
                for neighbor in self.getOutboundVertices(vertex):
                    transposed[neighbor].append(vertex)
            return transposed

        stack = []
        visited = set()
        originalGraph = {v: self.getOutboundVertices(v) for v in self._graph.getVertices()}
        for vertex in self._graph.getVertices():
            if vertex not in visited:
                dfs(vertex, visited, originalGraph, stack=stack)

        transposedGraph = transposeGraph()

        visited.clear()
        sccs = []
        while stack:
            vertex = stack.pop()
            if vertex not in visited:
                component = []
                dfs(vertex, visited, transposedGraph, component=component)
                sccs.append(component)

        return sccs

    def lowestCostWalk(self, startVertex, endVertex):
        n = len(self._graph.getVertices())
        INF = float('inf')

        d = [[INF] * (n + 1) for _ in range(n)]
        parent = [[-1] * (n + 1) for _ in range(n)]

        d[startVertex][0] = 0

        for k in range(1, n + 1):
            for u in self._graph.getVertices():
                d[u][k] = d[u][k - 1]
                parent[u][k] = parent[u][k - 1]
            for u in self._graph.getVertices():
                for v in self.getOutboundVertices(u):
                    cost_key = f"{u}-{v}"
                    cost = self._cost[cost_key]
                    if d[u][k - 1] + cost < d[v][k]:
                        d[v][k] = d[u][k - 1] + cost
                        parent[v][k] = u

        for u in self._graph.getVertices():
            for v in self.getOutboundVertices(u):
                cost_key = f"{u}-{v}"
                cost = self._cost[cost_key]
                if d[u][n - 1] + cost < d[v][n]:
                    print("Negative cost cycle detected accessible from the starting vertex.")
                    return None, None

        min_cost = INF
        best_k = -1
        for k in range(n + 1):
            if d[endVertex][k] < min_cost:
                min_cost = d[endVertex][k]
                best_k = k

        if min_cost == INF:
            return None, None

        path = []
        current = endVertex
        k = best_k
        while current != -1 and k >= 0:
            path.append(current)
            prev = parent[current][k]
            current = prev
            k -= 1

        path.reverse()
        return min_cost, path

    def countMinCostWalks(self, startVertex, endVertex):
        n = len(self._graph.getVertices())
        INF = float('inf')
        dist = [INF] * n

        dist[startVertex] = 0

        for _ in range(n - 1):
            for u in self._graph.getVertices():
                for v in self.getOutboundVertices(u):
                    cost = self._cost[f"{u}-{v}"]
                    if dist[u] + cost < dist[v]:
                        dist[v] = dist[u] + cost

        for u in self._graph.getVertices():
            for v in self.getOutboundVertices(u):
                cost = self._cost[f"{u}-{v}"]
                if dist[u] + cost < dist[v]:
                    print("Negative cost cycle detected.")
                    return None

        arr = [0] * n
        arr[startVertex] = 1

        order = sorted(self._graph.getVertices(), key=lambda x: dist[x])

        for u in order:
            for v in self.getOutboundVertices(u):
                cost = self._cost[f"{u}-{v}"]
                if dist[u] + cost == dist[v]:
                    arr[v] += arr[u]

        return arr[endVertex]

    def minimumSpanningTreeKruskal(self):
        parent = {}
        rank = {}

        def find(vertex):
            if parent[vertex] != vertex:
                parent[vertex] = find(parent[vertex])
            return parent[vertex]

        def union(u, v):
            root_u = find(u)
            root_v = find(v)
            if root_u != root_v:
                if rank[root_u] < rank[root_v]:
                    parent[root_u] = root_v
                elif rank[root_u] > rank[root_v]:
                    parent[root_v] = root_u
                else:
                    parent[root_v] = root_u
                    rank[root_u] += 1

        for vertex in self._graph.getVertices():
            parent[vertex] = vertex
            rank[vertex] = 0

        edges = self.getEdges()
        sorted_edges = sorted(edges, key=lambda edge: edge[2])

        mst = []
        total_cost = 0

        for u, v, cost in sorted_edges:
            if find(u) != find(v):
                union(u, v)
                mst.append((u, v, cost))
                total_cost += cost

        return mst, total_cost

    def findMinimumCostPath(self, startVertex, endVertex):

        if startVertex not in self._graph.getVertices() or endVertex not in self._graph.getVertices():
            raise GraphException("One or both vertices don't exist!")

        if startVertex == endVertex:
            return 0, [startVertex], False

        vertices = self._graph.getVertices()
        n = len(vertices)
        INF = float('inf')

        dist = {v: INF for v in vertices}
        pred = {v: None for v in vertices}

        dist[startVertex] = 0

        for i in range(n - 1):
            updated = False
            for u in vertices:
                if dist[u] != INF:
                    for v in self.getOutboundVertices(u):
                        cost = self.getCostPerEdge(u, v)
                        if dist[u] + cost < dist[v]:
                            dist[v] = dist[u] + cost
                            pred[v] = u
                            updated = True

            if not updated:
                break

        negative_cycle_vertices = set()
        for u in vertices:
            if dist[u] != INF:
                for v in self.getOutboundVertices(u):
                    cost = self.getCostPerEdge(u, v)
                    if dist[u] + cost < dist[v]:
                        negative_cycle_vertices.add(v)

        if negative_cycle_vertices:
            affected_by_negative_cycle = set(negative_cycle_vertices)
            changed = True
            while changed:
                changed = False
                new_affected = set()
                for u in affected_by_negative_cycle:
                    for v in self.getOutboundVertices(u):
                        if v not in affected_by_negative_cycle:
                            new_affected.add(v)
                            changed = True
                affected_by_negative_cycle.update(new_affected)

            if endVertex in affected_by_negative_cycle:
                return None, None, True

        if dist[endVertex] == INF:
            return None, None, False

        path = []
        current = endVertex
        while current is not None:
            path.append(current)
            current = pred[current]

        path.reverse()

        if path[0] != startVertex:
            return None, None, False

        return dist[endVertex], path, False


