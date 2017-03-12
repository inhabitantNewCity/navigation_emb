//---------------------------------------------------------------------------
#pragma hdrstop

#include "UtilsFunctions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
float module(float accX, float accY, float accZ){
	 float summ = accX * accX + accY * accY;
	 return sqrt(summ);
};
float* parse(char* buff, int* lenth)
{
	float* result = new float[6]

	result[0] = (float)((buff[11] >> 8) + buff[10]) / 256.0f * CONST_G;
	result[1] = (float)((buff[13] >> 8) + buff[12]) / 256.0f * CONST_G;
	result[2] = (float)((buff[15] >> 8) + buff[14]) / 256.0f * CONST_G;

	result[3] = (float)((buff[23] << 8) + buff[22]) / (100.0f * 360) * PI;
	result[4] = (float)((buff[25] << 8) + buff[24]) / (100.0f * 360) * PI;
	result[5] = (float)((buff[27] << 8) + buff[26]) / (100.0f * 360) * PI;

	return result;
};
