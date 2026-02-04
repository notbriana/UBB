def createTextFile(filePath):
    try:
        file = open(filePath, "x")
        file.close()
    except FileExistsError:
        pass