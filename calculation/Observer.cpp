//---------------------------------------------------------------------------

#pragma hdrstop

#include "Observer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
class Observer{
	private:
		TForm* form;
	public:

		Observer(IForm* form){
			this->form = form
		}
};
