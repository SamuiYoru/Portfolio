import cv2                    # 匯入 OpenCV 函式庫
import numpy as np
import matplotlib.pyplot as plt

fd = open("C:\\Users\\yuchi\\Downloads\\HM1_images_file\\T2\\lena512_out_error_t.raw", 'rb')
rows = int(512)#直向
cols = int(512)#橫向
f = np.fromfile(fd, dtype=np.uint8,count=rows*cols)
im = f.reshape((rows, cols)) #notice row, column format
fd.close()
cv2.imshow("raw_ori",im)
out_name = "lena512_test"
data1 =[]
data2 =[]
a = int(0)
# for o in range(len(f)):
#     if f[o]<128:
#         data1.append(f[o])
#     else:
#         data2.append(f[o])


for o in range(len(f)):
    if f[o]<128:
        data1.append(f[o])
    else:
        data2.append(f[o])
        
#original
for i in range(len(data1)):
    data1[i]=int(data1[i])-128
for j in range(len(data2)):
    if(data2[j]!=0):
        data2[j]=int(data2[j])-128
#mapping
for i in range(len(data1)):
    data1[i]=-(int(data1[i])-128)
for j in range(len(data2)):
    if(data2[j]!=0):
        data2[j]=(int(data2[j])-128)*2

# plt.hist(f, bins=256)
plt.hist(data1, bins=256, alpha=0.5, color='green')
plt.hist(data2, bins=256, alpha=0.5, color='red')
plt.savefig(f"{out_name}_histogram_mapping.png")
plt.show()
