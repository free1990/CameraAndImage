
#pragma once
#include <opencv2/opencv.hpp>
#include "iostream"
using namespace cv;



class Binarizer_
{
public:
	Binarizer_();
	virtual void  Binary_way(const Mat& input ,Mat& out_put )  ;
    virtual  ~Binarizer_ ();
};


