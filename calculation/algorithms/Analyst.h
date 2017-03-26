//---------------------------------------------------------------------------

#ifndef AnalystH
#define AnalystH
#define CountThread 5
//---------------------------------------------------------------------------
#endif
class Analyst: public TCppInterfacedObject<TProc>{
private:
	_di_ITask* tasks;
	int size_tasks;
	
	TList<TQueue<MultiVector*>*>* queueForTasks;

	Observer* observer;
	TQueue<MultiVector*>* queue;
	
	TQueue<MultiVector*>* query_agg;
	
	MultiVector* aggregation(){
		MultiVector* result = TList->Items[0]->Dequeue();
		for(int i = 1; i < TList->Count - 1; i++){
			result->aggregate(TList->Items[i]->Dequeue());
		}
		query_agg->Enqueue(result);
		return result;
	}

public:

	Analyst(Observer* observer){
		this->observer = observer;		
	}

	int analysting(){
		size_tasks = 2;
		
		tasks = new _di_ITask[size_tasks];
		
		TQueue<MultiVector*>* query_prim = new TQueue();
		queueForTasks->Add(query_prim);
		tasks[0] = TTask::Create(_di_TProc(new ThreePhageAlgorithm(query_prim)));
		
		query_agg = new TQueue();
		queueForTasks->Add(query_agg);
		tasks[1] = TTask::Create(_di_TProc(new Aggregator(query_agg, observer)));
		
		return 0;
	}

	virtual void __fastcall Invoke(){
		while(true){
			for(int i = 0; i < size_tasks; i++){
				tasks[i]->Start();
			}
			TTask::WaitForAll(tasks,(sizeof(tasks)/sizeof(tasks[0])-1));
			aggregation();
		}
		return 0;
	}

}