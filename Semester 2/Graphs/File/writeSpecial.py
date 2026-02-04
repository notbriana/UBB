
def writeSpecial(filePath, graph, service):
    with open(filePath, 'w') as file:
        vertices = graph.getVertices()
        edges = service.getEdges()

        file.write(f"{len(vertices)}\n")

        for vertex in vertices:
            file.write(f"{vertex}\n")

        file.write(f"{len(edges)}\n")

        for edge in edges:
            firstVertex, secondVertex, cost = edge
            file.write(f"{firstVertex} {secondVertex} {cost}\n")