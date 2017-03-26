//---------------------------------------------------------------------------

#ifndef ThreePhageAlgorithmH
#define ThreePhageAlgorithmH

#define CONST_ACCELERATION_MIN 0.8f * CONST_G
#define CONST_H_MIN 0.6 * CONST_G
#define CONST_ACCELERATION_MAX 2.3 * CONST_G
#define CONST_H_MAX 2.0 * CONST_G

#include <math.h>

//---------------------------------------------------------------------------
#endif
class ThreePhageAlgorithm: public Algorithm{
	private:

	Connection* connection;

	bool firstPhaseOfStepDetected;
	bool secondPhaseOfStepDetected;
	bool thridPhaseOfStepDetected;

	float accMaxVerticalForFirstPart;
	float accMinVerticalForFirstPart;
	float accMaxHorizontalForFirstPart;
	float accMinHorizontalForFirstPart;

	float accMaxVerticalForSecondPart;
	float accMinVerticalForSecondPart;
	float accMaxHorizontalForSecondPart;
	float accMinHorizontalForSecondPart;

	float accMaxVerticalForThridPart;
	float accMinVerticalForThridPart;
	float accMaxHorizontalForThridPart;
	float accMinHorizontalForThridPart;

	int deltaTime;

	float SumRecivedAcceleration;
	int countStep;
	TFileStream *fs;

	char* buff;
	int size_raw;
	int size_result;

	public:
	ThreePhageAlgorithm(TQueue<MultiVector*>* analystQuery):Algorithm(analystQuery)
	{
		fs = new TFileStream("temp.txt", fmCreate);
		ConnectionFactory* factory = new ConnectionFactory();
		connection = factory->getConnection(1);
		connection->connection();

		accMinVerticalForSecondPart = (CONST_ACCELERATION_MIN) * cos(angleBettwenLegOnSecondPhaseAndNormal) - ((CONST_ACCELERATION_MIN - CONST_G) * sin(angleBettwenLegOnSecondPhaseAndNormal)) - 5.0f;
		firstPhaseOfStepDetected = true;
		secondPhaseOfStepDetected = false;
		thridPhaseOfStepDetected = false;

		//set max and min value of accelerations
		double angleBettwenLegOnSecondPhaseAndNormal = PI/6;
		double angleBettwenLegOnThridPhaseAndNormal = PI/3;
		this->deltaTime = 100;
		UIOffset = 10;

		SumRecivedAcceleration = 0;
		countStep = 0;

		size_result = 6;
		size_raw = 28;

		// set max min for first phase
		accMinVerticalForFirstPart = -2.0f;
		accMaxVerticalForFirstPart = 2.0f;
		accMaxHorizontalForFirstPart = 1.0f;
		accMinHorizontalForFirstPart -7.0f;

		// set max, min for second phase
		accMaxVerticalForSecondPart = (CONST_ACCELERATION_MAX) * cos(angleBettwenLegOnSecondPhaseAndNormal) - ((CONST_ACCELERATION_MAX - CONST_G) * sin(angleBettwenLegOnSecondPhaseAndNormal)) - 5.0f;
		accMinHorizontalForSecondPart = ((CONST_H_MIN) * sin(angleBettwenLegOnSecondPhaseAndNormal)) + ((CONST_H_MIN - CONST_G) * cos(angleBettwenLegOnSecondPhaseAndNormal));
		accMaxHorizontalForSecondPart = ((CONST_H_MAX) * sin(angleBettwenLegOnSecondPhaseAndNormal)) + ((CONST_H_MAX - CONST_G) * cos(angleBettwenLegOnSecondPhaseAndNormal));

		//set max, min for thrid phase
		accMaxVerticalForThridPart = (CONST_ACCELERATION_MAX - CONST_G) * sin(angleBettwenLegOnThridPhaseAndNormal) + CONST_ACCELERATION_MAX * cos(angleBettwenLegOnThridPhaseAndNormal) - 0.5f;
		accMinVerticalForThridPart = (CONST_ACCELERATION_MIN - CONST_G) * sin(angleBettwenLegOnThridPhaseAndNormal) + CONST_ACCELERATION_MIN * cos(angleBettwenLegOnThridPhaseAndNormal) - 0.5f;
		accMaxHorizontalForThridPart = ((CONST_H_MAX - CONST_G) * cos(angleBettwenLegOnThridPhaseAndNormal)) - ((CONST_H_MAX) * sin(angleBettwenLegOnThridPhaseAndNormal)) + 6.0f;
		accMinHorizontalForThridPart = ((CONST_H_MIN - CONST_G) * cos(angleBettwenLegOnThridPhaseAndNormal)) - ((CONST_H_MIN) * sin(angleBettwenLegOnThridPhaseAndNormal)) + 6.0f;
	}

	bool firstPhaseOfStepIsDetected(float accX, float accY, float accZ)
	{
		accMinHorizontalForFirstPart = -1.0f;
		if( ((accX > accMinVerticalForFirstPart) && (accX < accMaxVerticalForFirstPart)) && ((accY > accMinHorizontalForFirstPart) && (accY < accMaxHorizontalForFirstPart)))
			return true;
		return false;
	};
	bool secondPhaseOfStepIsDetected(float accX ,float accY, float accZ)
	{
		bool result = false;
		if( ((accY > accMinVerticalForSecondPart) && (accY < accMaxVerticalForSecondPart))
			&& ((accX > accMinHorizontalForSecondPart) && (accX < accMaxHorizontalForSecondPart)))
			result = true;
		string s = "SECOND PHAGE RESULT: " + result +
			" [ " + accMinVerticalForSecondPart + " < " + accY + " < " + accMaxVerticalForSecondPart + " ] " +
			" [ " + accMinHorizontalForSecondPart + " < " + accX + " < " + accMaxHorizontalForSecondPart + " ] ";
			fs->Write(s, Length(s));
		return result;
	};
	bool thridPhaseOfStepIsDetected(float accX , float accY,float accZ)
	{
		bool result = false;
		if( ((accY > accMinVerticalForThridPart) && (accY < accMaxVerticalForThridPart))
			&& ((accX > accMaxHorizontalForThridPart) && (accX < accMinHorizontalForThridPart)))
			result = true;
		string s =  "THRID PHAGE RESULT: " + result +
			" [ " + accMinVerticalForThridPart + " < " + accY + " < " + accMaxVerticalForThridPart + " ] " +
			" [ " + accMinHorizontalForThridPart + " < " + accX + " < " + accMaxHorizontalForThridPart + " ] ";
			fs->Write(s, Length(s));
		return result;
	};
	float calculateLengthOfStep(float acc)
	{
		SumRecivedAcceleration += acc;
		float result = (CONST_G/countStep) * pow((double)SumRecivedAcceleration, 1.0 / 3.0);

		string s = "LENGTH OF STEP: result = " + result + " module acc = " + acc +
			" sum = " + SumRecivedAcceleration + "count step = " + countStep;
		fs->Write(s,Length(s));

		return result;
	}

	virtual void __fastcall Invoke()
	{
		float* data;

		if(connection->readData(buff, size_raw) != 0)
		{
			return; //incorrect read
		}

		data = parse(buff, size_result);

		if(secondPhaseOfStepIsDetected(data[0], data[1], data[2])){
			secondPhaseOfStepDetected = true;
			thridPhaseOfStepDetected = false;
		}
		if(thridPhaseOfStepIsDetected(data[0], data[1], data[2]))
			thridPhaseOfStepDetected = true;
		if(firstPhaseOfStepDetected  & secondPhaseOfStepDetected & thridPhaseOfStepDetected )
		{
			secondPhaseOfStepDetected = false;
			thridPhaseOfStepDetected = false;
			float moduleAcceleration = module(data[0], data[1], data[2]);
			countStep++;
			MultiVector* vector = new MultiVector(data[0], data[1], data[2], data[3], data[4], data[5], calculateLengthOfStep(moduleAcceleration));
			analystQuery->Enqueue(vector);
		}

	}

};
