# -*- coding: utf-8 -*-
"""程式設計初階班0728.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1qmSIYKoj1V4WiSl2C6bpfhDtSPbuw-tU

## 新興科技AI程式設計初階班 第三天 **函數**

## 4-1 函數 常見函數  
* Markdown 
* jupyter notebook

# 標題
---

### python常用的内建函數(一)
1. print(“格式字串"[,sep=' ',end='\n’]) 輸出， sep 間隔 符號， end 結束 符號  
2. input("提示字串") 鍵盤輸入，接收資料為字串 str
3. type() 傳回類別 名稱 str int float list tuple dict r ange…
4. bool() 傳回布林值 True False
5. dict() 傳 回 字典物件 使用 建立
"""

print(1,2,3)
print(1,2,3,sep=',')
print(1,2,3,sep='')
print(1,2,3,end=' ')
print(4,5,6)

a=input('提示字元：')
print(a,type(a))
b=int(a)
print(b,type(b))

a=10
b=20
c=a>b
print(c,type(c))
d=a==b
print(d,type(d))
#if (a=b):
#  print('a=b')

"""6. float () 傳 回 浮點 數 物件 12.34
7. int () 傳回整數物件 123
8. list () 傳回串列物件 使用 建立
9. range() 傳回範圍物件
10. tuple () 傳回元組物件 使用 或 建立， 取出個別元素
"""

a=range(10)
print(a,type(a))
print(a[2])
for i in a:
  print(i,end=',')

a=1256 
print(type(a)) 
b=a/100 
print(type(b)) 
c=int(b) 
print(type(c))
print(a,b,c)

a=(1,'a')
print(a,type(a))
c,d=a
print(c,type(c))
print(d,type(d))

"""### python常用内建函數(二)
1. sorted()排序的內建函數
2. str() 傳回字串物件
3. abs() 傳回絕對值
4. max() 傳回參數中的最大值 
5. min() 傳回參數中的最小值
"""

a=[1,2,5,7,3]
b=sorted(a)
print(a,type(a))
print(b,type(b))
c=sorted(a,reverse=True)
print(c,type(c))

a=10
b=20
c=a*b
print(a,'x',b,'=',c)
print(str(a)+'x'+str(b)+'='+str(c))
print(a,'x',b,'=',c,sep='')

print(abs(-2)) 
print(abs(-3.14))

print(max((1, 2, 3))) 
print(max(['A','B','C'])) 
print(max("abc")) 
print(min([1, 2, 3]))
print(min("abc"))

print(pow(2,3))
print(2**4)



"""6. pow(x,y) 傳回 x 的 y 次方 (x ** y)
7. round() 傳回四捨五入後最接近的數字
8. sum() 傳回總和
9. len() 傳回字串、列表等 長度
10. id() 物件編號
"""

print(pow(2,3)) 
print(round(12.456)) #整數位
print(round(12.456,2)) #小數2位

a=[1,2,3,4,5] 
print(len(a)) 
b="Hello World "
print(len(b))

a=2000
b=2000
print(a,id(a))
print(b,id(b))

a="123abc"
b=list(a)
print(a,type(a))
print(b,type(b))

a="11"
b=int(a)
print(a,type(a))
print(b,type(b))
c=int(a,base=2) #二進制
print(c,type(c))
c=int(a,base=8) #8進制
print(c,type(c))
c=int(a,base=7) #7進制
print(c,type(c))
c=int(a,base=16) #16進制
print(c,type(c))
a="1Z"
c=int(a,base=36) #36進制
print(c,type(c))

a=10
b=20
print(a,b)
a=b
b=a
print(a,b)
a=10
b=20
print(a,b)
t=a
a=b
b=t
print(a,b)

a=10
b=20
a,b=b,a
print(a,b)

a=10
b=20
c=a=b #c=(a=b)錯誤
print(c,type(c))

"""### 課後作業
1. 輸入兩個整數 然後做相加(a+b)。
2. 輸入兩個整數 求出商和餘數(q=a//b a%b)。
3. 對調兩個數值(a,b=b,a)。
4. 輸入一個整數 判斷是奇數或偶數(x%2==0)。

---

## 4-2 函數/自訂函數
+ 程式中的函數：定義一段可以重複呼叫並執行的程式碼。

python自訂函數語法：

def 函數名稱(參數1 ,參數2 , …):   
> 函數的敘述區塊  
> return 傳回值

* 無參數，無傳回值 vs 有參數，無傳回值
"""

def hello():
  print('hello')

hello()

hello()
def hello():
  print('hello')

def hello(name):
  print('hello',name)

n=input('輸入姓名：')
hello(n)

"""### 練習1 印出10個分隔符號"""

print("==========")
print("="*10)

def printline(n):
  for i in range(0,n):
    print("=",end='') #print(”=“)不能使用全型字
  print()
printline(10)
printline(20)

def printline(n):
  print("="*n)
printline(10)
printline(20)

def printline(p,n): #有參數函數
  print(p*n)
printline("=",10)
printline("*",20)

def printline(p,n=10): #有預設值的函數
  print(p*n)
printline("=")
printline("=",5)
printline("*",20)

def printline(p="=",n=10):
  print(p*n)
printline("=")
printline()
printline("=",5)
printline("*",20)
printline(n=50,p="*")

"""### 練習2/3 變數生命週期，區域變數和全域變數"""

a=10 #全域變數
def fun1():
  print('fun1中的變數a：',a) #全域變數

print('main中的變數a：',a) #全域變數
fun1() 
print('main中的變數a：',a) #全域變數

a=10 #全域變數
def fun1():
  a=5 #區域變數
  print('fun1中的變數a：',a) #區域變數
  a=100

print('main中的變數a：',a) #全域變數
fun1() 
print('main中的變數a：',a) #全域變數

a=10 #全域變數
def fun1():
  global a #全域變數
  print('fun1中的變數a：',a) #全域變數
  a=100 #全域變數

print('main中的變數a：',a) #全域變數
fun1() 
print('main中的變數a：',a) #全域變數

a=10 #全域變數
def fun1():
  print('fun1中的變數a：',a)  #區域變數  error
  a=2 #區域變數

print('main中的變數a：',a) #全域變數
fun1() 
print('main中的變數a：',a) #全域變數

def fun1(): 
  print('fun1中的a=',a,'id=',id(a)) 
  a=1 #區域變數
a=2 #全域變數 print('主程式中的a=',a,'id=',id(a))
fun1()

del a
def fun1(): 
  a=1 #區域變數 
  print('fun1中的a=',a,'id=',id(a))
print('主程式中的a=',a,'id=',id(a)) #錯誤

"""### 練習4 函數的傳回值 計算面積"""

def area(length,width):
  return length*width

a=eval(input('長：')) #int float eval
b=eval(input('寬：'))
ans=area(a,b)
print('area =',ans)

"""### 練習5 函數的傳回值 判斷平年閏年"""

year=2000
if( (year%4)==0 and (year%100)!=0 or (year%400)==0 ):
  print('閏年') 
else:
  print('平年')

def isleap(year):
  if( (year%4)==0 and (year%100)!=0 or (year%400)==0 ):
    print('閏年') 
  else:
    print('平年') 
isleap(2001)

def isleap(year):
  if( (year%4)==0 and (year%100)!=0 or (year%400)==0 ):
    return True 
  else:
    return False 
ans=isleap(2001)
if ans:
  print('閏年')
else:
  print('平年')

def isleap(year):
  if( (year%4)==0 and (year%100)!=0 or (year%400)==0 ):
    return True,'閏年' 
  else:
    return False,'平年' 
ans=isleap(2001)
print(ans,type(ans))
a,b=ans
print(a,type(a))
print(b,type(b))

"""### 練習6 函數1加到n的總和， n階層((factorial)"""

n=10
sum=0
for i in range(1,n+1):
  print(i,end=',')
  sum=sum+i
print(sum)

def total(n):
 sum=0
 for i in range(1,n+1):
  #print(i,end=',')
  sum=sum+i
 return sum

n=int(input('請輸入1加到n n=')) 
s=total(n)
print('1 加到',n,' = ',s)

def fact(n):
 prod=1
 for i in range(1,n+1):
  #print(i,end=',')
  prod=prod*i
 return prod

n=int(input('請輸入1x到n n=')) 
s=fact(n)
print('1 x到',n,' = ',s)

"""### 課後作業
5. 寫一個函數，完成攝氏溫度與華氏溫度的轉換(F=9/5*C+32)。
6. 寫一個函數，完成平方公尺與坪的轉換(1平方公尺=0.3025坪)。
7. 寫一個函數，輸入起迄西元年，計算共有幾個閏年。
---

### 練習7 函數 傳回前n項費氏數列費波那契數(fibonacci numbers)
第0項為0，第1項為1，第n項為前2項之和
"""

f0=0
f1=1
print(f0)
print(f1)
for i in range(8):
  f2=f0+f1
  print(f2)
  f0=f1
  f1=f2

def fibonacci(n):
 f0=0
 f1=1
 print(f0,end=' ')
 print(f1,end=' ')
 for i in range(1,n):
  f2=f0+f1
  print(f2,end=' ')
  f0=f1
  f1=f2
num=eval(input('前n項費氏數列,n='))
fibonacci(num)

def fibonacci(n):
 f0=0
 f1=1
 #print(f0,end=' ')
 #print(f1,end=' ')
 for i in range(1,n):
  f2=f0+f1
  #print(f2,end=' ')
  f0=f1
  f1=f2
 return f2 
num=eval(input('前n項費氏數列,n='))
ans=fibonacci(num) 
print('第',num,'項費氏數列:',ans,sep='')

"""### 練習8 函數 傳回第n項費氏數列(費波那契數fibonacci numbers)

"""

# 費氏數列
# 限制 n>2
# 日期作者
def fibonacci(n):
 f0=0; f1=1
 for i in range(1,n):
  f2=f0+f1; f0=f1; f1=f2
 return f2 
num=eval(input('前n項費氏數列,n='))
ans=fibonacci(num) 
print('第',num,'項費氏數列:',ans,sep='')

# 費氏數列
# 限制 n>2
# 日期作者
def fibonacci(n):
 f0,f1=0,1
 for i in range(1,n):
  f2=f0+f1; f0,f1=f1,f2
 return f2 
num=eval(input('前n項費氏數列,n='))
ans=fibonacci(num) 
print('第',num,'項費氏數列:',ans,sep='')

"""### 練習9 函數 求最大公因數

"""

def gcd(m,n): 
 if m>n: #找m,n中較小的數為d 
  d=n
 else: 
  d=m
 #從1到d，逐一檢查二個都可整除的數，就是最大公因數 
 for i in range(1, d+1): 
  if((m%i==0) and (n%i==0)): 
    gcd=i
 return gcd
m = int(input('請輸入m值？')) 
n = int(input('請輸入n值？')) 
ans = gcd(m, n)
print(m,'與',n,'的最大公因數為',ans,sep='')

"""## 4-3 函數/遞迴函數

#### 遞迴recursion

程式的解題方法，在執行過程中呼叫自己，稱為遞迴。為了避免函數無止盡地呼叫自已，遞迴程式需要有明確的終止條件。Python 遞迴呼叫有次數限制

### 練習1 階乘 Factorial 遞迴


"""

def fact(n):
  if n==1:
    return 1
  return n*fact(n-1)
ans=fact(50)
print(ans)

def sum(n):
  if n==1:
    return 1
  return n+sum(n-1)
ans=sum(100)
print(ans)

"""### 練習2 連加1加到n  遞迴

### 練習3 費氏數列 遞迴
"""

def f(n):
  if n==0:
    return 0
  elif n==1:  
    return 1
  else:  
    return f(n-1)+f(n-2)
print(f(8))

"""### 練習4 最大公因數 遞迴

"""

def gcd(m,n):
  if n==0:
    return m
  else:
    return gcd(n,m%n) 

ans=gcd(36,10)
print(ans)

"""# END 
# THANK YOU
###### 國立台南高級工業職業學校
##### 110年國教署補助前瞻基礎建設之普及高級中等以下學校新興科技之遠距示範教學計畫

"""