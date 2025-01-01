import shutil
import os
from os import walk
from os.path import join
MyPath  = '/Users/weiwei/Desktop/orginal_eggplant 2' #'./'  當下目錄
KeyWord =  input = a['ID']#原本是請輸入關鍵字
 
for ss in a['ID'] :
    print(ss) #這邊我把id的list讀成string?

for root, dirs, files in walk(MyPath):
  for i in files:
    FullPath = join(root, i) # 獲取檔案完整路徑
    FileName = join(i) # 獲取檔案名稱
    #print(FileName)
    if any ([KeyWord in FullPath]):
      if not os.path.exists(MyPath + '/' + KeyWord + '/' + FileName):
        if not os.path.exists(KeyWord):
          os.mkdir(KeyWord)
        shutil.move(FullPath, MyPath + '/' + KeyWord)
        print ('成功將', FileName, '移動至', KeyWord, '資料夾')
#這邊有個小問題，我看了下他是新增到另一個含有keyword的資料夾，但如果我要的是新增到另一個統一的（例如：new）的資料夾就有點怪，好像不能用mkdir
      else:
        print (FileName, '已存在，故不執行動作')
