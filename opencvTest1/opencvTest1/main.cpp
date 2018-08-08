#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace cv;

int xLeft=0X7FFFFFFF;
int xRight=0;
int yUp=0X7FFFFFFF;
int yDown=0;

//大板轮廓
std::vector<cv::Point> DaBancontours;

std::vector<cv::Point> findBiggestContour(cv::Mat binary_image)
{
	//放多个轮廓，每个轮廓点的集合
	std::vector<std::vector<cv::Point>> contours;

	//hierarchy层次
	std::vector<cv::Vec4i> hierarchy;
	
	//面积最大变量
	int largest_area = 0;

	//面积最大的轮廓的下标
	int largest_contour_index = 0;
	
	//使用findContours函数找到轮廓
	cv::findContours(binary_image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	
	//
	for (int i = 0; i < contours.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour
		if (a > largest_area){
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
		}
	}
	
	std::cout<<contours[largest_contour_index].size()<<std::endl;
	
	int sizeIndex=contours[largest_contour_index].size()-1;

	
	for(int i=0;i<contours[largest_contour_index].size();i++){
		if(contours[largest_contour_index][i].x<xLeft){
			xLeft=contours[largest_contour_index][i].x;
		}
		if(contours[largest_contour_index][i].x>xRight){
			xRight=contours[largest_contour_index][i].x;
		}
		if(contours[largest_contour_index][i].y<yUp){
			yUp=contours[largest_contour_index][i].y;
		}
		if(contours[largest_contour_index][i].y>yDown){
			yDown=contours[largest_contour_index][i].y;
		}
	}

	//std::cout<<"xLeft::"<<xLeft<<std::endl;
	//std::cout<<"xRight::"<<xRight<<std::endl;
	//std::cout<<"yUp::"<<yUp<<std::endl;
	//std::cout<<"yDown::"<<yDown<<std::endl;

	DaBancontours=contours[largest_contour_index];

	return contours[largest_contour_index];
}

bool isInPolygon(Point point, std::vector<cv::Point> points, int n);

int main(){
	cv::Mat src = cv::imread("111.jpg", 1);
	cv::Mat result = src.clone();
	cv::Mat gray;
	cv::Mat edge;
	
	/*
	cvCvtColor是Opencv里的颜色空间转换函数，
	可以实现RGB颜色向HSV，HSI等颜色空间的转换，
	也可以转换为灰度图像，参数CV_RGB2GRAY是RGB到gray。
	*/
	cv::cvtColor(src, gray, CV_BGR2GRAY);

	cv::Mat binary;

	/*
	图像的二值化就是将图像上的像素点的灰度值设置为0或255，
	这样将使整个图像呈现出明显的黑白效果。
	在数字图像处理中，二值图像占有非常重要的地位，
	图像的二值化使图像中数据量大为减少，
	从而能凸显出目标的轮廓。
	OpenCV中提供了函数cv::threshold();
	*/
	blur( gray, edge, Size(3,3) );  
	cv::threshold(edge, binary, 100, 255, cv::THRESH_BINARY);
	//cv::imshow("binary", binary);
 
	std::vector< std::vector< cv::Point> > contours;
	std::vector< cv::Point>  biggest_contour;
	std::vector< std::vector< cv::Point> > temp_contours;
	cv::findContours(
		binary,
		contours,
		cv::noArray(),
		cv::RETR_LIST,
		cv::CHAIN_APPROX_SIMPLE
		);
	biggest_contour = findBiggestContour(binary);
	temp_contours.push_back(biggest_contour);
 
	//cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0),1);
	cv::drawContours(result, temp_contours, 0, cv::Scalar(0, 0, 255),3);
	//cv::drawContours(gray, contours, -1, cv::Scalar(0, 255, 0),1);
	//cv::drawContours(gray, temp_contours, 0, cv::Scalar(0, 0, 255),1);

	//绘制直线
	cv::Point Point1(xLeft,yUp),Point2(xRight,yUp),Point3(xRight,yDown),Point4(xLeft,yDown);
	cv::Point center((xLeft+xRight)/2,(yUp+yDown)/2);
	//cv::line(result,Point1,Point2,cv::Scalar(0, 0, 255),3,8,0);
	//cv::line(result,Point2,Point3,cv::Scalar(0, 0, 255),3,8,0);
	//cv::line(result,Point3,Point4,cv::Scalar(0, 0, 255),3,8,0);
	//cv::line(result,Point4,Point1,cv::Scalar(0, 0, 255),3,8,0);

	cv::Rect rect1(xLeft+28,yUp+10,150,200);
	cv::Rect rect2(xLeft+28+150,yUp+10,150,300);
	cv::Rect rect3(xLeft+28,yUp+10+200,50,300);
	cv::Rect rect4(xLeft+28+50,yUp+10+200,50,310);

	cv::rectangle(result,rect1,cv::Scalar(255,0,0),3,8,0);
	cv::rectangle(result,rect2,cv::Scalar(255,0,0),3,8,0);
	cv::rectangle(result,rect3,cv::Scalar(255,0,0),3,8,0);
	cv::rectangle(result,rect4,cv::Scalar(255,0,0),3,8,0);

	cv::circle(result,center,1,cv::Scalar(0,0,255),3,8,0);

	std::cout<<DaBancontours<<std::endl;

 
	//cv::imshow("src", src);
	//cv::imshow("gray", gray);
	//cv::imshow("edge", edge);
	//cv::imshow("binary", binary);
	cv::imshow("result", result);
	cv::waitKey(0);
 
	return 0;
}

//判断点是否在曲线内（验证成功）
bool isInPolygon(Point point, std::vector<cv::Point> points, int n) {
		int nCross = 0;
		for (int i = 0; i < n; i++) {
			Point p1 = points[i];
			Point p2 = points[(i + 1) % n];
			// 求解 y=p.y 与 p1 p2 的交点
			// p1p2 与 y=p0.y平行
			if (p1.y == p2.y)
				continue;
			// 交点在p1p2延长线上
			if (point.y < min(p1.y, p2.y))
				continue;
			// 交点在p1p2延长线上
			if (point.y >= max(p1.y, p2.y))
				continue;
			// 求交点的 X 坐标
			double x = (double) (point.y - p1.y) * (double) (p2.x - p1.x)
					/ (double) (p2.y - p1.y) + p1.x;
			// 只统计单边交点
			if (x > point.x)
				nCross++;
		}
		return (nCross % 2 == 1);
	}
