// ---------------------------------------------------------------------------

#ifndef WMETVanH
#define WMETVanH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

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
	String FDepartStation;
	String FPurposeStation;
	String FInvoiceNum;
	String FInvoiceSupplier;
	String FInvoiceConsign;

	void SetCarrying(int Value);
	void SetBrutto(int Value);
	void SetTareTrft(int Value);
	void SetTareDyn(int Value);
	void SetTareSta(int Value);
	void SetTareIndex(int Value);

public:
	__fastcall TVan();

	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TVan* Source);
	String __fastcall ToString();

	void SetDefault();

	__property int Num = {read = FNum, write = FNum};
	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};
	__property String VanNum = {read = FVanNum, write = FVanNum};
	__property String VanType = {read = FVanType, write = FVanType};
	__property int Carrying = {read = FCarrying, write = FCarrying};
	__property int Brutto = {read = FBrutto, write = FBrutto};
	__property int Tare = {read = FTare};
	__property int TareTrft = {read = FTareTrft, write = FTareTrft};
	__property int TareDyn = {read = FTareDyn, write = FTareDyn};
	__property int TareSta = {read = FTareSta, write = FTareSta};
	__property int TareIndex = {read = FTareIndex, write = FTareIndex};
	__property int Netto = {read = FNetto};
	__property int Overload = {read = FOverload};
	__property String CargoType = {read = FCargoType, write = FCargoType};
	__property String DepartStation = {
		read = FDepartStation, write = FDepartStation};
	__property String PurposeStation = {
		read = FPurposeStation, write = FPurposeStation};
	__property String InvoiceNum = {read = FInvoiceNum, write = FInvoiceNum};
	__property String InvoiceSupplier = {
		read = FInvoiceSupplier, write = FInvoiceSupplier};
	__property String InvoiceConsign = {
		read = FInvoiceConsign, write = FInvoiceConsign};
};

// ---------------------------------------------------------------------------
#endif
