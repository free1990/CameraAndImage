#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include"Image_basic_function.h"
#include "DR_Question_Rect.h"
using namespace cv;

struct Fill_Missing_Question_Rect_Modle_Parament
{
	vector<cv::Rect> Modle_Parament_with_Top_Rect;
	vector<vector<cv::Rect>> Modle_Parament_with_Question_Rect;
};

class Fill_Missing_Question_Rect
{
public:
	vector<vector<cv::Point>> Question_Location_information;
	int Question_width;
	int Qustion_height;
	Mat Image_Question_Location;

private:
	
	vector<int>  Top_rect_number_information;
	vector<cv::Rect> Top_rect_Location_information;
	vector<int>  Question_number_information;

	vector<vector<float>> Template_Length;
    vector<vector<vector<float>>> Length_Scale_Left;
	vector<vector<vector<float>>> Length_Scale_Right;
	int exception_meaning;
	float scale_width;
	float scale_height;

private:
	vector<float> Current_Length;
public:
	Fill_Missing_Question_Rect();
	~Fill_Missing_Question_Rect();
	void Fill_The_Missing_Rect_by_Match_Model(Mat& Question_Rect_Missing_Image,vector<Fill_Missing_Question_Rect_Modle_Parament> &Stand_Model,
		                              vector<cv::Rect>& Top_Location_rect,vector<int>&Top_rect_information,vector<int>& Question_rect_information,int&exception_mean);

private:
    
	void InitiaLize_parament_model(Mat& Question_Rect_Missing_Image,vector<Fill_Missing_Question_Rect_Modle_Parament> &Stand_Model);
	void InitiaLize_basic_information( vector<cv::Rect>& Top_Location_rect,vector<int>&Top_rect_information,vector<int>& Question_rect_information);
	void Find_The_Missing_Point_by_linner_Line_With_Two_circle();
	void Fix_Virtual_Points_by_Real_Question_Points();
};