// ---------------------------------------------------------------------------

#ifndef WMEOptionsVanCatalogH
#define WMEOptionsVanCatalogH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "WMETVanCatalog.h"

// ---------------------------------------------------------------------------
class TfrmOptionsVanCatalog : public TForm {
__published:
	TButton *btnCancel;
	TButton *btnOk;
	TLabeledEdit *eCode;
	TLabeledEdit *eName;
	TBevel *Bevel;

	void __fastcall btnOkClick(TObject *Sender);

private:
public:
	__fastcall TfrmOptionsVanCatalog(TComponent * Owner);

	static bool Show(TComponent * Owner, String Caption,
		TVanCatalog * VanCatalog);
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmOptionsVanCatalog *frmOptionsVanCatalog;
// ---------------------------------------------------------------------------
#endif
