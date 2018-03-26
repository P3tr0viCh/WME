// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
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
bool TfrmLogin::Show() {
	bool Result = false;

	TfrmLogin *frmLogin = new TfrmLogin(Application);
	try {
#ifndef FORCELOGON
		Result = frmLogin->ShowModal() == mrOk;
#else
		Result = true;
#endif
	}
	__finally {
		delete frmLogin;
	}

	WriteToLog(Result ? IDS_LOG_LOGIN_OK : IDS_LOG_LOGIN_CANCEL);

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmLogin::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

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

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
void __fastcall TfrmLogin::FormCloseQuery(TObject *Sender, bool &CanClose) {
#ifdef FORCECLOSE
	CanClose = true;
#else
	CanClose = ModalResult == mrOk;
	if (!CanClose) {
		CanClose = MsgBoxYesNo(LoadStr(IDS_QUESTION_CLOSE_PROGRAM));
	}
#endif
}
// ---------------------------------------------------------------------------
