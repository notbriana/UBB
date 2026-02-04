# service.py
class InterstellarService:
    def __init__(self, game):
        self.game = game

    def process_command(self, command):
        """
        Process a command
        :param command:
        :return:
        """
        command_parts = command.split(" ")
        if not command_parts:
            return "Invalid command"

        cmd = command_parts[0].lower()

        if cmd == "warp" and len(command_parts) == 2:
            target = command_parts[1]
            try:
                self.game.warp(target)
            except ValueError as e:
                return str(e)

        elif cmd == "fire" and len(command_parts) == 2:
            target = command_parts[1]
            try:
                self.game.fire(target)
            except ValueError as e:
                return str(e)

        elif cmd == "cheat":
            self.game.cheat()

        else:
            return "Invalid command. Valid commands are: warp <coordinate>, fire <coordinate>, cheat."

        return "Command executed successfully"