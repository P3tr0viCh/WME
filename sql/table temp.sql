CREATE TABLE temp
(
  bdatetime         DATETIME DEFAULT '0000-00-00 00:00:00' NOT NULL,
  wtime             INT UNSIGNED DEFAULT '0'               NULL,
  scales            SMALLINT(6) DEFAULT '0'                NOT NULL,
  auto_num          CHAR(9)                                NULL,
  brutto            FLOAT(16, 2)                           NULL,
  tare              FLOAT(16, 2)                           NULL,
  idatetime_tare    DATETIME                               NULL,
  netto             FLOAT(16, 2)                           NULL,
  cargotype         CHAR(42)                               NULL,
  invoice_num       CHAR(16)                               NULL,
  invoice_supplier  CHAR(32)                               NULL,
  invoice_recipient CHAR(32)                               NULL,
  invoice_netto     FLOAT(16, 2) DEFAULT '0.00'            NULL,
  driver            CHAR(32)                               NULL,
  operator          CHAR(32)                               NULL,
  PRIMARY KEY (bdatetime, scales)
)
  ENGINE = MyISAM;