import cv2
from matplotlib import pyplot as plt
import glob

result_dict="C:\\Users\\yuchi\\Downloads\\draw\\result\\"
dict_path = "C:\\Users\\yuchi\\Downloads\\draw\\*.png"
file_list = glob.glob(dict_path)
print("file",file_list)
# file_name = "GreenEnv_0807-15-41-28.png"#"05060708_20230412_140000.jpg"
# file_path = dict_path + file_name
# date = "20230806_150000"
#multi_compare



def change_to_HSV(image_path):#https://stackoverflow.com/questions/67448555/python-opencv-how-to-change-hue-in-hsv-channels
    # Convert the BGR image to HSV Image
    image = cv2.imread(image_path)
    # cv2.imshow('image', image)
    hsv_img = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    # cv2.imshow('hsv_image', hsv_img)
    time = image_path.split("\\")[-1].split("-",1)[-1].split(".")[0]
    factory = image_path.split("\\")[-1].split("_",1)[0]
    date = image_path.split("\\")[-1].split("_",1)[1].split("-")[0]
    h = hsv_img[:,:,0]
    s = hsv_img[:,:,1]
    v = hsv_img[:,:,2]
    # cv2.imshow('h', h)
    cv2.imwrite(f'{factory}-{date}-{time}-h.png', h)
    # cv2.imshow('s', s)
    cv2.imwrite(f'{factory}-{date}-{time}-s.png', s)
    # cv2.imshow('v', v)
    cv2.imwrite(f'{factory}-{date}-{time}-v.png', v)
    # cv2.waitKey(0)
    draw_histogram(h,"h",image_path)
    draw_histogram(s,"s",image_path)
    draw_histogram(v,"v",image_path)
    # return s

def draw_histogram(image,name_tag,path):#https://blog.gtwang.org/programming/python-opencv-matplotlib-plot-histogram-tutorial/
    time = path.split("\\")[-1].split("-",1)[-1].split(".")[0]
    factory = path.split("\\")[-1].split("_",1)[0]
    date = path.split("\\")[-1].split("_",1)[1].split("-")[0]
    print(factory," ",date," ",time)
    #cv2.calcHist(images, channels, mask, histSize, ranges)
    
    hist = cv2.calcHist([image], [0], None, [256], [0, 256])  # ←計算直方圖資訊
    #cdf1 = hist.cumsum()
    #cdf_normalized1 = cdf1 * float(hist.max()) / cdf1.max()

    #plt.plot(cdf1, color = 'b')
    plt.hist(image.flatten(),256,[0,256], color = 'r')
    plt.xlim([0,256])
    #plt.ylim([0,(image.shape[0]*image.shape[1])])
    plt.title(factory+"_Histogram_"+date+time+" "+name_tag)
    plt.xlabel("Bins")
    plt.ylabel("# of Pixels")
    # plt.savefig(result_dict+factory+"_Histogram_"+date+time+" "+name_tag+".png")
    # plt.show()
    # plt.close()

def draw_cdf(file_path,image,name_tag):
    time = file_path.split("\\")[-1].split("-",1)[-1].split(".")[0]
    factory = file_path.split("\\")[-1].split("_",1)[0]
    date = file_path.split("\\")[-1].split("_",1)[1].split("-")[0]
    print(factory," ",date," ",time)
    #cv2.calcHist(images, channels, mask, histSize, ranges)
    
    hist = cv2.calcHist([image], [0], None, [256], [0, 256])  # ←計算直方圖資訊

    cdf1 = hist.cumsum()
    #cdf_normalized1 = cdf1 * float(hist.max()) / cdf1.max()
    cdf_normalized1 = (cdf1/ (image.shape[0]*image.shape[1]))*100

    plt.plot(cdf_normalized1, color = 'b')
    # plt.hist(image.flatten(),256,[0,256], color = 'r')
    plt.xlim([0,256])
    plt.ylim([0,105])
    plt.title(factory+"_CDF_"+"_"+date+name_tag)
    plt.xlabel("Bins")
    plt.ylabel("percent of Pixels(%)")
    # plt.savefig(dict_path+factory+"_CDF_"+"_"+date+name_tag+".png")
    plt.show()
    plt.close()


def draw_HSV_hist():
    for file_path in file_list:
        img = cv2.imread(file_path)
        # cv2.imshow('image', img)
        # cv2.waitKey(0)
        print (file_path)
        change_to_HSV(file_path)
    
def main():
    draw_HSV_hist()

main()