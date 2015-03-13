#pragma once
#include <opencv2/opencv.hpp>
#include "iostream"
#include <zxing/common/Counted.h>
#include <zxing/Binarizer.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <exception>
#include <zxing/Exception.h>
#include <zxing/common/IllegalArgumentException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/multi/qrcode/QRCodeMultiReader.h>
#include <zxing/multi/ByQuadrantReader.h>
#include <zxing/multi/MultipleBarcodeReader.h>
#include <zxing/multi/GenericMultipleBarcodeReader.h>
#include "Image_basic_function.h"


using namespace cv;
using namespace zxing;


namespace 
{
	bool more = false;
	bool test_mode = false;
	bool try_harder = false;
	bool search_multi = false;
	bool use_hybrid = false;
	bool use_global = false;
	bool verbose = false;

};



class QR_Encode_Process:public zxing::LuminanceSource 
{
public:

private:
	typedef LuminanceSource Super;

    zxing::ArrayRef<char> image;
    int comps;

	vector<Rect> bar_code;
public:
   QR_Encode_Process::QR_Encode_Process(zxing::ArrayRef<char> image_, int width, int height, int comps_);
   void Encode_Interface(Mat& input,bool Is_A4_Image,vector<string>& Bar_Code_Contain_Information);

public:
   void  Encode_Interface_All_Missing(Mat& input,vector<string>& Bar_Code_Contain_Information);

private:

	Ref<LuminanceSource> create(Mat& input) ;
	zxing::ArrayRef<char> getRow(int y, zxing::ArrayRef<char> row) const;
    zxing::ArrayRef<char> getMatrix() const;
	char convertPixel(const char* pixel) const;
	int read_QRcode_Information(Ref<LuminanceSource> source, bool hybrid, string expected,vector<string>& result,bool& whether_decode_successfully); 
	vector<Ref<Result> > decode_multi(Ref<BinaryBitmap> image, DecodeHints hints); 
	vector<Ref<Result> > decode(Ref<BinaryBitmap> image, DecodeHints hints);
	void Acculate_Location_Deode(Mat& input ,vector<string>& Bar_Code_Contain_Information,Mat& input_Source, Rect& bar_Code_ROI);
	void Encode_process_ways(Mat& input,vector<string>&Bar_Code_Contain_Information,bool& whether_decode_successfully);
	void A3Top_Bar_code_Location(Mat &Scale_Sorce_Image,bool Is_A4_Image);
	void A3Left_Bar_code_Location(Mat &Scale_Sorce_Image,bool Is_A4_Image);
	void Decode_Had_Detected_Bar_code(Mat& input,vector<string>& Bar_Code_Contain_Information);
	bool Check_bar_Detected_code();
	void Delete_detect_bar_code();
	void Detected_by_Rect_MOGRHY(Mat& Scale_Sorce_Image);
	void QR_Encode_Process::Detected_by_Rect_Eclipse(Mat& Scale_Sorce_Image,bool Is_A4_Image);
	void A3Top_Bar_code_Location_Rect_MOGRHY(Mat& Scale_Sorce_Image);
	void A3Left_Bar_code_Location_Rect_MOGRHY(Mat &Scale_Sorce_Image);
	void Delete_The_Same_detect_ROI();
	void Check_Whether_need_Re_detect(Mat& Scale_Sorce_Image,bool Is_A4_Image);
	void Detected_by_Rect_MOGRHY_with_top_rect(Mat& Scale_Sorce_Image,bool Is_A4_Image);
	void Missing_one_Top_Bar_code_Location(Mat& Scale_Sorce_Image);
	void Missing_one_Left_Bar_code_Location(Mat& Scale_Sorce_Image,bool Is_A4_Image);



	void Whole_Image_Encode(Mat& Scale_Sorce_Image);
};



 