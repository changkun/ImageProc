//
//  ImageEnhancement.cpp
//  ImageProc
//
//  Created by 欧长坤 on 15/5/24.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "ImageEnhancement.h"

using namespace std;
// 计算模板
Vec3b TempCompute(Vec3b * pixel_array,  ProductTemplate temp) {
    double temp1 = 0;
    double temp2 = 0;
    double temp3 = 0;
    for(int i = 0; i < temp_size*temp_size; i++) {
        double one = (double)pixel_array[i][0];
        double two = (double)pixel_array[i][1];
        double three = (double)pixel_array[i][2];
        
        switch (temp) {
            case CONV_TEMP3X3:
                temp1 += one*conv_temp_arr[i];
                temp2 += two*conv_temp_arr[i];
                temp3 += three*conv_temp_arr[i];
                if (temp1 > 255)
                    temp1 = 255;
                if (temp2 > 255)
                    temp2 = 255;
                if (temp3 > 255)
                    temp3 = 255;
                if (temp1 < 0)
                    temp1 = 0;
                if (temp2 < 0)
                    temp2 = 0;
                if (temp3 < 0)
                    temp3 = 0;
                break;
            case GAUSS_TEMP3X3:
                temp1 += one*gauss_temp_arr[i];
                temp2 += two*gauss_temp_arr[i];
                temp3 += three*gauss_temp_arr[i];break;
            case BOX_TEMP3X3:
                temp1 += one*box_temp_arr[i];
                temp2 += two*box_temp_arr[i];
                temp3 += three*box_temp_arr[i];  break;
            case MIDDL_TEMP:
                temp1 += one*middl_temp_arr[i];
                temp2 += two*middl_temp_arr[i];
                temp3 += three*middl_temp_arr[i];break;
            case SOBEL_TEMP3x3:
                temp1 += one*sobel_temp_arr_3x3[i];
                temp2 += two*sobel_temp_arr_3x3[i];
                temp3 += three*sobel_temp_arr_3x3[i];
                if (temp1 > 255)
                    temp1 = 255;
                if (temp2 > 255)
                    temp2 = 255;
                if (temp3 > 255)
                    temp3 = 255;
                if (temp1 < 0)
                    temp1 = 0;
                if (temp2 < 0)
                    temp2 = 0;
                if (temp3 < 0)
                    temp3 = 0;
                break;
            case LAPLACIAN_TEMP_3x3_1:
                temp1 += one*laplacian_temp_arr_3x3_1[i];
                temp2 += two*laplacian_temp_arr_3x3_1[i];
                temp3 += three*laplacian_temp_arr_3x3_1[i];
                if (temp1 > 255)
                    temp1 = 255;
                if (temp2 > 255)
                    temp2 = 255;
                if (temp3 > 255)
                    temp3 = 255;
                if (temp1 < 0)
                    temp1 = 0;
                if (temp2 < 0)
                    temp2 = 0;
                if (temp3 < 0)
                    temp3 = 0;
                break;
            case LAPLACIAN_TEMP_3x3_2:
                temp1 += one*laplacian_temp_arr_3x3_2[i];
                temp2 += two*laplacian_temp_arr_3x3_2[i];
                temp3 += three*laplacian_temp_arr_3x3_2[i];
                if (temp1 > 255)
                    temp1 = 255;
                if (temp2 > 255)
                    temp2 = 255;
                if (temp3 > 255)
                    temp3 = 255;
                if (temp1 < 0)
                    temp1 = 0;
                if (temp2 < 0)
                    temp2 = 0;
                if (temp3 < 0)
                    temp3 = 0;
                break;
            case LAPLACIAN_TEMP_3x3_3:
                temp1 += one*laplacian_temp_arr_3x3_3[i];
                temp2 += two*laplacian_temp_arr_3x3_3[i];
                temp3 += three*laplacian_temp_arr_3x3_3[i];
                if (temp1 > 255)
                    temp1 = 255;
                if (temp2 > 255)
                    temp2 = 255;
                if (temp3 > 255)
                    temp3 = 255;
                if (temp1 < 0)
                    temp1 = 0;
                if (temp2 < 0)
                    temp2 = 0;
                if (temp3 < 0)
                    temp3 = 0;
                break;
            default:
                temp1 += one*1;
                temp2 += two*1;
                temp3 += three*1;
                break;
        }
        
    }
//    cout << temp1 << endl;
//    cout << temp2 << endl;
//    cout << temp3 << endl;
//    cout << endl;
    Vec3b temp_pixel_value;
    switch (temp) {
            case CONV_TEMP3X3:
            temp_pixel_value[0] = temp1;
            temp_pixel_value[1] = temp2;
            temp_pixel_value[2] = temp3;
            return temp_pixel_value;
            case GAUSS_TEMP3X3:
            temp_pixel_value[0] = temp1/16.0;
            temp_pixel_value[1] = temp2/16.0;
            temp_pixel_value[2] = temp3/16.0;
            return temp_pixel_value;
            case BOX_TEMP3X3: // it is ok.
            temp_pixel_value[0] = temp1/9.0;
            temp_pixel_value[1] = temp2/9.0;
            temp_pixel_value[2] = temp3/9.0;
            return temp_pixel_value;
            case MIDDL_TEMP:
            temp_pixel_value[0] = temp1;
            temp_pixel_value[1] = temp2;
            temp_pixel_value[2] = temp3;
            return temp_pixel_value;
            case SOBEL_TEMP3x3:
            temp_pixel_value[0] = temp1;
            temp_pixel_value[1] = temp2;
            temp_pixel_value[2] = temp3;
            return temp_pixel_value;
            case LAPLACIAN_TEMP_3x3_1:
            temp_pixel_value[0] = temp1;
            temp_pixel_value[1] = temp2;
            temp_pixel_value[2] = temp3;
            return temp_pixel_value;
            case LAPLACIAN_TEMP_3x3_2:
            temp_pixel_value[0] = temp1;
            temp_pixel_value[1] = temp2;
            temp_pixel_value[2] = temp3;
            return temp_pixel_value;
            case LAPLACIAN_TEMP_3x3_3:
            temp_pixel_value[0] = temp1;
            temp_pixel_value[1] = temp2;
            temp_pixel_value[2] = temp3;
            return temp_pixel_value;
        default:          return 0;
    }
}

// Set The Center Pixel and Around Pixels Array
void SetPixelArray(Mat &src, int x, int y, Vec3b *pixel_array) {
    pixel_array[0] = src.at<Vec3b>(x-1,y-1);
    pixel_array[1] = src.at<Vec3b>(x-1,y);
    pixel_array[2] = src.at<Vec3b>(x-1,y+1);
    pixel_array[3] = src.at<Vec3b>(x,y-1);
    pixel_array[4] = src.at<Vec3b>(x,y);
    pixel_array[5] = src.at<Vec3b>(x,y+1);
    pixel_array[6] = src.at<Vec3b>(x+1,y-1);
    pixel_array[7] = src.at<Vec3b>(x+1,y);
    pixel_array[8] = src.at<Vec3b>(x+1,y+1);
}

// 进行图像增强
void Enhancement(Mat &src, Mat &dst, ProductTemplate temp) {
    int height = src.rows;
    int width  = src.cols;
    dst.create(height, width, CV_8UC3);
    assert( src.channels() == 3 );
    Vec3b pixel_array[9] = {0};
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height-1 || j == 0 || j == width-1) {
                dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
            } else {
                SetPixelArray(src, i, j, pixel_array);
                dst.at<Vec3b>(i, j) = TempCompute(pixel_array, temp);
            }
        }
    }
}
