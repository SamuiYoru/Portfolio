import threading
import time
import pygame
import os
import time
import tkinter as tk
import tkinter.filedialog
import threading
from datetime import datetime
from threading import Timer


#定義變數
folder = '' #歌曲資料夾路徑
res = [] #存放歌曲路徑
ret = [] #存放歌曲名稱
num = 0
now_music = ''
one_start = True
state = 0
pause = 0
pause_res = []
pause_resume = ''
NextClick = 0
PrevClick = 0
pause = False
nextMusic = ''
clock_on = True
playing = True

#輸入資料夾內容
def imp():
    global folder
    global res
    global ret
    folder = "D:\音樂\いかさん\いかさん　ボクらの最終定理"
    if folder:
        musics = [folder + '\\' + music for music in os.listdir(folder) if music.endswith(('.mp3'))]#只撥放MP3的檔案
        for i in musics:
            ret.append(i.split('\\')[4:])#檔名
            res.append(i.replace('\\','/'))#位置
            var2 = tkinter.StringVar()
            var2.set(ret)
            global listblock
            listblock = tkinter.Listbox(root,listvariable=var2)
            listblock.place(x=160,y=50,width=260,height=100)
    if not folder:
        return

    playing = True
    # 根據情況禁用和啓用相應的按鈕
    button_play['state'] = 'normal'
    #voice_bar['state'] = 'normal'
    pause_resume ='播放'
    state = 1

# 播放音樂
def play():
    global NextClick
    global one_start
    global nextMusic
    global PrevClick
    global playing
    if len(res):
        # 初始化
        pygame.mixer.init()
        pygame.mixer.music.set_volume(0.07)
        global num
        while playing:
            #print ('pause',pause)
            #print ('test',pygame.mixer.music.get_busy())
            if pause:
                pygame.mixer.music.stop()
                #time.sleep(0.1)
            else:
                if not pygame.mixer.music.get_busy():
                #print ('NextClick',NextClick)
                    if NextClick>0:
                        nextMusic = res[num]
                        nextMusic = listblock.get('active')
                        temp_list = [nextMusic[0]]
                        current_index = ret.index(temp_list)
                        num = current_index
                        nextMusic = res[current_index+NextClick-PrevClick] 
                    elif PrevClick>0:
                        nextMusic = res[num]
                        nextMusic = listblock.get('active')
                        temp_list = [nextMusic[0]]
                        current_index = ret.index(temp_list)
                        num = current_index
                        nextMusic = res[current_index+NextClick-PrevClick] 
                    else:
                        nextMusic = res[num]
                #if one_start:
                    # 播放選中的那首歌
                        nextMusic = listblock.get('active')
                        temp_list = [nextMusic[0]]
                        current_index = ret.index(temp_list)
                        num = current_index
                        nextMusic = res[current_index] 
                #print ('nextMusic',nextMusic)
                #print ('temp_list',temp_list)
                #print ('current_index',current_index)
                #print('nextMusic.encode()',nextMusic.encode())
                #print('pause_resume',pause_resume)
                #print(num)
                    
                    pygame.mixer.music.load(nextMusic.encode())
                    # 播放一次
                    pygame.mixer.music.play(1)

                # print(len(res)-1)
                    if len(res) - 1 == num:
                        num = 0
                    else:
                        num = num + 1

                    nextMusic = nextMusic.split('/')[-1]
                    #play_state.set('playing...')
                    musicName.set(nextMusic)
                    one_start = False
                else:
                    #NextClick = 0
                    time.sleep(0.1)


# 關閉視窗
def closeWindow():
    global playing
    global clock_on
    clock_on = False
    playing = False
    time.sleep(0.3)
    try:
        # 停止播放，如果已經停止
        # 再次停止時會拋出異常，所以需要異常捕獲
        pygame.mixer.music.stop()
        pygame.mixer.quit()
    except:
        pass
    root.destroy() # 整個介面退出

def play_click():
    global res
    global ret
    global num
    global NextClick
    global PrevClick
    global pause
    NextClick = 0
    PrevClick = 0
    pause = False
    #print (num)
    pause_resume = '播放'
    nextMusic = listblock.get('active')
    temp_list = [nextMusic[0]]
    current_index = ret.index(temp_list)
    nextMusic = res[current_index]
    if pause_resume == '播放':
        if one_start:
            #print('撥放')
            playing = True
            t = threading.Thread(target=play)
            t.start() 
            state = 1
        else:
            #print('其他')
            #print ('nextMusic',nextMusic)
            pygame.mixer.music.load(nextMusic.encode())
        
        button_pause['state'] = 'normal'
        button_prev['state'] = 'normal'
        button_next['state'] = 'normal'
        pause_resume = '暫停'

def pause_click():
    global res
    global ret
    global num
    global pause
    playing = False
    pygame.mixer.music.stop()
    pause = True
    #playing = True


def buttonPrevClick():
    pause = 0
    global playing
    global PrevClick
    global NextClick
    global nextMusic
    global num
    playing = False
    #NextClick = 0
    PrevClick +=1
    pause_resume='暫停'
    pygame.mixer.init()
    pygame.mixer.music.stop()
    if num == 0:
        num = len(res) - 2
    elif num == len(res) - 1:
        num -= 2
    else:
        num -= 2
    #print(num)
    playing = True


def buttonNextClick():
    global NextClick
    global playing
    global nextMusic
    global PrevClick
    playing = False
    pause_resume='暫停'
    pygame.mixer.init()
    pygame.mixer.music.stop()
    NextClick += 1 
    #PrevClick = 0
    global num
    if len(res) == num:
        num = 0
    pause_resume='播放'
    playing = True


def printTime(inc):
    global nextMusic
    print(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    print ('nextMusic',nextMusic)
    t = Timer(inc, printTime, (inc,))
    t.start()

def clo():
    global clock_on
    if clock_on:
        TTT = tkinter.StringVar(root,datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
        TIME_NAME=tkinter.Label(root,textvariable=TTT,font=("微軟雅黑", 12),fg='#7700BB')
        TIME_NAME.place(x=10,y=125,width=150,height=30)
        p = threading.Thread(target=clo)
        p.start()

# 介面
root = tkinter.Tk()
root.title('音樂播放器')
root.geometry('460x200')
root.resizable(False,False)
printTime(5)

button_clock = tkinter.Button(root,text='時鐘',command=clo)
button_clock.place(x=90,y=50,width=40,height=20)


# 視窗關閉
root.protocol("WM_DELETE_WINDOW",closeWindow)
# 新增檔案按鈕
button_choose = tkinter.Button(root,text='匯入',command=imp)
button_choose.place(x=40,y=50,width=40,height=20)

# 播放按鈕
button_play = tkinter.Button(root,text='＞',command=play_click)
button_play.place(x=70,y=80,width=30,height=20)
button_play['state'] = 'disabled'
button_play["fg"]="#00BBFF"

# 暫停按鈕
button_pause = tkinter.Button(root,text='∥',command= pause_click)
button_pause.place(x=70,y=100,width=30,height=20)
button_pause['state'] = 'disabled'
button_pause["fg"]="#CC0000"

# 上一首
button_prev = tkinter.Button(root,text='＜＜',command=buttonPrevClick)
button_prev.place(x=40,y=80,width=30,height=20)
button_prev['state'] = 'disabled'
button_prev["fg"]="#0044BB"

# 下一首
button_next = tkinter.Button(root,text='＞＞',command=buttonNextClick)
button_next.place(x=100,y=80,width=30,height=20)
button_next['state'] = 'disabled'
button_next["fg"]="#0044BB"

# 當前播放的音樂
musicName = tkinter.StringVar(root,value='')
labelName = tkinter.Label(root,textvariable=musicName,font=("微軟雅黑", 12),fg='#00FF99')
labelName.place(x=140,y=20,width=300,height=30)

TTT = tkinter.StringVar(root,datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
TIME_NAME=tkinter.Label(root,textvariable=TTT,font=("微軟雅黑", 12),fg='#666666')
TIME_NAME.place(x=10,y=10,width=150,height=30)



root.mainloop()