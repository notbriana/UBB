from File.createFile import createTextFile

def writeToFile2(filePath, graph, service):

    createTextFile(filePath)

    try:
        file = open(filePath, "wt")
        vertexEdges = str(len(graph.getVertices())) + ' ' + str(graph.getEdges())
        file.write(vertexEdges)
        file.write('\n')
        for firstVertex in service.getOutbounds():
            outboundVertices = service.getOutboundVertices(firstVertex)
            inboundVertices = service.getInboundVertices(firstVertex)
            if len(outboundVertices) == 0 and len(inboundVertices) == 0:
                file.write(str(firstVertex))
                file.write('\n')
            else:
                for secondVertex in outboundVertices:
                    finalKey = str(firstVertex) + '-' + str(secondVertex)
                    parameters = str(firstVertex) + ' ' + str(secondVertex) + ' ' + str(service.getCost()[finalKey])
                    file.write(parameters)
                    file.write('\n')
        file.close()
    except Exception as e:
        print(e)