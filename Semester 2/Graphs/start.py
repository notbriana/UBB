from Domain.graph import Graph
from Service.service import Service
from Console.console import Console
from Validator.validation import Validation

graph = Graph()
service = Service(graph)
validation = Validation(graph, service)
console = Console(service, graph, validation)
console.start()