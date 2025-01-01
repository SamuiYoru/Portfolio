import shutil
import os
from os import walk
from os.path import join

MyPath  = 'Z:\\EPA\\test_data\\refrigerant\\input_video\\T' # 目錄


KeyWord = "大東方"
folderpath = MyPath+"\\"+KeyWord
if os.path.isdir(folderpath):
  print("目錄存在。")
else:
  print("目錄不存在。")
  os.mkdir(folderpath)
  print("已建立資料夾")

for root, dirs, files in walk(MyPath):
   for i in files:
    FullPath = join(root, i) # 獲取檔案完整路徑
    if root != folderpath:
        FileName = join(i) # 獲取檔案名稱
        print(FileName)
        try:
            if KeyWord in FullPath:
                shutil.move(FullPath, MyPath + '/' + KeyWord)
                print ('成功將', FileName, '移動至', KeyWord, '資料夾')
            else:
                print (FileName, '已存在，故不執行動作')
        except:
            pass
    else:
       pass