/***************************************************************************************
* Filename    : 4.cpp                                                                  *
* Update date : 16/10/2022                                                                 *
* Author      : �C����                                                                 *
* Note        : find out the solutions frpm (0,14) to (34,93) using D4,D8,Dm distance  *
                on map100X100.raw,and show the shortest path                           *
***************************************************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Header.h"
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace W;

void D4(int x_new, int y_new, int x_old_flag, unsigned char img[100][100],int stop,int c);

//--------------------linked list �]�w-------------------------//

struct node {
    char data_x;
    char data_y;
    struct node* next1;
    struct node* next2;
};




void MY_HW2::HW2_4() {
    //--------------------------�Ѽ�---------------------------//
    FILE* input_file;
    FILE* output_file;
    char in_imgpath[] = ".\\HW2_images_file\\map100x100.raw";
    char out_imgpath[] = ".\\MAP_ans.raw";
    unsigned char* imgIN = new unsigned char[100 * 100];
    unsigned char img[100][100];
    unsigned char img_out[100][100];


    int dis_D4, dis_D8, dis_Dm;
    int x_ori = 14;
    int y_ori = 0;
    int x_end = 93;
    int y_end = 34;

    //--------------------------�}�ҡBŪ���ɮ�---------------------------//

    fopen_s(&input_file, in_imgpath, "rb");
    if (!input_file) {
        printf("Unable to open the image!\n");
    }
    fread(imgIN, sizeof(unsigned char), (100 * 100), input_file);

    //--------------------------�ন�G���}�C---------------------------//
    int c = 0;
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            img[x][y] = imgIN[c];
            img_out[x][y] = imgIN[c];
            //cout << +img[x][y] << " ";
            c++;
        }
        //cout << endl;
    }


    //--------------------------D4---------------------------//
    //�ˬd�|�P��������m( 2.4.6.8)���� x+1.x-1.y���� �άO y-1,y+1 X����
    int x_new = x_ori;
    int y_new = y_ori;
    int x_old_flag = 4;
    int stop = 0;
    int cX = 0;


    cout << "�_�l��m" << "[" << y_new << "," << x_new << "]" << endl;
    D4(x_new, y_new, x_old_flag,img,stop, cX);
    /*if (x_new - 1 >= 0) {
        cout << +img[x_new - 1][y_new] << " ";
        if (img[x_new - 1][y_new] == img[x_new][y_new]) {//4

            flag[4 - 1] = 1;
        }
    }
    if (x_new - 1 <= 99) {
        cout << +img[x_new + 1][y_new] << " ";
        if (img[x_new + 1][y_new] == img[x_new][y_new]) {//6
            flag[6 - 1] = 1;
        }
    }
    if (y_new - 1 >= 0) {
        cout << +img[x_new][y_new - 1] << " ";
        if (img[x_new][y_new - 1] == img[x_new][y_new]) {//2
            flag[2 - 1] = 1;
        }
    }
    if (y_new + 1 <= 99) {
        cout << +img[x_new][y_new + 1] << endl;
        if (img[x_new][y_new + 1] == img[x_new][y_new]) {//8
            flag[8 - 1] = 1;
        }
    }
    int count = 0;
    for (int i = 0; i < 9; i++) {
        cout << flag[i] << " ";
    }
    cout << endl;
    flag[x_old_flag] = 0;
    for (int i = 0; i < 9; i++) {
        if (flag[i] == 1) {
            count = count + 1;
        }
        cout << flag[i] << " ";
    }
    cout << endl;
    //�o�@���I�����i������V�Ӽ�
    */

    node* root = new node();
    root->data_x = 14;
    root->data_y = 0;
    root->next1 = NULL;
    root->next2 = NULL;
    node* current = root;















    //--------------------------D8---------------------------//
    //�ˬd�|�P��������m(12346789)����





    //--------------------------Dm---------------------------//
    //�ˬd�|�P��������m()���� ����ӱ���



    //--------------------------������@�Ӥ���u+�⹳����H�@�I�C�� �άO�P�乳�����---------------------------//


    //--------------------------��X�ɮ�---------------------------//

    fopen_s(&output_file, out_imgpath, "wb");
    fwrite(img_out, 1, 100 * 100, output_file);
    //--------------------------���X�O����---------------------------//
    delete[] imgIN;
    fclose(input_file);
    //fclose(output_file);
}

void D4(int x_new, int y_new, int x_old_flag, unsigned char img[100][100], int stop,int c) {
    c = c + 1;
    int flag[9] = { 0,0,0,0,0,0,0,0,0 };
    if (stop == 0) {
        //cout << "�_�l��m" << "[" << y_new << "," << x_new << "]" << endl;
        if (x_new - 1 >= 0) {
            //cout << +img[x_new - 1][y_new] << " ";
            if (img[x_new - 1][y_new] == img[x_new][y_new]) {//4

                flag[4 - 1] = 1;
            }
        }
        if (x_new - 1 <= 99) {
            //cout << +img[x_new + 1][y_new] << " ";
            if (img[x_new + 1][y_new] == img[x_new][y_new]) {//6
                flag[6 - 1] = 1;
            }
        }
        if (y_new - 1 >= 0) {
            //cout << +img[x_new][y_new - 1] << " ";
            if (img[x_new][y_new - 1] == img[x_new][y_new]) {//2
                flag[2 - 1] = 1;
            }
        }
        if (y_new + 1 <= 99) {
            //cout << +img[x_new][y_new + 1] << endl;
            if (img[x_new][y_new + 1] == img[x_new][y_new]) {//8
                flag[8 - 1] = 1;
            }
        }
        int count = 0;
        for (int i = 0; i < 9; i++) {
            //cout << flag[i] << " ";
        }
        //cout << endl;
        flag[x_old_flag] = 0;
        for (int i = 0; i < 9; i++) {
            if (flag[i] == 1) {
                count = count + 1;
            }
            //cout << flag[i] << " ";
        }
        //cout << endl;

        if (x_new == 93 && y_new == 34) {
            stop = 1;
        }
        if (c==100) {
            stop = 1;
        }
        if (count == 0) {
            cout << "���I" << endl;
            cout << "[" << y_new << "," << x_new << "]" << endl;
            stop = 1;
        }
        else {//����L���|
            if (flag[0] == 1) {
                D4(x_new - 1, y_new - 1, 8, img, stop,c);
            }
            if (flag[1] == 1) {
                D4(x_new, y_new - 1, 7, img, stop, c);
            }
            if (flag[2] == 1) {
                D4(x_new + 1, y_new - 1, 6, img, stop, c);
            }
            if (flag[3] == 1) {
                D4(x_new - 1, y_new, 5, img, stop, c);
            }
            if (flag[5] == 1) {
                D4(x_new + 1, y_new, 3, img, stop, c);
            }
            if (flag[6] == 1) {
                D4(x_new - 1, y_new + 1, 2, img, stop, c);
            }
            if (flag[7] == 1) {
                D4(x_new, y_new + 1, 1, img, stop, c);
            }
            if (flag[8] == 1) {
                D4(x_new + 1, y_new + 1, 0, img, stop, c);
            }
        }
    }
}
