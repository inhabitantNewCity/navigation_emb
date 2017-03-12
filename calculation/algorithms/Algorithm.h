//---------------------------------------------------------------------------

#ifndef AlgorithmH
#define AlgorithmH
//---------------------------------------------------------------------------
#endif
class Algorithm : public TCppInterfacedObject<TProc>{
protected:
	TQueue<T>* queue;
public:
	TCppSync(TQueue<MultiVector*>* analystQuery):queue(analystQuery){}
	virtual void __fastcall Invoke() = 0;
}