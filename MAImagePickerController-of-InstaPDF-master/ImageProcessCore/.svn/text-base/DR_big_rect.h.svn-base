#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "Compressive_Harr_Feature.h"
using namespace cv;



struct Rect_Area_Com_Haar_coefficient

{
	cv::Rect rect ;
	float area;
	float Com_Haar_coefficient_Centre;
	float Com_Haar_coefficient_Whole;
};




class DR_big_rect
{

public :
	vector<cv::Rect> candidate_rect;
	int number_big_rect;
	Compressive_Harr_Feature Haar_feature;
	Mat Rotation_frist;
	Mat Rotation_Second;
	Mat Rotation_frist_Enhancement;
	Mat Rotation_Second_Enhancement;
	int Question_width;
	int Question_height;

	float angle_Whole;
private:
	bool Frist_Detected_Location;
	bool Is_front_page;
	vector<cv::Rect>  Not_whole_top_rect;
public:
	vector<cv::Rect>  Wrong_candidate_rect;
	Mat Wrong_fit_Source;
	Mat Wrong_fit_Source_Ehancement;
 
public:
	 DR_big_rect();
	 void Top_bigrect_detect(Mat& input_sorce,Mat& RGB_Scale_Sorce_Image_Enhancement,Mat& input_first_binary,vector<int> &top_rect_information,bool Is_front_page,	 vector<cv::Rect> &QR_code_Location,int& expection_number);
    ~DR_big_rect();

private:
	// four deals to image  ,but there is exist perior  ,from the top to bottem  the perior is always down   
	void normal_search(Mat& input_sorce,bool Is_front_page,vector<cv::Rect>& QR_code_Location,int &expection_number);
	void Two_morphology_search(Mat& input_sorce,bool Is_front_page,vector<cv::Rect>& QR_code_Location,int &expection_number);
	void Fill_hole_search(Mat& input_sorce,bool Is_front_page,vector<cv::Rect>& QR_code_Location,int &expection_number);
	void One_morphology_search(Mat& input_sorce,bool Is_front_page,vector<cv::Rect>& QR_code_Location,int &expection_number);

	void All_rect_number(vector<int> &top_rect_information);
	void Detect_the_top_rect_accopulish(CvSeq *&Top_rect_contour,CvSeq *& Top_rect_contour_save,vector<cv::Rect>& QR_code_Location,Mat & Binary_15percent_input,Mat &Binary_15percent_morphology_input,int &expection_number);
    float find_the_like_Max_area(CvSeq *& Top_rect_contour,vector<cv::Rect>& QR_code_Location,Mat &  Binary_15percent_input,Mat & Binary_15percent_morphology_input);
	void Find_the_like_Rect(CvSeq *& Top_rect_contour_save,vector<cv::Rect>& QR_code_Location,Mat &   Binary_15percent_input,Mat & Binary_15percent_morphology_input,float max_area,vector<Rect_Area_Com_Haar_coefficient>& temple_together_parament);
	void basic_contours_information_get(CvSeq *& contour,float& circlearea,float &diffthrsould0,float& diffthrsould1, CvRect &templerect,CvBox2D& box);
	bool  Whether_Location_the_QR_position(bool Is_front_page,vector<cv::Rect>& QR_code_Location,CvRect templerect) ;
	void Get_sturctor_meaning(Mat &Binary_15percent_input,vector<float>&Harr_feature_temple,float &coff_Centre,float& coff_Whole,CvRect &templerect);
	void Doing_Sort(vector<Rect_Area_Com_Haar_coefficient>& temple_together_parament);
	void Doing_Check_by_width_height(int &expection_number);
	void Doing_Check_by_X_Y(int &expection_number);
	void Doing_Sort_by_X();
	void Doing_Check_by_X(int &expection_number); 
	void Doing_Check_by_Y(int &expection_number);
	void Fill_Image_Get(Mat& Binary_15percent_input,Mat&  fill_hole_Based_input);
	void Fill_contors_real_accompulish(CvSeq*& Top_rect_contour,CvSeq*&  Top_rect_contour_save,IplImage *& Binary_15percent_reverse_IplImage_Save);
	void Process_branch_trying(Mat &input_sorce,bool Is_front_page,vector<cv::Rect>& QR_code_Location,int &expection_number);
	float Get_the_rotation_angle();
	void Making_Clear_parament();


};