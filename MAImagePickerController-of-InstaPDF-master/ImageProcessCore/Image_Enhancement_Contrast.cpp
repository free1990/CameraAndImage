#include "Image_Enhancement_Contrast.h"


Image_Enhancement_Contrast::Image_Enhancement_Contrast():Thousold_Blue(0),Thousold_Green(0),Thousold_Red(0),Is_Enhancement(false)
{
	Blue_Max_Background_value=0;
	Green_Max_Background_value=0;
	Red_Max_Background_value=0;
	Blue_percent10_upper=0;
	Green_percent10_upper=0;
	Red_percent10_upper=0;
}

void Image_Enhancement_Contrast::Scan_Image_Enhancement(Mat& input ,Mat& output) // image was captured from the Scaning equaiment 
{
    std::vector<cv::Mat> Image_BGR;
//    Mat Image_BGR[3];
    Mat  Image_BGR_Binary_Virtual[3];
    Mat Image_Gray;
    Mat Image_Gray_Binary;

	// Split the three channnels image 
	cv::split(input,Image_BGR);
    

	// Using the Otsu algorithm to determine the globle threshld
	// blue channel
	Globle_Otsu_Binarizer* point=new Globle_Otsu_Binarizer();
	point->Binary_way(Image_BGR[0],Image_BGR_Binary_Virtual[0]);
	Thousold_Blue=point->Thoushold_Value;
	Blue_Max_Background_value=point->background_value;
	Blue_percent10_upper=point->Percent10_upper_by_Thoushold_Value_index;
	// green channel
	point->Binary_way(Image_BGR[1],Image_BGR_Binary_Virtual[1]);
	Thousold_Green=point->Thoushold_Value;
	Green_Max_Background_value=point->background_value;
	Green_percent10_upper=point->Percent10_upper_by_Thoushold_Value_index;
    // red channel 
	point->Binary_way(Image_BGR[2],Image_BGR_Binary_Virtual[2]);
	Thousold_Red=point->Thoushold_Value;
	Red_Max_Background_value=point->background_value;
	Red_percent10_upper=point->Percent10_upper_by_Thoushold_Value_index;
	delete point;
	// Get the sobel image fo the BGR Three channels 

	// if the dark is lower than 220 ,it represent the canner not using the correct contrast,and it should do a enhancement ,otherwise nothing should do 
	if (Blue_Max_Background_value<210&&Green_Max_Background_value<210&&Red_Max_Background_value<210)
	{
		Set_Background_With_MaxValue(Image_BGR[0],Image_BGR_Binary_Virtual[0],Thousold_Blue,Blue_percent10_upper);
		Set_Background_With_MaxValue(Image_BGR[1],Image_BGR_Binary_Virtual[1],Thousold_Green,Green_percent10_upper);
		Set_Background_With_MaxValue(Image_BGR[2],Image_BGR_Binary_Virtual[2],Thousold_Red,Red_percent10_upper);
		Is_Enhancement=true;
	}
	else
	{  
		Image_BGR_Binary_Virtual[0]=Image_BGR[0].clone();
		Image_BGR_Binary_Virtual[1]=Image_BGR[1].clone();
		Image_BGR_Binary_Virtual[2]=Image_BGR[2].clone();
	}
	// merge the three channels of the RGB
	merge(Image_BGR_Binary_Virtual,3,output);
}
void Image_Enhancement_Contrast::Fix_Photo_Image_Enhancement(Mat& input ,Mat& output) // Here the "fix" represent the Capture camera is not change! 
{
	 // it is fixed cammer to capture the image 

}
void Image_Enhancement_Contrast::Phone_Photo_Image_Enhancement(Mat& input ,Mat& output) // Image was captured from the narural phone devices 
{

	Mat Image_BGR[3];Mat Image_BGR_Binary[3],Image_BGR_Binary_Virtual[3];Mat Image_Gray;Mat Image_Gray_Binary;

	// Split the three channnels image 
	cv::split(input,Image_BGR);
	Image_BGR_Binary[0]=Image_BGR[0].clone();
	Image_BGR_Binary[1]=Image_BGR[1].clone();
	Image_BGR_Binary[2]=Image_BGR[2].clone();

	// Using the Otsu algorithm to determine the globle thrshold 
	FastSauvolaBinarizer* point=new FastSauvolaBinarizer(40,40,0.1,0.2);
	point->Image_Background_clean(Image_BGR[0],Image_BGR_Binary[0]);
	point->Image_Background_clean(Image_BGR[1],Image_BGR_Binary[1]);
	point->Image_Background_clean(Image_BGR[2],Image_BGR_Binary[2]);
	delete point;

	// using the special iamge enhancement handle way 
	Sharp_Image(Image_BGR_Binary[0],Image_BGR_Binary_Virtual[0]);
	Sharp_Image(Image_BGR_Binary[1],Image_BGR_Binary_Virtual[1]);
	Sharp_Image(Image_BGR_Binary[2],Image_BGR_Binary_Virtual[2]);
	merge(Image_BGR_Binary_Virtual,3,output);
	//imwrite("result2.jpg",output);
}


void Image_Enhancement_Contrast::Set_Background_With_MaxValue(Mat& input,Mat& output,float Thousold_Value,float Percent10_upper)
{   
	output.create(input.rows,input.cols,CV_8UC1);
	for (int j=0;j<input.rows;j++)
	{   
		unsigned char *point_Input=input.ptr<uchar>(j);
		unsigned char *point_Output=output.ptr<uchar>(j);
		for (int i=0;i<input.cols;i++)
		{
		    if (*point_Input>Thousold_Value)
			{     
				  if (*point_Input<Percent10_upper)
				  {
				      *point_Output=*point_Input;// it may to be the foreground ,so it should be save 
				  }
				  else
				  {
			          *point_Output=255;
				  }
			}
			else
			{    
				 if (*point_Input<20)
				 {
			        *point_Output=0;
				 }
				 else
				 {
				    *point_Output=0;
				 }
			}
			point_Input++;
			point_Output++;
		}
	}
}


void Image_Enhancement_Contrast::Set_Background_By_Binary_Image(Mat & input ,Mat& binary ,Mat& output)
{
	output.create(input.rows,input.cols,CV_8UC1);
	for (int j=0;j<input.rows;j++)
	{   
		unsigned char *point_Input=input.ptr<uchar>(j);
		unsigned char *point_binary=binary.ptr<uchar>(j);
		unsigned char *point_Output=output.ptr<uchar>(j);
		for (int i=0;i<input.cols;i++)
		{
			if (*point_binary>190)
			{
			     *point_Output=255;
			}
			else
			{
				*point_Output=0;
			}
			point_Input++;
			point_Output++;
			point_binary++;
		}
	}
}
void Image_Enhancement_Contrast::Sobel_edge_detection(Mat& input ,Mat& output)
{

	// Define operators
	Mat dst_x ,dst_y;
    Sobel(input, dst_x, input.depth(), 1, 0);  
    Sobel(input, dst_y, input.depth(), 0, 1);  
    convertScaleAbs(dst_x, dst_x);  
    convertScaleAbs(dst_y, dst_y);  
    addWeighted( dst_x, 0.5, dst_y, 0.5, 0, output);
}

Mat Image_Enhancement_Contrast::histeq(Mat& in)
{
    Mat out(in.size(), in.type());
    if(in.channels()==3)
	{
        Mat hsv;
        vector<Mat> hsvSplit;
        cvtColor(in, hsv, CV_BGR2HSV);
        split(hsv, hsvSplit);
        equalizeHist(hsvSplit[2], hsvSplit[2]);
        merge(hsvSplit, hsv);
        cvtColor(hsv, out, CV_HSV2BGR);
    }
	else if(in.channels()==1)
	{
        equalizeHist(in, out);
    }
    return out;
}

void Image_Enhancement_Contrast::Sharp_Image(Mat& myImage,Mat& Result )
{

	// This programe is accomadate with the one and three channels 
	Result.create(myImage.size(), myImage.type());
	const int nChannels = myImage.channels();

	// 
	for (int j = 1; j < myImage.rows - 1; j++)
	{
		const uchar* previous = myImage.ptr<uchar>(j - 1);
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j + 1);

		uchar* output = Result.ptr<uchar>(j);
		
		for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
		{
			*output++ = saturate_cast<uchar>(5 * current[i]
				- current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]); //when 
		}
		
	}
	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
}