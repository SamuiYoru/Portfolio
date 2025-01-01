/***************************************************************************************
* Filename    : 4_test.cpp                                                             *
* Update date : 16/10/2022                                                             *
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

void MY_HW2::HW2_4_TRY() {
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
    int flag[9] = { 0,0,0,0,0,0,0,0,0};
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
    // ���I�w�]���~(�b���U����m)
    // �J�즺�����ѨM��k (�O���ø��y�СA�J�즺��(����FLAG���O0���ɭ�)�N�^��ø��y�Шç������|��FLAG�令0�A���t�@������
    // �Q�ά۹��V�ӧP�_�u�����ǡA�٦����n���^�e�@���I�����D(x_old_flag ����m�令0)
    int x_new = x_ori;
    int y_new = y_ori;
    int x_old_flag = 0;
    int stop = 0;
    int x_cross = x_ori;
    int y_cross = y_ori;
    dis_D4 = 0;
    int x_old_flag_cross = 4;
    int already_dir=4;
    //cout << +img[x_new][y_new] << endl;
    cout << "[" << y_new << "," << x_new << "]" << endl << endl;;
    while (stop == 0) {
        cout << "�_�l��m"<<"[" << y_new << "," << x_new << "]" << endl;
        if (x_new - 1 >= 0) {
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

        for (int i = 0; i < 9; i++) {
            cout << flag[i] << " ";
        }
        cout << endl;

        cout << "x_old_flag =" << x_old_flag << endl;
        flag[x_old_flag] = 0;
        flag[already_dir] = 0;


        int count = 0;
        for (int i = 0; i < 9; i++) {
            if (flag[i] == 1) {
                count = count + 1;
            }
            cout << flag[i] << " ";
        }
        cout << endl;

        if (count >= 2) {//�O�����ø�//�~��
            cout << "�ø��I" << "[" << y_new << "," << x_new << "]" << endl;
            x_cross = x_new;
            y_cross = y_new;
            x_old_flag_cross = x_old_flag;
            int f1, f2, f3, f4;
            int x_direction = x_end - x_new;
            int y_direction = y_end - y_new;
            //cout << "x_direction=" << x_direction << "; y_direction = " << y_direction << endl;
            if (x_direction > 0 && y_direction < 0) {//�H���G
                f1 = 1;
                f2 = 3;
                f3 = 5;
                f4 = 7;
                //2.4.6.8
            }
            else if (x_direction < 0 && y_direction < 0) {//�H���T
                f1 = 5;
                f2 = 1;
                f3 = 3;
                f4 = 7;
                //6.2.4.8

            }
            else if (x_direction < 0 && y_direction > 0) {//�H���@
                f1 = 7;
                f2 = 3;
                f3 = 5;
                f4 = 1;
                //8.4.6.2

            }
            else if (x_direction > 0 && y_direction > 0) {//�H���|
                f1 = 5;
                f2 = 7;
                f3 = 3;
                f4 = 1;
                //6.8.4.2

            }

            //�[�W��V�P�w�M�w����(�t�ƧP�w
            // 
            // 
            //�V�e�@�B
            //�P�w�y��
            if (flag[f1] == 1) {
                cout << "��V=" << f1 << endl;
                x_old_flag = 8-f1;
                already_dir = f1;
                if (f1 == 3) {
                    x_new = x_new - 1;
                    y_new = y_new;
                }
                else if (f1 == 5) {
                    x_new = x_new + 1;
                    y_new = y_new ;
                }
                else if (f1 == 7) {
                    x_new = x_new;
                    y_new = y_new + 1;
                }
                else {
                    x_new = x_new ;
                    y_new = y_new - 1;
                }

                if (x_new >= 99) {
                    x_new = 99;
                }
                if (y_new >= 99) {
                    y_new = 99;
                }
                if (x_new <= 0) {
                    x_new = 0;
                }
                if (y_new <= 0) {
                    y_new = 0;
                }

                    //img_out[x_new + 1][y_new] = 125;
                    //img_out[x_new - 1][y_new] = 125;
            }
            else if (flag[f2] == 1) {
                cout << "��V=" << f2 << endl;
                x_old_flag = 8-f2;
                already_dir = f2;
                if (f2 == 3) {
                    x_new = x_new - 1;
                    y_new = y_new ;
                }
                else if (f2 == 5) {
                    x_new = x_new + 1;
                    y_new = y_new ;
                }
                else if (f2 == 7) {
                    x_new = x_new ;
                    y_new = y_new + 1;
                }
                else {
                    x_new = x_new ;
                    y_new = y_new - 1;
                }

                if (x_new >= 99) {
                    x_new = 99;
                }
                if (y_new >= 99) {
                    y_new = 99;
                }
                if (x_new <= 0) {
                    x_new = 0;
                }
                if (y_new <= 0) {
                    y_new = 0;
                }
                    //img_out[x_new][y_new - 1] = 125;
                    //img_out[x_new][y_new + 1] = 125;
            }

            else if (flag[f3] == 1) {
                cout << "��V=" << f3 << endl;
                x_old_flag = 8-f3;
                already_dir = f3;
                if (f3 == 3) {
                    x_new = x_new -1;
                    y_new = y_new;
                }
                else if (f3 == 5) {
                    x_new = x_new + 1;
                    y_new = y_new ;
                }
                else if (f3 == 7) {
                    x_new = x_new ;
                    y_new = y_new + 1;
                }
                else {
                    x_new = x_new ;
                    y_new = y_new - 1;
                }

                if (x_new >= 99) {
                    x_new = 99;
                }
                if (y_new >= 99) {
                    y_new = 99;
                }
                if (x_new <= 0) {
                    x_new = 0;
                }
                if (y_new <= 0) {
                    y_new = 0;
                }
                    //img_out[x_new + 1][y_new] = 125;
                    //img_out[x_new - 1][y_new] = 125;
                

            }
            else if (flag[f4] == 1) {
            cout << "��V=" << f4 << endl;
                already_dir = f4;
                x_old_flag = 8-f4;
                if (f4 == 3) {
                    x_new = x_new-1;
                    y_new = y_new;
                }
                else if(f4 == 5) {
                    x_new = x_new +1;
                    y_new = y_new;
                }
                else if (f4 == 7) {
                    x_new = x_new;
                    y_new = y_new +1;
                }
                else {
                    x_new = x_new;
                    y_new = y_new-1;
                }

                if (x_new >= 99) {
                    x_new = 99;
                }
                if (y_new >= 99) {
                    y_new = 99;
                }
                if (x_new <=0 ) {
                    x_new = 0;
                }
                if (y_new <= 0) {
                    y_new = 0;
                }
                    //img_out[x_new][y_new + 1] = 125;
                    //img_out[x_new][y_new - 1] = 125;
            }
            else {
                
                x_new = x_new;
                y_new = y_new;
            }



            cout <<"������m="<< "[" << y_new << "," << x_new << "]" << endl;
            cout << endl;
            cout << endl;
            for (int i = 0; i < 9; i++) {
                flag[i] = 0;
            }
            dis_D4 = dis_D4 + 1;
            if (x_new == x_end && y_new == y_end) {
                stop = 1;
            }
            if (dis_D4 == 75) {
                stop = 1;
            }



        }
        else if (count == 0) {//�����A�^��W�@�ӧø��f
            cout <<"���� ="<< "[" << y_new << "," << x_new << "]" << endl;
            x_new = x_cross;
            y_new = y_cross;
            x_old_flag = x_old_flag_cross;
            //x_old_flag_cross = 4;
            //already_dir = 4;
            //�Z��(��������ݨ�ø��f�Z��)

        }
        else {
        x_cross = x_cross;
        y_cross = y_cross;

        int f1, f2, f3, f4;
        int x_direction = x_end- x_new;
        int y_direction = y_end -y_new;
        if (x_direction > 0 && y_direction < 0) {//�H���G
            f1 = 1;
            f2 = 3;
            f3 = 5;
            f4 = 7;
            //2.4.6.8
        }
        else if (x_direction < 0 && y_direction < 0) {//�H���T
            f1 = 5;
            f2 = 1;
            f3 = 3;
            f4 = 7;
            //6.2.4.8

        }
        else if (x_direction < 0 && y_direction > 0) {//�H���@
            f1 = 7;
            f2 = 3;
            f3 = 5;
            f4 = 1;
            //8.4.6.2

        }
        else if (x_direction > 0 && y_direction > 0) {//�H���|
            f1 = 5;
            f2 = 7;
            f3 = 3;
            f4 = 1;
            //6.8.4.2

        }

        //�[�W��V�P�w�M�w����(�t�ƧP�w
        // 
        // 
        //�V�e�@�B
        //�P�w�y��
        if (flag[f1] == 1) {
            x_old_flag = 8 - f1;
            if (f1 == 3) {
                x_new = x_new-1;
                y_new = y_new;
            }
            else if (f1 == 5) {
                x_new = x_new+1;
                y_new = y_new ;
            }
            else if (f1 == 7) {
                x_new = x_new;
                y_new = y_new+1;
            }
            else {
                x_new = x_new;
                y_new = y_new-1;
            }

            if (x_new >= 99) {
                x_new = 99;
            }
            if (y_new >= 99) {
                y_new = 99;
            }
            if (x_new <= 0) {
                x_new = 0;
            }
            if (y_new <= 0) {
                y_new = 0;
            }

            //img_out[x_new + 1][y_new] = 125;
            //img_out[x_new - 1][y_new] = 125;
        }
        else if (flag[f2] == 1) {
            x_old_flag = 8 - f2;
            if (f2 == 3) {
                x_new = x_new-1;
                y_new = y_new;
            }
            else if (f2 == 5) {
                x_new = x_new+1;
                y_new = y_new;
            }
            else if (f2 == 7) {
                x_new = x_new;
                y_new = y_new+1;
            }
            else {
                x_new = x_new;
                y_new = y_new-1;
            }

            if (x_new >= 99) {
                x_new = 99;
            }
            if (y_new >= 99) {
                y_new = 99;
            }
            if (x_new <= 0) {
                x_new = 0;
            }
            if (y_new <= 0) {
                y_new = 0;
            }
            //img_out[x_new][y_new - 1] = 125;
            //img_out[x_new][y_new + 1] = 125;
        }

        else if (flag[f3] == 1) {
            x_old_flag = 8 - f3;
            if (f3 == 3) {
                x_new = x_new-1;
                y_new = y_new;
            }
            else if (f3 == 5) {
                x_new = x_new+1;
                y_new = y_new;
            }
            else if (f3 == 7) {
                x_new = x_new;
                y_new = y_new+1;
            }
            else {
                x_new = x_new;
                y_new = y_new-1;
            }

            if (x_new >= 99) {
                x_new = 99;
            }
            if (y_new >= 99) {
                y_new = 99;
            }
            if (x_new <= 0) {
                x_new = 0;
            }
            if (y_new <= 0) {
                y_new = 0;
            }
            //img_out[x_new + 1][y_new] = 125;
            //img_out[x_new - 1][y_new] = 125;


        }
        else if (flag[f4] == 1) {
            x_old_flag = 8 - f4;
            if (f4 == 3) {
                x_new = x_new-1;
                y_new = y_new;
            }
            else if (f4 == 5) {
                x_new = x_new+1;
                y_new = y_new;
            }
            else if (f4 == 7) {
                x_new = x_new;
                y_new = y_new+1;
            }
            else {
                x_new = x_new;
                y_new = y_new-1;
            }

            if (x_new >= 99) {
                x_new = 99;
            }
            if (y_new >= 99) {
                y_new = 99;
            }
            if (x_new <= 0) {
                x_new = 0;
            }
            if (y_new <= 0) {
                y_new = 0;
            }
            //img_out[x_new][y_new + 1] = 125;
            //img_out[x_new][y_new - 1] = 125;
        }
        else {
            x_new = x_new;
            y_new = y_new;
        }



        cout << "������m=" << "[" << y_new << "," << x_new << "]" << endl;
        cout << endl;
        cout << endl;
        for (int i = 0; i < 9; i++) {
            flag[i] = 0;
        }
        dis_D4 = dis_D4 + 1;
        if (x_new == x_end && y_new == y_end) {
            stop = 1;
        }
        if (dis_D4 == 75) {
            stop = 1;
        }



}


    }
    cout << "dis_D4 = " << dis_D4 << endl;


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