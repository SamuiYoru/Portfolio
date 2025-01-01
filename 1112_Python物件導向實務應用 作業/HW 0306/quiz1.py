def triangle ():
    x = int(input("Please enter a value:"))
    for i in range(x,0,-1):
        for j in range(1,i+1):
            print("*",end='')
            if (j != i+1):
                print(" ",end='')
        print("\n",end='')
    for i in range(2,x+1,1):
        for j in range(1,i+1):
            print("*",end='')
            if (j != i+1):
                print(" ",end='')
        print("\n",end='')


def quiz1_main():
    triangle()


