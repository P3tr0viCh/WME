// ---------------------------------------------------------------------------

#ifndef WMETrainListH
#define WMETrainListH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

// ---------------------------------------------------------------------------
class TfrmTrainList : public TForm {
__published: // IDE-managed Components
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
		private : // User declarations
	public : // User declarations
		__fastcall TfrmTrainList(TComponent* Owner);

	static void Show();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmTrainList *frmTrainList;
// ---------------------------------------------------------------------------
#endif
