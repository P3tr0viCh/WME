// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsMisc.h>
#include <UtilsFileIni.h>

#include "WMEDebug.h"

#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMETrainList.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmTrainList::TfrmTrainList(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void TfrmTrainList::Show() {
	TfrmTrainList *frmTrainList = new TfrmTrainList(Application);
	try {
		frmTrainList->ShowModal();
	}
	__finally {
		delete frmTrainList;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormBounds(this);
	}
	__finally {
		delete FileIni;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TfrmTrainList::FormDestroy(TObject *Sender) {
	TFileIni* FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	WriteToLogForm(false, ClassName());
}
// ---------------------------------------------------------------------------
