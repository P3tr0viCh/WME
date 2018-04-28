// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsStr.h>
#include <UtilsMisc.h>

#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMEOptionsVanCatalog.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmOptionsVanCatalog::TfrmOptionsVanCatalog(TComponent * Owner)
	: TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmOptionsVanCatalog::Show(TComponent * Owner, String Caption,
	TVanCatalog * VanCatalog) {
	bool Result = false;

	TfrmOptionsVanCatalog * frmOptionsVanCatalog =
		new TfrmOptionsVanCatalog(Owner);
	try {
		frmOptionsVanCatalog->Caption = Caption;

		frmOptionsVanCatalog->eCode->Text = VanCatalog->Code;
		frmOptionsVanCatalog->eName->Text = VanCatalog->Name;

		Result = frmOptionsVanCatalog->ShowModal() == mrOk;

		if (Result) {
			if (IsEmpty(frmOptionsVanCatalog->eCode->Text)) {
				VanCatalog->Code = VAN_CATALOG_CODE_NONE;
			}
			else {
				VanCatalog->Code = StrToInt(frmOptionsVanCatalog->eCode->Text);
			}
			VanCatalog->Name = frmOptionsVanCatalog->eName->Text;
		}
	}
	__finally {
		delete frmOptionsVanCatalog;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptionsVanCatalog::btnOkClick(TObject *Sender) {
	if (!IsEmpty(eCode->Text)) {
		if (!CheckIntValue(eCode->Text)) {
			MsgBoxErr(IDS_ERROR_NEED_INT);
			eCode->SetFocus();
			return;
		}
	}

	if (IsEmpty(eName->Text)) {
		MsgBoxErr(IDS_ERROR_TEXT_EMPTY);
		eName->SetFocus();
		return;
	}

	ModalResult = mrOk;
}
// ---------------------------------------------------------------------------
