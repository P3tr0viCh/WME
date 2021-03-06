CREATE TABLE trains
(
  trnum          INT(10) UNSIGNED                           NOT NULL,
  scales         INT(10) DEFAULT 0                          NOT NULL,
  wtime          INT(10) UNSIGNED DEFAULT 0                 NOT NULL,
  bdatetime      DATETIME DEFAULT '0000-00-00 00:00:00'     NOT NULL,
  weighttype     SMALLINT(5) UNSIGNED DEFAULT 0             NULL,
  carrying       INT(10) UNSIGNED DEFAULT 0                 NULL,
  brutto         INT(10) UNSIGNED DEFAULT 0                 NULL,
  tare           INT(10) UNSIGNED DEFAULT 0                 NULL,
  netto          INT(10) DEFAULT 0                          NULL,
  overload       INT(10) DEFAULT 0                          NULL,
  nvans          SMALLINT(5) DEFAULT 0                      NULL,
  operator_name  CHAR(24)                                   NULL,
  operator_tabn  CHAR(8)                                    NULL,
  operator_shift CHAR(4)                                    NULL,

  PRIMARY KEY (trnum, scales)
)
  ENGINE = MyISAM;
