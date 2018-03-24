// ---------------------------------------------------------------------------

#ifndef WMETrainH
#define WMETrainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

// ---------------------------------------------------------------------------
class TfrmTrain : public TForm {
__published: // IDE-managed Components
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
		private : // User declarations
	public : // User declarations
		__fastcall TfrmTrain(TComponent* Owner);

	static bool Show();
};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmTrain *frmTrain;
// ---------------------------------------------------------------------------
#endif
