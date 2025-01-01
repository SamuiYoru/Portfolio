
def print_colomns(c,size):
    for i in range(1,c+1,1):
        print("+",end = "")
        for j in range(1,size+1,1):
            print("-",end = "")
    print("+")

def print_rows(c,size):
    for i in range(1,c+1,1):
        print("|",end = "")
        for j in range(1,size+1,1):
            print(" ",end = "")
    print("|")

def draw_box(r,c,size):
    for i in range(1,r+1,1):
        print_colomns(c,size)
        for j in range(1,size+1,1):
            print_rows(c,size)
    print_colomns(c,size)


def quiz4_main():
    r = int(input("Number of rows:"))
    c = int(input("Number of column:"))
    size = int(input("Grid size:"))
    draw_box(r,c,size)