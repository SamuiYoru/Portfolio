def triangle_with_space():
    x = int(input("Please enter a value:"))
    for i in range(1,x+1):
        print("#",end ="")
        for j in range(1,i):
            print(" ",end="")
        print("#")


def quiz2_main():
    triangle_with_space()


