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

//�������
std::vector<cv::Point> DaBancontours;

std::vector<cv::Point> findBiggestContour(cv::Mat binary_image)
{
	//�Ŷ��������ÿ��������ļ���
	std::vector<std::vector<cv::Point>> contours;

	//hierarchy���
	std::vector<cv::Vec4i> hierarchy;
	
	//���������
	int largest_area = 0;

	//��������������±�
	int largest_contour_index = 0;
	
	//ʹ��findContours�����ҵ�����
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
	cvCvtColor��Opencv�����ɫ�ռ�ת��������
	����ʵ��RGB��ɫ��HSV��HSI����ɫ�ռ��ת����
	Ҳ����ת��Ϊ�Ҷ�ͼ�񣬲���CV_RGB2GRAY��RGB��gray��
	*/
	cv::cvtColor(src, gray, CV_BGR2GRAY);

	cv::Mat binary;

	/*
	ͼ��Ķ�ֵ�����ǽ�ͼ���ϵ����ص�ĻҶ�ֵ����Ϊ0��255��
	������ʹ����ͼ����ֳ����Եĺڰ�Ч����
	������ͼ�����У���ֵͼ��ռ�зǳ���Ҫ�ĵ�λ��
	ͼ��Ķ�ֵ��ʹͼ������������Ϊ���٣�
	�Ӷ���͹�Գ�Ŀ���������
	OpenCV���ṩ�˺���cv::threshold();
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

	//����ֱ��
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

//�жϵ��Ƿ��������ڣ���֤�ɹ���
bool isInPolygon(Point point, std::vector<cv::Point> points, int n) {
		int nCross = 0;
		for (int i = 0; i < n; i++) {
			Point p1 = points[i];
			Point p2 = points[(i + 1) % n];
			// ��� y=p.y �� p1 p2 �Ľ���
			// p1p2 �� y=p0.yƽ��
			if (p1.y == p2.y)
				continue;
			// ������p1p2�ӳ�����
			if (point.y < min(p1.y, p2.y))
				continue;
			// ������p1p2�ӳ�����
			if (point.y >= max(p1.y, p2.y))
				continue;
			// �󽻵�� X ����
			double x = (double) (point.y - p1.y) * (double) (p2.x - p1.x)
					/ (double) (p2.y - p1.y) + p1.x;
			// ֻͳ�Ƶ��߽���
			if (x > point.x)
				nCross++;
		}
		return (nCross % 2 == 1);
	}
