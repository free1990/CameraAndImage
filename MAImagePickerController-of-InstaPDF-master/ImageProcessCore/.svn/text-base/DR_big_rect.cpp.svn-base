#include "DR_big_rect.h"
#include <opencv2/opencv.hpp>
#include "iostream"
#include "Image_basic_function.h"
#include "Compressive_Harr_Feature.h"
#include"FastSauvolaBinarizer.h"
using namespace cv;
using namespace std;


DR_big_rect::DR_big_rect()
{
	number_big_rect=0;
	Frist_Detected_Location=true;
	angle_Whole=0;
}


void DR_big_rect::normal_search(Mat& input_sorce,bool Is_front_page,vector<Rect>& QR_code_Location,int &expection_number)
{   
	// The input_binary image brorrow the image from the QR_respond iput_ ,so it save the one binary time  
	Mat _15_rgb,_15_gray;Mat Binary_15percent_input; 
	_15_rgb.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC3);
	_15_gray.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC1);
	Binary_15percent_input.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC1);  

	Rect interst(0,0,input_sorce.cols,input_sorce.rows*0.15);
	Image_basic_function::Copy_Image(input_sorce,_15_rgb,interst,true);
	cvtColor(_15_rgb,_15_gray,CV_RGB2GRAY);
	FastSauvolaBinarizer *point=new FastSauvolaBinarizer();
	point->Binary_way(_15_gray,Binary_15percent_input);
	delete point;
	// Second get the morphology image of the input 
	Mat Binary_15percent_morphology_input ;
	Binary_15percent_morphology_input.create(Binary_15percent_input.rows,Binary_15percent_input.cols,CV_8UC1); 
	Binary_15percent_morphology_input=Binary_15percent_input.clone();

	//Third  Mat Reverse image ,it is save in the Binary_15percent_reverse
    Mat Binary_15percent_reverse;
	Binary_15percent_reverse.create(Binary_15percent_morphology_input.rows,Binary_15percent_morphology_input.cols,CV_8UC1);
	Binary_15percent_reverse=Binary_15percent_input.clone();
	Image_basic_function::Reverse_image(Binary_15percent_reverse);
	
	// Make a deep copy of Mat to Iplimage style 
	IplImage * Binary_15percent_reverse_IplImage;
	Binary_15percent_reverse_IplImage=cvCreateImage(cvSize(Binary_15percent_reverse.cols,Binary_15percent_reverse.rows),IPL_DEPTH_8U,1);
	Image_basic_function::Mat_deep_copy_to_Iplimage(Binary_15percent_reverse,Binary_15percent_reverse_IplImage);
	//Image_basic_function::C_show_image(Binary_15percent_reverse_IplImage);

	//find the contours of the Mat_deep_copy_to_Iplimage  ,The find methord is CV_RETR_EXTERNAL ,it just to find the 
    CvMemStorage* Top_rect_contour_storage = cvCreateMemStorage(0);
	CvSeq* Top_rect_contour;CvSeq* Top_rect_contour_save;
	Image_basic_function::find_contour_with_C_style(Binary_15percent_reverse_IplImage,Top_rect_contour,Top_rect_contour_storage); //find contour function will change the input image 

	//Image_basic_function::Draw_contours(Top_rect_contour,Binary_15percent_reverse_IplImage);
	Top_rect_contour_save=Top_rect_contour;

	// after all the preparing for the top rect detect ,the step is as following  
    Detect_the_top_rect_accopulish(Top_rect_contour,Top_rect_contour_save, QR_code_Location,Binary_15percent_input,Binary_15percent_morphology_input,expection_number);

	// free the C style menory storage 
	cvReleaseImage(&Binary_15percent_reverse_IplImage);
	cvReleaseMemStorage(&Top_rect_contour_storage);
}


void DR_big_rect::Two_morphology_search(Mat& input_sorce,bool Is_front_page,vector<Rect>& QR_code_Location,int &expection_number)
{
	// frist step get 15% percent of the input_sorce's top 
	Mat _15_rgb,_15_gray;Mat Binary_15percent_input; 
	_15_rgb.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC3);
	_15_gray.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC1);
	Binary_15percent_input.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC1);  

	Rect interst(0,0,input_sorce.cols,input_sorce.rows*0.15);
	Image_basic_function::Copy_Image(input_sorce,_15_rgb,interst,true);
	cvtColor(_15_rgb,_15_gray,CV_RGB2GRAY);
	FastSauvolaBinarizer *point=new FastSauvolaBinarizer();
	point->Binary_way(_15_gray,Binary_15percent_input);
	delete point;

	// second get the morphology image of the input 
	Mat Binary_15percent_morphology_input ;
	Binary_15percent_morphology_input.create(Binary_15percent_input.rows,Binary_15percent_input.cols,CV_8UC1); 
	Binary_15percent_morphology_input=Binary_15percent_input.clone();
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));  
	dilate(Binary_15percent_morphology_input, Binary_15percent_morphology_input, element,Point(-1,-1),2);  
	erode(Binary_15percent_morphology_input,Binary_15percent_morphology_input,element,Point(-1,-1),2);

	//Third  Mat Reverse image ,it is save in the Binary_15percent_reverse
    Mat Binary_15percent_reverse;
	Binary_15percent_reverse.create(Binary_15percent_morphology_input.rows,Binary_15percent_morphology_input.cols,CV_8UC1);
	Binary_15percent_reverse=Binary_15percent_morphology_input.clone();
	Image_basic_function::Reverse_image(Binary_15percent_reverse);
	//Image_basic_function::Show_Image(Binary_15percent_reverse);

	// Make a deep copy of Mat to Iplimage style 
	IplImage * Binary_15percent_reverse_IplImage;
	Binary_15percent_reverse_IplImage=cvCreateImage(cvSize(Binary_15percent_reverse.cols,Binary_15percent_reverse.rows),IPL_DEPTH_8U,1);
	Image_basic_function::Mat_deep_copy_to_Iplimage(Binary_15percent_reverse,Binary_15percent_reverse_IplImage);
	//Image_basic_function::C_show_image(Binary_15percent_reverse_IplImage);

	//find the contours of the Mat_deep_copy_to_Iplimage  ,The find methord is CV_RETR_EXTERNAL ,it just to find the 
    CvMemStorage* Top_rect_contour_storage = cvCreateMemStorage(0);
	CvSeq* Top_rect_contour;CvSeq* Top_rect_contour_save;
	Image_basic_function::find_contour_with_C_style(Binary_15percent_reverse_IplImage,Top_rect_contour,Top_rect_contour_storage); //find contour function will change the input image 

	//Image_basic_function::Draw_contours(Top_rect_contour,Binary_15percent_reverse_IplImage);
	Top_rect_contour_save=Top_rect_contour;
	
	// after all the preparing for the top rect detect ,the step is as following  
    Detect_the_top_rect_accopulish(Top_rect_contour,Top_rect_contour_save, QR_code_Location,Binary_15percent_input,Binary_15percent_morphology_input,expection_number);

	// free the C style memory storage 
	cvReleaseImage(&Binary_15percent_reverse_IplImage);
	cvReleaseMemStorage(&Top_rect_contour_storage);

}
void DR_big_rect::Fill_hole_search(Mat& input_sorce,bool Is_front_page,vector<Rect>& QR_code_Location,int &expection_number)
{
	// prepareing step one is get 15% percent of the input_sorce's top 
	Mat _15_rgb,_15_gray;Mat Binary_15percent_input; 
	_15_rgb.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC3);
	_15_gray.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC1);
	Binary_15percent_input.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC1);  

	Rect interst(0,0,input_sorce.cols,input_sorce.rows*0.15);
	Image_basic_function::Copy_Image(input_sorce,_15_rgb,interst,true);
	cvtColor(_15_rgb,_15_gray,CV_RGB2GRAY);
	FastSauvolaBinarizer *point=new FastSauvolaBinarizer();
	point->Binary_way(_15_gray,Binary_15percent_input);
	delete point;


	//Image_basic_function::Show_Image(Binary_15percent_input);
	// prepareing step two is get the fill_hole Mat image 
	Mat  fill_hole_Based_input;
	fill_hole_Based_input.create(Binary_15percent_input.rows,Binary_15percent_input.cols,CV_8UC1);
	Fill_Image_Get(Binary_15percent_input,fill_hole_Based_input);


	//  Now the following can be the same as other leaf ,bacause the fill foald iamge had get and it store in  fill_hole_Based_input;
	// first step is to get the 15 % percent fo the in_put
	Binary_15percent_input=fill_hole_Based_input.clone();

	// Second get the morphology image of the input 
	Mat Binary_15percent_morphology_input ;
	Binary_15percent_morphology_input.create(Binary_15percent_input.rows,Binary_15percent_input.cols,CV_8UC1); 
	Binary_15percent_morphology_input=Binary_15percent_input.clone();

	//Third  Mat Reverse image ,it is save in the Binary_15percent_reverse
    Mat Binary_15percent_reverse;
	Binary_15percent_reverse.create(Binary_15percent_morphology_input.rows,Binary_15percent_morphology_input.cols,CV_8UC1);
	Binary_15percent_reverse=Binary_15percent_morphology_input.clone();
	Image_basic_function::Reverse_image(Binary_15percent_reverse);

	// Make a deep copy of Mat to Iplimage style 
	IplImage * Binary_15percent_reverse_IplImage;
	Binary_15percent_reverse_IplImage=cvCreateImage(cvSize(Binary_15percent_reverse.cols,Binary_15percent_reverse.rows),IPL_DEPTH_8U,1);
	Image_basic_function::Mat_deep_copy_to_Iplimage(Binary_15percent_reverse,Binary_15percent_reverse_IplImage);
	//Image_basic_function::C_show_image(Binary_15percent_reverse_IplImage);

	//find the contours of the Mat_deep_copy_to_Iplimage  ,The find methord is CV_RETR_EXTERNAL ,it just to find the 
    CvMemStorage* Top_rect_contour_storage = cvCreateMemStorage(0);
	CvSeq* Top_rect_contour;CvSeq* Top_rect_contour_save;
	Image_basic_function::find_contour_with_C_style(Binary_15percent_reverse_IplImage,Top_rect_contour,Top_rect_contour_storage); //find contour function will change the input image 

	//Image_basic_function::Draw_contours(Top_rect_contour,Binary_15percent_reverse_IplImage);
	Top_rect_contour_save=Top_rect_contour;
	
	// after all the preparing for the top rect detect ,the step is as following  
    Detect_the_top_rect_accopulish(Top_rect_contour,Top_rect_contour_save, QR_code_Location,Binary_15percent_input,Binary_15percent_morphology_input,expection_number);

	// free the C style memory storage 
	cvReleaseImage(&Binary_15percent_reverse_IplImage);
	cvReleaseMemStorage(&Top_rect_contour_storage);
	
}
void DR_big_rect::One_morphology_search(Mat& input_sorce,bool Is_front_page,vector<Rect>& QR_code_Location,int &expection_number)
{
	// frist step get 15% percent of the input_sorce's top 
	Mat _15_rgb,_15_gray;Mat Binary_15percent_input; 
	_15_rgb.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC3);
	_15_gray.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC1);
	Binary_15percent_input.create(input_sorce.rows*0.15,input_sorce.cols,CV_8UC1);  

	Rect interst(0,0,input_sorce.cols,input_sorce.rows*0.15);
	Image_basic_function::Copy_Image(input_sorce,_15_rgb,interst,true);
	cvtColor(_15_rgb,_15_gray,CV_RGB2GRAY);
	FastSauvolaBinarizer *point=new FastSauvolaBinarizer();
	point->Binary_way(_15_gray,Binary_15percent_input);
	delete point;

	// second get the morphology image of the input 
	Mat Binary_15percent_morphology_input ;
	Binary_15percent_morphology_input.create(Binary_15percent_input.rows,Binary_15percent_input.cols,CV_8UC1); 
	Binary_15percent_morphology_input=Binary_15percent_input.clone();
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));  
	dilate(Binary_15percent_morphology_input, Binary_15percent_morphology_input, element,Point(-1,-1),1);  
	erode(Binary_15percent_morphology_input,Binary_15percent_morphology_input,element,Point(-1,-1),1);

	//Third  Mat Reverse image ,it is save in the Binary_15percent_reverse
    Mat Binary_15percent_reverse;
	Binary_15percent_reverse.create(Binary_15percent_morphology_input.rows,Binary_15percent_morphology_input.cols,CV_8UC1);
	Binary_15percent_reverse=Binary_15percent_morphology_input.clone();
	Image_basic_function::Reverse_image(Binary_15percent_reverse);
	//Image_basic_function::Show_Image(Binary_15percent_reverse);

	// Make a deep copy of Mat to Iplimage style 
	IplImage * Binary_15percent_reverse_IplImage;
	Binary_15percent_reverse_IplImage=cvCreateImage(cvSize(Binary_15percent_reverse.cols,Binary_15percent_reverse.rows),IPL_DEPTH_8U,1);
	Image_basic_function::Mat_deep_copy_to_Iplimage(Binary_15percent_reverse,Binary_15percent_reverse_IplImage);
	//Image_basic_function::C_show_image(Binary_15percent_reverse_IplImage);

	//find the contours of the Mat_deep_copy_to_Iplimage  ,The find methord is CV_RETR_EXTERNAL ,it just to find the 
    CvMemStorage* Top_rect_contour_storage = cvCreateMemStorage(0);
	CvSeq* Top_rect_contour;CvSeq* Top_rect_contour_save;
	Image_basic_function::find_contour_with_C_style(Binary_15percent_reverse_IplImage,Top_rect_contour,Top_rect_contour_storage); //find contour function will change the input image 

	//Image_basic_function::Draw_contours(Top_rect_contour,Binary_15percent_reverse_IplImage);
	Top_rect_contour_save=Top_rect_contour;
	
	// after all the preparing for the top rect detect ,the step is as following  
    Detect_the_top_rect_accopulish(Top_rect_contour,Top_rect_contour_save, QR_code_Location,Binary_15percent_input,Binary_15percent_morphology_input,expection_number);

	// free the C style memory storage 
	cvReleaseImage(&Binary_15percent_reverse_IplImage);
	cvReleaseMemStorage(&Top_rect_contour_storage);

}
void DR_big_rect::Top_bigrect_detect(Mat& input_sorce,Mat& RGB_Scale_Sorce_Image_Enhancement,Mat& input_first_binary,vector<int> &top_rect_information,bool Is_front_page,vector<Rect>& QR_code_Location,int& expection_number)// here the input image is after dealing 
{    

	//input_sorce ---the sorce image 
	// input_first_binary 
	Is_front_page=Is_front_page; // use the inner parament to know the page wheather is front page 
    All_rect_number(top_rect_information);
	//Compressive_Harr_Feature Harr_featur_selector;

	// frist time trying 
	Process_branch_trying(input_sorce,Is_front_page,QR_code_Location,expection_number);
    if (expection_number==1)
	{  
	   return;
	}
	float angle=Get_the_rotation_angle();
	Image_basic_function::Rotation(input_sorce,Rotation_frist,angle);//here the Rotation_frist malloc had not apply in the memory ,and the size of Rotation_frist is based on angle
	Image_basic_function::Rotation(RGB_Scale_Sorce_Image_Enhancement,Rotation_frist_Enhancement,angle);
	Making_Clear_parament();
	angle_Whole+=angle;

	//second time trying 
	Process_branch_trying(Rotation_frist,Is_front_page,QR_code_Location,expection_number);
	if(expection_number==1)
	{
	   return ;
	}
	angle=Get_the_rotation_angle();
	Image_basic_function::Rotation(Rotation_frist,Rotation_Second,angle);
	Image_basic_function::Rotation(Rotation_frist_Enhancement,Rotation_Second_Enhancement,angle);
	Making_Clear_parament();
	angle_Whole+=angle;
	//Thrid time trying 
	Process_branch_trying(Rotation_Second,Is_front_page,QR_code_Location,expection_number);

}

void DR_big_rect::Process_branch_trying(Mat &input_sorce, bool Is_front_page,vector<Rect>& QR_code_Location,int &expection_number)
{
	// first step :doing the normal path to detected the top rect location 
	normal_search(input_sorce,Is_front_page,QR_code_Location,expection_number); 
	if (expection_number==-1) 
	{
	     return ;
	}

	// second step Two_morphology_search
	if (expection_number==1) 
	{  
		expection_number=-1;
		Making_Clear_parament();
		Two_morphology_search(input_sorce,Is_front_page,QR_code_Location,expection_number);   
	}
	if (expection_number==-1)
	{
	   return ;
	}

	// third step Fill_hole_search
	if (expection_number==1)
	{
	    expection_number=-1;
		Making_Clear_parament();
		Fill_hole_search(input_sorce,Is_front_page,QR_code_Location,expection_number); 

	}

	if (expection_number==-1)
	{
	   return ;
	}

	// four step One_morphology_search 
	if (expection_number==1)
	{
	    expection_number=-1;
		Making_Clear_parament();
		One_morphology_search(input_sorce,Is_front_page,QR_code_Location,expection_number);
	}
}
void DR_big_rect::All_rect_number(vector<int> &top_rect_information) //  Sure to know the number of top big rect
{    

	for(int j=0;j<top_rect_information.size();j++)
	{
	   if (top_rect_information[j]!=0)
	   {
	   
	       number_big_rect++;
	   }
	    
	}
	 
}

void DR_big_rect::Detect_the_top_rect_accopulish(CvSeq *&Top_rect_contour,CvSeq *& Top_rect_contour_save,vector<Rect>& QR_code_Location,Mat & Binary_15percent_input,Mat &Binary_15percent_morphology_input,int &expection_number)
{
	float  max_like_area=0;vector<Rect_Area_Com_Haar_coefficient> temple_together_parament;
	//seek the biggest like area  
	max_like_area=find_the_like_Max_area(Top_rect_contour,QR_code_Location,Binary_15percent_input,Binary_15percent_morphology_input);
	//seek the  top rect Location and store them in a praparing storage 
	Find_the_like_Rect(Top_rect_contour_save,QR_code_Location,Binary_15percent_input,Binary_15percent_morphology_input,max_like_area,temple_together_parament);
    
	// if all the Rect is small than the shoule find Rect ,it may present there is a exception ,and the programe shoule shult down 
	if (temple_together_parament.size()<number_big_rect)
	{   
		Doing_Sort(temple_together_parament);
		for (int j=0;j<temple_together_parament.size();j++)
		{    
			if (temple_together_parament[j].Com_Haar_coefficient_Whole>6216.0*0.7)
			{
			    Not_whole_top_rect.push_back(temple_together_parament[j].rect);
			}
			break;
		}
	    expection_number =1;
		if(expection_number==1&&Frist_Detected_Location)
	    {
	   		for (int index=0;index<temple_together_parament.size();index++)
			{    
			
			  Wrong_candidate_rect.push_back(temple_together_parament[index].rect);
			}
			Frist_Detected_Location=false;
	    }

		return ;
	}

	// Recorde the wrong Location had detected 

	// making a sort by the element of temple_together_parament.coff_Whole
	if (temple_together_parament.size()>=number_big_rect)
	{
	    Doing_Sort(temple_together_parament);
	}

	// Giving the detected Rect to the candidate_rect 
	for(int j=0;j<number_big_rect;j++)
	{   
		Rect temple;
		temple=temple_together_parament[j].rect;
		candidate_rect.push_back(temple);      
	}

	if(Frist_Detected_Location)
	{
		for (int index=0;index<candidate_rect.size();index++)
		{    
			Wrong_candidate_rect.push_back(candidate_rect[index]);
		}
		Frist_Detected_Location=false;
	}
    
	Doing_Sort_by_X();// if can present the detected rect from left to right  
	Doing_Check_by_width_height(expection_number); // // Doing a check of the detected  Rect 
	Doing_Check_by_X(expection_number);
	Doing_Check_by_Y(expection_number);
}

float DR_big_rect::find_the_like_Max_area(CvSeq *& Top_rect_contour,vector<Rect>& QR_code_Location,Mat &  Binary_15percent_input,Mat & Binary_15percent_morphology_input)
{    
	vector<Rect_Area_Com_Haar_coefficient> temple_together_parament;
	float max_area=0;
	for (;Top_rect_contour!=0;Top_rect_contour=Top_rect_contour->h_next)
	{  
	   float circlearea,diffthrsould0, diffthrsould1,Whilte_pixel_percent; // max area and the min_box scale diver 
	   CvRect templerect; CvBox2D box ;
	   basic_contours_information_get(Top_rect_contour,circlearea,diffthrsould0,diffthrsould1,templerect,box);
	   // here can distinguish(force) the QR code location to enter 
	  bool Whether_Location=Whether_Location_the_QR_position(Is_front_page,QR_code_Location,templerect) ;
	  if (Whether_Location)
	  {
	     continue;
	  }

	   // if the Location is not belong with the QR code the following can be action 
	   if (templerect.x>5 &&  diffthrsould0>1.30 &&diffthrsould0<(3.50)&& diffthrsould1>0.10&&circlearea<47500 && 
			                                            templerect.width<300 && templerect.height<100 &&
			                                             circlearea>30) // it is simlar to the top big rect condition 
		{
			Whilte_pixel_percent=Image_basic_function::Black_pixls_of_input_image_Mat(Binary_15percent_input,templerect);
			if (Whilte_pixel_percent>0.6)
			{   
				vector<float> Harr_feature_temple; Rect_Area_Com_Haar_coefficient together_mening;float coff_Centre=0;float coff_Whole=0;

				Get_sturctor_meaning(Binary_15percent_input,Harr_feature_temple,coff_Centre,coff_Whole,templerect);
				together_mening.rect=templerect;
				together_mening.area=circlearea;
				together_mening.Com_Haar_coefficient_Centre=coff_Centre;
				together_mening.Com_Haar_coefficient_Whole=coff_Whole;
				temple_together_parament.push_back(together_mening);
			}
		
		}
	}

	for (int j=0;j<temple_together_parament.size();j++)
	{ 
		if (temple_together_parament[j].Com_Haar_coefficient_Centre>5526.5&&temple_together_parament[j].Com_Haar_coefficient_Whole>3592.0)
		{  
			if (max_area<=temple_together_parament[j].area)
			{
			   max_area=temple_together_parament[j].area;
			}
		
		}

	
	}
    return max_area;
}


// Find_the_like_Rect which is from the senond circle 

void DR_big_rect::Find_the_like_Rect(CvSeq *& Top_rect_contour_save,vector<Rect>& QR_code_Location,Mat &   Binary_15percent_input,Mat & Binary_15percent_morphology_input,float max_like_area,vector<Rect_Area_Com_Haar_coefficient>& temple_together_parament)
{
	while (Top_rect_contour_save)
	{
		if (fabs(cvContourArea(Top_rect_contour_save, CV_WHOLE_SEQ)) > max_like_area*0.50&&cvContourArea(Top_rect_contour_save, CV_WHOLE_SEQ) < 7500)
		{
		  float circlearea,diffthrsould0, diffthrsould1,Whilte_pixel_percent; // max area and the min_box scale diver 
	      CvRect templerect; CvBox2D box ;
		  basic_contours_information_get(Top_rect_contour_save,circlearea,diffthrsould0,diffthrsould1,templerect,box);
		  bool Whether_Location=Whether_Location_the_QR_position(Is_front_page,QR_code_Location,templerect) ;
		  if (Whether_Location)
		  {
			 continue;
		  }
		  float Black_pixl_percent=0;
		  Black_pixl_percent=Image_basic_function::Black_pixls_of_input_image_Mat(Binary_15percent_input,templerect);
		  if(templerect.x>5&&diffthrsould0 > 1.30 &&diffthrsould0<(3.950) &&diffthrsould1 > 0.10&&
			                                        circlearea < 47500 && templerect.width < 300 && templerect.height<150 && Black_pixl_percent>0.5)
		  {   
 
			  vector<float> Harr_feature_temple; Rect_Area_Com_Haar_coefficient together_mening;float coff_Centre=0;float coff_Whole=0;
			  Get_sturctor_meaning(Binary_15percent_input,Harr_feature_temple,coff_Centre,coff_Whole,templerect);

			 if (coff_Centre>5526.5&&coff_Whole>3592.0)
			  
			 //if ((coff_Centre>1000.5&&coff_Whole>1000.0))
			  {
				  together_mening.rect=templerect;
				  together_mening.area=circlearea;
				  together_mening.Com_Haar_coefficient_Centre=coff_Centre;
				  together_mening.Com_Haar_coefficient_Whole=coff_Whole;
				  temple_together_parament.push_back(together_mening);

			  }
		  }
		}

		Top_rect_contour_save=Top_rect_contour_save->h_next;
	}
}
void DR_big_rect::basic_contours_information_get(CvSeq *& contour,float& circlearea,float &diffthrsould0,float& diffthrsould1, CvRect &templerect,CvBox2D& box )
{
       circlearea=cvContourArea(contour, CV_WHOLE_SEQ);
	   templerect = cvBoundingRect(contour, 0);
	   box = cvMinAreaRect2(contour);// two ways of caluculte the min_contour_rect 
	   if (box.size.width>=box.size.height)
	    {
				diffthrsould0 = (float)box.size.width / box.size.height;
				diffthrsould1 = (float)box.size.height / box.size.width;
	    }
		else
	    {
				diffthrsould1 = (float)box.size.width / box.size.height;
				diffthrsould0 = (float)box.size.height / box.size.width;
		}
}

bool DR_big_rect::Whether_Location_the_QR_position(bool Is_front_page,vector<Rect> &QR_code_Location,CvRect templerect) 
{
	 if (Is_front_page)
	   {
		  
		   if (QR_code_Location.size()==1)
		   {
		        Rect temple=QR_code_Location[0];
				if (abs(temple.height-temple.width)<5&&temple.x!=0&&temple.y!=0)
				{
					float input_x= temple.x+0.5*temple.width;
					float input_y=temple.y+0.5*temple.height;
					float min_t_x=QR_code_Location[0].x;float mxa_t_x=QR_code_Location[0].x+QR_code_Location[0].width;
					float min_t_y=QR_code_Location[0].y;float mxa_t_y=QR_code_Location[0].y+QR_code_Location[0].height;
					if (input_x>min_t_x&&input_x<mxa_t_x  &&  input_y>min_t_y&&input_y<min_t_y)
					{
					
					    return true; 
					}
					else
					{
					 return false;
					}
				}

				else
				{
				   return false;
				}
		   
		   }
		   else
		   {
		      return false ;
		   }
	   
	   }
	 else
	 {
	     return false;
	 }

}

void DR_big_rect::Get_sturctor_meaning(Mat &Binary_15percent_input,vector<float>&Harr_feature_temple,float &coff_Centre,float &coff_Whole,CvRect &templerect)
{

	Harr_feature_temple=vector<float>((int)Haar_feature.Get__numFeature(), 0.0f);// positive sample vector list  __it is judge  by the whole black 
	Mat Like_temple_centre,Like_temple_sorce_rect;
	Rect interest_ROI_centre_rect(templerect.x + 0.25*templerect.width,templerect.y + 0.25*templerect.height,templerect.width*0.5,templerect.height*0.5);
	Rect interest_ROI_sorce_rect(templerect);
	Like_temple_centre.create(interest_ROI_centre_rect.height,interest_ROI_centre_rect.width,CV_8UC1);
	Like_temple_sorce_rect.create(interest_ROI_sorce_rect.height,interest_ROI_sorce_rect.width,CV_8UC1);
	Image_basic_function::Copy_Image(Binary_15percent_input,Like_temple_centre,interest_ROI_centre_rect,true);
	Image_basic_function::Copy_Image(Binary_15percent_input,Like_temple_sorce_rect,interest_ROI_sorce_rect,true);

	// First calculate the center centre image's compressive haar feature 
	Mat Normal_centre_25_50;
	Normal_centre_25_50.create(25,50,CV_8UC1);
	resize(Like_temple_centre,Normal_centre_25_50,Size(Normal_centre_25_50.cols,Normal_centre_25_50.rows),0.0,0.0,CV_INTER_NN);
	//Image_basic_function::Show_Image(Normal_centre_25_50);
	Haar_feature.Get_Harr_feture(Normal_centre_25_50,Harr_feature_temple);
	coff_Centre=Haar_feature.Similar_relationship(Harr_feature_temple);

	//Second calculate the whole image's compressive haar feature  
	resize(Like_temple_sorce_rect,Normal_centre_25_50,Size(Normal_centre_25_50.cols,Normal_centre_25_50.rows),0.0,0.0,CV_INTER_NN);
	Haar_feature.Get_Harr_feture(Normal_centre_25_50,Harr_feature_temple);
	coff_Whole=Haar_feature.Similar_relationship(Harr_feature_temple);
 

}
void DR_big_rect::Doing_Sort(vector<Rect_Area_Com_Haar_coefficient>& temple_together_parament)
{
     // pop  pop algorithm to making a sort of the sequence temple_together_parament
	Rect_Area_Com_Haar_coefficient tenple_store;
	for (int i = 0; i<temple_together_parament.size(); i++)
	{

		tenple_store = temple_together_parament[i];

		for (int j = temple_together_parament.size() - 1; j>i; j--)
		{
			if (tenple_store.Com_Haar_coefficient_Whole<= temple_together_parament[j].Com_Haar_coefficient_Whole)
			{
				temple_together_parament[i] = temple_together_parament[j];
				temple_together_parament[j] = tenple_store;
				tenple_store = temple_together_parament[i];
			}
		}
	}


}

void DR_big_rect::Doing_Check_by_width_height(int &expection_number)
{
    float Max_width=0;float Max_height=0;
	for (int j=0;j<candidate_rect.size();j++)
	{
		Max_width=candidate_rect[j].width;
		Max_height=candidate_rect[j].height;
		if (Max_width<candidate_rect[j].width)
		{
		      Max_width=candidate_rect[j].width;

		}

		if (Max_height<candidate_rect[j].height)
		{
		    Max_height=candidate_rect[j].height;

		}
	}

	for (int up=0;up<candidate_rect.size()-1;up++)
	{
		for (int down=up+1;down<candidate_rect.size();down++)
		{
			if(abs(candidate_rect[up].width-candidate_rect[down].width)>0.5*Max_width)
		    {
			   expection_number=1;
			   break;
		    }
			if (abs(candidate_rect[up].height-candidate_rect[down].height)>0.5*Max_height)
			{
			   expection_number=1;
			   break;
			    
			}
		
		}

		if (expection_number==1)
		{
			break;
        }
	
	}
}

void DR_big_rect::Doing_Sort_by_X()
{

    Rect tenple_store;
	for (int i = 0; i<candidate_rect.size(); i++)
	{
		tenple_store = candidate_rect[i];
		for (int j = candidate_rect.size() - 1; j>i; j--)
		{
			if (tenple_store.x>=candidate_rect[j].x)
			{
				candidate_rect[i] = candidate_rect[j];
				candidate_rect[j] = tenple_store;
				tenple_store = candidate_rect[i];
			}
		}
	}


}


void DR_big_rect::Doing_Check_by_X(int &expection_number)
{
	if (candidate_rect.size()==2)
	{
	    Rect left_rect=candidate_rect[0];
		Rect right_rect=candidate_rect[1];
		if (abs(left_rect.x-right_rect.x)<160)
		{
		   expection_number=1;
		}
	      
	}

	if (candidate_rect.size()==4)
	{
	
		if (abs(candidate_rect[0].x-candidate_rect[1].x)<160|| abs(candidate_rect[2].x-candidate_rect[3].x)<160)
		{
		  expection_number=1;   
		}
	      
	}

}

void DR_big_rect::Doing_Check_by_Y(int &expection_number)
{

	if (candidate_rect.size()==2)
	{
	    Rect left_rect=candidate_rect[0];
		Rect right_rect=candidate_rect[1];
		if (abs(left_rect.y-right_rect.y)>25)
		{
		   expection_number=1;
		}
	      
	}

	if (candidate_rect.size()==4)
	{
	
		if (abs(candidate_rect[0].y-candidate_rect[1].y)>25|| abs(candidate_rect[2].y-candidate_rect[3].y)>25)
		{
		   expection_number=1;   
		}

		if (abs(abs(candidate_rect[0].y-candidate_rect[1].y)-abs(candidate_rect[2].y-candidate_rect[3].y))>10)
		{
		   expection_number=1;  
		}
	      
	}
 
}

void DR_big_rect::Fill_Image_Get(Mat& Binary_15percent_input,Mat&  fill_hole_Based_input)
{
    // Here the function is to fill_fload of the rect hool ,where the hool present the center of the top rect 
	// Get the 15% reverse 
	Mat Binary_15percent_reverse;
	Binary_15percent_reverse.create(Binary_15percent_input.rows,Binary_15percent_input.cols,CV_8UC1);
	Binary_15percent_reverse=Binary_15percent_input.clone();
	Image_basic_function::Reverse_image(Binary_15percent_reverse);
	//Image_basic_function::Show_Image(Binary_15percent_reverse);

	// Make a deep copy of Mat to Iplimage style 
	IplImage * Binary_15percent_reverse_IplImage;
	Binary_15percent_reverse_IplImage=cvCreateImage(cvSize(Binary_15percent_reverse.cols,Binary_15percent_reverse.rows),IPL_DEPTH_8U,1);
	Image_basic_function::Mat_deep_copy_to_Iplimage(Binary_15percent_reverse,Binary_15percent_reverse_IplImage);
	//Image_basic_function::C_show_image(Binary_15percent_reverse_IplImage);

	// make a save of image of Iplimage style as input 
	IplImage * Binary_15percent_reverse_IplImage_Save;
	Binary_15percent_reverse_IplImage_Save=cvCreateImage(cvSize(Binary_15percent_reverse.cols,Binary_15percent_reverse.rows),IPL_DEPTH_8U,1);
	Image_basic_function::Mat_deep_copy_to_Iplimage(Binary_15percent_input,Binary_15percent_reverse_IplImage_Save);
	//Image_basic_function::C_show_image(Binary_15percent_reverse_IplImage_Save);

	//find the contours of the Mat_deep_copy_to_Iplimage  ,The find methord is CV_RETR_EXTERNAL ,it just to find the 
    CvMemStorage* Top_rect_contour_storage = cvCreateMemStorage(0);
	CvSeq* Top_rect_contour;CvSeq* Top_rect_contour_save;
	Image_basic_function::find_contour_with_C_style_additional_innerContour(Binary_15percent_reverse_IplImage,Top_rect_contour,Top_rect_contour_storage); //find contour function will change the input image 

	//Image_basic_function::Draw_contours(Top_rect_contour,Binary_15percent_reverse_IplImage);
	Top_rect_contour_save=Top_rect_contour;

	// The real accopulish paret 
	Fill_contors_real_accompulish(Top_rect_contour,Top_rect_contour_save,Binary_15percent_reverse_IplImage_Save);
	//Image_basic_function::C_show_image(Binary_15percent_reverse_IplImage_Save);
	Image_basic_function::IplImage_deep_copy_to_Mat(Binary_15percent_reverse_IplImage_Save,fill_hole_Based_input);
	// As the programe running here ,the fill foald image of C style had get ,and it store in  Binary_15percent_reverse_IplImage_Save ,anothe it was deeply copy in the fill_hole_Based_input
	//free the memstorage of the C style malloc storage 
	cvReleaseImage(&Binary_15percent_reverse_IplImage);
	cvReleaseImage(&Binary_15percent_reverse_IplImage_Save);
	cvReleaseMemStorage(&Top_rect_contour_storage);
}

void DR_big_rect::Fill_contors_real_accompulish(CvSeq*& Top_rect_contour,CvSeq*&  Top_rect_contour_save,IplImage *& Binary_15percent_reverse_IplImage_Save)
{    
	// The parament is used to accomuplish the district of the fill hole location 
	int rect_Width =0;
	int rect_Height=0;
	int rect_Y=0;
	if (Not_whole_top_rect.size()!=0)
	{
		rect_Width=Not_whole_top_rect[0].width;
		rect_Height=Not_whole_top_rect[0].height;
		rect_Y=Not_whole_top_rect[0].y;
	}

	if (rect_Width!=0)
	{
	 for (; Top_rect_contour != 0; Top_rect_contour =Top_rect_contour->h_next) 
	 {
		CvSeq* inner_contours;
		inner_contours=Top_rect_contour;
		CvRect temple_rect= cvBoundingRect(Top_rect_contour, 0);// it is used to detected bounding rect ,and here is used to delete the QR Location fill folad  
		if (abs(temple_rect.width-rect_Width)<0.5*rect_Width&&abs(temple_rect.height-rect_Height)<0.5*rect_Height&&abs(temple_rect.y-rect_Y)<25&&
			((float)temple_rect.width/(float)temple_rect.height)>1.3&&((float)temple_rect.height/(float)temple_rect.width)<0.7)
		{
			for (inner_contours=inner_contours->v_next;inner_contours!=NULL;inner_contours=inner_contours->h_next)
			{
				float  dConArea = fabs(cvContourArea(inner_contours, CV_WHOLE_SEQ)); 
				if (dConArea <= 150)   
				{   
					cvDrawContours(Binary_15percent_reverse_IplImage_Save, inner_contours, CV_RGB(0, 0, 0), CV_RGB(255, 255, 255), 0, CV_FILLED, 8, cvPoint(0, 0));  
				} 

			}
		}

	 }
	}
	else 
	{
		for (; Top_rect_contour_save!= 0; Top_rect_contour_save =Top_rect_contour_save->h_next) 
		{
			CvSeq* inner_contours;
			inner_contours=Top_rect_contour_save;
			CvRect temple_rect= cvBoundingRect(Top_rect_contour_save, 0);
			if (//abs(temple_rect.width-rect_Width)<0.5*rect_Width&&abs(temple_rect.height-rect_Height)<0.5*rect_Height&&abs(temple_rect.y-rect_Y)<25&&
				 temple_rect.width<70&&temple_rect.height<50&&
				((float)temple_rect.width/(float)temple_rect.height)>1.3&&((float)temple_rect.height/(float)temple_rect.width)<0.7)
			{
				for (inner_contours=inner_contours->v_next;inner_contours!=NULL;inner_contours=inner_contours->h_next)
				{
					float  dConArea = fabs(cvContourArea(inner_contours, CV_WHOLE_SEQ)); 
					if (dConArea <= 150)   
					{   
						cvDrawContours(Binary_15percent_reverse_IplImage_Save, inner_contours, CV_RGB(0, 0, 0), CV_RGB(255, 255, 255), 0, CV_FILLED, 8, cvPoint(0, 0));  
					} 
			    }
			}	
		}
	
	}

}

float  DR_big_rect::Get_the_rotation_angle()
{
	float angel_point_left_x=candidate_rect[0].x;float angel_point_left_y=candidate_rect[0].y;
	float angel_point_right_x=candidate_rect[1].x;float angel_point_right_y=candidate_rect[1].y;
	float absy=angel_point_right_y-angel_point_left_y;
	float absx=angel_point_right_x-angel_point_left_x; float angle=0; float radian =0; 
	if (absx!=0)
	{
	    radian=atan(absy/absx);
		angle=radian*180.0/3.1415926;
	}
	else
	{
	  radian=0;
	  angle=0;
	}
	return angle ;
}

void DR_big_rect::Making_Clear_parament()
{   

	int delete_times_candidate_rect=candidate_rect.size();
	int delete_times_Not_whole_top_rect=Not_whole_top_rect.size();
	for (int j=0;j<delete_times_candidate_rect;j++)
	{
		candidate_rect.erase(candidate_rect.begin());
	}

	for (int j=0;j<delete_times_Not_whole_top_rect;j++)
	{
		Not_whole_top_rect.erase(Not_whole_top_rect.begin());
	}

} 
DR_big_rect::~DR_big_rect()
{    



}

