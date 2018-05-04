// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>
#include <UtilsMisc.h>

#include "WMEAdd.h"
#include "WMEStrings.h"

#include "WMETDBSaveTrain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBSaveTrain::TDBSaveTrain(TConnectionInfo * ConnectionInfo,
	TTrain * Train) : TDatabaseOperation(ConnectionInfo) {
	VansFields = new TDBVansFields();
	TrainsFields = new TDBTrainsFields();

	FTrain = Train;
}

// ---------------------------------------------------------------------------
__fastcall TDBSaveTrain::~TDBSaveTrain() {
	TrainsFields->Free();
	VansFields->Free();
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationStart() {
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationEndOK() {
	WriteToLog(Format(IDS_LOG_MYSQL_SAVE_TRAIN_OK,
		ARRAYOFCONST((Train->VanList->Count))));
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_SAVE_TRAIN_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::SetVansParam(TADOQuery * Query, TDBVansFieldName Name,
	int Index, Variant Value) {
	TParameter * Param = Query->Parameters->ParamByName
		(VansFields->GetParamName(Name, Index));
	Param->DataType = VansFields->GetFieldType(Name);
	Param->Value = Value;
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::SetTrainParam(TADOQuery * Query, TDBTrainsFieldName Name,
	Variant Value) {
	TParameter * Param = Query->Parameters->ParamByName
		(TrainsFields->GetParamName(Name));
	Param->DataType = TrainsFields->GetFieldType(Name);
	Param->Value = Value;
}

// ---------------------------------------------------------------------------
void TDBSaveTrain::Operation() {
	if (Train->VanList->IsEmpty()) {
		return;
	}

	UseDatabase = true;

	Connection->Open();

	TADOQuery * Query = new TADOQuery(NULL);
	try {
		Query->Connection = Connection;

		if (Train->TrainNum == TRAINNUM_NONE) {
			Train->TrainNum = DateTimeToWTime(Now());
		}
		else {
			// TODO: mark as deleted and delete after successful save

			Query->SQL->Add("DELETE FROM vans");
			Query->SQL->Add("WHERE");
			Query->SQL->Add(VansFields->GetFieldName(fnVansTrnum) + "=" +
				VansFields->GetParamValue(fnVansTrnum));

			SetVansParam(Query, fnVansTrnum, -1, Train->TrainNum);

			Query->Prepared = true;

			Query->ExecSQL();

			Query->SQL->Clear();
			Query->SQL->Add("DELETE FROM trains");
			Query->SQL->Add("WHERE");
			Query->SQL->Add(TrainsFields->GetFieldName(fnTrainsTrnum) + "=" +
				TrainsFields->GetParamValue(fnTrainsTrnum));

			SetTrainParam(Query, fnTrainsTrnum, Train->TrainNum);

			Query->Prepared = true;

			Query->ExecSQL();
		}

		Query->SQL->Clear();
		Query->SQL->Add("INSERT INTO vans");
		Query->SQL->Add("(");
		Query->SQL->Add(VansFields->GetFields());
		Query->SQL->Add(")");
		Query->SQL->Add("VALUES");

		Query->SQL->Add("(" + VansFields->GetValues(0) + ")");
		for (int i = 1; i < Train->VanList->Count; i++) {
			Query->SQL->Add(",");
			Query->SQL->Add("(" + VansFields->GetValues(i) + ")");
		}

		for (int i = 0; i < Train->VanList->Count; i++) {
			SetVansParam(Query, fnVansTrnum, i, Train->TrainNum);

			SetVansParam(Query, fnVansNum, i, Train->VanList->Items[i]->Num);
			SetVansParam(Query, fnVansWTime, i, Train->UnixTime);
			SetVansParam(Query, fnVansDatetime, i,
				DateTimeToSQLStr(Train->VanList->Items[i]->DateTime));

			SetVansParam(Query, fnVansVanNum, i,
				Train->VanList->Items[i]->VanNum);

			SetVansParam(Query, fnVansVanType, i,
				Train->VanList->Items[i]->VanType->Name);
			SetVansParam(Query, fnVansVanTypeCode, i,
				Train->VanList->Items[i]->VanType->Code);

			SetVansParam(Query, fnVansCarrying, i,
				Train->VanList->Items[i]->Carrying);
			SetVansParam(Query, fnVansBrutto, i,
				Train->VanList->Items[i]->Brutto);

			SetVansParam(Query, fnVansTare, i, Train->VanList->Items[i]->Tare);
			SetVansParam(Query, fnVansTareTrft, i,
				Train->VanList->Items[i]->TareTrft);
			SetVansParam(Query, fnVansTareDyn, i,
				Train->VanList->Items[i]->TareDyn);
			SetVansParam(Query, fnVansTareSta, i,
				Train->VanList->Items[i]->TareSta);
			SetVansParam(Query, fnVansTareIndex, i,
				Train->VanList->Items[i]->TareIndex);

			SetVansParam(Query, fnVansNetto, i,
				Train->VanList->Items[i]->Netto);
			SetVansParam(Query, fnVansOverload, i,
				Train->VanList->Items[i]->Overload);

			SetVansParam(Query, fnVansCargoType, i,
				Train->VanList->Items[i]->CargoType->Name);
			SetVansParam(Query, fnVansCargoTypeCode, i,
				Train->VanList->Items[i]->CargoType->Code);

			SetVansParam(Query, fnVansAxisCount, i,
				Train->VanList->Items[i]->VanType->AxisCount);

			SetVansParam(Query, fnVansOperator, i,
				Train->VanList->Items[i]->User->Name);
			SetVansParam(Query, fnVansOperatorTabNum, i,
				Train->VanList->Items[i]->User->TabNum);
			SetVansParam(Query, fnVansOperatorShiftNum, i,
				Train->VanList->Items[i]->User->ShiftNum);

			SetVansParam(Query, fnVansDepartStation, i,
				Train->VanList->Items[i]->DepartStation->Name);
			SetVansParam(Query, fnVansDepartStationCode, i,
				Train->VanList->Items[i]->DepartStation->Code);

			SetVansParam(Query, fnVansPurposeStation, i,
				Train->VanList->Items[i]->PurposeStation->Name);
			SetVansParam(Query, fnVansPurposeStationCode, i,
				Train->VanList->Items[i]->PurposeStation->Code);

			SetVansParam(Query, fnVansInvoiceNum, i,
				Train->VanList->Items[i]->InvoiceNum);

			SetVansParam(Query, fnVansInvoiceSupplier, i,
				Train->VanList->Items[i]->InvoiceSupplier->Name);
			SetVansParam(Query, fnVansInvoiceSupplierCode, i,
				Train->VanList->Items[i]->InvoiceSupplier->Code);

			SetVansParam(Query, fnVansInvoiceRecipient, i,
				Train->VanList->Items[i]->InvoiceRecipient->Name);
			SetVansParam(Query, fnVansInvoiceRecipientCode, i,
				Train->VanList->Items[i]->InvoiceRecipient->Code);
		}

		Query->Prepared = true;

		Query->ExecSQL();

		Query->Prepared = false;

		Query->SQL->Clear();

		Query->SQL->Add("INSERT INTO trains");
		Query->SQL->Add("(");
		Query->SQL->Add(TrainsFields->GetFields());
		Query->SQL->Add(")");
		Query->SQL->Add("VALUES");

		Query->SQL->Add("(" + TrainsFields->GetValues(-1) + ")");

		SetTrainParam(Query, fnTrainsTrnum, Train->TrainNum);
		SetTrainParam(Query, fnTrainsWTime, Train->UnixTime);
		SetTrainParam(Query, fnTrainsDatetime,
			DateTimeToSQLStr(Train->DateTime));
		SetTrainParam(Query, fnTrainsCarrying, Train->Carrying);
		SetTrainParam(Query, fnTrainsBrutto, Train->Brutto);
		SetTrainParam(Query, fnTrainsTare, Train->Tare);
		SetTrainParam(Query, fnTrainsNetto, Train->Netto);
		SetTrainParam(Query, fnTrainsOverload, Train->Overload);
		SetTrainParam(Query, fnTrainsVanCount, Train->VanCount);

		SetTrainParam(Query, fnTrainsOperator, Train->User->Name);
		SetTrainParam(Query, fnTrainsOperatorTabNum, Train->User->TabNum);
		SetTrainParam(Query, fnTrainsOperatorShiftNum, Train->User->ShiftNum);

		Query->Prepared = true;

		Query->ExecSQL();
	}
	__finally {
		Query->Free();
	}

	Connection->Close();
}

// ---------------------------------------------------------------------------
