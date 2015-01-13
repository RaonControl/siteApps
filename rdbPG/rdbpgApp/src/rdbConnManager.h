#ifndef __RDB_CONN_MANAGER_H
#define __RDB_CONN_MANAGER_H

#include "alarm.h"
#include "cvtTable.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "recGbl.h"
#include "recSup.h"
#include "devSup.h"
#include "link.h"
#include "menuScan.h"
#include "rdbpostgreSQLRecord.h"
#include "epicsExport.h"

#ifdef __cplusplus
extern "C" {
#endif

long init_record(void *);
long read_rdb(void*);
long write_rdb(void*);

typedef struct devRdbpostgreSQLSoft{
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	read_rdb;
}devRdbpostgreSQLSoft;


using namespace std;
using namespace pqxx;

class RDBManager
{

public:
	RDBManager();
	~RDBManager();
};

#endif // __RDB_CONN_MANAGER_H

#ifdef __cplusplus
}
#endif

