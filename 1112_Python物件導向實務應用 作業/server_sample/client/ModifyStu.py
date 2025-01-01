class ModifyStu:
    def __init__(self, client):
        self.client = client

    def check_name_exit(self):
        name = input("  Please input a student's name or exit: ")
        if name == 'exit':
            return
        self.client.send_command('query', {'name': name})
        status = self.client.wait_response()
        if not status:
            print("    The name {} is not found".format(name))
            return

        self.student = {'name': name, 'scores': status['scores']}
        self.get_scores()

    def set_student(self, subject, score):
        self.student['scores'][subject] = score
        self.client.send_command('modify', self.student)
        status = self.client.wait_response()
        if status is False:
            print("    Modify {} fail".format(self.student['name']))
        else:
            print("    Modify [{}, {}, {}] success".format(self.student['name'], subject, score))

    def get_score(self, str):
        while True:
            try:
                score = float(input(str))
                if score < 0:
                    raise Exception
            except ValueError as e:
                print("    Wrong format with reason {}".format(e))
                continue
            except:
                print("    Something wrong!")
                return -1
            else:
                return score

    def get_scores(self):
        print("  current subjects are ", end="")
        for key in self.student['scores'].keys():
            print(key, end=" ")
        subject = input("\n\n  Please input a subject you want to change: ")
        try:
            if self.student['scores'].get(subject, False) is False:
                raise KeyError
        except KeyError:
            str = "  Add a new subject for {} please input {} score or < 0 for discarding the subject: ".format(self.student['name'], subject)
        except:
            print("    Something wrong!")
            return
        else:
            str = "  Please input {}'s new score of {}: ".format(subject, self.student['name'])
        finally:
            score = self.get_score(str)
            if score > 0:
                self.set_student(subject, score)

    def execute(self):
        self.check_name_exit()
