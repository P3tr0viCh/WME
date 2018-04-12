CREATE TABLE trains
(
  trnum     INT(10)                                    NOT NULL,
  scales    INT(10) DEFAULT '0'                        NOT NULL,
  wtime     INT(10) UNSIGNED DEFAULT 0                 NOT NULL,
  bdatetime DATETIME DEFAULT '0000-00-00 00:00:00'     NULL,
  carrying  INT(10) UNSIGNED DEFAULT 0                 NULL,
  brutto    INT(10) UNSIGNED DEFAULT 0                 NULL,
  tare      INT(10) UNSIGNED DEFAULT 0                 NULL,
  netto     INT(10) DEFAULT 0                          NULL,
  overload  INT(10) DEFAULT 0                          NULL,
  nvans     SMALLINT(5) DEFAULT 0                      NULL,

  PRIMARY KEY (trnum, scales)
)
  ENGINE = MyISAM;