// ---------------------------------------------------------------------------

#ifndef WMETVanH
#define WMETVanH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

#include <ObjList.h>

#include "WMETUser.h"
#include "WMETVanCatalog.h"
#include "WMETVanType.h"

const TDateTime DEFAULT_DATETIME = 0;

enum TWeightType {
	wtBrutto = 0, wtTare = 1, wtMixed = 2
};
const TWeightType DEFAULT_WEIGHTTYPE = wtBrutto;

enum TTareIndex {
	tiTrafaret = 0, tiDynamic = 1, tiStatic = 2
};
const TTareIndex DEFAULT_TARE_INDEX = tiTrafaret;

// ---------------------------------------------------------------------------
class TVan : public TObject {
private:
	int FNum;

	TDateTime FDateTime;

	TWeightType FWeightType;

	String FVanNum;

	TVanType * FVanType;

	int FCarrying;
	int FBrutto;
	int FTare;
	int FTareTrft;
	int FTareDyn;
	int FTareSta;

	TTareIndex FTareIndex;

	int FNetto;
	int FOverload;

	TVanCatalog * FCargoType;

	TUser * FUser;

	TVanCatalog * FDepartStation;
	TVanCatalog * FPurposeStation;
	String FInvoiceNum;
	TVanCatalog * FInvoiceSupplier;
	TVanCatalog * FInvoiceRecipient;

	void Init();

	void UpdateValues();

	void SetCarrying(int Value);
	void SetBrutto(int Value);
	void SetTareTrft(int Value);
	void SetTareDyn(int Value);
	void SetTareSta(int Value);
	void SetTareIndex(TTareIndex Value);

	void SetUser(TUser * Value);

public:
	__fastcall TVan();
	__fastcall ~TVan();

	bool __fastcall Equals(TObject * Obj);
	void __fastcall Assign(TVan * Source);
	String __fastcall ToString();

	__property int Num = {read = FNum, write = FNum};

	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};

	__property TWeightType WeightType = {read = FWeightType, write = FWeightType
	};

	__property String VanNum = {read = FVanNum, write = FVanNum};

	__property TVanType * VanType = {read = FVanType};

	__property int Carrying = {read = FCarrying, write = SetCarrying};
	__property int Brutto = {read = FBrutto, write = SetBrutto};
	__property int Tare = {read = FTare};
	__property int TareTrft = {read = FTareTrft, write = SetTareTrft};
	__property int TareDyn = {read = FTareDyn, write = SetTareDyn};
	__property int TareSta = {read = FTareSta, write = SetTareSta};

	__property TTareIndex TareIndex = {read = FTareIndex, write = SetTareIndex};

	__property int Netto = {read = FNetto};
	__property int Overload = {read = FOverload};

	__property TVanCatalog * CargoType = {read = FCargoType};

	__property TUser * User = {read = FUser, write = SetUser};

	__property TVanCatalog * DepartStation = {read = FDepartStation};
	__property TVanCatalog * PurposeStation = {read = FPurposeStation};

	__property String InvoiceNum = {read = FInvoiceNum, write = FInvoiceNum};

	__property TVanCatalog * InvoiceSupplier = {read = FInvoiceSupplier};
	__property TVanCatalog * InvoiceRecipient = {read = FInvoiceRecipient};
};

// ---------------------------------------------------------------------------
typedef TObjList<TVan>TVanList;

// ---------------------------------------------------------------------------
#endif
