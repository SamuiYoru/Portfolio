class CalAvgPoints:
    def __init__(self, count, dice1, dice2):
        self.count = count
        self.dice1 = dice1
        self.dice2 = dice2

    def execute(self):
        total = 0

        for _ in range(self.count):
            total += (self.dice1.roll_dice() + self.dice2.roll_dice())
 
        return total/self.count
