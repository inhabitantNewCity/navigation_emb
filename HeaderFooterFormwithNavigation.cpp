//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "HeaderFooterFormwithNavigation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.LgXhdpiPh.fmx", _PLAT_ANDROID)
#pragma resource ("*.iPhone4in.fmx", _PLAT_IOS)

THeaderFooterwithNavigation *HeaderFooterwithNavigation;
//---------------------------------------------------------------------------
__fastcall THeaderFooterwithNavigation::THeaderFooterwithNavigation(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THeaderFooterwithNavigation::FormCreate(TObject *Sender)
{
	// This define the default active tab at runtime
	TabControl1->ActiveTab = TabItem1;
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterwithNavigation::FormKeyUp(TObject *Sender, WORD &Key,
          System::WideChar &KeyChar, TShiftState Shift)
{
	if (Key == vkHardwareBack && TabControl1->TabIndex != 0) {
		TabControl1->First(TTabTransition::Slide, TTabTransitionDirection::Normal);
		Key = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall THeaderFooterwithNavigation::TitleActionUpdate(TObject *Sender)
{
	TCustomAction * act = dynamic_cast<TCustomAction *>(Sender);
	if (act != NULL) {
		if (TabControl1->ActiveTab != NULL) {
			act->Text = TabControl1->ActiveTab->Text;
		} else {
			act->Text = "";
		}
	}
}
//---------------------------------------------------------------------------


