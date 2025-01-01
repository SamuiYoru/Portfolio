# coding = utf-8
import cv2                    # 匯入 OpenCV 函式庫
import numpy as np
fd = open("C:\\Users\\user\\project\\MED\\MED_C\\output\\cat_512_out_error.raw", 'rb')
rows = int(512)#直向
cols = int(512)#橫向
f = np.fromfile(fd, dtype=np.uint8,count=rows*cols)
im = f.reshape((rows, cols)) #notice row, column format
fd.close()
cv2.imshow("raw_ori",im)
out_name = "lena_test"

cv2.waitKey(0)
cv2.destroyAllWindows()