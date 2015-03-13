#pragma once
#include <opencv2/opencv.hpp>
#include "iostream"
#include "Image_basic_function.h"
#include "Globle_Otsu_Binarizer.h"
#include "FastSauvolaBinarizer.h"

using namespace cv;
class Image_Enhancement_Contrast
{

private:
	float Thousold_Gray;
	float Thousold_Blue; 
	float Thousold_Green; 
	float Thousold_Red;
private: 
	float Blue_Max_Background_value;
	float Green_Max_Background_value;
	float Red_Max_Background_value;

	float Blue_percent10_upper;
	float Green_percent10_upper;
	float Red_percent10_upper;
public:
	bool Is_Enhancement;


public :
	
    Image_Enhancement_Contrast();
	void Scan_Image_Enhancement(Mat& input ,Mat& ouyput);
	void Fix_Photo_Image_Enhancement(Mat& input ,Mat& ouyput);
	void Phone_Photo_Image_Enhancement(Mat& input ,Mat& ouyput);

private:

	void Set_Background_With_MaxValue(Mat& input,Mat& output,float Thousold_Value,float Percent10_upper);
	void Set_Background_By_Binary_Image(Mat & input ,Mat& binary ,Mat& output);
	void Sobel_edge_detection(Mat& input ,Mat& output);
	Mat histeq(Mat& in);
	void Sharp_Image(Mat& input,Mat& output );

};