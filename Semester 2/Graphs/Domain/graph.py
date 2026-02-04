

class GraphException(Exception):

        def __init__(self, message):
            self._message = message

        def __str__(self):
            return str(self._message)

class Graph:

    def __init__(self):
        self._vertices = []
        self._edges = 0

    def initializeVertices(self, numberOfVertices):
        if(len(self._vertices)) != 0:
            self._vertices.clear()

        for i in range(0, numberOfVertices):
            self._vertices.append(i)


    def initializeEdges(self, numberOfEdges):
        self._edges = numberOfEdges


    def addVertex(self, newVertex):
        if newVertex not in self._vertices:
            self._vertices.append(newVertex)
        else:
            raise GraphException("The given vertex already exists.")


    def removeVertex(self, vertex):
        if self.checkExistence(vertex):
            self._vertices.remove(vertex)
        else:
            raise GraphException("The given vertex does not exist.")


    def getEdges(self):
        return self._edges

    def getVertices(self):
        return self._vertices

    def setEdges(self, newEdges):
        self._edges = newEdges

    def parseVertices(self):
        for vertex in self._vertices:
            yield vertex

    def checkExistence(self, vertex):
        vertices = self.parseVertices()
        for v in vertices:
            if v == vertex:
                return True
        return False

    def __len__(self):
        return len(self._vertices)

    def findVertex(self, vertex):
        for vertex in self._vertices:
                return True
        return False


