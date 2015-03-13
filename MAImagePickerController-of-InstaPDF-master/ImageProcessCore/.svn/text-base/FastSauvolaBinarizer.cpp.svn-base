
#include "FastSauvolaBinarizer.h"
#include "Image_basic_function.h"

#include "iostream"
using namespace std;

FastSauvolaBinarizer::FastSauvolaBinarizer()// default constructor 

{  
	// defult set  
	//cout <<"send "<<endl;
	windowsx = 29;
	windowsy = 29;
	kx = 0.10;
	max_var = 0.5;
 
}

FastSauvolaBinarizer::FastSauvolaBinarizer(int box_x,int box_y,float set_off_kx,float set_var )// parament  constructor 
{    
	 // user set 
	 windowsx=box_x;
	 windowsy=box_y;
	 kx=set_off_kx;
	 max_var=set_var;
}

void  FastSauvolaBinarizer::Binary_way(const Mat & input ,Mat& out_put ) 
{  

	// using the virtual to accomplish the binary ways   
	Mat  mean ;Mat square; //    declear the mean and square image 
	mean.create(input.rows,input.cols,CV_32FC1);
	square.create(input.rows,input.cols,CV_32FC1);
	// get the mean plane 
	M_mean(input, mean,CV_8U);
	// get the S_square plane 
	S_square(input,square);

	Mat mean_multi,deviation;
	mean_multi.create(mean.rows,mean.cols,CV_64FC1);
	deviation.create(mean.rows,mean.cols,CV_64FC1);
	Image_basic_function::multiply_own(mean,mean_multi); //32 64 
	Image_basic_function::subtract_own_32_32_64(square,mean_multi,deviation); // 32 32 64 
	FastSauvolaBinarizer::doing_sqrt(deviation);
	// malloc the  thousaldget plane space 
	Mat thousaldget;
	thousaldget.create(input.rows,input.cols,CV_32FC1);
	The_thousould_function(mean, deviation, thousaldget);
	Get_theBInary_image(thousaldget, input, out_put);

}


void FastSauvolaBinarizer::Image_Background_clean(Mat& input ,Mat& out_put)
{
		// using the virtual to accomplish the binary ways   
	Mat  mean ;Mat square; //    declear the mean and square image 
	mean.create(input.rows,input.cols,CV_32FC1);
	square.create(input.rows,input.cols,CV_32FC1);
	// get the mean plane 
	M_mean(input, mean,CV_8U);
	// get the S_square plane 
	S_square(input,square);

	Mat mean_multi,deviation;
	mean_multi.create(mean.rows,mean.cols,CV_64FC1);
	deviation.create(mean.rows,mean.cols,CV_64FC1);
	Image_basic_function::multiply_own(mean,mean_multi); //32 64 
	Image_basic_function::subtract_own_32_32_64(square,mean_multi,deviation); // 32 32 64 
	FastSauvolaBinarizer::doing_sqrt(deviation);
	// malloc the  thousaldget plane space 
	Mat thousaldget;
	thousaldget.create(input.rows,input.cols,CV_32FC1);
	The_thousould_function(mean, deviation, thousaldget);
	Get_The_clean_Image(thousaldget, input, out_put);

}
void FastSauvolaBinarizer::M_mean(const Mat &sourseimage, Mat& mean__square, int int_put_type) // in_put the sourceimage ;out_put the mean image 
{
   Mat intergral_image,Exterv_sourseimage;// intergeal image and  extern image declear 

   intergral_image.create(sourseimage.rows+windowsx+1,sourseimage.cols+windowsy+1,CV_64FC1);

   if(int_put_type==CV_8UC1)
   {

	   Exterv_sourseimage.create(sourseimage.rows+windowsx,sourseimage.cols+windowsy, CV_8UC1);
	   Image_basic_function::Set_Image_To_0_CV_8U(Exterv_sourseimage);
   }
   

   if (int_put_type==CV_32FC1)
   {

		 Exterv_sourseimage.create(sourseimage.rows+windowsx,sourseimage.cols+windowsy, CV_32FC1);
		 Image_basic_function::Set_Image_To_0_CV_32F(Exterv_sourseimage);
    
   }

   //Image_basic_function::Show_Image(Exterv_sourseimage);//  static  function  to call to show the dealing image 
   cv::Rect interest_rect;bool flag;
   interest_rect.x=(windowsx+1)/2;
   interest_rect.y=(windowsy+1)/2;
   interest_rect.height=sourseimage.rows;
   interest_rect.width=sourseimage.cols;
   flag=false;
   Image_basic_function::Copy_Image(sourseimage,Exterv_sourseimage,interest_rect,flag);// make the smaller sourseimage to bigger Exterv_sourseimage 
                                                                                  // with same interstROI by the interest_rect
   //Image_basic_function::Show_Image(Exterv_sourseimage); //  imshow  the  input image 
   integral(Exterv_sourseimage,intergral_image,CV_64F);
   Mat left_top_image ,left_bottem_image,right_top_image,right_bottem_image; //  Four index using image 
   left_top_image.create(sourseimage.rows,sourseimage.cols,CV_64FC1);
   left_bottem_image.create(sourseimage.rows,sourseimage.cols,CV_64FC1);
   right_top_image.create(sourseimage.rows,sourseimage.cols,CV_64FC1);
   right_bottem_image.create(sourseimage.rows,sourseimage.cols,CV_64FC1);
   cv::Rect rect_index[4]; 
   // first 
   rect_index[0].x=0;rect_index[0].y=0;rect_index[0].height=sourseimage.rows;rect_index[0].width=sourseimage.cols;
   flag=true;
   Image_basic_function::Copy_Image(intergral_image,left_top_image,rect_index[0],flag);
   //second 
   rect_index[1].x=windowsx;rect_index[1].y=windowsy;rect_index[1].height=sourseimage.rows;rect_index[1].width=sourseimage.cols;
   Image_basic_function::Copy_Image(intergral_image,right_bottem_image,rect_index[1],flag);
   // third 
   rect_index[2].x=0;rect_index[2].y=windowsy;rect_index[2].height=sourseimage.rows;rect_index[2].width=sourseimage.cols;
   Image_basic_function::Copy_Image(intergral_image,left_bottem_image,rect_index[2],flag);
   // four 
   rect_index[3].x=windowsx;rect_index[3].y=0;rect_index[3].height=sourseimage.rows;rect_index[3].width=sourseimage.cols;
   Image_basic_function::Copy_Image(intergral_image,right_top_image,rect_index[3],flag);

   Mat temple_add1,temple_add2;
   temple_add1.create(sourseimage.rows,sourseimage.cols,CV_64FC1);
   temple_add2.create(sourseimage.rows,sourseimage.cols,CV_64FC1);
   add(left_top_image,right_bottem_image,temple_add1,noArray(),CV_64FC1); //sorce  function  
  // Image_basic_function::add_own(left_top_image,right_bottem_image,temple_add1);// own function 
   Image_basic_function::add_own(left_bottem_image,right_top_image,temple_add2);
   Image_basic_function::subtract_own(temple_add1,temple_add2,mean__square);
   Image_basic_function::Value_Scale_Change(mean__square,windowsx ,windowsy); // calculate the windows's average ,it is a static  function 
}

void FastSauvolaBinarizer::S_square(const Mat& sourseimage, Mat& mean__square)
{
	 Mat Mul_image;
	 Mul_image.create(sourseimage.rows,sourseimage.cols,CV_32FC1);
	 Image_basic_function::multiply_8to32(sourseimage,Mul_image); //calculate the multi image
	 M_mean(Mul_image,mean__square,CV_32FC1);
   
}

void  FastSauvolaBinarizer::doing_sqrt( Mat & input  ) 
{
	for (int row_index=0;row_index<input.rows;row_index++)
	{  
		double* data =input.ptr<double>(row_index);
		for (int col_index=0;col_index<input.cols;col_index++)
		{
		  	    * data=sqrt(*data);
			     data++;
		}
	   
	}

}

void FastSauvolaBinarizer::The_thousould_function(Mat & mean, Mat & deviation, Mat & thousaldget)
{  
	// first step is to get the max_var

	max_var=Get_the_max_var(deviation);
	for (int row_index= 0; row_index<thousaldget.rows; row_index++)
		{
			float * point1 = mean.ptr<float>(row_index);
			double * point2 = deviation.ptr<double>(row_index);
			float * point3 = thousaldget.ptr<float>(row_index);

			for (int cols_index = 0; cols_index<thousaldget.cols; cols_index++)
			{
				double f1 = *point1;
				double f2 = 1 + kx*((*point2 / max_var) - 1);
				double f3 = f1*f2;
				*point3 = f3;
				point1++;
				point2++;
				point3++;
			}
		}
 
}


void FastSauvolaBinarizer::Get_theBInary_image(Mat &  thousaldget,const Mat &  input, Mat &  out_put)
{
	  for (int row_index = 0; row_index<out_put.rows; row_index++)
	  {
			float * point1 = thousaldget.ptr<float>(row_index);
			const unsigned char  * point2 = input.ptr<const unsigned char >(row_index);
			unsigned char  * point3 = out_put.ptr<unsigned char >(row_index);

			for (int cols_index = 0; cols_index<out_put.cols; cols_index++)
			{
				if (*point2> * point1)
				{
					*point3 = 255;
				}
				else
				{
					*point3 = 0;
				}

				point1++;
				point2++;
				point3++;
			}
	 }
}
void FastSauvolaBinarizer::Get_The_clean_Image(Mat &  thousaldget,const  Mat &  input, Mat &  out_put)
{

	for (int row_index = 0; row_index<out_put.rows; row_index++)
	{
			float * point1 = thousaldget.ptr<float>(row_index);
			const unsigned char  * point2 = input.ptr<const unsigned char >(row_index);
			unsigned char  * point3 = out_put.ptr<unsigned char >(row_index);

			for (int cols_index = 0; cols_index<out_put.cols; cols_index++)
			{
				if (*point2> * point1)
				{
					*point3 = 255;
				}
				else
				{
					*point3 = * point2;
				}

				point1++;
				point2++;
				point3++;
			}
	}
}


float FastSauvolaBinarizer::Get_the_max_var(Mat & deviation)
{   
	float max_value_var=0;
	for (int row_index=0;row_index<deviation.rows;row_index++)
	{  
		double* data =deviation.ptr<double>(row_index);
		for (int col_index=0;col_index<deviation.cols;col_index++)
		{
		  	     if (* data>max_value_var)
				 {
				   max_value_var=* data;
				     
				 }
			     data++;
		}
	   
	}
    return  max_value_var ;
}



FastSauvolaBinarizer:: ~FastSauvolaBinarizer()
{

   // cout<<"hello0"<<endl;
}

