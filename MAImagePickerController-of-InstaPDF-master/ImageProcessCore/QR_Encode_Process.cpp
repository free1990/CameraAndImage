#include "QR_Encode_Process.h"
#include <vector>
#include <string>
#include <zxing/multi/MultipleBarcodeReader.h>
#include <zxing/multi/MultipleBarcodeReader.h>
#include <zxing/multi/GenericMultipleBarcodeReader.h>
#include "FastSauvolaBinarizer.h"
#include "QR_Location_detect.h"

using namespace std ;
using namespace multi;


QR_Encode_Process::QR_Encode_Process(zxing::ArrayRef<char> image_, int width, int height, int comps_): Super(width, height), image(image_), comps(comps_) 
{

}

void QR_Encode_Process::Encode_Interface(Mat& input,bool Is_A4_Image,vector<string>& Bar_Code_Contain_Information)
{   
	// Here has two image as input arguement ,one is A4 ,another is A3
	// Frist step is to resize the input image to 0.5 scale of the input ,so it is quickly detect the bar_code location 
	// As the bar_code location had detected ,than project to the sorce image ,and copy it to the bar_code for Zxing to decode 
	// if the page is A4,Top and left is all 25 Percent,but the Left is 25% percent 
	if (Is_A4_Image)
	{
		// resize the image to the half scale 
		Mat Scale_Sorce_Image; 
		resize(input,Scale_Sorce_Image,Size(input.cols*0.5,input.rows*0.5));

		// detect the bar_code location using the Eclipse mogphy
	    Detected_by_Rect_Eclipse(Scale_Sorce_Image,Is_A4_Image);

		// check the detected if it is true ---if the detect is false ,it need to using kernel Rect mogphy to the bar_code Location
 		bool Is_detecte_true=Check_bar_Detected_code();
		if (Is_detecte_true==false)
		{
		   //clear the detected  bar_code Location 
		   Delete_detect_bar_code();
		   Detected_by_Rect_MOGRHY(Scale_Sorce_Image);
		} 
	    // delete the same detect Rogin of the bar_code 
		Delete_The_Same_detect_ROI();

		// if the paper_ID is influence by the line ,the detected bar_code Location is just student ID,it need to make a judge ,if smaller ,needs to redetect 
		Check_Whether_need_Re_detect(Scale_Sorce_Image,Is_A4_Image);

		//decode the Detect bar_code Image 
		if (bar_code.size()<=3)
		{  
		   Decode_Had_Detected_Bar_code(input,Bar_Code_Contain_Information);
		}
	/*	for (int i=0;i<Bar_Code_Contain_Information.size();i++)
		{
		   cout<<Bar_Code_Contain_Information[i]<<endl;
		}*/
	}

	//if the input image is not A4 style  ,as present it is A3 style image 
	if (!Is_A4_Image)
	{   
		// resize the image to the half scale 
		Mat Scale_Sorce_Image; 
		resize(input,Scale_Sorce_Image,Size(input.cols*0.5,input.rows*0.5));

		// detect the bar_code location using the Eclipse mogphy
	    Detected_by_Rect_Eclipse(Scale_Sorce_Image,Is_A4_Image);

		// check the detected if it is true ---if the detect is false ,it need to using kernel Rect mogphy to the bar_code Location
 		bool Is_detecte_true=Check_bar_Detected_code();
		if (Is_detecte_true==false)
		{
		   //clear the detected  bar_code Location 
		   Delete_detect_bar_code();
		   Detected_by_Rect_MOGRHY(Scale_Sorce_Image);
		}
	    // delete the same detect Rogin of the bar_code 
		Delete_The_Same_detect_ROI();

		Check_Whether_need_Re_detect(Scale_Sorce_Image,Is_A4_Image);

		if (bar_code.size()<=3)
		{

			Decode_Had_Detected_Bar_code(input,Bar_Code_Contain_Information);
		}
		for (int i=0;i<Bar_Code_Contain_Information.size();i++)
		{
		  cout<<Bar_Code_Contain_Information[i]<<endl;
		}
	}
}



void  QR_Encode_Process::Encode_Interface_All_Missing(Mat& input,vector<string>& Bar_Code_Contain_Information)
{

		// resize the image to the half scale 
		Mat Scale_Sorce_Image; 
		resize(input,Scale_Sorce_Image,Size(input.cols*0.5,input.rows*0.5));
		Whole_Image_Encode(Scale_Sorce_Image);
		Decode_Had_Detected_Bar_code(input,Bar_Code_Contain_Information);
}



void QR_Encode_Process::Whole_Image_Encode(Mat& Scale_Sorce_Image)
{

	Mat Gray; cvtColor(Scale_Sorce_Image,Gray,CV_RGB2GRAY);
	Mat binary;binary.create(Gray.rows,Gray.cols,CV_8UC1);
	FastSauvolaBinarizer*point_binary =new FastSauvolaBinarizer();
	point_binary->Binary_way(Gray,binary);
	delete point_binary ;

	QR_Location_detect *point =new QR_Location_detect();
	point->QR_find_Location(binary);

	if (point->QR_Bar_code_Location.size()==0)// it may means manner bar_code is be infulence by the line 
	{
		point->QR_find_Location(binary,true);
	}

	for(int i=0;i<point->QR_Bar_code_Location.size();i++)
	{
		bar_code.push_back(point->QR_Bar_code_Location[i]);
	}
	delete point ;

}

void QR_Encode_Process::Check_Whether_need_Re_detect(Mat& Scale_Sorce_Image,bool Is_A4_Image)
{
	if (bar_code.size()<2)
	{  
	   Delete_detect_bar_code();
	   Detected_by_Rect_MOGRHY_with_top_rect(Scale_Sorce_Image,Is_A4_Image);
	   bool Is_detecte_true=Check_bar_Detected_code();
	   if(Is_detecte_true==false)
	   {
	   
	   }
	}
}

void QR_Encode_Process::Detected_by_Rect_MOGRHY_with_top_rect(Mat& Scale_Sorce_Image,bool Is_A4_Image) 
{

	//Detected the top 25 percent bar_code location of the input image ,here may detected two bar_code Location Rect 
	Missing_one_Top_Bar_code_Location(Scale_Sorce_Image);
	    
	//when detected bar_code Location is smaller than one ,it means student's ID bar_code had not detected 
	if(bar_code.size()<2) 
	{
		//Just one _bar_code had detected in the image ,it needs to detect another bar_code in the left_15_Percent Image
		//Get the Left_15Percent_Image of the input Source,and than binary it 
	   Missing_one_Left_Bar_code_Location(Scale_Sorce_Image,Is_A4_Image);
	}
}

void QR_Encode_Process::Missing_one_Top_Bar_code_Location(Mat& Scale_Sorce_Image)
{
	// Declear the 25_percent and the 15_percent of the input image   
	Mat Top_25Percent_Image;
	Rect Top_25Percent_Rect(0,0,Scale_Sorce_Image.cols,Scale_Sorce_Image.rows*0.25);
		
	// Get the Top_25Percent_Image of the input Source 
	Top_25Percent_Image.create(Top_25Percent_Rect.height,Top_25Percent_Rect.width,CV_8UC3);
	Image_basic_function::Copy_Image(Scale_Sorce_Image,Top_25Percent_Image,Top_25Percent_Rect);

	//Detect the acculate Barcode Location ,it is confirme that 25 percent is sure have one bar code loacation at least 
	//if detect two bar_code ,the 15_Percent,bar_code detect will be sult down ,otherwise it should continue to detect the bar_code 
	Mat Gray; cvtColor(Top_25Percent_Image,Gray,CV_RGB2GRAY);
	Mat binary;binary.create(Top_25Percent_Rect.height,Top_25Percent_Rect.width,CV_8UC1);
	FastSauvolaBinarizer*point_binary =new FastSauvolaBinarizer();
	point_binary->Binary_way(Gray,binary);
	delete point_binary ;
	//Image_basic_function::Show_Image(binary);
	//detect the Bar_code Location and Get the it responding area ,and copy it for Zxing decode 
	QR_Location_detect *point =new QR_Location_detect();
	//Image_basic_function::Show_Image(binary);
    point->QR_find_Location(binary,true);
	for (int i=0;i<point->QR_Bar_code_Location.size();i++)
	{   
		bar_code.push_back(point->QR_Bar_code_Location[i]);
	}
	delete point;
}


void QR_Encode_Process::Missing_one_Left_Bar_code_Location(Mat& Scale_Sorce_Image ,bool Is_A4_Image)
{

	Mat Left_15Percent_Image; 
	Rect Left_15Percent_Rect;

	// if the iamge is A3 style 
	if (!Is_A4_Image)
	{
		Left_15Percent_Rect.x=0;Left_15Percent_Rect.y=0;
		Left_15Percent_Rect.width=Scale_Sorce_Image.cols*0.15;Left_15Percent_Rect.height=Scale_Sorce_Image.rows;
		Left_15Percent_Image.create(Left_15Percent_Rect.height,Left_15Percent_Rect.width,CV_8UC3);
		Image_basic_function::Copy_Image(Scale_Sorce_Image,Left_15Percent_Image,Left_15Percent_Rect);
	}

	//if the image is A4 style 
	if (Is_A4_Image)
	{    
		Left_15Percent_Rect.x=0;Left_15Percent_Rect.y=0;
		Left_15Percent_Rect.width=Scale_Sorce_Image.cols*0.25;Left_15Percent_Rect.height=Scale_Sorce_Image.rows;
		Left_15Percent_Image.create(Left_15Percent_Rect.height,Left_15Percent_Rect.width,CV_8UC3);
		Image_basic_function::Copy_Image(Scale_Sorce_Image,Left_15Percent_Image,Left_15Percent_Rect);
	
	}
	Mat Gray; cvtColor(Left_15Percent_Image,Gray,CV_RGB2GRAY);
	Mat binary;binary.create(Left_15Percent_Rect.height,Left_15Percent_Rect.width,CV_8UC1);
	FastSauvolaBinarizer*point_binary =new FastSauvolaBinarizer();
	point_binary->Binary_way(Gray,binary);
	delete point_binary ;
	//Image_basic_function::Show_Image(binary);
			
	QR_Location_detect *point =new QR_Location_detect();
	point->QR_find_Location(binary,true);
	for(int i=0;i<point->QR_Bar_code_Location.size();i++)
	{
		bar_code.push_back(point->QR_Bar_code_Location[i]);
	}
	delete point ;
}
bool  QR_Encode_Process::Check_bar_Detected_code()
{  
	Rect temp ;
	if (bar_code.size()!=0)
	{
	   temp=bar_code[0];
	}
	for (int i=1;i<bar_code.size();i++)
	{ 
		if (abs(temp.width-bar_code[i].width)>15) 
		{
			return false;
		}
	}
	return true ;
}
void QR_Encode_Process::Delete_detect_bar_code()
{
	int delete_times=bar_code.size ();
	for (int j=0;j<delete_times;j++)
	{
		bar_code.erase(bar_code.begin());            
	}
}

void QR_Encode_Process::Delete_The_Same_detect_ROI()
{   
	// if the bar_code size is bigger than three  ,there may have the same detected ROI 
	if (bar_code.size()>=2)
	{
		Rect Start=bar_code[0];
		for (int i=1;i<bar_code.size();i++)
		{
			if (abs(Start.x-bar_code[i].x)<10)
			{
			    bar_code.erase(bar_code.begin()+i);     
			    break ;
			}
		
		}
	}
}
void QR_Encode_Process::Detected_by_Rect_MOGRHY(Mat& Scale_Sorce_Image)
{
	   A3Top_Bar_code_Location_Rect_MOGRHY(Scale_Sorce_Image);
	   if(bar_code.size()<2) // when detected bar_code Location is smaller than one ,it means student's ID bar_code had not detected 
	   {
	        A3Left_Bar_code_Location_Rect_MOGRHY(Scale_Sorce_Image);
	   }
}

void QR_Encode_Process::Detected_by_Rect_Eclipse(Mat& Scale_Sorce_Image,bool Is_A4_Image)
{
	//Detected the top 25 percent bar_code location of the input image ,here may detected two bar_code Location Rect 
	A3Top_Bar_code_Location(Scale_Sorce_Image,Is_A4_Image);
	    
	//when detected bar_code Location is smaller than one ,it means student's ID bar_code had not detected 
	if(bar_code.size()<2) 
	{
		//Just one _bar_code had detected in the image ,it needs to detect another bar_code in the left_15_Percent Image
		//Get the Left_15Percent_Image of the input Source,and than binary it 
		A3Left_Bar_code_Location(Scale_Sorce_Image,Is_A4_Image);
	}
}

void QR_Encode_Process::A3Left_Bar_code_Location_Rect_MOGRHY(Mat &Scale_Sorce_Image)
{

	Mat Left_15Percent_Image;
	Rect Left_15Percent_Rect(0,0,Scale_Sorce_Image.cols*0.15,Scale_Sorce_Image.rows);
	Left_15Percent_Image.create(Left_15Percent_Rect.height,Left_15Percent_Rect.width,CV_8UC3);
	Image_basic_function::Copy_Image(Scale_Sorce_Image,Left_15Percent_Image,Left_15Percent_Rect);
	Mat Gray; cvtColor(Left_15Percent_Image,Gray,CV_RGB2GRAY);
	Mat binary;binary.create(Left_15Percent_Rect.height,Left_15Percent_Rect.width,CV_8UC1);
	FastSauvolaBinarizer*point_binary =new FastSauvolaBinarizer();
	point_binary->Binary_way(Gray,binary);
	delete point_binary ;
	//Image_basic_function::Show_Image(binary);
			
	QR_Location_detect *point =new QR_Location_detect();
	point->QR_find_Location_Rect_MOGRHY(binary);

	if (point->QR_Bar_code_Location.size()==0)// it may means manner bar_code is be infulence by the line 
	{
		point->QR_find_Location_Rect_MOGRHY(binary,true);
	}

	for(int i=0;i<point->QR_Bar_code_Location.size();i++)
	{
		bar_code.push_back(point->QR_Bar_code_Location[i]);
	}
	delete point ;



}
void QR_Encode_Process::A3Top_Bar_code_Location_Rect_MOGRHY(Mat& Scale_Sorce_Image)
{
	// Declear the 25_percent and the 15_percent of the input image   
	Mat Top_25Percent_Image;
	Rect Top_25Percent_Rect(0,0,Scale_Sorce_Image.cols,Scale_Sorce_Image.rows*0.25);
		
	// Get the Top_25Percent_Image of the input Source 
	Top_25Percent_Image.create(Top_25Percent_Rect.height,Top_25Percent_Rect.width,CV_8UC3);
	Image_basic_function::Copy_Image(Scale_Sorce_Image,Top_25Percent_Image,Top_25Percent_Rect);

	//Detect the acculate Barcode Location ,it is confirme that 25 percent is sure have one bar code loacation at least 
	//if detect two bar_code ,the 15_Percent,bar_code detect will be sult down ,otherwise it should continue to detect the bar_code 
	Mat Gray; cvtColor(Top_25Percent_Image,Gray,CV_RGB2GRAY);
	Mat binary;binary.create(Top_25Percent_Rect.height,Top_25Percent_Rect.width,CV_8UC1);
	FastSauvolaBinarizer*point_binary =new FastSauvolaBinarizer();
	point_binary->Binary_way(Gray,binary);
	delete point_binary ;
	//Image_basic_function::Show_Image(binary);
	//detect the Bar_code Location and Get the it responding area ,and copy it for Zxing decode 
	QR_Location_detect *point =new QR_Location_detect();
	//Image_basic_function::Show_Image(binary);
	point->QR_find_Location_Rect_MOGRHY(binary);
	if(point->QR_Bar_code_Location.size()==0)
	{
		point->QR_find_Location_Rect_MOGRHY(binary,true);
	}
	for (int i=0;i<point->QR_Bar_code_Location.size();i++)
	{   
		bar_code.push_back(point->QR_Bar_code_Location[i]);
	}
	delete point;

}
void QR_Encode_Process::A3Top_Bar_code_Location(Mat &Scale_Sorce_Image,bool Is_A4_Image)
{
	// Declear the 25_percent and the 15_percent of the input image   
	Mat Top_25Percent_Image;
	Rect Top_25Percent_Rect(0,0,Scale_Sorce_Image.cols,Scale_Sorce_Image.rows*0.25);
		
	// Get the Top_25Percent_Image of the input Source 
	Top_25Percent_Image.create(Top_25Percent_Rect.height,Top_25Percent_Rect.width,CV_8UC3);
	Image_basic_function::Copy_Image(Scale_Sorce_Image,Top_25Percent_Image,Top_25Percent_Rect);

	//Detect the acculate Barcode Location ,it is confirme that 25 percent is sure have one bar code loacation at least 
	//if detect two bar_code ,the 15_Percent,bar_code detect will be sult down ,otherwise it should continue to detect the bar_code 
	Mat Gray; cvtColor(Top_25Percent_Image,Gray,CV_RGB2GRAY);
	Mat binary;binary.create(Top_25Percent_Rect.height,Top_25Percent_Rect.width,CV_8UC1);
	FastSauvolaBinarizer*point_binary =new FastSauvolaBinarizer();
	point_binary->Binary_way(Gray,binary);
	delete point_binary ;
	//Image_basic_function::Show_Image(binary);
	//detect the Bar_code Location and Get the it responding area ,and copy it for Zxing decode 
	QR_Location_detect *point =new QR_Location_detect();
	//Image_basic_function::Show_Image(binary);
	point->QR_find_Location(binary);
	if(point->QR_Bar_code_Location.size()==0)
	{
		point->QR_find_Location(binary,true);
	}
	for (int i=0;i<point->QR_Bar_code_Location.size();i++)
	{   
		bar_code.push_back(point->QR_Bar_code_Location[i]);
	}
	delete point;
}

void QR_Encode_Process::A3Left_Bar_code_Location(Mat &Scale_Sorce_Image,bool Is_A4_Image)
{
	Mat Left_15Percent_Image;
	Rect Left_15Percent_Rect;

	// if the iamge is A3 style 
	if (!Is_A4_Image)
	{
		Left_15Percent_Rect.x=0;Left_15Percent_Rect.y=0;
		Left_15Percent_Rect.width=Scale_Sorce_Image.cols*0.15;Left_15Percent_Rect.height=Scale_Sorce_Image.rows;
		Left_15Percent_Image.create(Left_15Percent_Rect.height,Left_15Percent_Rect.width,CV_8UC3);
		Image_basic_function::Copy_Image(Scale_Sorce_Image,Left_15Percent_Image,Left_15Percent_Rect);
	}

	//if the image is A4 style 
	if (Is_A4_Image)
	{    
		Left_15Percent_Rect.x=0;Left_15Percent_Rect.y=0;
		Left_15Percent_Rect.width=Scale_Sorce_Image.cols*0.25;Left_15Percent_Rect.height=Scale_Sorce_Image.rows;
		Left_15Percent_Image.create(Left_15Percent_Rect.height,Left_15Percent_Rect.width,CV_8UC3);
		Image_basic_function::Copy_Image(Scale_Sorce_Image,Left_15Percent_Image,Left_15Percent_Rect);
	
	}
	Mat Gray; cvtColor(Left_15Percent_Image,Gray,CV_RGB2GRAY);
	Mat binary;binary.create(Left_15Percent_Rect.height,Left_15Percent_Rect.width,CV_8UC1);
	FastSauvolaBinarizer*point_binary =new FastSauvolaBinarizer();
	point_binary->Binary_way(Gray,binary);
	delete point_binary ;
	//Image_basic_function::Show_Image(binary);
			
	QR_Location_detect *point =new QR_Location_detect();
	point->QR_find_Location(binary);

	if (point->QR_Bar_code_Location.size()==0)// it may means manner bar_code is be infulence by the line 
	{
		point->QR_find_Location(binary,true);
	}

	for(int i=0;i<point->QR_Bar_code_Location.size();i++)
	{
		bar_code.push_back(point->QR_Bar_code_Location[i]);
	}
	delete point ;
}

void QR_Encode_Process::Decode_Had_Detected_Bar_code(Mat& input,vector<string>& Bar_Code_Contain_Information)
{
	for (int i=0;i<bar_code.size();i++)
	{  
		bar_code[i].x=(float)bar_code[i].x/(float)0.5;
		bar_code[i].y=(float)bar_code[i].y/(float)0.5;
		bar_code[i].width=(float)bar_code[i].width/(float)0.5;
		bar_code[i].height=(float)bar_code[i].height/(float)0.5;
		Mat Bar_code_Image;
		Bar_code_Image.create(bar_code[i].height,bar_code[i].width,CV_8UC1);
		Image_basic_function::Copy_Image(input,Bar_code_Image,bar_code[i]);
		//Image_basic_function::Show_Image(Bar_code_Image);
		Acculate_Location_Deode(Bar_code_Image,Bar_Code_Contain_Information,input,bar_code[i]);
	}
}
void QR_Encode_Process::Acculate_Location_Deode(Mat& input,vector<string>& Bar_Code_Contain_Information,Mat& input_Source,Rect& bar_Code_ROI)
{   
	// Here is using difference type to decode the input bar_code image 
	bool whether_decode_successfully=true;

	// First:   normal decode 
    Encode_process_ways(input,Bar_Code_Contain_Information,whether_decode_successfully);
	
	// Scend:  MORPH_ELLIPSE moyphy decode and doing the small rotation to the MORPH_ELLIPSE image for another decode 
	if (whether_decode_successfully==false)
	{
	   Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));  Mat Result_Image;
	   erode(input,Result_Image,element,Point(-1,-1),1);
	   //Image_basic_function::Show_Image(Result_Image);
	   Encode_process_ways(Result_Image,Bar_Code_Contain_Information,whether_decode_successfully);
	   if (whether_decode_successfully==false)
	   {
	       for (float angle=-2;angle<3;angle+=0.2)
		   {
		       Mat Rotata_Image;
			   Image_basic_function::Rotation(Result_Image,Rotata_Image,angle);
			   //Image_basic_function::Show_Image(Rotata_Image);
			   Encode_process_ways(Rotata_Image,Bar_Code_Contain_Information,whether_decode_successfully);
			   if(whether_decode_successfully==true)
			   {
			     break;
			   }
		   }
	   }
	}
	//Third:   MORPH_CROSS moyphy decode and doing the small rotation to the MORPH_CROSS image for another decode
	if (whether_decode_successfully==false)
	{
	   Mat element = getStructuringElement(MORPH_CROSS, Size(2, 2));  Mat Result_Image;
	   erode(input,Result_Image,element,Point(-1,-1),1);
	   //Image_basic_function::Show_Image(Result_Image);
	   Encode_process_ways(Result_Image,Bar_Code_Contain_Information,whether_decode_successfully);
	   if (whether_decode_successfully==false)
	   {
	       for (float angle=1;angle<3;angle+=0.2)
		   {
		       Mat Rotata_Image;
			   Image_basic_function::Rotation(Result_Image,Rotata_Image,angle);
			   //Image_basic_function::Show_Image(Rotata_Image);
			   Encode_process_ways(Rotata_Image,Bar_Code_Contain_Information,whether_decode_successfully);
			   if(whether_decode_successfully==true)
			   {
			     break;
			   }
		   }
	   }
	}
	// Fourth:   MORPH_RECT moyphy decode 2 puls 2 
	if (whether_decode_successfully==false)
	{
	   Mat element = getStructuringElement(MORPH_RECT, Size(2, 2));  Mat Result_Image;
	   erode(input,Result_Image,element,Point(-1,-1),1);
	   //Image_basic_function::Show_Image(Result_Image);
	   Encode_process_ways(Result_Image,Bar_Code_Contain_Information,whether_decode_successfully);
	   if (whether_decode_successfully==false)
	   {
	       for (float angle=0.2;angle<1;angle+=0.2)
		   {
		       Mat Rotata_Image;
			   Image_basic_function::Rotation(Result_Image,Rotata_Image,angle);
			   //Image_basic_function::Show_Image(Rotata_Image);
			   Encode_process_ways(Rotata_Image,Bar_Code_Contain_Information,whether_decode_successfully);
			   if(whether_decode_successfully==true)
			   {
			     break;
			   }
		   }
	   }
	}

	//Fivth:    MORPH_RECT moyphy decode 3 puls 3
	if (whether_decode_successfully==false)
	{
	   Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));  Mat Result_Image;
	   erode(input,Result_Image,element,Point(-1,-1),1);
	   //Image_basic_function::Show_Image(Result_Image);
	   Encode_process_ways(Result_Image,Bar_Code_Contain_Information,whether_decode_successfully);
	   if (whether_decode_successfully==false)
	   {
	       for (float angle=-2;angle<3;angle+=0.2)
		   {
		       Mat Rotata_Image;
			   Image_basic_function::Rotation(Result_Image,Rotata_Image,angle);
			   //Image_basic_function::Show_Image(Rotata_Image);
			   Encode_process_ways(Rotata_Image,Bar_Code_Contain_Information,whether_decode_successfully);
			   if(whether_decode_successfully==true)
			   {
			     break;
			   }
		   }
	   }
	}

	// Six:  Extern the bar_imge with the input source Image 
	if (whether_decode_successfully==false)
	{
	    for (float scale=1.2;scale<2.5;scale+=0.2)
		{
			Rect temporary_Rect;temporary_Rect.width=scale*bar_Code_ROI.width;temporary_Rect.height=scale*bar_Code_ROI.height;
			temporary_Rect.x=bar_Code_ROI.x-(temporary_Rect.width-bar_Code_ROI.width)/2.0;
			temporary_Rect.y=bar_Code_ROI.y-(temporary_Rect.height-bar_Code_ROI.height)/2.0;
			if(temporary_Rect.x<0)
			{
				temporary_Rect.x=0;
			}
			Mat temporary_Image;temporary_Image.create(temporary_Rect.height,temporary_Rect.width,CV_8UC3);
			Image_basic_function::Copy_Image(input_Source,temporary_Image,temporary_Rect);
			//Image_basic_function::Show_Image(temporary_Image);
			Encode_process_ways(temporary_Image,Bar_Code_Contain_Information,whether_decode_successfully);
			if(whether_decode_successfully==true)
			{
			  break;
			}
			if (whether_decode_successfully==false)
			{
				 for (float angle=-2;angle<3;angle+=1)
		         {
				   Mat Rotata_Image;
				   Image_basic_function::Rotation(temporary_Image,Rotata_Image,angle);
				   //Image_basic_function::Show_Image(Rotata_Image);
				   Encode_process_ways(Rotata_Image,Bar_Code_Contain_Information,whether_decode_successfully);
				   if(whether_decode_successfully==true)
				   {
					 break;
				   }
		        }
			    
			}
			if(whether_decode_successfully==true)
			{
			  break;
			}
		}
	}

	// Seven :   Using scale factor to up scale the bar_code Image 
	if (whether_decode_successfully==false)
	{
	   for (float scale=1.2;scale<2.5;scale+=0.2)
	   {
		   Mat Resize_temporary_Image;Rect temporary_Rect(0,0,scale*input.cols,scale*input.rows);
		   resize(input,Resize_temporary_Image,Size(input.cols*scale,input.rows*scale),0,0,CV_INTER_NN);
		   //Image_basic_function::Show_Image(Resize_temporary_Image);
		   Encode_process_ways(Resize_temporary_Image,Bar_Code_Contain_Information,whether_decode_successfully);
		   if(whether_decode_successfully==true)
		   {
			  break;
		   }
	   }
	}
}

void QR_Encode_Process::Encode_process_ways(Mat& input,vector<string>&Bar_Code_Contain_Information,bool& whether_decode_successfully)
{
	use_global=false;use_hybrid=false;
    if (!use_global && !use_hybrid)
	{
      use_global = use_hybrid = true;
    }
	Ref<LuminanceSource> source; 
	source=create(input);
	int gresult = 1;
    int hresult = 1;
    if (use_hybrid) 
	{
      hresult = read_QRcode_Information(source, true,"",Bar_Code_Contain_Information,whether_decode_successfully);//when the return nubmber is true  //it results the bar_code had decode successfuly
    }
    if (use_global && (verbose || hresult==0)) 
	{
      gresult = read_QRcode_Information(source, false,"",Bar_Code_Contain_Information,whether_decode_successfully);
      if (!verbose && gresult == 0) 
	  {
        //cout << "decoding failed" << endl;
		whether_decode_successfully=false;
      }
    }
}

Ref<LuminanceSource> QR_Encode_Process::create(Mat& input)
{
	int width=input.cols;int height=input.rows;int comps = 4;
    zxing::ArrayRef<char> image;
    std::vector<unsigned char> out;
	out=vector<unsigned char>(4*width*height, 0);
	for (int row_index=0;row_index<input.rows;row_index++)
	{  
		unsigned char * data =input.ptr<unsigned char>(row_index);

		
		for (int col_index=0;col_index<input.cols;col_index++)
		{    
			out[row_index*4*width+4*col_index+0]=* data;
			data++;
			out[row_index*4*width+4*col_index+1]=* data;
			data++;
			out[row_index*4*width+4*col_index+2]=* data;
			data++;
			out[row_index*4*width+4*col_index+3]=255;
		}
	}
    image = zxing::ArrayRef<char>(4 * width * height);
	memcpy(&(image.array_->values_[0]), &out[0], image->size());
	return Ref<LuminanceSource>(new QR_Encode_Process(image, width, height, comps));
}


zxing::ArrayRef<char> QR_Encode_Process::getRow(int y, zxing::ArrayRef<char> row) const 
{
  const char* pixelRow = &image[0] + y * getWidth() * 4;
  if (!row) 
  {
    row = zxing::ArrayRef<char>(getWidth());
  }
  for (int x = 0; x < getWidth(); x++) 
  {
    row[x] = convertPixel(pixelRow + (x * 4));
  }
  return row;
}

/** This is a more efficient implementation. */
zxing::ArrayRef<char> QR_Encode_Process::getMatrix() const 
{
  const char* p = &image[0];
  zxing::ArrayRef<char> matrix(getWidth() * getHeight());
  char* m = &matrix[0];
  for (int y = 0; y < getHeight(); y++) 
  {
    for (int x = 0; x < getWidth(); x++) 
	{
      *m = convertPixel(p);
      m++;
      p += 4;
    }
  }
  return matrix;
}

inline char QR_Encode_Process::convertPixel(char const* pixel_) const 
{
  unsigned char const* pixel = (unsigned char const*)pixel_;
  if (comps == 1 || comps == 2) 
  {
    // Gray or gray+alpha
    return pixel[0];
  } 
  if (comps == 3 || comps == 4) 
  {
    // Red, Green, Blue, (Alpha)
    // We assume 16 bit values here
    // 0x200 = 1<<9, half an lsb of the result to force rounding
    return (char)((306 * (int)pixel[0] + 601 * (int)pixel[1] +
        117 * (int)pixel[2] + 0x200) >> 10);
  }
  else 
  {
    throw zxing::IllegalArgumentException("Unexpected image depth");
  }
}


int QR_Encode_Process::read_QRcode_Information(Ref<LuminanceSource> source, bool hybrid, string expected,vector<string>& result_,bool& whether_decode_successfully)
{
  vector<Ref<Result> > results;
  string cell_result;
  int res = -1;
  try 
  {
    Ref<zxing::Binarizer> binarizer;
    if (hybrid) 
	{
      binarizer = new HybridBinarizer(source);
    } 
	else 
	{
      binarizer = new GlobalHistogramBinarizer(source);
    }
    DecodeHints hints(DecodeHints::DEFAULT_HINT);
    hints.setTryHarder(try_harder);
    Ref<BinaryBitmap> binary(new BinaryBitmap(binarizer));
    results = decode(binary, hints);
    res = 0;
  }
  catch (const ReaderException& e) 
  {
    cell_result = "zxing::ReaderException: " + string(e.what());
    res = -2;
  } 
  catch (const zxing::IllegalArgumentException& e) 
  {
    cell_result = "zxing::IllegalArgumentException: " + string(e.what());
    res = -3;
  } 
  catch (const zxing::Exception& e) 
  {
    cell_result = "zxing::Exception: " + string(e.what());
    res = -4;
  } 
  catch (const std::exception& e) 
  {
    cell_result = "std::exception: " + string(e.what());
    res = -5;
  }
  if (results.size()!=0)
  {
      std::string result = results[0]->getText()->getText();
	  result_.push_back(result);
	  whether_decode_successfully=true;
	  return 1;
  }
   return 0;
}


vector<Ref<Result> > QR_Encode_Process::decode_multi(Ref<BinaryBitmap> image, DecodeHints hints) 
{
  MultiFormatReader delegate;
  GenericMultipleBarcodeReader reader(delegate);
  return reader.decodeMultiple(image, hints);
}


vector<Ref<Result> > QR_Encode_Process::decode(Ref<BinaryBitmap> image, DecodeHints hints) 
{
  Ref<Reader> reader(new MultiFormatReader);
  return vector<Ref<Result> >(1, reader->decode(image, hints));
}