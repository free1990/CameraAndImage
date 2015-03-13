#include "Extern_C_dll.h"

QrcodeResult GetQrcode(char* path)
{
	bool Is_A4_Image=true;

	Mat RGB_Sorce_Image=imread(path,1);

	cout<<path<<endl;

	zxing::ArrayRef<char> image_;

	QR_Encode_Process message(image_,4,2,4);

	vector<string> result;

	message.Encode_Interface(RGB_Sorce_Image, Is_A4_Image,result);

	QrcodeResult qrcodes;

	int count = result.size();

	if (count == 1)
	{
		qrcodes.code1 = result[0];
	}
	else if (count != 0)
	{
		qrcodes.code1 = result[0];
		qrcodes.code2 = result[1];
	}

    return qrcodes;
}