// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <UtilsStr.h>
#include <UtilsMisc.h>

#include "WMEAdd.h"
#include "WMEStrings.h"
#include "WMEStringsGridHeader.h"

#include "WMEOptionsVanType.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TfrmOptionsVanType::TfrmOptionsVanType(TComponent * Owner)
	: TForm(Owner) {
}

// ---------------------------------------------------------------------------
bool TfrmOptionsVanType::Show(TComponent * Owner, TVanType * VanType) {
	bool Result = false;

	TfrmOptionsVanType * frmOptionsVanType = new TfrmOptionsVanType(Owner);
	try {
		frmOptionsVanType->Caption = LoadStr(IDS_GRID_HEADER_VANTYPE);

		frmOptionsVanType->eCode->Text = VanType->Code;
		frmOptionsVanType->eName->Text = VanType->Name;
		frmOptionsVanType->eAxisCount->Text = VanType->AxisCount;

		Result = frmOptionsVanType->ShowModal() == mrOk;

		if (Result) {
			if (IsEmpty(frmOptionsVanType->eCode->Text)) {
				VanType->Code = VAN_CATALOG_CODE_NONE;
			}
			else {
				VanType->Code = StrToInt(frmOptionsVanType->eCode->Text);
			}
			VanType->Name = frmOptionsVanType->eName->Text;
			if (IsEmpty(frmOptionsVanType->eAxisCount->Text)) {
				VanType->AxisCount = VAN_TYPE_AXIS_NONE;
			}
			else {
				VanType->AxisCount =
					StrToInt(frmOptionsVanType->eAxisCount->Text);
			}
		}
	}
	__finally {
		delete frmOptionsVanType;
	}

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TfrmOptionsVanType::btnOkClick(TObject *Sender) {
	if (!IsEmpty(eCode->Text)) {
		if (!CheckIntValue(eCode->Text)) {
			MsgBoxErr(IDS_ERROR_NEED_INT);
			eCode->SetFocus();
			return;
		}
	}

	if (!IsEmpty(eAxisCount->Text)) {
		if (!CheckIntValue(eAxisCount->Text)) {
			MsgBoxErr(IDS_ERROR_NEED_INT);
			eAxisCount->SetFocus();
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
