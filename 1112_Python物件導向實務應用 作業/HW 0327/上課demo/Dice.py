import random

class Dice:
    def __init__(self, side_number=6):
        self.point = 1
        self.side_number = side_number

    def roll_dice(self):
        ponit = self.execute_roll()
        return ponit

    def execute_roll(self):
        self.point = random.randint(1, self.side_number)
        
        return self.point
