#pragma once
#include <opencv2/opencv.hpp>
#include "iostream"
#include "Compressive_Harr_Feature.h"
using namespace cv;



class  QR_Location_detect
{

public:
	vector<cv::Rect> QR_Bar_code_Location;
private:
	Compressive_Harr_Feature Harr_feature;
	 
public :
	QR_Location_detect();
    void QR_find_Location(Mat& input_Binary,bool Is_Dilate=false);

	void QR_find_Location_Rect_MOGRHY(Mat& input_Binary,bool Is_Dilate=false);
	~QR_Location_detect();
private:
	void  Fill_Pos_Neg_Vector();
	void  QR_find_methord_Morphology(Mat& input_Binary,bool Is_Dilate=false,bool Is_strict_judge_bar_code=false,bool IS_Rect_MPYPH=false);
	void QR_find_methord_Morphology_Rect_MOGRHY(Mat& input_Binary,bool Is_Dilate=false,bool Is_strict_judge_bar_code=false);
	void  QR_find_methord_three_back(Mat& input_Binary);
	float find_the_QR_max_area(CvSeq *&Barcode_contours,IplImage * &C_syle_image_Copy);
	void  find_the_Barcode_location(CvSeq *& Barcode_contours_save,float Max_like_QR,IplImage *& input_image,Mat& input_Binary,bool Is_strict_judge_bar_code=false);
	void  Set_The_around_point_To_255(Mat &Accluate_image_cpoy,int & x,int & y);
	bool  Find_Barcode_three_Location(IplImage *& input_image,CvRect & templerect,Mat& input_Binary);
	void  Calculate_The_Coffnicent(vector<float>& All_Rect_Image_Coffnicent,CvSeq*& Barcode_contours, Mat& Interst_Image);
};

