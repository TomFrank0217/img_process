#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "matrix.h"
#include "features.h"
#include "kernels.h"
#include "layer.h"

using namespace std;
using namespace cv;

void f();
void write_y(string img_name);
void test(int* x){
	int n = sizeof(x) / sizeof(x[0]);
	std::cout << "sizeof(x)=" << sizeof(x) << endl;
	std::cout << "sizeof(x[0])=" << sizeof(x[0]) << endl;
	cout << "n=" << n << endl;
}
int main(){
	//write_y("data//lena.jpg");
	Mat lena = imread("data//lena.jpg", 0);
	cout << lena.rows << " " << lena.cols << " " << lena.channels() << endl;
	Mat bound;
	//cv::Sobel(lena, bound, -1, 1, 1, 3);
	//imshow("bound", bound);
	//waitKey(100);
	//imwrite("data/lena_bound.jpg", bound);
	
	//lena_.show();
	Mat mat_t(lena.size(), 0);
	for (int i = 1; i < mat_t.rows - 1; ++i){
		for (int j = 1; j < mat_t.cols - 1; ++j){
			//char x = int(lena_.mp_matrixes[0].mp_data[i*lena_.m_cols + j]);
			//mat_t.at<uchar>(i, j) = x;
			//mat_t.at<uchar>(i, j) = (lena_.mp_matrixes[0].mp_data[i*lena_.m_cols + j]);
			//int x1 = lena.at<uchar>(i - 1, j + 1);
			//int x2 = lena.at<uchar>(i    , j + 1);
			//int x3 = lena.at<uchar>(i + 1, j + 1);
			//int y1 = lena.at<uchar>(i - 1, j - 1);
			//int y2 = lena.at<uchar>(i    , j - 1);
			//int y3 = lena.at<uchar>(i + 1, j - 1);

			int x1 = lena.at<uchar>(i + 1, j - 1);
			int x2 = lena.at<uchar>(i + 1, j    );
			int x3 = lena.at<uchar>(i + 1, j + 1);
			int y1 = lena.at<uchar>(i - 1, j - 1);
			int y2 = lena.at<uchar>(i - 1, j    );
			int y3 = lena.at<uchar>(i - 1, j + 1);
			mat_t.at<uchar>(i, j) = abs(0.25*(x1 + 2 * x2 + x3 - y1 - 2 * y2 - y3));
		}
	}
	imwrite("data//My_sobel_y.jpg",mat_t);
	//cv::Sobel(lena, bound, -1, 1, 0, 3);
	//imwrite("data//opencv_sobel_x.jpg", bound);
	//double ks[] = {
	//	 -1, 0, 1,
	//	- 2, 0, 2,
	//	- 1, 0, 1
	//};
	double ks[] = {
		-1, -2, -1,
		 0,  0,  0,
		 1,  2,  1
	};
	for (int i = 0; i < 9; ++i){
		ks[i] *= 0.25;
	}
	kernels kers(1, 3, 3, 1, ks);
	//kers.show();
	layer ly;
	//ly.m_padding_mode = SAME_PADDING;
	ly.m_kers = kers;
	//ly.m_kers.show();
	matrix mat_img;
	img lena_(lena, 0, 1);
	ly.m_fts = lena_;
	//ly.reshape(lena_, mat_img);
	matrix mat_kers;
	ly.reshape(kers, mat_kers);
	mat_kers.show();
	matrix out = ly.conv();
	img result;
	ly.reshape(out, result);
	Mat mat_result(Size(result.m_rows, result.m_cols), 0);
	for (int i = 0; i < result.m_rows; ++i){
		for (int j = 0; j < result.m_cols; ++j){
			//char x = int(lena_.mp_matrixes[0].mp_data[i*lena_.m_cols + j]);
			//mat_t.at<uchar>(i, j) = x;
			mat_result.at<uchar>(i, j) = ABS(result.mp_matrixes[0].mp_data[i*result.m_cols + j]);
			//mat_result.at<uchar>(i, j) = (result.mp_matrixes[0].mp_data[i*result.m_cols + j]);
		}
	}
	imshow("tmp", mat_result);
	waitKey(1000);
	imwrite("data//conv_sobel_y.jpg", mat_result);
	//lena_.show(SHOW_IMAGE_INITAIL_VALUE);
	return 0;
}

void write_y(string img_name){
	Mat image = imread(img_name, 0);
	imwrite(img_name.substr(0, img_name.length() - 4) + "_y" + img_name.substr(img_name.length() - 4, 4), image);

}
void f(){
	Mat lena = imread("data//lena.jpg");
	imshow("lena", lena);
	cout << lena.rows << " " << lena.cols << " " << lena.channels() << endl;
	//namedWindow("lena", 1);
	//while (waitKey(1000) == 27){}
	cout << waitKey(5000) << endl;
	cout << "Hello,world!\n";
}