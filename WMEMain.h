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
#include <Vcl.AppEvnts.hpp>

#include "WMETSettings.h"

#include "WMETVan.h"

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
	TUser * FUser;
	TSettings * FSettings;

	String WeightTypeAsText[sizeof(TWeightType)];
	String TareIndexAsText[sizeof(TTareIndex)];

public:
	__fastcall TMain(TComponent* Owner);

	int DefaultRowHeight;

	void ChangeUser();

	void InitStrings();

	String GetWeightTypeAsText(TWeightType Value);
	String GetTareIndexAsText(TTareIndex Value);

	__property TUser * User = {read = FUser};

	__property TSettings * Settings = {read = FSettings};
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif
