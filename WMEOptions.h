// ---------------------------------------------------------------------------

#ifndef WMEOptionsH
#define WMEOptionsH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TfrmOptions : public TForm {
__published: // IDE-managed Components

	TButton *btnOk;
	TButton *btnCancel;
	TPageControl *PageControl;
	TTabSheet *tsDatabase;
	TTabSheet *tsUsers;
	TLabeledEdit *eDBUser;
	TLabel *Label1;
	TLabeledEdit *eDBPass;
	TLabel *Label2;
	TButton *btnDBConnectionCheck;
	TBevel *bvlDB;
	TLabeledEdit *eDBServer;
	TLabeledEdit *eDBPort;
	TButton *btnDBConnectionDefault;
	TPanel *pnlButtons;
	TButton *btnDatabase;
	TButton *btnUsers;
	TButton *btnDBCreate;
	TButton *btnDBDelete;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnPageSelectClick(TObject *Sender);
	void __fastcall btnDBConnectionCheckClick(TObject *Sender);
	void __fastcall btnDBConnectionDefaultClick(TObject *Sender);

private: // User declarations

		public : // User declarations
	__fastcall TfrmOptions(TComponent* Owner);

	static bool Show();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
// ---------------------------------------------------------------------------
#endif
