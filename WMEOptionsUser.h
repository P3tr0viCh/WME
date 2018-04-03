// ---------------------------------------------------------------------------

#ifndef WMEOptionsUserH
#define WMEOptionsUserH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "WMETUser.h"

// ---------------------------------------------------------------------------
class TfrmOptionsUser : public TForm {
__published:

	TButton *btnCancel;
	TButton *btnOk;
	TLabeledEdit *eName;
	TLabeledEdit *ePass;
	TLabeledEdit *eTabNum;
	TLabeledEdit *eShiftNum;
	TCheckBox *cboxAdmin;

	void __fastcall btnOkClick(TObject *Sender);

private:
public:

	__fastcall TfrmOptionsUser(TComponent* Owner);

	static bool Show(TComponent* Owner, TUser *User, int AdminCount);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmOptionsUser *frmOptionsUser;
// ---------------------------------------------------------------------------
#endif
