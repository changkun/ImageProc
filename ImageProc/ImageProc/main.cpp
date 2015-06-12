//
//  main.cpp
//  loadBMP
//
//  Created by 欧长坤 on 15/3/27.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#include "LoadBMP.h"
#include "Demo.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    // create a Mat
    Mat image = Mat();
    const char * imagepath = "/Users/ouchangkun/Pictures/11.bmp";
    // self-implementation function to load a bmp image for extension opencv api cv::imread()
    loadBMPimage(imagepath, image);
    
    // if cannot read picture, then it does not need to show in window
    if (image.empty()) {
        cout << "cannot show this image" << endl;
        return 0;
    }
    
    // 灰度变换
    // GrayTransferProc(image);
    // 画直方图
    //HistogramProc(image);
    // 直方图均衡化
    //HistogramEualProc(image);
    // 图像增强
    //ImageEnhancement(image);
    // 迭代阈值分割
    ImageSegmentation(image);
    // 傅里叶变换和傅里叶逆变换
    DiscreteFourierTransformImage(imagepath);
    
    // wait a keybroad action and quit this program.
    waitKey();
    return 0;
}
