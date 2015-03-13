
#include <opencv2/core/core.hpp>
#include <highgui.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "cv.h"
#include "highgui.h"
#include "math.h"
#include "cxcore.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include "FastSauvolaBinarizer.h"
#include "Image_basic_function.h"
#include "QR_Location_detect.h"
#include "DR_big_rect.h"
#include "DR_Question_Rect.h"
#include "Exam_Paper_Analysis.h"
#include "Image_Enhancement_Contrast.h"
#include "QR_Encode_Process.h"

using namespace std;

struct QrcodeResult
{
   string code1;

   string code2;
};

extern "C" _declspec(dllexport) QrcodeResult GetQrcode(char* path);
