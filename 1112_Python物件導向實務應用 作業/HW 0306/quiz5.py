

def guessing(guess_time,answer):
    upper_bound = 100
    lower_bound = 0
    flag = 1
    print("You have {} times to guess.".format(guess_time))
    for i in range(1,guess_time+1,1):
        guess = int(input("{}: Please guess a number from {} to {} :".format(i,lower_bound,upper_bound)))
        if(0<=guess<answer):
            lower_bound = guess
        elif(answer<guess<=100):
            upper_bound = guess

        if(guess==answer):
            print("You passed")
            flag =0
            break
    if (flag ==1):
        print("Achieve time limitted")

def quiz5_main():
    guess_time=5
    answer = 66
    guessing(guess_time,answer)
