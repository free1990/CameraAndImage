
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "math.h"
#include <vector>
#include"Image_basic_function.h"
#include"FastSauvolaBinarizer.h"
#include "QR_Location_detect.h"
#include "DR_big_rect.h"
#include "DR_Question_Rect.h"
#include "Fill_Missing_Question_Rect.h"
using namespace std;




class Exam_Paper_Analysis // entrance class 
{

public:
	 vector<cv::Rect> Top_Location_rect;
	 vector<vector<cv::Point>> Question_Location_point;
	 vector<cv::Rect> QR_code_Location;


	 
	 Mat Fit_Change_image;
	 Mat Fit_Change_image_Enhancement;
	 Mat RGB_Scan_Image_Enhancement;
	 int Question_width;
	 int Question_height;
	 float Scale;

	 float Rotation_Angle;

	 bool Is_Enhace;
public :
	 vector<cv::Rect> Wrong_Top_Location_rect;
	 vector<vector<cv::Point>> Wrong_Question_Location_point;
	 int Wrong_Question_width;
	 int Wrong_Question_height;


public:
	 Exam_Paper_Analysis();
	 void  Paper_information_get(Mat &RGB_Sorce_input,vector<int> &Top_rect_information, vector<int>& Question_rect_information,bool front_page,bool Is_A3_style,int& exception_mean);

	 void  Fill_Question_Rect_By_Match_Modle(Mat& Miss_Question_Rect_Image,vector<Fill_Missing_Question_Rect_Modle_Parament>& Stand_Modle_Parament,bool front_page,int &exception_mean);

private:
	 void Top_QR_barcode_information_Get(Mat& _25percent_binary_image,bool front_page);
	 void Top_Rect_Information_Get(Mat & RGB_Sorce_input,Mat& RGB_Scale_Sorce_Image_Enhancement,Mat& _25percent_binary_image,vector<int> &Top_rect_information,bool Is_front_page,int &exception_mean );
	 void Question_information_get(vector<int> &Top_rect_information,vector<int> Question_rect_information,int& exception_mean);


private:

	  void Get_The_input_information(Mat& Miss_Question_Rect_Image,vector<Fill_Missing_Question_Rect_Modle_Parament>&  Stand_Modle_Parament,Mat& RGB_Sorce_Image , vector<int>& Top_rect_information,vector<int>& Question_rect_information);
	  void Question_information_get_With_Missing(vector<Fill_Missing_Question_Rect_Modle_Parament>& Stand_Modle_Parament,vector<int>& Top_rect_information,vector<int>& Question_rect_information ,int& exception_mean);

};

