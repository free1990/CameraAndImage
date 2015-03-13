
#include <vector>
#include "QR_Location_detect.h"
#include "Image_basic_function.h"

//自定义排序函数  
bool SortBy_Max(  float& A, float& B)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
    return A > B;//升序排列  
}  


QR_Location_detect::QR_Location_detect()
{
	Fill_Pos_Neg_Vector();
}

void QR_Location_detect::QR_find_Location(Mat& input_Binary,bool Is_Dilate)
{
	QR_find_methord_Morphology(input_Binary,Is_Dilate);
}

void QR_Location_detect::QR_find_Location_Rect_MOGRHY(Mat& input_Binary,bool Is_Dilate)
{

	QR_find_methord_Morphology_Rect_MOGRHY(input_Binary,Is_Dilate);

}


void QR_Location_detect::QR_find_methord_Morphology_Rect_MOGRHY(Mat& input_Binary,bool Is_Dilate,bool Is_strict_judge_bar_code)
{
	 // The  input image is the 25% percent of the scale image 
	 // Here is a rule that is the input can not change ,so when change the image ，should make a clone 

	 Mat Bar_code_contain_image;
	 Bar_code_contain_image.create(input_Binary.rows,int(input_Binary.cols),CV_8UC1);
	 Rect interst_rect(0,0,int(input_Binary.cols),input_Binary.rows);
	 Image_basic_function::Copy_Image(input_Binary,Bar_code_contain_image,interst_rect);
	 Mat element_MORPH_RECT = getStructuringElement(MORPH_RECT, Size(3, 3));  
	 if (Is_Dilate==true)
	 {  
	    dilate(Bar_code_contain_image,Bar_code_contain_image,element_MORPH_RECT,Point(-1,-1),1);
	 }
	 // Image_basic_function::Show_Image(Bar_code_contain_image);
	 Image_basic_function::Reverse_image(Bar_code_contain_image); // now we have get the reverse contaion bar_code image
	 if (Is_Dilate==true)
	 {
	   dilate(Bar_code_contain_image, Bar_code_contain_image, element_MORPH_RECT,Point(-1,-1),5);  
	   //Image_basic_function::Show_Image(Bar_code_contain_image);
	   //imwrite("result.jpg",Bar_code_contain_image);
	 }
	 else
	 {
	   dilate(Bar_code_contain_image, Bar_code_contain_image, element_MORPH_RECT,Point(-1,-1),2);  
       //Image_basic_function::Show_Image(Bar_code_contain_image);
	   //imwrite("result.jpg",Bar_code_contain_image);
	 }
	 //erode(Bar_code_contain_image,Bar_code_contain_image,element,Point(-1,-1),1);
	 //Image_basic_function::Show_Image(Bar_code_contain_image);
	 // when find the C++ interface "may " not have the inner contour ,it need to make a deep conpy of iplimage style 
	 // temple use the C interface 
	 CvMemStorage* Barcode_storage = cvCreateMemStorage(0);
	 CvSeq* Barcode_contours;CvSeq* Barcode_contours_save;
	 IplImage * C_syle_image ;C_syle_image=cvCreateImage(cvSize(Bar_code_contain_image.cols,Bar_code_contain_image.rows),IPL_DEPTH_8U,1);
	 IplImage * C_syle_image_Copy ;C_syle_image_Copy=cvCreateImage(cvSize(Bar_code_contain_image.cols,Bar_code_contain_image.rows),IPL_DEPTH_8U,1);
	 Image_basic_function::Mat_deep_copy_to_Iplimage(Bar_code_contain_image,C_syle_image);
	 Image_basic_function::Mat_deep_copy_to_Iplimage(Bar_code_contain_image,C_syle_image_Copy);
	 Image_basic_function::find_contour_with_C_style(C_syle_image,Barcode_contours,Barcode_storage); //find contour function will change the input image 
	 Barcode_contours_save=Barcode_contours; // it need to make a  contour save when the sencond time to search 
	 //Image_basic_function::Draw_contours(Barcode_contours,C_syle_image);
	 float Max_like_QR=find_the_QR_max_area(Barcode_contours,C_syle_image_Copy);
	 find_the_Barcode_location(Barcode_contours_save,Max_like_QR,C_syle_image_Copy,input_Binary,Is_strict_judge_bar_code);
	 // C style should free the stroge
	 cvReleaseImage(&C_syle_image);
	 cvReleaseImage(&C_syle_image_Copy);
	 cvReleaseMemStorage(&Barcode_storage);
}

void QR_Location_detect::Fill_Pos_Neg_Vector()
{    
	// generator the input positive image 
	Mat Pos_image;Mat input_positive;
    Pos_image.create(70,70,CV_8UC1);
	for (int j=0;j<Pos_image.rows;j++)
	{
	    unsigned char *point =Pos_image.ptr<unsigned char>(j);
		for (int i=0;i<Pos_image.cols;i++)
		{
			if ((i>=0&&i<10)&&(j>=0&&j<70))
			{
			    *point=255;
			}
			else if((i>=10&&i<20)&&((j>=0&&j<10)||(j>=60&&j<70)))
			{
			    *point=255;
			}  
            else if ((i>=20&&i<50)&&((j>=0&&j<10)||(j>=20&&j<50)||(j>=60&&j<70)))
			{
			    *point=255;
			}
			else if ((i>=50&&i<60)&&((j>=0&&j<10)||(j>=60&&j<70)))
			{
			   *point=255;
			}
			else if ((i>=60&&i<70)&&((j>=0&&j<70)))
			{
				*point=255;
			}
			else 
			{
			   *point=0;
			}
			point++;
		} 
	}

	//generator the neg image of input negtive
	Mat Neg_image;Mat input_negtive;
    Neg_image.create(70,70,CV_8UC1);
	for (int j=0;j<Neg_image.rows;j++)
	{
	    unsigned char *point =Neg_image.ptr<unsigned char>(j);
		for (int i=0;i<Neg_image.cols;i++)
		{
			if ((i>=0&&i<10)&&(j>=0&&j<70))
			{
			    *point=0;
			}
			else if((i>=10&&i<20)&&((j>=0&&j<10)||(j>=60&&j<70)))
			{
			    *point=0;
			}  
            else if ((i>=20&&i<50)&&((j>=0&&j<10)||(j>=20&&j<50)||(j>=60&&j<70)))
			{
			    *point=0;
			}
			else if ((i>=50&&i<60)&&((j>=0&&j<10)||(j>=60&&j<70)))
			{
			   *point=0;
			}
			else if ((i>=60&&i<70)&&((j>=0&&j<70)))
			{
				*point=0;
			}
			else 
			{
			   *point=255;
			}
			point++;
		} 
	}
	
	//generator the Pos and Neg feature vector of the neg and Pos image 
	resize(Pos_image,input_positive,Size(50,25),0,0,CV_INTER_NN);
	Harr_feature.Fill_pos_vector(input_positive,false);

	resize(Neg_image,input_negtive,Size(50,25),0,0,CV_INTER_NN);
	Harr_feature.Fill_neg_vector(input_negtive,false);
}

void QR_Location_detect::QR_find_methord_Morphology(Mat& input_Binary,bool Is_Dilate,bool Is_strict_judge_bar_code,bool IS_Rect_MPYPH) // The detect methord by Morphology  
{
	 // The  input image is the 25% percent of the scale image 
	 // Here is a rule that is the input can not change ,so when change the image ，should make a clone 

	 Mat Bar_code_contain_image;
	 Bar_code_contain_image.create(input_Binary.rows,int(input_Binary.cols),CV_8UC1);
	 Rect interst_rect(0,0,int(input_Binary.cols),input_Binary.rows);
	 Image_basic_function::Copy_Image(input_Binary,Bar_code_contain_image,interst_rect);
	 Mat element_MORPH_CROSS = getStructuringElement(MORPH_CROSS, Size(3, 3));  
	 if (Is_Dilate==true)
	 {  
	    dilate(Bar_code_contain_image,Bar_code_contain_image,element_MORPH_CROSS,Point(-1,-1),1);
	 }
	 // Image_basic_function::Show_Image(Bar_code_contain_image);
	 Image_basic_function::Reverse_image(Bar_code_contain_image); // now we have get the reverse contaion bar_code image
	 if (Is_Dilate==true)
	 {
	   dilate(Bar_code_contain_image, Bar_code_contain_image, element_MORPH_CROSS,Point(-1,-1),5);  
	   //Image_basic_function::Show_Image(Bar_code_contain_image);
	   //imwrite("result.jpg",Bar_code_contain_image);
	 }
	 else
	 {
	   dilate(Bar_code_contain_image, Bar_code_contain_image, element_MORPH_CROSS,Point(-1,-1),2);  
       //Image_basic_function::Show_Image(Bar_code_contain_image);
	   //imwrite("result.jpg",Bar_code_contain_image);
	 }
	 //erode(Bar_code_contain_image,Bar_code_contain_image,element,Point(-1,-1),1);
	 //Image_basic_function::Show_Image(Bar_code_contain_image);
	 // when find the C++ interface "may " not have the inner contour ,it need to make a deep conpy of iplimage style 
	 // temple use the C interface 
	 CvMemStorage* Barcode_storage = cvCreateMemStorage(0);
	 CvSeq* Barcode_contours;CvSeq* Barcode_contours_save;
	 IplImage * C_syle_image ;C_syle_image=cvCreateImage(cvSize(Bar_code_contain_image.cols,Bar_code_contain_image.rows),IPL_DEPTH_8U,1);
	 IplImage * C_syle_image_Copy ;C_syle_image_Copy=cvCreateImage(cvSize(Bar_code_contain_image.cols,Bar_code_contain_image.rows),IPL_DEPTH_8U,1);
	 Image_basic_function::Mat_deep_copy_to_Iplimage(Bar_code_contain_image,C_syle_image);
	 Image_basic_function::Mat_deep_copy_to_Iplimage(Bar_code_contain_image,C_syle_image_Copy);
	 Image_basic_function::find_contour_with_C_style_list(C_syle_image,Barcode_contours,Barcode_storage); //find contour function will change the input image 
	 Barcode_contours_save=Barcode_contours; // it need to make a  contour save when the sencond time to search 
	 //Image_basic_function::Draw_contours(Barcode_contours,C_syle_image);
	 float Max_like_QR=find_the_QR_max_area(Barcode_contours,C_syle_image_Copy);
	 find_the_Barcode_location(Barcode_contours_save,Max_like_QR,C_syle_image_Copy,input_Binary,Is_strict_judge_bar_code);
	 // C style should free the stroge
	 cvReleaseImage(&C_syle_image);
	 cvReleaseImage(&C_syle_image_Copy);
	 cvReleaseMemStorage(&Barcode_storage);
}

void QR_Location_detect::QR_find_methord_three_back(Mat& input_Binary) // it the stand detect 
{
	// it will store the stand detect methord ,it is the wide used methord 

}

float QR_Location_detect::find_the_QR_max_area(CvSeq * & Barcode_contours,IplImage *& C_syle_image_Copy)
{
	 float max_area =0;

	 for(;Barcode_contours!=NULL;Barcode_contours=Barcode_contours->h_next)
	 {
	        float circlearea = cvContourArea(Barcode_contours, CV_WHOLE_SEQ);

			// two ways of caluculte the min_contour_rect 
			CvRect templerect = cvBoundingRect(Barcode_contours, 0);
			CvBox2D box = cvMinAreaRect2(Barcode_contours);
			// calculate the width/height and the  height/width
			float diffthrsould0, diffthrsould1;
			diffthrsould0 = (float)box.size.width / box.size.height;
			diffthrsould1 = (float)box.size.height / box.size.width;

			// here just lift the papaer index information 
			if (templerect.x>5&&
							diffthrsould0>0.6&&diffthrsould0<1.4&&
							diffthrsould1>0.6&&diffthrsould1<1.4&&
							templerect.width>35&&templerect.width<85&&
							templerect.height>35&&templerect.height<85&&
							circlearea<7000&&
							abs((box.size.width-box.size.height)<8))
			{
				float white_percent=Image_basic_function::White_pixls_of_input_image(C_syle_image_Copy,templerect);
			    if (white_percent>0.8)
				{
				    if (max_area<circlearea)
					{
				       max_area=circlearea;
					}
				}
			}
	 }
	 return  max_area;
}


void QR_Location_detect::find_the_Barcode_location(CvSeq *& Barcode_contours_save,float Max_like_QR,IplImage *& input_image,Mat& input_Binary,bool Is_strict_judge_bar_code)
{    
	 
	 for(;Barcode_contours_save!=NULL;Barcode_contours_save=Barcode_contours_save->h_next)
	 {
	        float circlearea = cvContourArea(Barcode_contours_save, CV_WHOLE_SEQ);
			// two ways of caluculte the min_contour_rect 
			CvRect templerect = cvBoundingRect(Barcode_contours_save, 0);
			CvBox2D box = cvMinAreaRect2(Barcode_contours_save);
			// calculate the width/height and the  height/width
			float diffthrsould0, diffthrsould1;
			diffthrsould0 = (float)box.size.width / box.size.height;
			diffthrsould1 = (float)box.size.height / box.size.width;

			// here just lift the papaer index information 
			if (templerect.x>5&&
							diffthrsould0>0.6&&diffthrsould0<1.4&&
							diffthrsould1>0.6&&diffthrsould1<1.4&&
							templerect.width>35&&templerect.width<85&&
							templerect.height>35&&templerect.height<85&&
							circlearea>0.6*Max_like_QR&&circlearea<7000&&
							abs(box.size.width-box.size.height)<8)
			{
			   float white_percent=Image_basic_function::White_pixls_of_input_image(input_image,templerect);

			   if (white_percent>0.70)
			   
			   {   //here shoud entrance the strict classfire judegement,whether it is a bar_code flag 
			  
					   if (abs((templerect.y+templerect.height)-input_Binary.rows)>5)//Here is to reject the student ID that is near to the conner
					   {
						   Rect rect(templerect);
						   QR_Bar_code_Location.push_back(rect);
					   }
				   
			  }
		   }
	 }

}

bool  QR_Location_detect::Find_Barcode_three_Location(IplImage *& input_image,CvRect & templerect,Mat& input_Binary)
{   

	 bool Is_barcode_Pattern=false;
	 Rect Interst_ROI(templerect.x,templerect.y,templerect.width,templerect.height);
	 Mat Interst_Image;Interst_Image.create(templerect.height,templerect.width,CV_8UC1);
	 Image_basic_function::Copy_Image(input_Binary,Interst_Image,Interst_ROI);
	 Image_basic_function::Reverse_image(Interst_Image); // now we have get the reverse contaion bar_code image

	 CvMemStorage* Barcode_storage = cvCreateMemStorage(0);
	 CvSeq* Barcode_contours;
	 IplImage * C_syle_image ;C_syle_image=cvCreateImage(cvSize(Interst_Image.cols,Interst_Image.rows),IPL_DEPTH_8U,1);
	 Image_basic_function::Mat_deep_copy_to_Iplimage(Interst_Image,C_syle_image);
	 Image_basic_function::find_contour_with_C_style(C_syle_image,Barcode_contours,Barcode_storage); //find contour function will change the input image
	 vector<float> All_Rect_Image_Coffnicent;
	 Calculate_The_Coffnicent(All_Rect_Image_Coffnicent,Barcode_contours,Interst_Image);
	 std::sort(All_Rect_Image_Coffnicent.begin(),All_Rect_Image_Coffnicent.end(),SortBy_Max);
	 if(All_Rect_Image_Coffnicent.size()>=3)
	 {  
		 if(All_Rect_Image_Coffnicent[0]>1000&&All_Rect_Image_Coffnicent[1]>800)
		 {
		   Is_barcode_Pattern=true;
		 }
	     if(All_Rect_Image_Coffnicent[0]>800&&All_Rect_Image_Coffnicent[1]>800&&All_Rect_Image_Coffnicent[2]>500)
		 {
		   Is_barcode_Pattern=true;
		 }
	 }
	 else
	 {
	        Is_barcode_Pattern=false;
	 }
	 // When the MAX value can pass 1200,it represents it is bar_code Image 
	 if(All_Rect_Image_Coffnicent.size()>=1)
	 {
	    if(All_Rect_Image_Coffnicent[0]>900)
		{
		   Is_barcode_Pattern=true;
		}
	 }
	 cvReleaseImage(&C_syle_image);
	 cvReleaseMemStorage(&Barcode_storage);
	 return Is_barcode_Pattern ;
}

void  QR_Location_detect::Calculate_The_Coffnicent(vector<float>& All_Rect_Image_Coffnicent,CvSeq*& Barcode_contours, Mat& Interst_Image)
{   
	 //Image_basic_function::Show_Image(Interst_Image);
	 for(;Barcode_contours!=NULL;Barcode_contours=Barcode_contours->h_next)
	 {
	        float circlearea = cvContourArea(Barcode_contours, CV_WHOLE_SEQ);
			// two ways of caluculte the min_contour_rect 
			CvRect templerect = cvBoundingRect(Barcode_contours, 0);
			CvBox2D box = cvMinAreaRect2(Barcode_contours);
			// calculate the width/height and the  height/width
			float diffthrsould0, diffthrsould1;
			diffthrsould0 = (float)box.size.width / box.size.height;
			diffthrsould1 = (float)box.size.height / box.size.width;

			if (diffthrsould0>0.2&&diffthrsould0<1.8&&
				diffthrsould1>0.2&&diffthrsould1<1.8&&circlearea>70)
			{
				Rect Interst_ROI(templerect.x,templerect.y,templerect.width,templerect.height);
				Mat  Interst_ROI_Image;Interst_ROI_Image.create(templerect.height,templerect.width,CV_8UC1);
				Image_basic_function::Copy_Image(Interst_Image,Interst_ROI_Image,Interst_ROI);
 
				Mat Binary_normal_image(25,50,CV_8UC1);
				resize(Interst_ROI_Image,Binary_normal_image,Size(50,25),0,0,CV_INTER_NN);

				//Image_basic_function::Show_Image(Binary_normal_image);
				vector<float> Haar_feature_candicate;
				Haar_feature_candicate=vector<float>((int)Harr_feature.Get__numFeature(), 0.0f);
				Harr_feature.Get_Harr_feture(Binary_normal_image,Haar_feature_candicate);
				float relationship_parament=Harr_feature.Similar_relationship(Haar_feature_candicate);
				All_Rect_Image_Coffnicent.push_back(relationship_parament);
			}
	 }
}
QR_Location_detect::~QR_Location_detect()
{
	
	
}



