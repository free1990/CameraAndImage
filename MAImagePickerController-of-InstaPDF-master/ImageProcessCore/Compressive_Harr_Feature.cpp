#include "Compressive_Harr_Feature.h"
#include <opencv2/opencv.hpp>
#include "Image_basic_function.h"

#include <vector>
#include <math.h>
#include <iostream>
using namespace cv;



Compressive_Harr_Feature::Compressive_Harr_Feature():_numFeature(100)
{
	featureMinNumRect=2;
    featureMaxNumRect=3;
	features_box=vector<vector<cv::Rect>>(_numFeature, vector<cv::Rect>());
	featuresWeight = vector<vector<float>>(_numFeature, vector<float>());
	Harr_feature_list_pos=vector<float>(_numFeature, 0.0f);// positive sample vector list  __it is judge  by the whole black 
	Harr_feature_list_neg=vector<float>(_numFeature, 0.0f);// negtive  sample vector list  -- it is judege by the whole white
	feature_box_generetor();
	fill_neg_vetor();
}
Compressive_Harr_Feature::Compressive_Harr_Feature(int number_box) // user inerface 
{
	_numFeature=number_box;
	featureMinNumRect=2;
    featureMaxNumRect=3;
	features_box=vector<vector<cv::Rect>>(_numFeature, vector<cv::Rect>());
	featuresWeight = vector<vector<float>>(_numFeature, vector<float>());
	Harr_feature_list_pos=vector<float>(_numFeature, 0.0f);// positive sample vector list  __it is judge  by the whole black 
	Harr_feature_list_neg=vector<float>(_numFeature, 0.0f);// negtive  sample vector list  -- it is judege by the whole white
	feature_box_generetor();
	fill_neg_vetor();

}


float Compressive_Harr_Feature::Get__numFeature() const 
{
	return _numFeature;

}
void Compressive_Harr_Feature::Get_Harr_feture(Mat& input_image,vector<float> & Harr_feature_list_input)
{
	 Mat input_intergel;
	 input_intergel.create(input_image.rows+1,input_image.cols+1,CV_32FC1);
	 integral(input_image,input_intergel,CV_32FC1); // it is used to calculate 

	 for (int j=0;j<_numFeature;j++)
	 { 
	   float temp_value_acculate=0;
	   for(int i=0;i<features_box[j].size();i++)
	   {  
		  float temp_value=0;
	      Rect get_temp_rect;
		  get_temp_rect=features_box[j][i];

		  // index the left top point 
		  float *point_left_top;
		  point_left_top =input_intergel.ptr<float>(get_temp_rect.y);
		  point_left_top+=get_temp_rect.x;

		  // index the right top point 
		  float *point_right_top;
		  point_right_top=point_left_top+get_temp_rect.width;

		  // index the left bottem point 
		  float *point_left_bottem;
		  point_left_bottem =input_intergel.ptr<float>(get_temp_rect.y+get_temp_rect.height);
		  point_left_bottem+=get_temp_rect.x;

		  // index the right bottem point 
		  float *point_right_bottem;
		  point_right_bottem=point_left_bottem+get_temp_rect.width;
		  temp_value= *point_right_bottem+*point_left_top-*point_right_top-*point_left_bottem;
		  temp_value=temp_value*featuresWeight[j][i];
		  temp_value_acculate+=temp_value;
	   }

	   Harr_feature_list_input[j]=temp_value_acculate;

	 }
}

float Compressive_Harr_Feature::Similar_relationship(vector<float>& Harr_feature_list_Sample) // bei ye si classfilar ,which can stand the similar between the input and sample image 
{
	float pos,neg;
	float sum_class=0;
	for (int i =0;i<Harr_feature_list_Sample.size();i++)
	{
		pos=exp( (Harr_feature_list_Sample[i]-Harr_feature_list_pos[i])*(Harr_feature_list_Sample[i]-Harr_feature_list_pos[i])/-(2.0*0*0+1e-30))/(0+1e-30);
		neg=exp( (Harr_feature_list_Sample[i]-Harr_feature_list_neg[i])*(Harr_feature_list_Sample[i]-Harr_feature_list_neg[i])/-(2.0*0*0+1e-30))/(0+1e-30);
	    sum_class+=log(pos+1e-30) - log(neg+1e-30);	
	}   
	return  sum_class;

}

float Compressive_Harr_Feature::Similar_relationship_with_signle_Positive(vector<float> &Harr_feature_list_temple)
{
	float pos=0;
	float sum_class=0;
    for (int i =0;i<Harr_feature_list_temple.size();i++)
	{
		pos=abs(Harr_feature_list_temple[i]-Harr_feature_list_pos[i]);
	    sum_class+=pos;
	}   
    return sum_class;
}
 


void Compressive_Harr_Feature::feature_box_generetor() // generator the feature box 
{   
	int numRect=0;
	Rect _objectBox;
	_objectBox.x=0;_objectBox.y=0;
	_objectBox.width=50;_objectBox.height=25;
	Rect rectTemp;

   	for (int i = 0; i<_numFeature; i++)
    {

			numRect = cvFloor(rng.uniform((double)featureMinNumRect, (double)featureMaxNumRect));// number of radom sample box 
			float weightTemp=0; // weight of the sprace
			for (int j = 0; j<numRect; j++)
			{
				rectTemp.x = cvFloor(rng.uniform(0.0, (double)(_objectBox.width - 3)));
				rectTemp.y = cvFloor(rng.uniform(0.0, (double)(_objectBox.height - 3)));
				rectTemp.width = cvCeil(rng.uniform(0.0, (double)(_objectBox.width - rectTemp.x - 2)));
				rectTemp.height = cvCeil(rng.uniform(0.0, (double)(_objectBox.height - rectTemp.y - 2)));
			
				weightTemp = (float)pow(-1.0, cvFloor(rng.uniform(0.0, 2.0)))/sqrt(float(numRect)); // conform to the space alogrithm's weight 
			    features_box[i].push_back(rectTemp);
				featuresWeight[i].push_back(weightTemp);
			}
	}
 
}

void Compressive_Harr_Feature::fill_neg_vetor()
{
	Mat neg_image;
	neg_image.create(25,50,CV_8UC1);
	Image_basic_function::Set_Image_To_255_CV_8U(neg_image);// it is used to generator the neg image  

	Get_Harr_feture(neg_image,Harr_feature_list_neg);
}

void Compressive_Harr_Feature::Fill_pos_vector(Mat& input,bool Whole_black)
{
    if (Whole_black==true)
	{
	   return ; //default all the Pos value is Zero
	}

	if (Whole_black==false)
	{
	   Get_Harr_feture(input,Harr_feature_list_pos); //Get the pos vectoer 
	}

}

void Compressive_Harr_Feature::Fill_neg_vector(Mat& input,bool Whole_black)
{

    if (Whole_black==true)
	{
	   return ; //default all the Pos value is Zero
	}

	if (Whole_black==false)
	{
	   Get_Harr_feture(input,Harr_feature_list_neg); //Get the pos vectoer 
	}

}


Compressive_Harr_Feature:: ~Compressive_Harr_Feature()
{

   
}

