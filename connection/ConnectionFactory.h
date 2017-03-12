//---------------------------------------------------------------------------

#ifndef ConnectionFactoryH
#define ConnectionFactoryH
//---------------------------------------------------------------------------
#endif
 class ConnectionFactory{
	private:
		Connection* connections[2];
		int connectionSize = 2;
	public:

		ConnectionFactory(){
		   connections[0] = new ConnectionBluetooth();
		   connections[1] = new ConnectionFixed();
		}

		Connection* getConnection(int i){
			if(connectionSize < 2 && connectionSize >= 0)
				return connections[i];
		}
};