// ---------------------------------------------------------------------------

#pragma hdrstop

#include <UtilsLog.h>
#include <UtilsStr.h>

#include "WMEStrings.h"

#include "WMETDBLoadTrain.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TDBLoadTrain::TDBLoadTrain(TConnectionInfo *ConnectionInfo,
	int TrainNum) : TDatabaseOperation(ConnectionInfo) {
	FVanList = new TVanList();

	VansFields = new TDBVansFields();

	FTrainNum = TrainNum;
}

// ---------------------------------------------------------------------------
__fastcall TDBLoadTrain::~TDBLoadTrain() {
	VansFields->Free();

	FVanList->Free();
}

// ---------------------------------------------------------------------------
void TDBLoadTrain::OperationStart() {
}

// ---------------------------------------------------------------------------
void TDBLoadTrain::OperationEndOK() {
	WriteToLog(Format(IDS_LOG_MYSQL_LOAD_TRAIN_OK,
		ARRAYOFCONST((VanList->Count))));
}

// ---------------------------------------------------------------------------
void TDBLoadTrain::OperationEndFail() {
	WriteToLog(Format(IDS_LOG_MYSQL_LOAD_TRAIN_FAIL, ErrorMessage));
}

// ---------------------------------------------------------------------------
int TDBLoadTrain::GetFieldAsInteger(TADOQuery * Query, String FieldName,
	int Default) {
	TField * Field = Query->FieldByName(FieldName);

	return Field->IsNull ? Default : Field->AsInteger;
}

// ---------------------------------------------------------------------------
void TDBLoadTrain::Operation() {
	UseDatabase = true;

	Connection->Open();

	TADOQuery * Query = new TADOQuery(NULL);
	try {
		Query->Connection = Connection;

		WriteToLog(VansFields->GetParamValue(fnVansTrnum));

		Query->SQL->Add("SELECT");
		Query->SQL->Add(VansFields->GetFields());
		Query->SQL->Add("FROM vans");
		Query->SQL->Add("WHERE");
		Query->SQL->Add(VansFields->GetFieldName(fnVansTrnum));
		Query->SQL->Add("=");
		Query->SQL->Add(VansFields->GetParamValue(fnVansTrnum));
		Query->SQL->Add("ORDER BY");
		Query->SQL->Add(VansFields->GetFieldName(fnVansNum));

		// WriteToLog(Query->SQL->Text);

		TParameter * Param = Query->Parameters->ParamByName
			(VansFields->GetParamName(fnVansTrnum));
		Param->DataType = VansFields->GetFieldType(fnVansTrnum);
		Param->Value = TrainNum;

		Query->Open();

		TVan * Van;

		while (!Query->Eof) {
			Van = new TVan();

			Van->Num = Query->FieldByName(VansFields->GetFieldName(fnVansNum))
				->AsInteger;

			Van->DateTime =
				Query->FieldByName(VansFields->GetFieldName(fnVansDatetime))
				->AsDateTime;

			Van->WeightType =
				Query->FieldByName(VansFields->GetFieldName(fnVansWeightType))
				->AsInteger;

			Van->VanNum =
				Query->FieldByName(VansFields->GetFieldName(fnVansVanNum))
				->AsString;

			Van->VanType->Name =
				Query->FieldByName(VansFields->GetFieldName(fnVansVanType))
				->AsString;
			Van->VanType->Code =
				GetFieldAsInteger(Query,
				VansFields->GetFieldName(fnVansVanTypeCode),
				Van->VanType->Code);
			Van->VanType->AxisCount =
				GetFieldAsInteger(Query,
				VansFields->GetFieldName(fnVansAxisCount),
				Van->VanType->AxisCount);

			Van->Carrying =
				Query->FieldByName(VansFields->GetFieldName(fnVansCarrying))
				->AsInteger;
			Van->Brutto =
				Query->FieldByName(VansFields->GetFieldName(fnVansBrutto))
				->AsInteger;

			Van->TareTrft =
				Query->FieldByName(VansFields->GetFieldName(fnVansTareTrft))
				->AsInteger;
			Van->TareDyn =
				Query->FieldByName(VansFields->GetFieldName(fnVansTareDyn))
				->AsInteger;
			Van->TareSta =
				Query->FieldByName(VansFields->GetFieldName(fnVansTareSta))
				->AsInteger;
			Van->TareIndex =
				Query->FieldByName(VansFields->GetFieldName(fnVansTareIndex))
				->AsInteger;

			Van->CargoType->Name =
				Query->FieldByName(VansFields->GetFieldName(fnVansCargoType))
				->AsString;
			Van->CargoType->Code =
				GetFieldAsInteger(Query,
				VansFields->GetFieldName(fnVansCargoTypeCode),
				Van->CargoType->Code);

			Van->DepartStation->Name =
				Query->FieldByName(VansFields->GetFieldName(fnVansDepartStation)
				)->AsString;
			Van->DepartStation->Code =
				GetFieldAsInteger(Query,
				VansFields->GetFieldName(fnVansDepartStationCode),
				Van->DepartStation->Code);

			Van->PurposeStation->Name =
				Query->FieldByName
				(VansFields->GetFieldName(fnVansPurposeStation))->AsString;
			Van->PurposeStation->Code =
				GetFieldAsInteger(Query,
				VansFields->GetFieldName(fnVansPurposeStationCode),
				Van->PurposeStation->Code);

			Van->InvoiceNum =
				Query->FieldByName(VansFields->GetFieldName(fnVansInvoiceNum))
				->AsString;

			Van->InvoiceSupplier->Name =
				Query->FieldByName
				(VansFields->GetFieldName(fnVansInvoiceSupplier))->AsString;
			Van->InvoiceSupplier->Code =
				GetFieldAsInteger(Query,
				VansFields->GetFieldName(fnVansInvoiceSupplierCode),
				Van->InvoiceSupplier->Code);

			Van->InvoiceRecipient->Name =
				Query->FieldByName
				(VansFields->GetFieldName(fnVansInvoiceRecipient))->AsString;
			Van->InvoiceRecipient->Code =
				GetFieldAsInteger(Query,
				VansFields->GetFieldName(fnVansInvoiceRecipientCode),
				Van->InvoiceRecipient->Code);

			FVanList->Add(Van);

			Query->Next();
		}
	}
	__finally {
		Query->Free();
	}

	Connection->Close();
}

// ---------------------------------------------------------------------------
