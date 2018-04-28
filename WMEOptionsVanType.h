// ---------------------------------------------------------------------------

#ifndef WMEOptionsVanTypeH
#define WMEOptionsVanTypeH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "WMETVanType.h"

// ---------------------------------------------------------------------------
class TfrmOptionsVanType : public TForm {
__published:
	TButton *btnCancel;
	TButton *btnOk;
	TLabeledEdit *eCode;
	TLabeledEdit *eName;
	TBevel *Bevel;
	TLabeledEdit *eAxisCount;

	void __fastcall btnOkClick(TObject *Sender);

private:
public:
	__fastcall TfrmOptionsVanType(TComponent * Owner);

	static bool Show(TComponent * Owner, TVanType * VanType);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmOptionsVanType *frmOptionsVanType;
// ---------------------------------------------------------------------------
#endif
