#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;


class Compressive_Harr_Feature
{
private:
    RNG rng;
	int _numFeature;
	vector<vector<cv::Rect>> features_box; // sample_box 

	vector<vector<float>> featuresWeight; //  sample_box_feature 
	vector<float> Harr_feature_list_pos;// positive sample vector list  __it is judge  by the whole black 
	vector<float> Harr_feature_list_neg;// negtive  sample vector list  -- it is judege by the whole white

	int featureMinNumRect; 
	int featureMaxNumRect;

public:
	 Compressive_Harr_Feature();
	 Compressive_Harr_Feature(int number_box);
	 float Similar_relationship(vector<float> &Harr_feature_list_temple);
	 float Similar_relationship_with_signle_Positive(vector<float> &Harr_feature_list_temple);
	 void Get_Harr_feture(Mat& input_image,vector<float> & Harr_feature_list_input);
    ~Compressive_Harr_Feature();
	 float Get__numFeature() const ;
	 void Fill_pos_vector(Mat& input,bool Whole_black=true);
	 void Fill_neg_vector(Mat& input,bool Whole_black=true);

private:
	 void feature_box_generetor();
	 void fill_neg_vetor();
};