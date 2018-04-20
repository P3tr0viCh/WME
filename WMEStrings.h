// ---------------------------------------------------------------------------
#ifndef DP_RepStringsH
#define DP_RepStringsH
// ---------------------------------------------------------------------------

#define IDS_COPYRIGHT					0001
#define IDS_COPYRIGHT_STATUS			0002

#define IDS_QUESTION_CLOSE_PROGRAM		0100
#define IDS_QUESTION_SETTINGS_CHANGED	0101
#define IDS_QUESTION_DB_DROP			0102
#define IDS_QUESTION_DB_CREATE			0103
#define IDS_QUESTION_TRAIN_CHANGED		0104

#define IDS_ERROR_UNKNOWN				0200
#define IDS_ERROR_SETTINGS_SAVE			0201
#define IDS_ERROR_NEED_USERNAME			0202
#define IDS_ERROR_SELECT_USERNAME		0203
#define IDS_ERROR_PASS_WRONG			0204
#define IDS_ERROR_USERS_LAST_ADMIN		0205
#define IDS_ERROR_UNKNOWN_EXCEPTION		0206

#define IDS_ERROR_MYSQL_CONNECTION		0250
#define IDS_ERROR_MYSQL_DB_DROP			0251
#define IDS_ERROR_MYSQL_DB_CREATE		0252
#define IDS_ERROR_NOTHING_SAVE			0253
#define IDS_ERROR_BAD_VALUES			0254
#define IDS_ERROR_TRAINS_LOAD			0255
#define IDS_ERROR_TRAIN_SAVE			0256
#define IDS_ERROR_TRAIN_LOAD            0257

#define IDS_MSG_MYSQL_CONNECTION_OK		0300
#define IDS_MSG_MYSQL_DB_DROP_OK		0301
#define IDS_MSG_MYSQL_DB_CREATE_OK		0302

#define IDS_TXT_ADMIN_DEFAULT_NAME		0400

#define IDS_MYSQL_CONNECTION			1000
#define IDS_MYSQL_VERSION				1001
#define IDS_MYSQL_DATABASE_DROP			1002
#define IDS_MYSQL_DATABASE_CREATE		1003
#define IDS_MYSQL_TBL_TRAINS_CREATE		1004
#define IDS_MYSQL_TBL_VANS_CREATE		1005

#define IDS_LOG_START_PROGRAM			2000
#define IDS_LOG_STOP_PROGRAM			2001
#define IDS_LOG_OPTIONS_SAVE			2002
#define IDS_LOG_OPTIONS_CANCEL			2003
#define IDS_LOG_LOGIN_OK				2004
#define IDS_LOG_LOGIN_CANCEL			2005
#define IDS_LOG_CREATE_DIR_FAIL			2010
#define IDS_LOG_WRITE_FILE_FAIL			2011
#define IDS_LOG_READ_FILE_FAIL			2012
#define IDS_LOG_EXCEPTION				2013

#define IDS_LOG_MYSQL_CONNECT			2100
#define IDS_LOG_MYSQL_CONNECT_OK		2101
#define IDS_LOG_MYSQL_CONNECT_FAIL		2102
#define IDS_LOG_MYSQL_DB_DROP_OK		2103
#define IDS_LOG_MYSQL_DB_DROP_FAIL		2104
#define IDS_LOG_MYSQL_DB_CREATE_OK		2105
#define IDS_LOG_MYSQL_DB_CREATE_FAIL	2106
#define IDS_LOG_MYSQL_SAVE_TRAIN_OK		2107
#define IDS_LOG_MYSQL_SAVE_TRAIN_FAIL	2108
#define IDS_LOG_MYSQL_LOAD_TRAINS_OK	2109
#define IDS_LOG_MYSQL_LOAD_TRAINS_FAIL	2110
#define IDS_LOG_MYSQL_LOAD_TRAIN_OK		2111
#define IDS_LOG_MYSQL_LOAD_TRAIN_FAIL	2112

// ---------------------------------------------------------------------------
#endif
