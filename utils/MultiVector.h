//---------------------------------------------------------------------------
#include <math.h>
#ifndef MultiVectorH
#define MultiVectorH
//---------------------------------------------------------------------------
#endif
class MultiVector{
	private:
		float angleX;
		float angleY;
		float angleZ;

		float accX;
		float accY;
		float accZ;

		float length;
	public:
	  MultiVector(
		float angleX, float angleY, float angleZ,
		float accX, float accY, float accZ, float length
		 ):
		angleX(angleX), angleY(angleY), angleZ(angleZ),
		accX(accX),	accY(accY), accZ(accZ), length(length){}

		float getAngleX()
		{
			return angleX
		};

		float getAngleY()
		{
			return angleY
		};
		float getAngleZ()
		{
			return angleZ
		};

		float getAccX()
		{
			return accX
		};
		float getAccY()
		{
			return accY
		};
		float getAccZ()
		{
			return accZ
		};

		float getLength()
		{
			return length
		};
}