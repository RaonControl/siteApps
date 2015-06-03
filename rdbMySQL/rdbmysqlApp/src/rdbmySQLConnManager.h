#ifndef __RDB_MYSQL_CONN_MANAGER_H
#define __RDB_MYSQL_CONN_MANAGER_H

#include <vector>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>

#ifdef MY_CONFIG_H
#undef	NO_ALARM
#endif

#include "alarm.h"
#include "cvtTable.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "recGbl.h"
#include "recSup.h"
#include "devSup.h"
#include "link.h"
#include "menuScan.h"
#include "rdbmySQLRecord.h"
#include "epicsExport.h"
#include "shareLib.h"
#include "dbCommon.h"
#include "dbScan.h"
#include "callback.h"
#include "cantProceed.h"
#include "epicsStdio.h"
#include "epicsMutex.h"
#include "epicsEvent.h"
#include "epicsThread.h"
#include "iocsh.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

long read_init_record(void *);
long write_init_record(void *);
long read_rdb(void*);
long write_rdb(void*);
long getIoIntInfo(int cmd, dbCommon *pr, IOSCANPVT *iopvt);
static void devRDBScanThread(void);


epicsShareFunc int drvMySQLConnInit(const char *dbname, const char *user, const char *password, 
		const char *hostaddr, const char *port );

static void devMySQLScanThread(void);

typedef struct devRdbmySQLSoft{
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	//long  (*get_ioint_info) (int, dbCommon*, IOSCANPVT*);
	DEVSUPFUN	read_rdb;
}devRdbmySQLSoft;

class MySQLConnManager {

public:
	MySQLConnManager();
	~MySQLConnManager();

	int Version();
	int Connect(const char *dbname, const char *user, const char *password, const char *hostaddr, const char* port);
	float ReadValue(const char *table, const char *field);
	int WriteValue(const void *precord);

	//member function
private:
	int initialize();
	int updateValue(const void *precord);

//member data
private:
	MYSQL *conn;
    epicsMutexId mutex;
		
};

#ifdef __cplusplus
}
#endif

#endif // __RDB_MYSQL_CONN_MANAGER_H

