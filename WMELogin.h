// ---------------------------------------------------------------------------

#ifndef WMELoginH
#define WMELoginH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include <ObjList.h>

#include "WMETUser.h"
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TfrmLogin : public TForm {
__published:
	TButton *btnOk;
	TButton *btnCancel;
	TEdit *ePass;
	TLabel *lblPass;
	TLabel *lblUser;
	TComboBox *cboxUser;
	TBevel *Bevel;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall btnOkClick(TObject *Sender);

private:
	TUserList * UserList;

public:
	__fastcall TfrmLogin(TComponent* Owner);

	static bool Show(TUserList * UserList, TUser * User);

	void UpdateForm();

	bool CheckPass();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmLogin *frmLogin;
// ---------------------------------------------------------------------------
#endif
