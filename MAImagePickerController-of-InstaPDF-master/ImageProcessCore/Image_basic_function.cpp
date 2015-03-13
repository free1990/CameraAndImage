
#include "Image_basic_function.h"
#include "iostream"
using namespace std;

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
void  Image_basic_function::Set_Image_To_255_CV_8U(Mat & input)
{ 

	for (int row_index=0;row_index<input.rows;row_index++)
	{  
		unsigned char * data =input.ptr<unsigned char>(row_index);
		for (int col_index=0;col_index<input.cols;col_index++)
		{
		  	    * data=255;
			    data++;
		}
	   
	}
 
}

void  Image_basic_function::Set_Image_To_0_CV_32F(Mat & input)
{

	for (int row_index=0;row_index<input.rows;row_index++)
	{  
	    float  * data =input.ptr<float>(row_index);
		for (int col_index=0;col_index<input.cols;col_index++)
		{
		  	    * data=0;
			    data++;
		}
	   
	}
 

}
void  Image_basic_function::Set_Image_To_0_CV_8U(Mat & input)
{

	for (int row_index=0;row_index<input.rows;row_index++)
	{  
		unsigned char * data =input.ptr<unsigned char>(row_index);
		for (int col_index=0;col_index<input.cols;col_index++)
		{
		  	    * data=0;
			    data++;
		}
	   
	}

}
void  Image_basic_function::Set_Image_To_0_CV_8U_3Channel(Mat & input)
{

	for (int row_index=0;row_index<input.rows;row_index++)
	{  
		unsigned char * data =input.ptr<unsigned char>(row_index);
		for (int col_index=0;col_index<input.cols;col_index++)
		{
		  	    * data=0;
			      data++;

				* data=0;
				  data++;

				* data=0;
				  data++;
		}
	   
	}

}


void  Image_basic_function::Show_Image(Mat & input)
{
    namedWindow("input_image");
	imshow ("input_image",input);
	waitKey(0);

}

void  Image_basic_function::Show_Image_Wait_Key_20(Mat & input )
{
	namedWindow("input_image");
	imshow ("input_image",input);
	waitKey(1);
}


void  Image_basic_function::Copy_Image(const Mat & input ,Mat& out_put,Rect& interest_rect, bool flag )
{   
	if (flag==false)
	{
		cv::Mat imageROI=out_put(interest_rect);
		input.copyTo(imageROI);
	}

	if (flag==true)
	{
	   cv::Mat imageROI=input(interest_rect);
	   imageROI.copyTo(out_put);
	}


}

void  Image_basic_function::Value_Scale_Change(Mat &mean__square,int windowsx ,int windowsy)
{
  
	int Scale_factor=(windowsx+1)*(windowsy+1);

	for (int row_index=0;row_index<mean__square.rows;row_index++)
	{  
		float * data =mean__square.ptr<float>(row_index);
		for (int col_index=0;col_index<mean__square.cols;col_index++)
		{
		  	    * data=(* data)/Scale_factor;
			     data++;
		}
	   
	}
	

}

 void  Image_basic_function::add_own(Mat &input1,Mat &input2,Mat &output) // 64F 64F 64F 
{
	for (int row_index=0;row_index<output.rows;row_index++)
	{  
		double * data1 =input1.ptr<double>(row_index);
		double * data2 =input2.ptr<double>(row_index);
		double * data3 =output.ptr<double>(row_index);
		for (int col_index=0;col_index<output.cols;col_index++)
		{
		  	     *data3=(* data1)+(* data2);
			     data1++;
				 data2++;
				 data3++;
		}
	   
	}
	

 
}
 void  Image_basic_function::subtract_own(Mat &input1,Mat &input2,Mat &output) // 64F 64F 64F 
{
	for (int row_index=0;row_index<output.rows;row_index++)
	{  
		double * data1 =input1.ptr<double>(row_index);
		double * data2 =input2.ptr<double>(row_index);
		float * data3 =output.ptr<float>(row_index);
		for (int col_index=0;col_index<output.cols;col_index++)
		{
		  	     *data3=(* data1)-(* data2);
			     data1++;
				 data2++;
				 data3++;
		}
	   
	}
	

 
}

 void Image_basic_function::subtract_own_32_32_64(Mat &input1,Mat &input2,Mat &output)// 32 32 64
 {
 	for (int row_index=0;row_index<output.rows;row_index++)
	{  
		float * data1 =input1.ptr<float>(row_index);
		double * data2 =input2.ptr<double>(row_index);
		double * data3 =output.ptr<double>(row_index);
		for (int col_index=0;col_index<output.cols;col_index++)
		{
		  	     *data3=(* data1)-(* data2);
			     data1++;
				 data2++;
				 data3++;
		}
	   
	}
	
 
 }

 void  Image_basic_function::multiply_own(Mat &mean,Mat &mean_multi)// 32 64 
 {
 	for (int row_index=0;row_index<mean_multi.rows;row_index++)
	{  
		double * data1 =mean_multi.ptr<double>(row_index);
		float * data2 =mean.ptr<float>(row_index);
	
		for (int col_index=0;col_index<mean_multi.cols;col_index++)
		{
		  	     *data1=(* data2)*(* data2);
			     data1++;
				 data2++;
				
		}
	   
	}
	
 
 
 }
void Image_basic_function::multiply_8to32(const Mat & sourseimage,Mat & Mul_image) //calculate the   multi image 
{

	for (int row_index=0;row_index<Mul_image.rows;row_index++)
	{  
		float  * data1 =Mul_image.ptr<float>(row_index);
		const uchar * data2 =sourseimage.ptr<const uchar>(row_index);
	
		for (int col_index=0;col_index<Mul_image.cols;col_index++)
		{
		  	     *data1=(* data2)*(* data2);
			     data1++;
				 data2++;
				
		}
	   
	}

 

}

void  Image_basic_function::Reverse_image(Mat & input)
{

	if (input.type()==CV_8UC1)
	{
	   	for (int row_index=0;row_index<input.rows;row_index++)
	    {  
			
			 uchar * data=input.ptr<uchar>(row_index);
	
			for (int col_index=0;col_index<input.cols;col_index++)
			{
		  		if (* data==255)
				{
				    * data=0;
				}
				else
				{
					* data=255;
				    
				}
				data++;
				
			}
	   
	    }
	     
	}

}

 void  Image_basic_function::Mat_deep_copy_to_Iplimage(Mat &Bar_code_contain_image,IplImage *& C_syle_image)
 {
	 for(int j=0;j<C_syle_image->height;j++)
	 {
		 unsigned char *point_C =(unsigned char * )(C_syle_image->imageData+C_syle_image->widthStep*j);
		 unsigned char *point_Mat=Bar_code_contain_image.ptr<uchar>(j);
		 for (int i=0;i<C_syle_image->width;i++)
		 {
		        *point_C=*point_Mat;
				 point_C++;
				 point_Mat++;         
		 }
	       
	 
	 }
      
 
 }

void  Image_basic_function::IplImage_deep_copy_to_Mat(IplImage *&input ,Mat& output )
{    
	 for(int j=0;j<input->height;j++)
	 {
		 unsigned char *point_C =(unsigned char * )(input->imageData+input->widthStep*j);
		 unsigned char *point_Mat=output.ptr<uchar>(j);
		 for (int i=0;i<input->width;i++)
		 {
		         *point_Mat=*point_C;
				 point_C++;
				 point_Mat++;         
		 }
	 }
 
}


void Image_basic_function::Mat_deep_copy_to_IplImage(Mat& input ,IplImage* & output)
{   
	 
	 for(int j=0;j<output->height;j++)
	 {
		 unsigned char *point_C =(unsigned char * )(output->imageData+output->widthStep*j);
		 unsigned char *point_Mat=input.ptr<uchar>(j);
		 for (int i=0;i<output->width;i++)
		 {
		          *point_C=*point_Mat;
				   point_C++;
				   point_Mat++;
				  *point_C=*point_Mat;
				   point_C++;
				   point_Mat++;
				  *point_C=*point_Mat;
				   point_C++;
				   point_Mat++;
		 }
	 }
}
void  Image_basic_function::Mat_deep_copy_to_Iplimage_RGB(Mat &input,IplImage *&output)
{    
	 
 	 for(int j=0;j<output->height;j++)
	 {
		 unsigned char *point_C =(unsigned char * )(output->imageData+output->widthStep*j);
		 unsigned char *point_Mat=input.ptr<uchar>(j);
		 for (int i=0;i<output->width;i++)
		 {
		         *point_C=*point_Mat;

				  point_C++;
				  point_Mat++;
				 *point_C=*point_Mat;

				  point_C++;
				  point_Mat++;
				 *point_C=*point_Mat;

				  point_C++;
				  point_Mat++;
		 }
	       
	 }

}


 void  Image_basic_function::find_contour_with_C_style(IplImage* &Binary_input,CvSeq* &contours,CvMemStorage* &storage)
 {
 
     cvFindContours(Binary_input, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, cvPoint(0, 0));
 }

 void  Image_basic_function::find_contour_with_C_style_list(IplImage* &Binary_input,CvSeq* &contours,CvMemStorage* &storage)
 {
     cvFindContours(Binary_input, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0, 0));
 }


void Image_basic_function::find_contour_with_C_style_additional_innerContour(IplImage* & Binary_input,CvSeq* &contours,CvMemStorage* &storage)
{

    cvFindContours(Binary_input, storage, &contours, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, cvPoint(0, 0));

}
void Image_basic_function ::C_show_image(IplImage * & input)
{

	  cvNamedWindow("input",0);
	  cvShowImage("input",input);
	  cvWaitKey(0);

}

void  Image_basic_function::Draw_contours(CvSeq* &contours,IplImage* & input )
{
	IplImage * RGB_copy;
	RGB_copy=cvCreateImage(cvSize(input->width,input->height),IPL_DEPTH_8U,3);
    for (;contours != 0; contours = contours->h_next)
	{
		int totol_points=contours->total;
	  
		for(int i=0;i<totol_points;i++) 
		{
			CvPoint *p =(CvPoint *)cvGetSeqElem(contours ,i);// it needs to make a  force transform
			CvPoint pt1;
			pt1=*p;
			int x=pt1.x;
			int y=pt1.y;
			CvScalar color=CV_RGB(255,0,0);
			cvCircle(RGB_copy,pt1,1,color);// make a small circle ,so it is easy to show the templevalue when runing the programme
			cvNamedWindow("RGB_copy_drawing",0);
			cvShowImage("RGB_copy_drawing",RGB_copy);
			cvWaitKey(100);
		}	
	}
}

 float Image_basic_function::White_pixls_of_input_image(IplImage * & C_syle_image_Copy, CvRect &templerect)
 {
    
	    float percent = 0;
		float hole_number = templerect.width*templerect.height;
		int  acculate_white_number = 0;

		IplImage * image = cvCreateImage(cvSize(templerect.width, templerect.height), 8, 1);
		cvSetImageROI(C_syle_image_Copy, templerect);
		cvCopy(C_syle_image_Copy, image);
		cvResetImageROI(C_syle_image_Copy);
		for (int i = 0; i < image->height; i++)
		{
			unsigned char * p = (unsigned char*)image->imageData + image->widthStep*i;

			for (int j = 0; j < image->width; j++)
			{
				if (*p == 255)
				{
					acculate_white_number++;
				}

				p++;
			}
		}

		cvReleaseImage(&image);
		return  acculate_white_number / float(hole_number);
  
 }

float Image_basic_function::Black_pixls_of_input_image_Mat(Mat &input_Mat, CvRect &templerect)
{    
	 float whitle_percent =0;
	 int  acculate_white_number = 0; 

	 // The function is to find the whilte percent of the input_Mat's ROI
	 Rect interest_Roi(templerect);
	 Mat  interst_image;
	 interst_image.create(templerect.height,templerect.width,CV_8UC1);
	 Copy_Image(input_Mat,interst_image,interest_Roi,true);
	 //Image_basic_function::Show_Image(interst_image);
	 for (int row_index = 0; row_index<interst_image.rows; row_index++)
	 {
		unsigned char * p = interst_image.ptr<unsigned char>(row_index);
		for (int col_index = 0; col_index < interst_image.cols; col_index++)
		{
			if (*p == 0)
			{
				acculate_white_number++;
			}

			p++;
		}
	 }
	 return  (float)acculate_white_number / float(templerect.width*templerect.height);
  
}

void  Image_basic_function::Rotation(Mat& src_img,Mat& dst,float angle)
{ 

  if (angle!=0&&abs(angle)>0.3) 
  {
	  // get the dst image,the size is same as the src_img ,it can sure that the sacle between top rect and question rect stabily  
	  Mat dst_img = src_img.clone();

	  // set ROI ,it can rotation the interest part by users 
	  Rect roi_rect(cvRound(src_img.cols*0.0), cvRound(src_img.rows*0.0), cvRound(src_img.cols), cvRound(src_img.rows));
	  Mat src_roi(src_img, roi_rect);
	  Mat dst_roi(dst_img, roi_rect);

	  // With specified three parameters (angle, rotation center, scale)
	  // calculate an affine transformation matrix by cv2DRotationMatrix
	  float  scale =1.0;
	  Point2d center(src_roi.cols*0.5, src_roi.rows*0.5);
	  const Mat affine_matrix = getRotationMatrix2D( center, angle, scale );

	  //rotate the image by warpAffine taking the affine matrix
	  warpAffine(src_roi, dst_roi, affine_matrix, dst_roi.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(255));

	  //show source and destination images with a rectangle indicating ROI
	  //rectangle(src_img, roi_rect.tl(), roi_rect.br(), Scalar(255,0,255), 2);

	  //imshow the rotation image 
	  dst=dst_roi.clone();

	  //Image_basic_function::Show_Image(dst);
  }
  else 
  {
  
      dst=src_img.clone();
  }

  // here some tips ,when the rotation is to big ,the top rect and question rect may remove out of the image  ,if the situation had occured ,the progranme should make a small change 
}

int Image_basic_function::Static_Calculate(Mat &Image_interst_ROI,float& H_max,float & H_min,float& S_max,float &S_min,float& V_max,float &V_min)
{  

	int number_like=0;
	IplImage* Image_interst_ROI_C=cvCreateImage(cvSize(Image_interst_ROI.cols,Image_interst_ROI.rows),IPL_DEPTH_8U,3);
	Mat_deep_copy_to_Iplimage_RGB(Image_interst_ROI,Image_interst_ROI_C);
	IplImage * floatsrc = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 3);
	IplImage * floathsv = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 3);
	IplImage * floatimgH = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 1);
	IplImage * floatimgS = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 1);
	IplImage * floatimgV = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 1);
	cvConvertScale(Image_interst_ROI_C, floatsrc, 1.0 / 255.0, 0);
	cvCvtColor(floatsrc, floathsv, CV_BGR2HSV);
	cvSplit(floathsv, floatimgH, floatimgS, floatimgV, NULL);
	for (int j = 0; j < Image_interst_ROI_C->height; j++)
	{
		float *H = (float *)(floatimgH->imageData + floatimgH->widthStep*j);
		float *S = (float *)(floatimgS->imageData + floatimgS->widthStep*j);
		float *V = (float *)(floatimgV->imageData + floatimgV->widthStep*j);
		for (int i = 0; i < Image_interst_ROI_C->width; i++)
		{
			if ((*S >S_min)&&(*S <S_max)&& (*V >V_min)&&(*V<V_max))
			{
				if( (*H >H_min) && (*H<H_max) )
				{
					number_like++;
				}

			}
			H++;
			S++;
			V++;
		}
	}
	cvReleaseImage(&floatsrc);
	cvReleaseImage(&floathsv);
	cvReleaseImage(&floatimgH);
	cvReleaseImage(&floatimgS);
	cvReleaseImage(&floatimgV);
	cvReleaseImage(&Image_interst_ROI_C);
	return number_like;
}
void Image_basic_function::Set_Bule_Gray_to_White(Mat & Image_interst_ROI )
{

    IplImage* Image_interst_ROI_C=cvCreateImage(cvSize(Image_interst_ROI.cols,Image_interst_ROI.rows),IPL_DEPTH_8U,3);
	Mat_deep_copy_to_Iplimage_RGB(Image_interst_ROI,Image_interst_ROI_C);
	IplImage * floatsrc = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 3);
	IplImage * floathsv = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 3);
	IplImage * floatimgH = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 1);
	IplImage * floatimgS = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 1);
	IplImage * floatimgV = cvCreateImage(cvSize(Image_interst_ROI_C->width, Image_interst_ROI_C->height), IPL_DEPTH_32F, 1);
	cvConvertScale(Image_interst_ROI_C, floatsrc, 1.0 / 255.0, 0);
	cvCvtColor(floatsrc, floathsv, CV_BGR2HSV);
	cvSplit(floathsv, floatimgH, floatimgS, floatimgV, NULL);
	for (int j = 0; j < Image_interst_ROI_C->height; j++)
	{
		float *H = (float *)(floatimgH->imageData + floatimgH->widthStep*j);
		float *S = (float *)(floatimgS->imageData + floatimgS->widthStep*j);
		float *V = (float *)(floatimgV->imageData + floatimgV->widthStep*j);
		unsigned char *point_interst_ROI=Image_interst_ROI.ptr<unsigned char>(j);

		for (int i = 0; i < Image_interst_ROI_C->width; i++)
		{
			if ((*S >0.28)&&(*S <0.48)&& (*V >0.24)&&(*V<0.44)&&(*H >155) && (*H<185) )
			{
				*point_interst_ROI=255;
				 point_interst_ROI++;
				*point_interst_ROI=255;
				 point_interst_ROI++;
				*point_interst_ROI=255;
				 point_interst_ROI++;
			}	
			else
			{
				point_interst_ROI++;
				point_interst_ROI++;
				point_interst_ROI++;
			}

		
			H++;
			S++;
			V++;
		}
	 }
	
	cvReleaseImage(&floatsrc);
	cvReleaseImage(&floathsv);
	cvReleaseImage(&floatimgH);
	cvReleaseImage(&floatimgS);
	cvReleaseImage(&floatimgV);
	cvReleaseImage(&Image_interst_ROI_C);
 }
void Image_basic_function::Set_32F_To_Zero(Mat &input)
{
	for (int row_index=0;row_index<input.rows;row_index++)
	{  
		float * data =input.ptr<float >(row_index);
		for (int col_index=0;col_index<input.cols;col_index++)
		{
		  	    * data=0;
			    data++;
		}
	   
	}

}
Mat Image_basic_function::Create_space_with_hough(Mat &Image_interst_ROI_Binary,int &angle_start ,int& angle_end ,int & rho_max)
{
	Mat canny_image;Mat The_rho_space;
	Canny(Image_interst_ROI_Binary,canny_image,30,90);

	//Image_basic_function::Show_Image(canny_image);
	int width =canny_image.cols;int height=canny_image.rows;
	rho_max=sqrt((float)(width*width+height*height)); int numangle =180;
	The_rho_space.create(rho_max,numangle,CV_32FC1);
	Set_32F_To_Zero(The_rho_space);
	for ( int j=0;j<canny_image.rows;j++)
	{
	   unsigned char * point =canny_image.ptr<unsigned char>(j);
	   for (int i=0;i<canny_image.cols;i++)
	   {
	      Point temp_point(i,j);
		  if (temp_point.x>3&&temp_point.x<(canny_image.cols-3)&&
			     temp_point.y>3&&temp_point.y<(canny_image.rows-3))
		  {
		       if (* point==255)
			   {
				    for(int n=angle_start;n<angle_end;n++)
					{
					    float the1=cos(float(n*CV_PI/180));
						float the2=sin(float(n*CV_PI/180));
						float rho=temp_point.x*cos(float(n*CV_PI/180))+temp_point.y*sin(float(n*CV_PI/180));
					    rho+=rho_max;
						rho=rho/2;
						if (rho>The_rho_space.rows) //it is used for de_force out of range
						{
						   rho=The_rho_space.rows-1;
						}
					    float * point_space=The_rho_space.ptr<float>(rho);
						point_space+=n;
						++(*point_space);
					}
			   }
		  }
		  point++;   
	   }
	}
	return The_rho_space;
}

void Image_basic_function::Show_line_in_image(Point& pt1 ,Point& pt2 ,Mat & image)
{
	line(image,pt1,pt2,CV_RGB(255,0,0),1);
	Image_basic_function::Show_Image(image);
}


float Image_basic_function::Black_Points_Get(Mat& input)
{
	 int  Black_pixls_number = 0; 
	 for (int row_index = 0; row_index<input.rows; row_index++)
	 {
		unsigned char * p = input.ptr<unsigned char>(row_index);
		for (int col_index = 0; col_index < input.cols; col_index++)
		{   
		
			if (*p == 0)
			{
				Black_pixls_number++;
			}
			p++;

		}
	 }
	 return Black_pixls_number;
}

float Image_basic_function::Red_Points_Get(Mat& input,bool Is_Enhancement)
{
	int Red_Pixls_number=0;
	IplImage* output =cvCreateImage(cvSize(input.cols,input.rows),IPL_DEPTH_8U,3);
	Image_basic_function::Mat_deep_copy_to_Iplimage_RGB(input,output);
	IplImage * floatsrc = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 3);
	IplImage * floathsv = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 3);
	IplImage * floatimgH = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 1);
	IplImage * floatimgS = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 1);
	IplImage * floatimgV = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 1);
	cvConvertScale(output, floatsrc, 1.0 / 255.0, 0);
	cvCvtColor(floatsrc, floathsv, CV_BGR2HSV);
	cvSplit(floathsv, floatimgH, floatimgS, floatimgV, NULL);

	float S_thshould=0,V_thshould=0;

	if (Is_Enhancement)
	{
	   S_thshould=0.6;V_thshould=0.6;
	}
	else
	{
	   S_thshould=0.15;V_thshould=0.5;
	}
	for (int j = 0; j < output->height; j++)
	{
		float *H = (float *)(floatimgH->imageData + floatimgH->widthStep*j);
		float *S = (float *)(floatimgS->imageData + floatimgS->widthStep*j);
		float *V = (float *)(floatimgV->imageData + floatimgV->widthStep*j);
		for (int i = 0; i < output->width; i++)
		{
			if (*S >=S_thshould&&*V >=V_thshould)
			{
				if((*H >=0&&*H<=12)||(*H >=315&&*H<=360))
				{
					Red_Pixls_number++;
				}
			}
			H++;
			S++;
			V++;
		}
	}
	cvReleaseImage(&floatsrc);
	cvReleaseImage(&floathsv);
	cvReleaseImage(&floatimgH);
	cvReleaseImage(&floatimgS);
	cvReleaseImage(&floatimgV);
	cvReleaseImage(&output);
    return Red_Pixls_number;
}

float Image_basic_function::Red_Together_Points_Get(Mat& input)
{
	float  Red_together_Pixls_number=0;
	IplImage* output =cvCreateImage(cvSize(input.cols,input.rows),IPL_DEPTH_8U,3);
	IplImage* red_reflect =cvCreateImage(cvSize(input.cols,input.rows),IPL_DEPTH_8U,1);
	Image_basic_function::Mat_deep_copy_to_Iplimage_RGB(input,output);
	Get_Red_reflect_image(output,red_reflect);
	IplImage* BIgger_image=cvCreateImage(cvSize(input.cols*3,input.rows*3),IPL_DEPTH_8U,1);
	Set_8U_IplImage_To_zero(BIgger_image);
	CvRect copy_interest;
	copy_interest.x=BIgger_image->width/2-output->width/2;
	copy_interest.y=BIgger_image->height/2-output->height/2;
	copy_interest.width=output->width;copy_interest.height=output->height;
	cvSetImageROI(BIgger_image, copy_interest);
	cvCopy(red_reflect, BIgger_image);
	cvResetImageROI(BIgger_image);
	//Now the BIgger_image is black  ,but not Whole  ,beacuse the Red part in centre is project to the  BIgger_image's centre 
	
	//Find the Red Countour in the BIgger_image image ,which present us is whilte together pixls
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours;
	cvFindContours(BIgger_image, storage, &contours, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, cvPoint(0, 0));

	for (; contours != 0; contours = contours->h_next)
	{
		float current_length = cvArcLength(contours, CV_WHOLE_SEQ, -1);
		if (Red_together_Pixls_number < current_length)
		{
			Red_together_Pixls_number = current_length;
		}

	}
	cvReleaseImage(&output); 
	cvReleaseImage(&red_reflect);
	cvReleaseMemStorage(&storage);
	return Red_together_Pixls_number;
}
void Image_basic_function::Get_Red_reflect_image(IplImage*& output,IplImage*& red_reflect)
{
	IplImage * floatsrc = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 3);
	IplImage * floathsv = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 3);
	IplImage * floatimgH = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 1);
	IplImage * floatimgS = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 1);
	IplImage * floatimgV = cvCreateImage(cvSize(output->width, output->height), IPL_DEPTH_32F, 1);
	cvConvertScale(output, floatsrc, 1.0 / 255.0, 0);
	cvCvtColor(floatsrc, floathsv, CV_BGR2HSV);
	cvSplit(floathsv, floatimgH, floatimgS, floatimgV, NULL);
	for (int j = 0; j < red_reflect->height; j++)
	{
		float *H = (float *)(floatimgH->imageData + floatimgH->widthStep*j);
		float *S = (float *)(floatimgS->imageData + floatimgS->widthStep*j);
		float *V = (float *)(floatimgV->imageData + floatimgV->widthStep*j);
		unsigned char *reflect_point = (unsigned char *)(red_reflect->imageData + red_reflect->widthStep*j);
		for (int i = 0; i < red_reflect->width; i++)
		{
			if (*S >= 0.15 && *V >= 0.15)
			{

				if ((*H >= 0 && *H <= 12) || (*H >= 315 && *H <= 360))
				{
					*reflect_point = 255;
				}
				else
				{
					*reflect_point = 0;
				}
			}
			else
			{
				*reflect_point = 0;
			}
			H++;
			S++;
			V++;
			reflect_point++;
		}
	}
	cvReleaseImage(&floatsrc);
	cvReleaseImage(&floathsv);
	cvReleaseImage(&floatimgH);
	cvReleaseImage(&floatimgS);
	cvReleaseImage(&floatimgV);
}

void Image_basic_function::Set_8U_IplImage_To_zero(IplImage* & BIgger_image)
{
	for (int j = 0; j < BIgger_image->height; j++)
	{
		unsigned char *point = (unsigned char *)(BIgger_image->imageData + BIgger_image->widthStep*j);
		for (int i = 0; i < BIgger_image->width; i++)
		{
			*point = 0;
			point++;
		}
	}
}
void  Image_basic_function::readImageSequenceFiles(char* imgFilePath,vector <string> &imgNames)
{
//	imgNames.clear();
//	char tmpDirSpec[MAX_PATH+1];
//	sprintf (tmpDirSpec, "%s/*", imgFilePath);
//
//	WIN32_FIND_DATA f;
//	HANDLE h = FindFirstFile(tmpDirSpec , &f);
//	if(h != INVALID_HANDLE_VALUE)
//	{
//		FindNextFile(h, &f);	//read ..
//		FindNextFile(h, &f);	//read .
//		do
//		 {
//		 imgNames.push_back(f.cFileName);
//		 }
//		 while(FindNextFile(h, &f));
//
//	}
//	FindClose(h);	
}

void Image_basic_function::ImgRotate_ownSelf(cv::Mat& imgIn, float& theta, cv::Mat& imgOut) 
{   
	// The input theta is not angle ,is in cirle judjetment 
    int oldWidth = imgIn.cols;  
    int oldHeight = imgIn.rows;  
  
    // sorce image's  four contour ,which is project to the top aix_X_Y 
    float fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;  
    fSrcX1 = (float) (- (oldWidth  - 1) / 2);  
    fSrcY1 = (float) (  (oldHeight - 1) / 2);  
    fSrcX2 = (float) (  (oldWidth  - 1) / 2);  
    fSrcY2 = (float) (  (oldHeight - 1) / 2);  
    fSrcX3 = (float) (- (oldWidth  - 1) / 2);  
    fSrcY3 = (float) (- (oldHeight - 1) / 2);  
    fSrcX4 = (float) (  (oldWidth  - 1) / 2);  
    fSrcY4 = (float) (- (oldHeight - 1) / 2);  
  
    // After rotation the New Points of the four contour 
    float fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;  
    fDstX1 =  cos(theta) * fSrcX1 + sin(theta) * fSrcY1;  
    fDstY1 = -sin(theta) * fSrcX1 + cos(theta) * fSrcY1;  
    fDstX2 =  cos(theta) * fSrcX2 + sin(theta) * fSrcY2;  
    fDstY2 = -sin(theta) * fSrcX2 + cos(theta) * fSrcY2;  
    fDstX3 =  cos(theta) * fSrcX3 + sin(theta) * fSrcY3;  
    fDstY3 = -sin(theta) * fSrcX3 + cos(theta) * fSrcY3;  
    fDstX4 =  cos(theta) * fSrcX4 + sin(theta) * fSrcY4;  
    fDstY4 = -sin(theta) * fSrcX4 + cos(theta) * fSrcY4;  
  
    int newWidth  = ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);  
    int newHeight = ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) )  + 0.5);  
  
    imgOut.create(newHeight, newWidth, imgIn.type());  
  
    float dx = -0.5*newWidth*cos(theta) - 0.5*newHeight*sin(theta) + 0.5*oldWidth;  
    float dy = 0.5*newWidth*sin(theta) - 0.5*newHeight*cos(theta) + 0.5*oldHeight;  
  
    int x=0;int y=0 ;  
    for (int i=0; i<newHeight; i++)  
    {  
        for (int j=0; j<newWidth; j++)  
        {  
            x = float(j)*cos(theta) + float(i)*sin(theta) + dx;  
            y = float(-j)*sin(theta) + float(i)*cos(theta) + dy;  
  
            if ((x<0) || (x>=oldWidth) || (y<0) || (y>=oldHeight))  
            {  
                if (imgIn.channels() == 3)  
                {  
                    imgOut.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);  
                }  
                else if (imgIn.channels() == 1)  
                {  
                    imgOut.at<uchar>(i,j) = 0;  
                }  
            }  
            else  
            {  
                if (imgIn.channels() == 3)  
                {  
                    imgOut.at<cv::Vec3b>(i,j) = imgIn.at<cv::Vec3b>(y,x);  
                }  
                else if (imgIn.channels() == 1)  
                {  
                    imgOut.at<uchar>(i,j) = imgIn.at<uchar>(y,x);  
                }  
            }  
        }  
    }  
}  

void Image_basic_function::Sharp_To_Image(Mat& input ,Mat & output)
{
    Mat kernel(3,3,CV_32F,Scalar(-1));   
    kernel.at<float>(1,1) = 9.0;  
    filter2D(input,output,input.depth(),kernel); 
}

void Image_basic_function::Write_message_To_Text(vector<Rect>& Top_Rect_Infoemation ,vector<vector<Point>>)
{
     FILE* resultStream;
	 resultStream=fopen("Location_result.txt","w");

}
float Image_basic_function::Distance_Between_Points(Point& pt1,Point& pt2)
{
	float distance=sqrt((float)((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y)));
	return distance;
}

float Image_basic_function::Distance_Between_Location(float x1,float y1,float x2,float y2)
{
	float distance=sqrt((float)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
	return distance;
}
int Image_basic_function::circle_circle_intersection(float x0, float y0, float r0,float x1, float y1, float r1,float *xi, float *yi,float *xi_prime, float *yi_prime)
{
  float a, dx, dy, d, h, rx, ry;
  float x2, y2;

  /* dx and dy are the vertical and horizontal distances between
   * the circle centers.
   */
  dx = x1 - x0;
  dy = y1 - y0;

  /* Determine the straight-line distance between the centers. */
  //d = sqrt((dy*dy) + (dx*dx));
  d = hypot(dx,dy); // Suggested by Keith Briggs

  /* Check for solvability. */
  if (d > (r0 + r1))
  {
    /* no solution. circles do not intersect. */
    return 0;
  }
  if (d < fabs(r0 - r1))
  {
    /* no solution. one circle is contained in the other */
    return 0;
  }
  /* 'point 2' is the point where the line through the circle
   * intersection points crosses the line between the circle
   * centers.  
   */

  /* Determine the distance from point 0 to point 2. */
  a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;
  /* Determine the coordinates of point 2. */
  x2 = x0 + (dx * a/d);
  y2 = y0 + (dy * a/d);

  /* Determine the distance from point 2 to either of the
   * intersection points.
   */
  h = sqrt((r0*r0) - (a*a));

  /* Now determine the offsets of the intersection points from
   * point 2.
   */
  rx = -dy * (h/d);
  ry = dx * (h/d);

  /* Determine the absolute intersection points. */
  *xi = x2 + rx;
  *xi_prime = x2 - rx;
  *yi = y2 + ry;
  *yi_prime = y2 - ry;
  return 1;
}


void Image_basic_function::Connect_Two_Image_vertical(Mat& input1 ,Mat& input2,Mat& output)
{
	int bigger_width=0;int height=input1.rows+input2.rows;
	if (input1.cols>=input2.cols)
	{
		bigger_width=input1.cols;
	}
	else
	{
		bigger_width=input2.cols;
	}
	output.create(height,bigger_width,CV_8UC3);
	Rect up_rect(0,0,input1.cols,input1.rows);
	Copy_Image(input1,output,up_rect,false);
	Rect bottem_rect(0,input1.rows,input2.cols,input2.rows);
	Copy_Image(input2,output,bottem_rect,false);
}