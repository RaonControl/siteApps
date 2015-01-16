#ifndef __RTP_DEV_MANAGER_H
#define __RTP_DEV_MANAGER_H

#include <vector>
#include <stdlib.h>
#include "alarm.h"
#include "cvtTable.h"
#include "dbDefs.h"
#include "dbAccess.h"
#include "recGbl.h"
#include "recSup.h"
#include "devSup.h"
#include "link.h"
#include "menuScan.h"
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

#include "asynEpicsUtils.h"
#include "asynDriver.h"
#include "asynDrvUser.h"
#include "asynInt32.h"
#include "asynFloat64.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct devRTP{
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	long  (*get_ioint_info) (int, dbCommon*, IOSCANPVT*);
	//DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	read_rdb;
}devRTP;

long read_init (void *);
long read_rtp (void *);

long write_init (void *);
long getIoIntInfo(int cmd, dbCommon *prec, IOSCANPVT *iopvt);
long write_rtp (void *);

#ifdef __cplusplus
}
#endif


using namespace std;

class RDBDEVManager
{

public:
	RDBDEVManager();
	~RDBDEVManager();

	//float ReadValue();

private:
};

#endif // __RTP_DEV_MANAGER_H


