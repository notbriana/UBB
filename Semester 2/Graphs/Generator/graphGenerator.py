import sys
from random import randint
from Domain.graph import GraphException


def generateGraph(graph, directedGraph, numberOfVertices, numberOfEdges):
    if numberOfVertices * (numberOfVertices - 1) < numberOfEdges:
        raise GraphException("Invalid input: too many edges for the number of vertices.")

    graph.setEdges(0)
    directedGraph.initializeGraph(numberOfVertices)

    while numberOfEdges > 0:
        firstVertex = randint(0, numberOfVertices - 1)
        secondVertex = randint(0, numberOfVertices - 1)
        if firstVertex != secondVertex:
            try:
                cost = randint(-sys.maxsize, sys.maxsize)
                directedGraph.addEdge(firstVertex, secondVertex, cost)
                numberOfEdges -= 1
            except GraphException:
                continue