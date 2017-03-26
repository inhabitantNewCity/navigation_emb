//---------------------------------------------------------------------------

#ifndef AppManagerH
#define AppManagerH
//---------------------------------------------------------------------------
#endif
class AppManager {
	private:	
		Observer* observer;
		TQueue<MultiVector*>* queue;
	public:
	AppManager(){};
	
	Observer* buildObserver(){
		queue = new TQueue<MultiVector*>(); 
		observer = new Observer(queue);
		return observer;
	}
	
	TQueue<MultiVector*>* getObserverQueue(){
		return queue;
	}
	
	void run(){
		TTask::Create(_di_TProc(new Analyst(observer)))->Start();
	}
	
}
