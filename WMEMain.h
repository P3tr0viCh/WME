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

// ---------------------------------------------------------------------------
class TMain : public TForm {
__published: // IDE-managed Components

	TButton *btnAbout;
	TButton *btnClose;
	TButton *btnOptions;
	TButton *btnManual;
	TButton *btnDatabase;
	TStatusBar *StatusBar;
	TButton *btnOperator;
	TADOConnection *Connection;
	TADOQuery *Query;

	void __fastcall btnAboutClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnManualClick(TObject *Sender);
	void __fastcall btnDatabaseClick(TObject *Sender);
	void __fastcall btnOperatorClick(TObject *Sender);
	void __fastcall btnOptionsClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private: // User declarations
		public : // User declarations
	__fastcall TMain(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------
#endif
