#pragma once
#include <opencv2/opencv.hpp>
#include "iostream"
using namespace cv;

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>

class Image_basic_function
{

public:
     static void  Set_Image_To_255_CV_8U(Mat & input);// 
	 static void  Set_Image_To_0_CV_8U(Mat & input);
	 static void  Set_Image_To_0_CV_8U_3Channel(Mat & input);
	 static void  Show_Image(Mat & input );
    static void  Copy_Image(const Mat & input ,Mat& out_put,cv::Rect& interest_rect ,bool input_bigger_than_out_put=true);
	 static void  Value_Scale_Change(Mat &mean__square,int windowsx=29 ,int windowsy=29);
	 static void  add_own(Mat &left_top_image,Mat &right_bottem_image,Mat &temple_add1);
	 static void  subtract_own(Mat &input1,Mat &input2,Mat &output);
	 static void  multiply_own(Mat &mean,Mat &mean_multi);
	 static void  multiply_8to32(const Mat & sourseimage,Mat & Mul_image); //calculate the 
	 static void  Set_Image_To_0_CV_32F(Mat & input);
	 static void  subtract_own_32_32_64(Mat &input1,Mat &input2,Mat &output);// 32 32 64
	 static void  Reverse_image(Mat & input);// 
	 static void  find_contour_with_C_style(IplImage* &Binary_input,CvSeq* &contours,CvMemStorage* &storage);
	 static void  find_contour_with_C_style_list(IplImage* &Binary_input,CvSeq* &contours,CvMemStorage* &storage);

	 static void  Mat_deep_copy_to_Iplimage(Mat &Bar_code_contain_image,IplImage *&C_syle_image);
	 static void  IplImage_deep_copy_to_Mat(IplImage *&input ,Mat& output );


	 static void Mat_deep_copy_to_IplImage(Mat& input ,IplImage* & output);

	 static void  C_show_image(IplImage * & input);
	 static void  Draw_contours(CvSeq* &contours,IplImage* & input );
	 static float White_pixls_of_input_image(IplImage * & C_syle_image_Copy, CvRect &templerect);
	 static float Black_pixls_of_input_image_Mat(Mat &input_Mat, CvRect &templerect);
	 static void  find_contour_with_C_style_additional_innerContour(IplImage* & Binary_15percent_reverse_IplImage,CvSeq* & Top_rect_contour,CvMemStorage* & Top_rect_contour_storage);
	 static void  Rotation(Mat& input_sorce,Mat& Rotation_frist,float angle);
	 static int   Static_Calculate(Mat &Image_interst_ROI,float& H_max,float& H_min,float& S_max,float& S_min,float&V_max,float&V_min);
	 static void  Mat_deep_copy_to_Iplimage_RGB(Mat & Image_interst_ROI,IplImage *&Image_interst_ROI_C);
	 static void  Set_Bule_Gray_to_White(Mat & input );
	 static	Mat   Create_space_with_hough(Mat &Image_interst_ROI_Binary,int &angle_start ,int& angle_end,int& rho_max);
	 static void  Set_32F_To_Zero(Mat &input);
    static void  Show_line_in_image(cv::Point& pt1 ,cv::Point& pt2 ,Mat & image);
	 static void  Show_Image_Wait_Key_20(Mat & input );

	 // extern  interface to Project ---bt the .net to call
	  

	 static float Black_Points_Get(Mat& input);
	 static float Red_Points_Get(Mat& input,bool Is_Enhancement);
	 static float Red_Together_Points_Get(Mat& input);


	 // exten interface using function  
	 static void  Get_Red_reflect_image(IplImage*& output,IplImage*& red_reflect);
	 static void  Set_8U_IplImage_To_zero(IplImage* & BIgger_image);
	 static void  readImageSequenceFiles(char* imgFilePath,vector <string> &imgNames);


	 // usefule interfance 
	 static void ImgRotate_ownSelf(Mat& imgIn, float& theta, cv::Mat& imgOut);
     static void Sharp_To_Image(Mat& input ,Mat & output);
     static void Write_message_To_Text(vector<cv::Rect>& Top_Rect_Infoemation ,vector<vector<cv::Point>>);
	 static float Distance_Between_Points(cv::Point& pt1,cv::Point& pt2);
	 static float Distance_Between_Location(float x1,float y1,float x2,float y2);
	 static int circle_circle_intersection(float x0, float y0, float r0,float x1, float y1, float r1,float *xi, float *yi,float *xi_prime, float *yi_prime);

	 // Recognize The choice question and  return the desicion the had bolted options 


	 // Connect Two  Image together 

	 static void Connect_Two_Image_vertical(Mat& input1 ,Mat& input2,Mat& output);

}; 
