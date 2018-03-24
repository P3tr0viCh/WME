// ---------------------------------------------------------------------------

#ifndef WMELoginH
#define WMELoginH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

// ---------------------------------------------------------------------------
class TfrmLogin : public TForm {
__published: // IDE-managed Components

	TButton *btnOk;
	TButton *btnCancel;
	TEdit *ePass;
	TLabel *lblPass;
	TLabel *lblUser;
	TComboBox *cboxUser;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

private: // User declarations
		public : // User declarations

	__fastcall TfrmLogin(TComponent* Owner);

	static bool Show();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmLogin *frmLogin;
// ---------------------------------------------------------------------------
#endif
