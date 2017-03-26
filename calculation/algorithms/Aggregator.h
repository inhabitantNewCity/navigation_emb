//---------------------------------------------------------------------------

#ifndef AnalystH
#define AnalystH
//---------------------------------------------------------------------------
#endif
class Aggregator: public Algorithm  {
private:
	Observer* observer;
public:
	Aggregator(TQueue<MultiVector*>* analystQuery, Observer* observer):Algorithm(analystQuery){
		this->observer = observer;
	}
	virtual void __fastcall Invoke() {
		
	}

}