// ---------------------------------------------------------------------------

#ifndef WMETVanH
#define WMETVanH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

#include <ObjList.h>

#include "WMETUser.h"

// ---------------------------------------------------------------------------
class TVan : public TObject {
private:
	int FNum;

	TDateTime FDateTime;

	String FVanNum;
	String FVanType;

	int FCarrying;
	int FBrutto;
	int FTare;
	int FTareTrft;
	int FTareDyn;
	int FTareSta;

	int FTareIndex;

	int FNetto;
	int FOverload;

	String FCargoType;

	TUser *FUser;

	String FDepartStation;
	String FPurposeStation;
	String FInvoiceNum;
	String FInvoiceSupplier;
	String FInvoiceRecipient;

	void Init();

	void SetCarrying(int Value);
	void SetBrutto(int Value);
	void SetTareTrft(int Value);
	void SetTareDyn(int Value);
	void SetTareSta(int Value);
	void SetTareIndex(int Value);

	void SetUser(TUser *Value);

public:
	__fastcall TVan();
	__fastcall ~TVan();

	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TVan* Source);
	String __fastcall ToString();

	__property int Num = {read = FNum, write = FNum};

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};

	__property String VanNum = {read = FVanNum, write = FVanNum};
	__property String VanType = {read = FVanType, write = FVanType};

	__property int Carrying = {read = FCarrying, write = SetCarrying};
	__property int Brutto = {read = FBrutto, write = SetBrutto};
	__property int Tare = {read = FTare};
	__property int TareTrft = {read = FTareTrft, write = SetTareTrft};
	__property int TareDyn = {read = FTareDyn, write = SetTareDyn};
	__property int TareSta = {read = FTareSta, write = SetTareSta};
	__property int TareIndex = {read = FTareIndex, write = SetTareIndex};
	__property int Netto = {read = FNetto};
	__property int Overload = {read = FOverload};

	__property String CargoType = {read = FCargoType, write = FCargoType};

	__property TUser *User = {read = FUser, write = SetUser};

	__property String DepartStation = {
		read = FDepartStation, write = FDepartStation};
	__property String PurposeStation = {
		read = FPurposeStation, write = FPurposeStation};
	__property String InvoiceNum = {read = FInvoiceNum, write = FInvoiceNum};
	__property String InvoiceSupplier = {
		read = FInvoiceSupplier, write = FInvoiceSupplier};
	__property String InvoiceRecipient = {
		read = FInvoiceRecipient, write = FInvoiceRecipient};
};

// ---------------------------------------------------------------------------
typedef TObjList<TVan>TVanList;

// ---------------------------------------------------------------------------
#endif
