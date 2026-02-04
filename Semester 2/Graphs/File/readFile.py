from Domain.graph import GraphException
from File.createFile import createTextFile

def readFromFile(filePath, graph, service):

        createTextFile(filePath)

        try:
            file = open(filePath, "rt")
            lines = file.readlines()
            firstLine = False
            for line in lines:
                line = line.strip('\n')
                if firstLine is False:
                    graphParameters = line.split(' ')
                    if int(graphParameters[0]) * int(graphParameters[0]) < int(graphParameters[1]):
                        raise GraphException("Invalid input!")
                    else:
                        service.initializeGraph(int(graphParameters[0]))
                        graph.initializeEdges(int(graphParameters[1]))
                        service.initializeVerticesIn()
                        service.initializeVerticesOut()
                        firstLine = True
                elif line == '':
                    continue
                else:
                    graphParameters = line.split(' ')
                    service.addVertexToInbounds(int(graphParameters[0]), int(graphParameters[1]))
                    service.addVertexToOutbounds(int(graphParameters[0]), int(graphParameters[1]))
                    service.addCost(int(graphParameters[0]), int(graphParameters[1]), int(graphParameters[2]))
        except Exception as e:
            pass
