class DelStu:
    def __init__(self, client):
        self.client = client

    def confirm_del(self, name):
        confirm = input('Confirm to delete (y/n):')
        if confirm == 'y':
            self.client.send_command('delete', {'name': name})
            status = self.client.wait_response()
            if status is False:
                print("    Del fail".format(name))
            else:
                print("    Del success".format(name))

    def check_name_exit(self):
        name = input("  Please input a student's name or exit: ")
        if name == 'exit':
            return
        self.client.send_command('query', {'name': name})
        status = self.client.wait_response()
        if not status:
            print("    The name {} is not found".format(name))
            return
        self.confirm_del(name)

    def execute(self):
        self.check_name_exit()
