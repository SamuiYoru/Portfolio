from Dice import Dice
from CalAvgPoint import CalAvgPoints

def main():
    dice1 = Dice()
    dice2 = Dice()

    result = CalAvgPoints(10, dice1, dice2).execute()
    

main()
