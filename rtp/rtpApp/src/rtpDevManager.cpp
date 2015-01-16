#include <iostream>
#include <aiRecord.h>
#include "rtpDevManager.h"

#define DEFAULT_RING_BUFFER_SIZE 10
#define MAX_ENUM_STATES 16
#define MAX_ENUM_STRING_SIZE 26

unsigned char maskBit[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned short fcstab[256] = {
// 16 bit FCS lookup table per RFC1331 : For HDLC CRC calculation
0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf, 
0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7, 
0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e, 
0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876, 
0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd, 
0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5, 
0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c, 
0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974, 
0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb, 
0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3, 
0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a, 
0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72, 
0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9, 
0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1, 
0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738, 
0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70, 
0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7, 
0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff, 
0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036, 
0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e, 
0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5, 
0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd, 
0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134, 
0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c, 
0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3, 
0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb, 
0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232, 
0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a, 
0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1, 
0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9, 
0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330, 
0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};
#if 0 
// Format of RTP communications message frame.
==============================================
		SYNC	= 0xC3
----------------------------------------------
		LENGTH	= N+1		(L)
							(H)
----------------------------------------------
		NODE/PHASE
----------------------------------------------
		COMMAND/RESPONSE
----------------------------------------------
		DATA[1]
----------------------------------------------
		... 
		...
----------------------------------------------
		DATA[1392]
----------------------------------------------
		CRC[1]				(L)
							(H)
----------------------------------------------
		...
		...
----------------------------------------------
		CRC[58]				(L)
						    (H)
===============================================	
#endif

typedef struct ringBufferElement {
    epicsInt32      value;
    epicsTimeStamp  time;
    asynStatus      status;
} ringBufferElement;

typedef struct devInt32Pvt{
    dbCommon          *pr;
    asynUser          *pasynUser;
    asynUser          *pasynUserSync;
    asynUser          *pasynUserEnumSync;
    asynInt32         *pint32;
    void              *int32Pvt;
    void              *registrarPvt;
    int               canBlock;
    epicsInt32        deviceLow;
    epicsInt32        deviceHigh;
    epicsMutexId      mutexId;
    epicsAlarmCondition alarmStat;
    epicsAlarmSeverity alarmSevr;
    ringBufferElement *ringBuffer;
    int               ringHead;
    int               ringTail;
    int               ringSize;
    int               ringBufferOverflows;
    ringBufferElement result;
    interruptCallbackInt32 interruptCallback;
    double            sum;
    int               numAverage;
    int               bipolar;
    epicsInt32        mask;
    epicsInt32        signBit;
    CALLBACK          callback;
    IOSCANPVT         ioScanPvt;
    char              *portName;
    char              *userParam;
    int               addr;
    char              *enumStrings[MAX_ENUM_STATES];
    int               enumValues[MAX_ENUM_STATES];
    int               enumSeverities[MAX_ENUM_STATES];
}devInt32Pvt;

int		getCallbackValue (devInt32Pvt *pPvt);

devRTP devAsynRTPRead  ={6, NULL, NULL, initAi, getIoIntInfo, processAi, convertAi};
devRTP devAsynRTPWrite ={6, NULL, NULL, initAo, getIoIntInfo, processAo, convertAo};

epicsExportAddress(dset,devAsynRTPRead);
epicsExportAddress(dset,devAsynRTPWrite);

asynStatus initCommon(dbCommon *pr, DBLINK *plink,
    userCallback processCallback,interruptCallbackInt32 interruptCallback, interruptCallbackEnum callbackEnum,
    int maxEnums, char *pFirstString, int *pFirstValue, epicsEnum16 *pFirstSeverity)
{
    devInt32Pvt *pPvt;
    asynStatus status;
    asynUser *pasynUser;
    asynInterface *pasynInterface;
    epicsUInt32 mask=0;
    int nbits;

    pPvt = (devInt32Pvt*)callocMustSucceed(1, sizeof(*pPvt), "devAsynInt32::initCommon");
    pr->dpvt = pPvt;
    pPvt->pr = pr;
    /* Create asynUser */
    pasynUser = pasynManager->createAsynUser(processCallback, 0);
    pasynUser->userPvt = pPvt;
    pPvt->pasynUser = pasynUser;
    pPvt->mutexId = epicsMutexCreate();
 
    /* Parse the link to get addr and port */
    /* We accept 2 different link syntax (@asyn(...) and @asynMask(...)
     * If parseLink returns an error then try parseLinkMask. */
    status = pasynEpicsUtils->parseLink(pasynUser, plink, 
                &pPvt->portName, &pPvt->addr, &pPvt->userParam);
    if (status != asynSuccess) {
        status = pasynEpicsUtils->parseLinkMask(pasynUser, plink, 
                &pPvt->portName, &pPvt->addr, &mask, &pPvt->userParam);
    }
    if (status != asynSuccess) {
        printf("%s devAsynInt32::initCommon  %s\n",
                     pr->name, pasynUser->errorMessage);
        goto bad;
    }
    
    /* Parse nbits if it was specified */
    nbits = (int)mask;
    if (nbits) {
        if (nbits < 0) {
            nbits = -nbits;
            pPvt->bipolar = 1;
        }
        pPvt->signBit = (epicsInt32) ldexp(1.0, nbits-1);
        pPvt->mask = pPvt->signBit*2 - 1;
        if (pPvt->bipolar) {
            pPvt->deviceLow = ~(pPvt->mask/2)+1;
            pPvt->deviceHigh = (pPvt->mask/2);
        } else {
            pPvt->deviceLow = 0;
            pPvt->deviceHigh = pPvt->mask;
        }
    }
            
    /* Connect to device */
    status = pasynManager->connectDevice(pasynUser, pPvt->portName, pPvt->addr);
    if (status != asynSuccess) {
        printf("%s devAsynInt32::initCommon connectDevice failed %s\n",
                     pr->name, pasynUser->errorMessage);
        goto bad;
    }
    status = pasynManager->canBlock(pPvt->pasynUser, &pPvt->canBlock);
    if (status != asynSuccess) {
        printf("%s devAsynInt32::initCommon canBlock failed %s\n",
                     pr->name, pasynUser->errorMessage);
        goto bad;
    }
    /*call drvUserCreate*/
    pasynInterface = pasynManager->findInterface(pasynUser,asynDrvUserType,1);
    if(pasynInterface && pPvt->userParam) {
        asynDrvUser *pasynDrvUser;
        void       *drvPvt;

        pasynDrvUser = (asynDrvUser *)pasynInterface->pinterface;
        drvPvt = pasynInterface->drvPvt;
        status = pasynDrvUser->create(drvPvt,pasynUser,pPvt->userParam,0,0);
        if(status!=asynSuccess) {
            printf("%s devAsynInt32::initCommon drvUserCreate %s\n",
                     pr->name, pasynUser->errorMessage);
            goto bad;
        }
    };

    /* Get interface asynInt32 */
    pasynInterface = pasynManager->findInterface(pasynUser, asynInt32Type, 1);
    if (!pasynInterface) {
        printf("%s devAsynInt32::initCommon findInterface asynInt32Type %s\n",
                     pr->name,pasynUser->errorMessage);
        goto bad;
    };

    pPvt->pint32 = (asynInt32 *)pasynInterface->pinterface;
    pPvt->int32Pvt = pasynInterface->drvPvt;
    scanIoInit(&pPvt->ioScanPvt);
    pPvt->interruptCallback = interruptCallback;

    /* Initialize synchronous interface */
    status = pasynInt32SyncIO->connect(pPvt->portName, pPvt->addr, &pPvt->pasynUserSync, pPvt->userParam);
    if (status != asynSuccess) {
        printf("%s devAsynInt32::initCommon Int32SyncIO->connect failed %s\n",
               pr->name, pPvt->pasynUserSync->errorMessage);
        goto bad;
    };

    /* Initialize asynEnum interfaces */
    pasynInterface = pasynManager->findInterface(pPvt->pasynUser,asynEnumType,1);
    if (pasynInterface && (maxEnums > 0)) {
        size_t numRead;
        asynEnum *pasynEnum = (asynEnum*)pasynInterface->pinterface;
        void *registrarPvt;
        status = pasynEnumSyncIO->connect(pPvt->portName, pPvt->addr, 
                 &pPvt->pasynUserEnumSync, pPvt->userParam);
        if (status != asynSuccess) {
            printf("%s devAsynInt32::initCommon EnumSyncIO->connect failed %s\n",
                   pr->name, pPvt->pasynUserEnumSync->errorMessage);
            goto bad;
        }

        status = pasynEnumSyncIO->read (pPvt->pasynUserEnumSync, pPvt->enumStrings, pPvt->enumValues, pPvt->enumSeverities, maxEnums, 
                    &numRead, pPvt->pasynUser->timeout);

        if (status == asynSuccess) {
            setEnums(pFirstString, pFirstValue, pFirstSeverity, 
                     pPvt->enumStrings, pPvt->enumValues,  pPvt->enumSeverities, numRead, maxEnums);
        }

        status = pasynEnum->registerInterruptUser( pasynInterface->drvPvt, pPvt->pasynUser, callbackEnum, pPvt, &registrarPvt);

        if(status!=asynSuccess) {
            printf("%s devAsynInt32 enum registerInterruptUser %s\n",
                   pr->name,pPvt->pasynUser->errorMessage);
        }
    }
    return status;

bad:
   pr->pact=1;
   return asynError;
}

void setEnums(char *outStrings, int *outVals, epicsEnum16 *outSeverities, char *inStrings[], int *inVals, int *inSeverities, 
                     size_t numIn, size_t numOut)
{
    size_t i;
    
    for (i=0; i<numOut; i++) {
        if (outStrings) outStrings[i*MAX_ENUM_STRING_SIZE] = '\0';
        if (outVals) outVals[i] = 0;
        if (outSeverities) outSeverities[i] = 0;
    }
    for (i=0; (i<numIn && i<numOut); i++) {
        if (outStrings) strncpy(&outStrings[i*MAX_ENUM_STRING_SIZE], inStrings[i], MAX_ENUM_STRING_SIZE);
        if (outVals) outVals[i] = inVals[i];
        if (outSeverities) outSeverities[i] = inSeverities[i];
    }
}

long initAi (void *prec)
{
    devInt32Pvt *pPvt;
    asynStatus status;
	aiRecord *pr = (aiRecord*)prec;

    status = initCommon((dbCommon*)pr,&pr->inp,
        processCallbackInput, interruptCallbackInput, NULL, 0, NULL, NULL, NULL);

    if(status != asynSuccess) return 0;
    pPvt = (devInt32Pvt*) pr->dpvt;

    /* Don't call getBounds if we already have non-zero values from
     * parseLinkMask */

    if ((pPvt->deviceLow == 0) && (pPvt->deviceHigh == 0)) {
        pasynInt32SyncIO->getBounds(pPvt->pasynUserSync,
                                &pPvt->deviceLow, &pPvt->deviceHigh);
    }
    convertAi(pr, 1);
	return (0);
}

void processCallbackInput(asynUser *pasynUser)
{
    devInt32Pvt *pPvt = (devInt32Pvt *)pasynUser->userPvt;
    dbCommon *pr = (dbCommon *)pPvt->pr;

    pPvt->result.status = pPvt->pint32->read(pPvt->int32Pvt, pPvt->pasynUser, &pPvt->result.value);
    if (pPvt->bipolar && (pPvt->result.value & pPvt->signBit)) pPvt->result.value |= ~pPvt->mask;
    if (pPvt->result.status == asynSuccess) {
        asynPrint(pasynUser, ASYN_TRACEIO_DEVICE,
            "%s devAsynInt32 process value=%d\n",pr->name,pPvt->result.value);
    } else {
        asynPrint(pasynUser, ASYN_TRACE_ERROR,
              "%s devAsynInt32 process read error %s\n",
              pr->name, pasynUser->errorMessage);
    }
    if(pr->pact) callbackRequestProcessCallback(&pPvt->callback,pr->prio,pr);
}

void interruptCallbackInput(void *drvPvt, asynUser *pasynUser, epicsInt32 value)
{
    devInt32Pvt *pPvt = (devInt32Pvt *)drvPvt;
    dbCommon *pr = pPvt->pr;
    ringBufferElement *rp;

    if (pPvt->bipolar && (value & pPvt->signBit)) value |= ~pPvt->mask;

    asynPrint(pPvt->pasynUser, ASYN_TRACEIO_DEVICE,
        "%s devAsynInt32::interruptCallbackInput new value=%d\n",
        pr->name, value);

    if (!interruptAccept) return;
    epicsMutexLock(pPvt->mutexId);

    rp = &pPvt->ringBuffer[pPvt->ringHead];
    rp->value = value;
    rp->time = pasynUser->timestamp;
    rp->status = (asynStatus)pasynUser->auxStatus;
    pPvt->ringHead = (pPvt->ringHead==pPvt->ringSize) ? 0 : pPvt->ringHead+1;

    if (pPvt->ringHead == pPvt->ringTail) {
        /* There was no room in the ring buffer.  In the past we just threw away
         * the new value.  However, it is better to remove the oldest value from the
         * ring buffer and add the new one.  That way the final value the record receives
         * is guaranteed to be the most recent value */
        pPvt->ringTail = (pPvt->ringTail==pPvt->ringSize) ? 0 : pPvt->ringTail+1;
        pPvt->ringBufferOverflows++;
    } else {
        /* We only need to request the record to process if we added a new
         * element to the ring buffer, not if we just replaced an element. */
        scanIoRequest(pPvt->ioScanPvt);
    }
    epicsMutexUnlock(pPvt->mutexId);
}

long processAi (void *precord)
{
	aiRecord *pr = (aiRecord*)precord;
    devInt32Pvt *pPvt = (devInt32Pvt *)pr->dpvt;
    asynStatus status;

    if(!getCallbackValue(pPvt) && !pr->pact) {
        if(pPvt->canBlock) pr->pact = 1;
        status = pasynManager->queueRequest(pPvt->pasynUser, asynQueuePriority(0), 0);
        if((status==asynSuccess) && pPvt->canBlock) return 0;
        if(pPvt->canBlock) pr->pact = 0;
        if(status != asynSuccess) {
            pPvt->result.status = status;
            asynPrint(pPvt->pasynUser, ASYN_TRACE_ERROR,
                "%s devAsynInt32 queueRequest %s\n", 
                pr->name,pPvt->pasynUser->errorMessage);
        };
    };

    pr->rval = pPvt->result.value; 
    pr->time = pPvt->result.time; 

    if (pPvt->result.status == asynSuccess) {
        pr->udf = 0;
    }
    else {
        pasynEpicsUtils->asynStatusToEpicsAlarm(pPvt->result.status, READ_ALARM, &pPvt->alarmStat,
                                            INVALID_ALARM, &pPvt->alarmSevr);
        (void)recGblSetSevr(pr, pPvt->alarmStat, pPvt->alarmSevr);
    }
	return (0);
}

long	convertAi(void *precord, int pass)
{
	aiRecord *airec = (aiRecord*)precord;

    devInt32Pvt *pPvt = (devInt32Pvt *)airec->dpvt;
    double eguf,egul,deviceHigh,deviceLow;

    if (pass==0) return 0;

    /* set linear conversion slope */
    if(pPvt->deviceHigh!=pPvt->deviceLow) {
        eguf = airec->eguf;
        egul = airec->egul;
        deviceHigh = (double)pPvt->deviceHigh;
        deviceLow = (double)pPvt->deviceLow;
        airec->eslo = (eguf - egul)/(deviceHigh - deviceLow);
        airec->eoff = (deviceHigh*egul - deviceLow*eguf)/
                        (deviceHigh - deviceLow);
    }
    return 0;
}

long initAo (void *)
{
	return (0);
}

long processAo (void *)
{
	return (0);
}

long	convertAo(void *precord, int pass)
{
	return (0);
}

long getIoIntInfo(int cmd, dbCommon *prec, IOSCANPVT *iopvt)
{
	return (0);
}

int getCallbackValue(devInt32Pvt *pPvt)
{
    int ret = 0;
    epicsMutexLock(pPvt->mutexId);
    if (pPvt->ringTail != pPvt->ringHead) {
        if (pPvt->ringBufferOverflows > 0) {
            asynPrint(pPvt->pasynUser, ASYN_TRACEIO_DEVICE,
                "%s devAsynInt32 getCallbackValue warning, %d ring buffer overflows\n",
                                    pPvt->pr->name, pPvt->ringBufferOverflows);
            pPvt->ringBufferOverflows = 0;
        }
        pPvt->result = pPvt->ringBuffer[pPvt->ringTail];
        pPvt->ringTail = (pPvt->ringTail==pPvt->ringSize) ? 0 : pPvt->ringTail+1;
        asynPrint(pPvt->pasynUser, ASYN_TRACEIO_DEVICE,
            "%s devAsynInt32::getCallbackValue from ringBuffer value=%d\n",
                                            pPvt->pr->name,pPvt->result.value);
        ret = 1;
    }
    epicsMutexUnlock(pPvt->mutexId);
    return ret;
}

unsigned short getcrc(unsigned char *writecmd, int loopcnt) 
{
	int i;

	unsigned short fcsval = FCSINIT;
	
	for(i = 1; i < loopcnt; i++)
	{
		fcsval = ((fcsval >> 8) & 0xff) ^ fcstab[(fcsval ^ writecmd[i]) & 0xff]; 
	}
	
	writecmd[loopcnt] = fcsval & 0xff;
	writecmd[loopcnt + 1] = (fcsval >> 8) & 0xff;
	
	return fcsval;
}


static RDBDEVManager mrtpDevManager;

//RDBDEVManager
RDBDEVManager::RDBDEVManager()
{
#if 0
	try{
		mpConn = new connection("dbname=epics_db user=postgres password=qwer1234 hostaddr=127.0.0.1 port=5432");
		if (mpConn->is_open()) {
			cout << "Opened database successfully: " << mpConn->dbname() << endl;
		} else {
			cout << "Can't open database" << endl;
		}
		mpConn->disconnect ();
	}catch (const std::exception &e){
		cerr << e.what() << std::endl;
	}
#endif
}

RDBDEVManager::~RDBDEVManager()
{

}
