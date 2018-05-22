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
#include "WMEStringsGridHeader.h"

#include "WMEMain.h"

#include "WMEService.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmService::TfrmService(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmService::Show(TVanList * VanList) {
	bool Result = false;

	TfrmService * frmService = new TfrmService(Application);
	try {
		frmService->VanList = VanList;

		Result = frmService->ShowModal() == mrOk;
	}
	__finally {
		delete frmService;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::FormCreate(TObject *Sender) {
	WriteToLogForm(true, ClassName());

	sgVans->DefaultRowHeight = Main->DefaultRowHeight;

	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->ReadFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::FormDestroy(TObject *Sender) {
	TFileIni * FileIni = TFileIni::GetNewInstance();
	try {
		FileIni->WriteFormBounds(this);
	}
	__finally {
		delete FileIni;
	}

	WriteToLogForm(false, ClassName());
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::tbtnCloseClick(TObject *Sender) {
	Close();
}

// ---------------------------------------------------------------------------
void __fastcall TfrmService::sgVansDrawCell(TObject *Sender, int ACol, int ARow,
	TRect &Rect, TGridDrawState State) {
	StringGridDrawCell(sgVans, ACol, ARow, Rect, State, NUSet, NUSet, NUSet,
		Main->Settings->ColorReadOnly, NUColor, true);
}
// ---------------------------------------------------------------------------
