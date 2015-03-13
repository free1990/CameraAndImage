
#pragma once

#include "Binarizer.h"

class  FastSauvolaBinarizer :public Binarizer_

{	
private:
	int windowsx;
	int windowsy;
	float kx;
	float max_var;
public :

	FastSauvolaBinarizer();
	explicit FastSauvolaBinarizer(int box_x,int box_y,float set_off_kx,float set_var );
	virtual  void  Binary_way(const Mat& input ,Mat & out_put ) ;
	void Image_Background_clean(Mat& input ,Mat& output);
	~FastSauvolaBinarizer(); 

private:
	void  M_mean(const  Mat & sourseimage, Mat& mean__square,int input_type); // it backs the average image  
	void  S_square(const Mat& sourseimage, Mat& mean__square);    // it backs the s(x,y)*s(x,y)/windowsx*windowsy
    static void doing_sqrt( Mat & input ); 
	void  The_thousould_function(Mat & mean, Mat & deviation, Mat & thousaldget);
	void  Get_theBInary_image(Mat &  thousaldget,const  Mat &  input, Mat &  out_put);

	void Get_The_clean_Image(Mat &  thousaldget,const  Mat &  input, Mat &  out_put);
	float Get_the_max_var(Mat & deviation);
	 
};