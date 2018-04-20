// ---------------------------------------------------------------------------

#ifndef WMEMainH
#define WMEMainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>

#include "WMETSettings.h"
#include <Vcl.AppEvnts.hpp>

// ---------------------------------------------------------------------------
class TMain : public TForm {
__published:

	TButton *btnAbout;
	TButton *btnClose;
	TButton *btnOptions;
	TButton *btnManual;
	TButton *btnDatabase;
	TStatusBar *StatusBar;
	TButton *btnOperator;
	TApplicationEvents *ApplicationEvents;

	void __fastcall btnAboutClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnManualClick(TObject *Sender);
	void __fastcall btnDatabaseClick(TObject *Sender);
	void __fastcall btnOperatorClick(TObject *Sender);
	void __fastcall btnOptionsClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ApplicationEventsException(TObject *Sender, Exception *E);

private:
	TUser *FUser;
	TSettings *FSettings;

public:
	__fastcall TMain(TComponent* Owner);

	void ChangeUser();

	__property TUser *User = {read = FUser};

	__property TSettings *Settings = {read = FSettings};
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif
