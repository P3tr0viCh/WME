// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEDebug.h"

#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMELogin.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmLogin::TfrmLogin(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmLogin::Show(TUserList *UserList, TUser* User) {
	bool Result = false;

	TfrmLogin *frmLogin = new TfrmLogin(Application);
	try {
		frmLogin->UserList->Assign(UserList);
		frmLogin->UpdateForm();

		Result = frmLogin->ShowModal() == mrOk;

		if (Result) {
			User->Assign(UserList->Items[frmLogin->cboxUser->ItemIndex]);
			WriteToLog(Format(IDS_LOG_LOGIN_OK, User->Name));
		}
		else {
			WriteToLog(IDS_LOG_LOGIN_CANCEL);
		}
	}
	__finally {
		delete frmLogin;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmLogin::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	UserList = new TUserList();

	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormPosition(this);
	}
	__finally {
		delete FileIni;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmLogin::FormDestroy(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormPosition(this);
	}
	__finally {
		delete FileIni;
	}

	UserList->Free();

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
void __fastcall TfrmLogin::FormCloseQuery(TObject *Sender, bool &CanClose) {
#ifdef FORCECLOSE
	CanClose = true;
#else
	CanClose = ModalResult == mrOk;
	if (!CanClose) {
		CanClose = MsgBoxYesNo(IDS_QUESTION_CLOSE_PROGRAM);
	}
#endif
}

// ---------------------------------------------------------------------------
void TfrmLogin::UpdateForm() {
	for (int i = 0; i < UserList->Count; i++) {
		cboxUser->Items->Add(UserList->Items[i]->Name);
	}

}

// ---------------------------------------------------------------------------
bool TfrmLogin::CheckPass() {
	if (cboxUser->ItemIndex == -1) {
		cboxUser->Text = "";
		cboxUser->SetFocus();

		MsgBoxErr(IDS_ERROR_SELECT_USERNAME);

		return false;
	}

	if (!AnsiSameStr(ePass->Text, UserList->Items[cboxUser->ItemIndex]->Pass)) {
		ePass->Clear();
		ePass->SetFocus();

		MsgBoxErr(IDS_ERROR_PASS_WRONG);

		return false;
	}

	return true;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmLogin::btnOkClick(TObject *Sender) {
	if (!CheckPass()) {
		ModalResult = mrNone;
	}
}
// ---------------------------------------------------------------------------
