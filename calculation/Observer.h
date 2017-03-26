//---------------------------------------------------------------------------

#ifndef ObserverH
#define ObserverH
//---------------------------------------------------------------------------
#endif
class Observer{
	private:
		TQueue<MultiVector*>* query;
	
	public:
	Observer(TQueue<MultiVector*>* query){
		this->query = query;
	}
	
	void putCurrentLocation(MultiVector* vector){
		query->Enqueue(vector);
	}
}