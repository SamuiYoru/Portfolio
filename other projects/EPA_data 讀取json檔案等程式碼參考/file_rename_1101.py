import os
import cv2
import glob
import shutil
import os
mother_dict_path="Z:\\EPA\\112-測試資料\\冷媒 測試資料\\67月重跑\\*"
dict_list = glob.glob(mother_dict_path)
for n in dict_list:
    # print(n)
    fac_name = n.split("\\")[len(n.split("\\"))-1]
    # print(fac_name)
    path=n
    # print("path = ",path)
    dict_path = path + "\\*.mp4"
    # print(dict_path)
    fileList = glob.glob(dict_path)
    for i in fileList:
        # print(i)
        name = i.split("\\")[len(i.split("\\"))-1].split(".")[0].split("_")
        # print(name)
        new_name = path + "\{}-{}-{}-{}.mp4".format(fac_name,name[0],name[1],name[2])
        # print(new_name)
        
        os.rename(i,new_name)
        print(i,'======>',new_name)
        