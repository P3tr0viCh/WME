// ---------------------------------------------------------------------------

#ifndef WMETTrainH
#define WMETTrainH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

#include <ObjList.h>

#include "WMETVan.h"

// ---------------------------------------------------------------------------
class TTrain : public TObject {
private:
	int FTrainNum;

	int FUnixTime;
	TDateTime FDateTime;

	int FCarrying;
	int FBrutto;
	int FTare;
	int FNetto;
	int FOverload;

	TVanList *FVanList;

	void Init();

	void SetCarrying(int Value);
	void SetBrutto(int Value);
	void SetTare(int Value);

	void SetVanList(TVanList *AVanList);

	void CalcFields();

public:
	__fastcall TTrain();
	__fastcall TTrain(TVanList *AVanList);

	__fastcall ~TTrain();

	bool __fastcall Equals(TObject* Obj);
	void __fastcall Assign(TTrain* Source);
	String __fastcall ToString();

	__property int TrainNum = {read = FTrainNum, write = FTrainNum};

	__property int UnixTime = {read = FUnixTime, write = FUnixTime};
	__property TDateTime DateTime = {read = FDateTime, write = FDateTime};

	__property int Carrying = {read = FCarrying, write = SetCarrying};
	__property int Brutto = {read = FBrutto, write = SetBrutto};
	__property int Tare = {read = FTare, write = SetTare};
	__property int Netto = {read = FNetto};
	__property int Overload = {read = FOverload};

	__property TVanList *VanList = {read = FVanList, write = SetVanList};
};

// ---------------------------------------------------------------------------
typedef TObjList<TTrain>TTrainList;

// ---------------------------------------------------------------------------
#endif
