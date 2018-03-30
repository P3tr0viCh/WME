// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsStr.h>
#include <UtilsMisc.h>

#include "WMEStrings.h"

#include "WMEOptionsUser.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmOptionsUser::TfrmOptionsUser(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmOptionsUser::Show(TComponent* Owner, TUser *User) {
	bool Result = false;

	TfrmOptionsUser *frmOptionsUser = new TfrmOptionsUser(Owner);
	try {
		frmOptionsUser->eName->Text = User->Name;
		frmOptionsUser->ePass->Text = User->Pass;
		frmOptionsUser->eTabNum->Text = User->TabNum;
		frmOptionsUser->eShiftNum->Text = User->ShiftNum;

		Result = frmOptionsUser->ShowModal() == mrOk;

		if (Result) {
			User->Name = frmOptionsUser->eName->Text;
			User->Pass = frmOptionsUser->ePass->Text;
			User->TabNum = frmOptionsUser->eTabNum->Text;
			User->ShiftNum = frmOptionsUser->eShiftNum->Text;
		}
	}
	__finally {
		delete frmOptionsUser;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptionsUser::btnOkClick(TObject *Sender) {
	if (IsEmpty(eName->Text)) {
		MsgBoxErr(LoadStr(IDS_ERROR_NEED_USERNAME), this->Handle);
		eName->SetFocus();
		return;
	}

	ModalResult = mrOk;
}
// ---------------------------------------------------------------------------
