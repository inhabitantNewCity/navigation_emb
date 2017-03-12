//---------------------------------------------------------------------------

#ifndef AnalystH
#define AnalystH
//---------------------------------------------------------------------------
#endif
class Analyst {
private:
	_di_ITask* tasks;
	TQueue** queueForTasks;

	Observer* observer;
	TQueue queue;

	void aggregation(){

	}

public:

	Analyst(Observer* observer, TQueue* agregationQueue){
		this->queue = agregationQueue;
		this->observer = observer;
	}

	int analysting(){

		return 0;
	}

	int executeCalculation(){
		aggregation();
		return 0;
	}

}