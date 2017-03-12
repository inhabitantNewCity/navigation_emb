//---------------------------------------------------------------------------

#ifndef HeaderFooterFormwithNavigationH
#define HeaderFooterFormwithNavigationH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ActnList.hpp>
#include <System.Actions.hpp>
#include <FMX.Controls.Presentation.hpp>
//---------------------------------------------------------------------------
class THeaderFooterwithNavigation : public TForm
{
__published:	// IDE-managed Components
	TTabControl *TabControl1;
	TToolBar *BottomToolBar;
	TActionList *ActionList1;
	TTabItem *TabItem1;
	TTabItem *TabItem2;
	TControlAction *TitleAction;
	TNextTabAction *NextTabAction;
	TPreviousTabAction *PreviousTabAction;
	TToolBar *TopToolBar;
	TLabel *ToolBarLabel;
	TSpeedButton *btnBack;
	TSpeedButton *btnNext;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall TitleActionUpdate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall THeaderFooterwithNavigation(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THeaderFooterwithNavigation *HeaderFooterwithNavigation;
//---------------------------------------------------------------------------
#endif
