def diamond(x):
    for i in range(1,x+2,2):
        for z in range(1,(x//2-i//2+1),1):
            print("  ",end = "")
        for j in range(1,i+1,1):
            #print(j,end = "")
            print("*",end = "")
            if(j!=x):
                print(" ",end = "")
        print("\n",end = "")
    for i2 in range(x-2,0,-2):
        for z2 in range((x//2-i2//2+1),1,-1):
            print("  ",end = "")
        for j2 in range(i2+1,1,-1):
            print("*",end = "")
            if(j2!=x):
                print(" ",end = "")
        print("\n",end = "")
        

def Q3_check():
    while True:
        x = int(input("Please enter a value:"))
        if(x%2!=0):
            diamond(x)
            break
        else:
            continue

def quiz3_main():
    Q3_check()
