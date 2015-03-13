
#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "Compressive_Harr_Feature.h"
using namespace cv;



struct Point_SimlarParament
{   
	cv::Point pt;
	float simalar_Parament;
	Point_SimlarParament(cv::Point point,float simlar)
	{
		pt=point;
		simalar_Parament=simlar;
	}
};


class DR_Question_Rect
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

	int exception_meaning;
	float scale_width;
	float scale_height;

	vector<vector<cv::Point>>  Temp_Real_points;
public:
	vector<vector<cv::Point>> Wrong_Question_Location_information;
	int Wrong_Question_width;
	int Wrong_Qustion_height;
   
public:

	DR_Question_Rect();

	// normal interface for users 
    void Question_Rect_Detect(Mat &Fit_Change_image,vector<cv::Rect>&Top_Location_rect,vector<int >&Top_rect_information,vector<int>Question_rect_information,int &exception_mean);
	 
	//	Missing Question Rect user interface 

	void Missing_Rect_Points_fixed(Mat &Fit_Change_image,vector<vector<cv::Point>>&Had_vretual_Question_Points,vector<cv::Rect>&Top_Location_rect,vector<int >&Top_rect_information,vector<int>Question_rect_information,int &exception_mean);
	~DR_Question_Rect();
private:
	void Initialize(Mat &Fit_Change_image,vector<cv::Rect>&Top_Location_rect,vector<int >&Top_rect_information,vector<int>Question_rect_information,int &exception_mean);
	
	// search ways of find the Question rect in the scale exam paper  
	void Normal_Search_Qustion_Rect();
	void Abnormal_normal_hem_line_Search_Qustion_Rect();
	void Abnormal_abnormal_hem_line_Search_Qustion_Rect();
	void Abnormal_handle_dirty_Search_Qustion_Rect(bool& left ,bool & right);
	void Abnormal_One_edge_true_Qustion_Rect(bool& left ,bool& right);
	cv::Rect Interst_Rect_Back(int &index);
	void Get_the_complex_information_with_Rect_Binary(int &index ,cv::Rect & Interst_Question_Rect,Mat & Image_Question_Location ,Mat &Image_interst_ROI_Gray,Mat &Image_interst_ROI_Binary) ;
	void Box_Acculate_Get(Mat & Image_interst_ROI_Binary,Mat &Acculate_Box_image_based_Question_WH);
	void Width_Height_box_mapping(Mat &Intergral_image,Mat &Acculate_Box_image_based_Question_WH);
	void Seek_The_best_Location(int &j,cv::Rect & Interst_Question_Rect,Mat &Acculate_Box_image_based_Question_WH);
	void Seek_The_best_Location_by_Position_limit(vector<vector<cv::Point>> &Had_vretual_Question_Points,int &j,cv::Rect & Interst_Question_Rect,Mat &Acculate_Box_image_based_Question_WH);
	void Find_Question_with_Zero_Min_points(int &index,Mat &Accluate_image_cpoy,cv::Rect & set_off_rect,bool Whether_find_more_points=false);
	void Find_Question_with_Zero_Min_points_Be_Mapping(int &index,Mat &Accluate_image_cpoy,cv::Rect & set_off_rect,bool Whether_find_more_points=false);
	void Find_Question_with_Zero_Min_points_additional_by_model(int &index,Mat &Accluate_image_cpoy_Two,cv::Rect &Interst_Question_Rect,float &inner_k,float &inner_b);

	void Find_Question_with_Zero_Min_points_by_Position_limit(vector<vector<cv::Point>> &Had_vretual_Question_Points,int& index,Mat& Accluate_image_cpoy,cv::Rect & Interst_Question_Rect,bool Whether_find_more_points=false);
	void Set_The_around_point_To_255(Mat &Accluate_image_cpoy,int & x,int & y);
	void Simple_check_with_RANSAC_To_Question_rect(int & index );
	void Deep_check_with_RANSAC_To_Question_rect(Mat & lin_message_index,int &index);

	void Deep_check_with_RANSAC_To_Question_rect_by_hem_drity(Mat & lin_message_index,int &index);
	void Get_model_by_Max_innernumber(Mat& lin_message_index,float& inner_k,float& inner_b);
	int  Get_model_by_Max_innernumber_Points(Mat& lin_message_index,float& inner_k,float& inner_b);
	void Check_Question_rect_Location();
	void Doing_sort_by_Y_Location();
	void Clear_relation_parament();
	void Relationship_Information_Binary(cv::Rect & Interst_Question_Rect,Mat & Image_interst_ROI ,Mat &Image_interst_ROI_Gray,Mat &Image_interst_ROI_Binary);
    void Set_The_aangle_start_And_angle_end(int& j,int & angle_start,int &angle_end);
	void Find_line(cv::Point &pt1,cv::Point& pt2,cv::Point &pt3,cv::Point& pt4,Mat &The_Rho_space,int &rhomax,Mat&Image_interst_ROI);
	void Set_Point_Round_To_Zero(Mat &The_Rho_space,cv::Point& MaxLocation);
	void Reverse_Pixs_With_Line(Mat& interest_ROI_binary,cv::Point& pt1,cv::Point&pt2,cv::Point&pt3,cv::Point& pt4);
	void Check_Question_rect_Location_with_BOOL(bool& left ,bool& right);
	void Seek_The_best_Location_With_Classifer(int&j,cv::Rect &Interst_Question_Rect,Mat &Gray_image,Mat &Image_interst_ROI_Binary,Mat &Acculate_Box_image_based_Question_WH,Compressive_Harr_Feature& Harr_featue);
	void Find_Question_with_Simlar_parament(int& j,Mat& Image_interst_ROI_Gray,Mat&Image_interst_ROI_Binary,Mat&Accluate_image_cpoy,cv::Rect &Interst_Question_Rect,Compressive_Harr_Feature& Harr_featue);
	void Rect_similar_information_get(Compressive_Harr_Feature& Harr_featue,Mat &Accluate_image_cpoy,Mat &Whole_Gray,cv::Rect& set_off_rect ,cv::Point & Temp_Location,vector<Point_SimlarParament>&More_Rect_points_Together,int& x ,int &y );
	void Fill_Rect_Locatin_by_SimlarParament(int & index ,vector<Point_SimlarParament> &More_Rect_points_Together);
	void Doing_sort_by_Parament_Simlar(int & index ,vector<Point_SimlarParament> &More_Rect_points_Together);
	void Get_Pos_Neg_Vector( Compressive_Harr_Feature &Harr_featue);
	void Mapping_Methord_To_Find_Qusetion_Rect(int& Map_index,int& Be_Map_index,Mat& Map_image,Mat& Be_Map_Image,cv::Rect& Map_Rect_set_off,cv::Rect& Be_Map_Rect_set_off,bool& Is_Matching);
	void Seek_Question_rect_Location_With_Be_Maping_Image(int& Be_Map_index,Mat & Be_Map_Image,cv::Rect& Be_Map_Rect_set_off);
	void Using_model_To_delete_Points(int & index,float &inner_k,float& inner_b); 	
	void Mapping_Corresponding_Search(int& Map_index,int& Be_Map_index);
	void Making_check_With_The_Corresponding_Points(int& Map_index,int& Be_Map_index,bool& Is_Matching);
	void Doing_sort_by_Y_Location_Not_Whole(int &k);
	void Save_The_Normal_detected_Rect_points(bool& left,bool& right);
	void Get_The_Have_save_Points(int& j);
	void Clear_Corresponding_Question_Locarion_Points(int& j);

	// missing Question Rect using for fixed the had detected vritual Question Rect 
	void Find_The_Exist_Question_Rect(vector<vector<cv::Point>>&Had_vretual_Question_Points);
	void RANSAC_Alogrithem_To_Separarte_Out_Points(int& index);
	void Deep_check_with_RANSAC_To_Question_rect_by_Limit_Condition(Mat& lin_message_index,int &index);
	void Set_The_Out_points_To_Zero(int& index,float& inner_K ,float& inner_b);
	void Last_Fixed_The_Virtual_Points(Mat &Fit_Change_image,vector<vector<cv::Point>>& Had_vretual_Question_Points);
	void Get_Pos_Neg_Vector_Sorce_Temple(Compressive_Harr_Feature& Harr_featue);
	float Get_The_judgement_cofficient_by_Harr(cv::Rect& set_off_rect, cv::Point& min_loc,Compressive_Harr_Feature &Harr_featue);
	int Get_The_inner_Points(int& index);
	void Store_The_Had_Dtected_Question_Points();
};