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
#include"Exam_Paper_Analysis.h"
#include "Image_Enhancement_Contrast.h"
using namespace std;



Exam_Paper_Analysis:: Exam_Paper_Analysis():Scale(0.55F),Rotation_Angle(0.0F)
{
	
	


}
// accomuplish the real part 
void Exam_Paper_Analysis::Top_QR_barcode_information_Get(Mat& input,bool front_page)
{
   // the input image is the 25% percent of the scale image 

   Rect  temple_rect(0,0,0,0);
   if (front_page==false)
   {
	   QR_code_Location.push_back(temple_rect);
	   QR_code_Location.push_back(temple_rect);
   }
   if (front_page==true)
   {
     QR_Location_detect *point =new QR_Location_detect();
	 point->QR_find_Location(input);
	 for (int j=0;j<point->QR_Bar_code_Location.size();j++)
	 {
		 QR_code_Location.push_back(point->QR_Bar_code_Location[j]);
	 }
	 delete point;
   }

}
void Exam_Paper_Analysis::Top_Rect_Information_Get(Mat &RGB_Sorce_input,Mat& RGB_Scale_Sorce_Image_Enhancement,Mat& _25percent_binary_image,vector<int> &Top_rect_information,bool Is_front_page,int& exception_mean)
{    
	// it has a judge here  if the front page is true and the QR_code_Location detected is true ,the location will useful in the top rect information get 
	// in the former vision the prercent of the whole image is 15% ,project the _25percent_binary_image is 60% 
	  DR_big_rect *point =new DR_big_rect();
      point->Top_bigrect_detect(RGB_Sorce_input,RGB_Scale_Sorce_Image_Enhancement,_25percent_binary_image,Top_rect_information,Is_front_page,QR_code_Location,exception_mean);
	  if (exception_mean==-1)
	  {
		  for (int j=0;j<point->candidate_rect.size();j++)
		  {
			  Top_Location_rect.push_back(point->candidate_rect[j]);
		  }
		  Fit_Change_image=point->Rotation_Second.clone();
		  Fit_Change_image_Enhancement=point->Rotation_Second_Enhancement.clone();
		  Rotation_Angle=point->angle_Whole;
	  }
	  if (exception_mean==1)
	  {
		for (int j=0;j<point->Wrong_candidate_rect.size();j++)
		{
			Wrong_Top_Location_rect.push_back(point->Wrong_candidate_rect[j]);
		}
	    Fit_Change_image=RGB_Sorce_input.clone();
		Fit_Change_image_Enhancement=RGB_Scale_Sorce_Image_Enhancement.clone();
	  }
	  delete point;

	  if (exception_mean==1)
	  {
	    return ;
	  }
	  //Image_basic_function::Show_Image(Fit_Change_image);
}

void Exam_Paper_Analysis::Question_information_get(vector<int> &Top_rect_information,vector<int> Question_rect_information,int& exception_mean)
{  

	Question_Location_point=vector<vector<Point>>(Question_rect_information.size(),vector<Point>());
	Wrong_Question_Location_point=vector<vector<Point>>(Question_rect_information.size(),vector<Point>());
	DR_Question_Rect *point =new DR_Question_Rect();
	//Image_basic_function::Show_Image(Fit_Change_image);
	point->Question_Rect_Detect(Fit_Change_image,Top_Location_rect,Top_rect_information,Question_rect_information,exception_mean);
	if (exception_mean==-1)
	{   
		Question_width=point->Question_width;
		Question_height=point->Qustion_height;
		for (int i=0;i<Question_rect_information.size();i++)
		{
		      for (int j=0;j<Question_rect_information[i];j++)
			  {   
				  Point ptt=point->Question_Location_information[i][j];
				  Question_Location_point[i].push_back(point->Question_Location_information[i][j]);
			  }
		}
	
	}
	if(exception_mean==2)
	{
		Wrong_Question_width=point->Wrong_Question_width;
		Wrong_Question_height=point->Wrong_Qustion_height;
		for (int i=0;i<Wrong_Question_Location_point.size();i++)
		{    
			if (Question_rect_information[i]!=0)
			{
				for(int j=0;j<point->Question_Location_information[i].size();j++)
				{
					Wrong_Question_Location_point[i].push_back(point->Question_Location_information[i][j]);
				}
			}
		}
	}
	delete point;
	if (exception_mean==2)
	{   
	    return ;
	}
}

void Exam_Paper_Analysis::Get_The_input_information(Mat& Miss_Question_Rect_Image,vector<Fill_Missing_Question_Rect_Modle_Parament>&  Stand_Modle_Parament,Mat& RGB_Sorce_Image ,vector<int>& Top_rect_information,vector<int>& Question_rect_information)
{   
	// Fill the Fit_Change_image Space 
	Fit_Change_image=Miss_Question_Rect_Image.clone();
	// make a deep copy from Miss_Question_Rect_Image to RGB_Sorce_Image 
	RGB_Sorce_Image=Miss_Question_Rect_Image.clone();

	// Get the uniform style to accomulish the user interfacer 
	if (Stand_Modle_Parament.size()>0)
	{
		for(int index=0;index<Stand_Modle_Parament[0].Modle_Parament_with_Top_Rect.size();index++)
		{
			Top_rect_information.push_back(1);
		}
        
		for (int index=0;index<Stand_Modle_Parament[0].Modle_Parament_with_Question_Rect.size();index++)
		{
			Question_rect_information.push_back(Stand_Modle_Parament[0].Modle_Parament_with_Question_Rect[index].size());
		}
	}
	else
	{
	    return;
	}
}


 void Exam_Paper_Analysis::Question_information_get_With_Missing(vector<Fill_Missing_Question_Rect_Modle_Parament>& Stand_Modle_Parament,
	                                                              vector<int>& Top_rect_information,vector<int>& Question_rect_information ,int& exception_mean)
 {  
	 // malloc the Question Rect Location space ,here is just New the head number 
     Question_Location_point=vector<vector<Point>>(Question_rect_information.size(),vector<Point>());
	
	 Fill_Missing_Question_Rect * point =new Fill_Missing_Question_Rect();
	 point->Fill_The_Missing_Rect_by_Match_Model(Fit_Change_image,Stand_Modle_Parament,Top_Location_rect,Top_rect_information,Question_rect_information,exception_mean);
	 if (exception_mean==-1)
	 {	
		 Fit_Change_image=point->Image_Question_Location.clone();
		 Question_width=point->Question_width;
		 Question_height=point->Qustion_height;
		for (int i=0;i<Question_rect_information.size();i++)
		{
		      for (int j=0;j<Question_rect_information[i];j++)
			  {   
				  Point ptt=point->Question_Location_information[i][j];
				  Question_Location_point[i].push_back(point->Question_Location_information[i][j]);
			  }
		}
	 }
	 delete point;
	 if(exception_mean==2)
	 {
	    return ;
	 }
 }

void Exam_Paper_Analysis::Paper_information_get(Mat &RGB_Sorce_input,vector<int> &Top_rect_information,vector<int>& Question_rect_information,bool Is_front_page,bool Is_A3_style,int& exception_mean) // it may need primer information of the test_papre  
{   
	exception_mean = -1;
	try
	{   
		// Enhacement the Scane image 
		Image_Enhancement_Contrast* point_E =new Image_Enhancement_Contrast();
		point_E->Scan_Image_Enhancement(RGB_Sorce_input,RGB_Scan_Image_Enhancement);
		Is_Enhace=point_E->Is_Enhancement;
		delete point_E ;
		Mat RGB_Scale_Sorce_Image,RGB_Scale_Sorce_Image_Enhancement; 
		resize(RGB_Sorce_input,RGB_Scale_Sorce_Image,Size(RGB_Scan_Image_Enhancement.cols*Scale,RGB_Scan_Image_Enhancement.rows*Scale),0,0);  // scale to 40% dst image 
		resize(RGB_Scan_Image_Enhancement,RGB_Scale_Sorce_Image_Enhancement,Size(RGB_Scan_Image_Enhancement.cols*Scale,RGB_Scan_Image_Enhancement.rows*Scale));  // scale to 40% dst Enhancement image 

		//Make a test 
		//Image_basic_function::Show_Image(RGB_Scale_Sorce_Image );  // imshow the scale resize image 
		Rect  interst_ROI(0,0,RGB_Scale_Sorce_Image.cols,RGB_Scale_Sorce_Image.rows*0.25); // get the 15% scale fo the sorce image 
		Mat RGB_top_Barcode;RGB_top_Barcode.create(RGB_Scale_Sorce_Image.rows*0.25,RGB_Scale_Sorce_Image.cols,CV_8UC3);
		Image_basic_function::Copy_Image(RGB_Scale_Sorce_Image,RGB_top_Barcode,interst_ROI);
		Mat Gray_Top,Binary_Top;
		cvtColor(RGB_top_Barcode, Gray_Top, CV_RGB2GRAY);  
		Binary_Top.create(Gray_Top.rows,Gray_Top.cols,CV_8UC1);
		// making the top image to binary image
		FastSauvolaBinarizer * point=new FastSauvolaBinarizer();
		point->Binary_way(Gray_Top,Binary_Top);
		delete point;
		//Image_basic_function::Show_Image(Binary_Top);
		// get the bar code location  
		Top_QR_barcode_information_Get(Binary_Top,false);

		// get the top rect location  information 
		Top_Rect_Information_Get(RGB_Scale_Sorce_Image,RGB_Scale_Sorce_Image_Enhancement,Binary_Top,Top_rect_information,Is_front_page,exception_mean);

 		if (exception_mean==1)
		{
		  return; // it he programe is enter the language ,the top rect persent that there is a exception in the top rect detected ,and means the rect is missing 
		}
		// Get the Question rect Location information in the exam paper 
		Question_information_get(Top_rect_information,Question_rect_information,exception_mean);
	}
	catch(...)
	{
	  exception_mean=3;
	  return;
	}
}


 void Exam_Paper_Analysis::Fill_Question_Rect_By_Match_Modle(Mat& RGB_Sorce_input,vector<Fill_Missing_Question_Rect_Modle_Parament>& Stand_Modle_Parament,
                                                                                                                            bool Is_front_page,int &exception_mean)
 {   

	exception_mean = -1;
	try
	{   
		// Enhacement the Scane image 
		Image_Enhancement_Contrast* point_E =new Image_Enhancement_Contrast();
		point_E->Scan_Image_Enhancement(RGB_Sorce_input,RGB_Scan_Image_Enhancement);
		delete point_E ;

		Mat RGB_Scale_Sorce_Image,RGB_Scale_Sorce_Image_Enhancement; 
		resize(RGB_Sorce_input,RGB_Scale_Sorce_Image,Size(RGB_Scan_Image_Enhancement.cols*0.4,RGB_Scan_Image_Enhancement.rows*0.4),0,0);  // scale to 40% dst image 
		resize(RGB_Scan_Image_Enhancement,RGB_Scale_Sorce_Image_Enhancement,Size(RGB_Scan_Image_Enhancement.cols*0.4,RGB_Scan_Image_Enhancement.rows*0.4));  // scale to 40% dst Enhancement image 


		vector<int> Top_rect_information;vector<int> Question_rect_information;
		Get_The_input_information(RGB_Scale_Sorce_Image,Stand_Modle_Parament,RGB_Scale_Sorce_Image ,Top_rect_information,Question_rect_information);
		//Make a test 
		//Image_basic_function::Show_Image(RGB_Scale_Sorce_Image );  // imshow the scale resize image 
		Rect  interst_ROI(0,0,RGB_Scale_Sorce_Image.cols,RGB_Scale_Sorce_Image.rows*0.25); // get the 15% scale fo the sorce image 
		Mat RGB_top_Barcode;RGB_top_Barcode.create(RGB_Scale_Sorce_Image.rows*0.25,RGB_Scale_Sorce_Image.cols,CV_8UC3);
		Image_basic_function::Copy_Image(RGB_Scale_Sorce_Image,RGB_top_Barcode,interst_ROI);
		Mat Gray_Top,Binary_Top;
		cvtColor(RGB_top_Barcode, Gray_Top, CV_RGB2GRAY);  
		Binary_Top.create(Gray_Top.rows,Gray_Top.cols,CV_8UC1);
		// making the top image to binary image
		FastSauvolaBinarizer * point=new FastSauvolaBinarizer();
		point->Binary_way(Gray_Top,Binary_Top);
		delete point;
		//Image_basic_function::Show_Image(Binary_Top);
		// get the bar code location  
		Top_QR_barcode_information_Get(Binary_Top,false);

		// get the top rect location  information 
		Top_Rect_Information_Get(RGB_Scale_Sorce_Image,RGB_Scale_Sorce_Image_Enhancement,Binary_Top,Top_rect_information,Is_front_page,exception_mean);

		if (exception_mean==1)
		{
		  return; // it he programe is enter the language ,the top rect persent that there is a exception in the top rect detected ,and means the rect is missing 
		}
		// Get the Question rect Location information in the exam paper 
		Question_information_get_With_Missing(Stand_Modle_Parament,Top_rect_information,Question_rect_information,exception_mean);
	}
	catch(...)
	{
	  exception_mean=3;
	  return;
	}
}
	 ////-----------------------------------------------------------------------
  //    try
	 // {  
		// //Generator the input arguement 
	 //    Mat RGB_Sorce_Image,RGB_Scale_Sorce_Image_Enhancement; 
		// vector<int> Top_rect_information;vector<int> Question_rect_information;
		// Get_The_input_information(Miss_Question_Rect_Image,Stand_Modle_Parament,RGB_Sorce_Image ,Top_rect_information,Question_rect_information);

		// // If the Is_front_page is true ,the bar_code will be detected 
		// Rect  interst_ROI(0,0,RGB_Sorce_Image.cols,RGB_Sorce_Image.rows*0.25); // get the 15% scale fo the sorce image 
		// Mat RGB_top_Barcode;RGB_top_Barcode.create(RGB_Sorce_Image.rows*0.25,RGB_Sorce_Image.cols,CV_8UC3);
		// Image_basic_function::Copy_Image(RGB_Sorce_Image,RGB_top_Barcode,interst_ROI);
		// Mat Gray_Top,Binary_Top;
		// cvtColor(RGB_top_Barcode, Gray_Top, CV_RGB2GRAY);  
		// Binary_Top.create(Gray_Top.rows,Gray_Top.cols,CV_8UC1);
		// // making the top image to binary image
		// FastSauvolaBinarizer * point=new FastSauvolaBinarizer();

		// point->Binary_way(Gray_Top,Binary_Top);
		// delete point;

		// // get the bar code location  
		// Top_QR_barcode_information_Get(Binary_Top,Is_front_page);

		// // get the Top rect information 
		// Top_Rect_Information_Get(RGB_Sorce_Image,Binary_Top,RGB_Scale_Sorce_Image_Enhancement,Top_rect_information,Is_front_page,exception_mean);
		// if (exception_mean==1)
		// {
		//   return; // it he programe is enter the language ,the top rect persent that there is a exception in the top rect detected ,and means the rect is missing 
		// }

		// // get the Missing Question Information
		// Question_information_get_With_Missing(Stand_Modle_Parament,Top_rect_information,Question_rect_information,exception_mean);
	 // }
	 // catch(...)
	 // {
	 //    exception_mean=3;
		// return;
	 // }

