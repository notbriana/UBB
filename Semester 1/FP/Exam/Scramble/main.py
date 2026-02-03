from UI import UI

if __name__ == "__main__":
    from service import Service
    from repository import Repository

    repository = Repository()
    service = Service()
    ui = UI(service, repository)
    ui.main()