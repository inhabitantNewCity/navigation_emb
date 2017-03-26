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

		MultiVector* aggregate(MultiVector* vector){
			return result = new MultiVector((this->angleX+vector->getAngleX())/2,
			(this->angleY + vector->getAngleY() )/2,
			(this->angleZ+vector->getAngleZ())/2,
			(this->accX+vector->getAccX())/2,(this->accY+vector->getAccY())/2,(this->accZ+vector->getAccZ())/2);
				
		}
		
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