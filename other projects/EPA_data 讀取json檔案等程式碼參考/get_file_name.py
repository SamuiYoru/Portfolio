from os import walk

# 指定要列出所有檔案的目錄
mypath = "Z:/EPA/EPA-112-casebycase/EPA-Dissipation/code/AllParameter/ref_roi"
txtpath = '0915 所有測試影片.txt'
txtfile = open(txtpath, 'w')
# 遞迴列出所有子目錄與檔案
for root, dirs, files in walk(mypath):
    print("路徑：", root)
    print("  目錄：", dirs)
    print("  檔案：", files)
    for f in files:
        print(f)
        str = f.split(".")
        txtfile.write(str[0])
        txtfile.write("\n")

txtfile.close()
