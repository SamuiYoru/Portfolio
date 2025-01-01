import cv2                    # 匯入 OpenCV 函式庫
import numpy as np
fd = open("C:\\Users\\yuchi\\Downloads\\HM1_images_file\\lena512.raw", 'rb')
rows = int(512)#直向
cols = int(512)#橫向
f = np.fromfile(fd, dtype=np.uint8,count=rows*cols)
im = f.reshape((rows, cols)) #notice row, column format
fd.close()
cv2.imshow("raw_ori",im)
out_name = "lena_test"

# for i in range(0,rows):
#     for j in range(0,cols):
#         if (img_new[i][j]+50)>225:
#             img_new[i][j] = 225
#         else :
#             img_new[i][j] =  img_new[i][j]+50

# img_new = im
img_padding = np.ones((rows+2,cols+2))
img_padding = img_padding.astype('uint8')
for i in range(0,rows+2):#point filling
    for j in range(0,cols+2):
        if (i == 0):
            img_padding[i][j] = 0
        elif (j == 0):
            img_padding[i][j] = img_padding[i-1][j+1]
        elif (i == rows+1):
            img_padding[i][j] = 0
        elif(j == cols+1):
            img_padding[i][j] = img_padding[i][j-1]
        else:#(i>0 and j>0 and i < rows+1 and j < cols+1)
            img_padding[i][j] = im[i-1][j-1]

# img_new = np.ones((rows,cols))
# img_new = img_new.astype('uint8')
img_new = im.copy()
time_count=0
for i in range(1,rows+1):
    for j in range(1,cols+1):
        # x = int(img_padding[i][j])
        a = int(img_padding[i][j-1])
        b = int(img_padding[i-1][1])
        c = int(img_padding[i-1][j-1])
        d = int(img_padding[i-1][j+1])
        print(type(a))
        
        ans = 0
        print(type(ans))
        if(c>=max([a,b])):
            ans = min([a,b])
        elif(c<=min([a,b])):
            ans = max([a,b])
        else:
            ans = a+b-c
        print(type(ans))
        img_new[i-1][j-1] = ans

img_new = img_new.astype('uint8') 
img_error = im - img_new

cv2.imshow("paddingfile",img_padding)
cv2.imshow("newfile",img_new)
cv2.imshow("errorfile",img_error)
cv2.waitKey(0)
# cv2.imwrite(f"{out_name}_original.png",im)
# cv2.imwrite(f"{out_name}_padding.png",img_padding)
# cv2.imwrite(f"{out_name}_MED.png",img_new)
cv2.imwrite(f"{out_name}_error.png",img_error)
cv2.destroyAllWindows()

# co = 0
# for i in range(0,rows):
#     for j in range(0,cols):
#         # print(f[co],end = " ")
#         print(img_error[i][j],end = " ")
#         # co = co+1
#     print(" ")

print(type(img_error[15][15]))
# print(img_new[15][15])

# a = x-1 col-1
# b = x-col row -1
# c = x-col-1 
# d = x-col+1