import quiz1,quiz2,quiz3,quiz4,quiz5

def main():
    print("1.Print double triangle")
    print("2.Print spacing triangle")
    print("3.Print diamond")
    print("4.Print grid")
    print("5.Guessing game")
    con = "y"
    while (con == "y"):
        n = int(input("Please select:"))
        if(n == 1):
            print("Quiz1:Print double triangle")
            quiz1.quiz1_main()
        elif(n == 2):
            print("Quiz2:Print spacing triangle")
            quiz2.quiz2_main()
        elif(n == 3):
            print("Quiz3:Print diamond")
            quiz3.quiz3_main()
        elif(n == 4):
            print("Quiz4:Print grid")
            quiz4.quiz4_main()
        elif(n == 5):
            print("Quiz5:Guessing game")
            quiz5.quiz5_main()
        else:
            continue

        con = input("Test again (y/n)?")
        if(con!="y"):
            break

main()