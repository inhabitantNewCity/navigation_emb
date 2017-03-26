//---------------------------------------------------------------------------

#ifndef AlgorithmH
#define AlgorithmH
//---------------------------------------------------------------------------
#endif
class Algorithm : public TCppInterfacedObject<TProc>{
protected:
	TQueue<MultiVector*>* queue;
public:
	Algorithm(TQueue<MultiVector*>* analystQuery):queue(analystQuery){}
	virtual void __fastcall Invoke() = 0;
}