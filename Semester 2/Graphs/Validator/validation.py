from Domain.graph import GraphException

class Validation:

    def __init__(self, graph, service):
        self._graph = graph
        self._service = service

    def verticesExist(self, firstVertex, secondVertex):
        if self._graph.findVertex(firstVertex) is False:
            raise GraphException("The first given vertex doesn't exist!")
        if self._graph.findVertex(secondVertex) is False:
            raise GraphException("The second vertex doesn't exist!")


