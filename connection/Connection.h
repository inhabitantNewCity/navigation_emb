//---------------------------------------------------------------------------


#ifndef ConnectionH
#define ConnectionH
//---------------------------------------------------------------------------
#endif
class Connection {

	public:
		virtual void connection() = 0;
		virtual int readData(char* buf, int size) = 0;

};