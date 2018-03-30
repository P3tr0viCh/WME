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
	TADOConnection *ADOConnection;
	TADOQuery *ADOQuery;

	void __fastcall btnAboutClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnManualClick(TObject *Sender);
	void __fastcall btnDatabaseClick(TObject *Sender);
	void __fastcall btnOperatorClick(TObject *Sender);
	void __fastcall btnOptionsClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private:

public:
	TSettings *Settings;

	TUser *User;

	__fastcall TMain(TComponent* Owner);

	void ChangeUser();

	bool CheckConnection(TConnection *Connection);
	bool CheckConnection(TConnection *Connection, String &MySqlVersion);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif
