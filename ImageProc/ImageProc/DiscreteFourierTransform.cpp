//
//  DiscreteFourierTransform.cpp
//  ImageProc
//
//  Created by 欧长坤 on 15/6/11.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "DiscreteFourierTransform.h"

//傅里叶正变换
void fft2(IplImage *src, IplImage *dst)
{   //实部、虚部
    IplImage *image_Re = 0, *image_Im = 0, *Fourier = 0;
    //   int i, j;
    image_Re = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);  //实部
    //Imaginary part
    image_Im = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);  //虚部
    //2 channels (image_Re, image_Im)
    Fourier = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 2);
    // Real part conversion from u8 to 64f (double)
    cvConvertScale(src, image_Re, 1, 0);
    // Imaginary part (zeros)
    cvZero(image_Im);
    // Join real and imaginary parts and stock them in Fourier image
    cvMerge(image_Re, image_Im, 0, 0, Fourier);
    // Application of the forward Fourier transform
    cvDFT(Fourier, dst, CV_DXT_FORWARD);
    cvReleaseImage(&image_Re);
    cvReleaseImage(&image_Im);
    cvReleaseImage(&Fourier);
}

void fft2shift(IplImage *src, IplImage *dst)
{
    IplImage *image_Re = 0, *image_Im = 0;
    int nRow, nCol, i, j, cy, cx;
    double scale, shift, tmp13, tmp24;
    image_Re = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);
    //Imaginary part
    image_Im = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);
    cvSplit( src, image_Re, image_Im, 0, 0 );
    // 具体原理见冈萨雷斯数字图像处理p123
    // Compute the magnitude of the spectrum Mag = sqrt(Re^2 + Im^2)
    // 计算傅里叶谱
    cvPow( image_Re, image_Re, 2.0);
    cvPow( image_Im, image_Im, 2.0);
    cvAdd( image_Re, image_Im, image_Re);
    cvPow( image_Re, image_Re, 0.5 );
    //对数变换以增强灰度级细节(这种变换使以窄带低灰度输入图像值映射
    //一宽带输出值，具体可见冈萨雷斯数字图像处理p62)
    // Compute log(1 + Mag);
    cvAddS( image_Re, cvScalar(1.0), image_Re ); // 1 + Mag
    cvLog( image_Re, image_Re ); // log(1 + Mag)
    //Rearrange the quadrants of Fourier image so that the origin is at the image center
    nRow = src->height;
    nCol = src->width;
    cy = nRow/2; // image center
    cx = nCol/2;
    //CV_IMAGE_ELEM为OpenCV定义的宏，用来读取图像的像素值，这一部分就是进行中心变换
    for( j = 0; j < cy; j++ ){
        for( i = 0; i < cx; i++ ){
            //中心化，将整体份成四块进行对角交换
            tmp13 = CV_IMAGE_ELEM( image_Re, double, j, i);
            CV_IMAGE_ELEM(image_Re, double, j, i) = CV_IMAGE_ELEM(image_Re, double, j+cy, i+cx);
            CV_IMAGE_ELEM(image_Re, double, j+cy, i+cx) = tmp13;
            tmp24 = CV_IMAGE_ELEM( image_Re, double, j, i+cx);
            CV_IMAGE_ELEM(image_Re, double, j, i+cx) = CV_IMAGE_ELEM(image_Re, double, j+cy, i);
            CV_IMAGE_ELEM(image_Re, double, j+cy, i) = tmp24;
        }
    }
    // normalnization the matrix to [0, 255]
    // [(f(x,y)-minVal)/(maxVal-minVal)]*255
    double minVal = 0, maxVal = 0;
    // Localize minimum and maximum values
    cvMinMaxLoc( image_Re, &minVal, &maxVal );
    // Normalize image (0 - 255) to be observed as an u8 image
    scale = 255/(maxVal - minVal);
    shift = -minVal * scale;
    cvConvertScale(image_Re, dst, scale, shift);
    cvReleaseImage(&image_Re);
    cvReleaseImage(&image_Im);
}

void DFTImage(const char * imagepath) {
    IplImage *src;  //源图像
    IplImage *Fourier;   //傅里叶系数
    IplImage *dst ;
    IplImage *ImageRe;
    IplImage *ImageIm;
    IplImage *Image;
    IplImage *ImageDst;
    double m, M;
    double scale;
    double shift;
    src = cvLoadImage(imagepath,0);   //加载源图像，第二个参数表示将输入的图片转为单信道
    Fourier = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 2);
    dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 2);
    ImageRe = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);
    ImageIm = cvCreateImage(cvGetSize(src), IPL_DEPTH_64F, 1);
    Image = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    ImageDst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    fft2(src, Fourier);                  //傅里叶变换
    fft2shift(Fourier, Image);          //中心化
    cvDFT(Fourier, dst, CV_DXT_INV_SCALE);//实现傅里叶逆变换，并对结果进行缩放
    cvSplit(dst, ImageRe, ImageIm, 0, 0);

    //对数组每个元素平方并存储在第二个参数中
    cvPow(ImageRe,ImageRe,2);
    cvPow(ImageIm,ImageIm,2);
    cvAdd(ImageRe,ImageIm,ImageRe,NULL);
    cvPow(ImageRe,ImageRe,0.5);
    cvMinMaxLoc(ImageRe,&m,&M,NULL,NULL);
    scale = 255/(M - m);
    shift = -m * scale;
    //将shift加在ImageRe各元素按比例缩放的结果上，存储为ImageDst
    cvConvertScale(ImageRe,ImageDst,scale,shift);
    
    cvNamedWindow("Original Image", 0);
    cvShowImage("Original Image", src);
    
    cvNamedWindow("Fourier Sectrum",0);
    cvShowImage("Fourier Sectrum", Image);
    
    cvNamedWindow("Fourier Inversion", 0);
    cvShowImage("Fourier Inversion",ImageDst);
    
    
    //释放图像
    cvWaitKey(10000);
    cvReleaseImage(&src);
    cvReleaseImage(&Image);
    cvReleaseImage(&ImageIm);
    cvReleaseImage(&ImageRe);
    cvReleaseImage(&Fourier);
    cvReleaseImage(&dst);
    cvReleaseImage(&ImageDst);
}