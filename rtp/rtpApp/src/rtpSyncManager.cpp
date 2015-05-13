#include <iostream>
#include "rtpSyncManager.h"

#define FLAG_BROADCAST                  0x1
#define FLAG_CONNECT_PER_TRANSACTION    0x2
#define FLAG_SHUTDOWN                   0x4


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

static RTPSyncManager mrtpSyncManager;
static long	convertAi(void *precord, int pass);
static long	processAi (void *precord);
static long	initAi (void *prec);
//devRTP devSyncRTPRead  ={6, NULL, NULL, initAi, NULL, processAi, convertAi};
devRTP devSyncRTPRead  ={6, 0, 0, initAi, 0, processAi, 0};
//devRTP devSyncRTPRead  ={5, NULL, NULL, initAi, NULL, processAi};
//devRTP devSyncRTPWrite ={6, NULL, NULL, initAo, getIoIntInfo, processAo, convertAo};

epicsExportAddress(dset,devSyncRTPRead);
//epicsExportAddress(dset,devSyncRTPWrite);

static long initAi (void *prec)
{
	aiRecord *pr = (aiRecord*)prec;
	if(recGblInitConstantLink(&pr->inp,DBF_DOUBLE,&pr->val))
		pr->udf = FALSE;

    //convertAi(pr, 1);

	return (0);
}

static long processAi (void *precord)
{
	aiRecord *pr = (aiRecord*)precord;

	//long status = dbGetLink(&(pr->inp),DBF_DOUBLE, &(pr->val),0,0);
    //	status = dbGetLink(&(prdbpostgreSQL->inp),DBF_DOUBLE, &(prdbpostgreSQL->val),0,0);

	/*If return was succesful then set undefined false*/
	//if(!status) pr->udf = FALSE;

	epicsFloat32 fvalue;

	mrtpSyncManager.ReadSFloatData(fvalue);
	pr->val = (epicsFloat64)fvalue;
	//	pr->rval = fvalue;

	printf("RTP AI:%f\n", pr->val);

	return (2);
}

static long	convertAi(void *precord, int pass)
{
	aiRecord *airec = (aiRecord*)precord;
    if (pass==0) return 0;

	airec->val = airec->rval*2;
    return 0;
}


epicsShareFunc int drvSyncRTPConfigure(const char *portName, const char *hostInfo, unsigned int priority, int noAutoConnect)
{
    int nbytes;
    static int firstTime = 1;

    /*
     * Check arguments
     */
    if (portName == NULL) {
        printf("Port name missing.\n");
        return -1;
    }
    if (hostInfo == NULL) {
        printf("TCP host information missing.\n");
        return -1;
    }

    /*
     * Perform some one-time-only initializations
     */
    if (firstTime) {
        firstTime = 0;
        if (osiSockAttach() == 0) {
            printf("drvSyncRTPConfigure: osiSockAttach failed\n");
            return -1;
        }
    }
	///mptty
	mrtpSyncManager.ConnectDevice(portName, hostInfo, priority, noAutoConnect);

#if 0
    /*
     * Register for socket cleanup
     */
    epicsAtExit(cleanup, tty);
#endif

    return 0;
}

/*
 * IOC shell command registration
 */
static const iocshArg drvSyncRTPConfigureArg0 = { "port name",iocshArgString};
static const iocshArg drvSyncRTPConfigureArg1 = { "host:port [protocol]",iocshArgString};
static const iocshArg drvSyncRTPConfigureArg2 = { "priority",iocshArgInt};
static const iocshArg drvSyncRTPConfigureArg3 = { "disable auto-connect",iocshArgInt};
static const iocshArg *drvSyncRTPConfigureArgs[] = {
    &drvSyncRTPConfigureArg0, &drvSyncRTPConfigureArg1,
    &drvSyncRTPConfigureArg2, &drvSyncRTPConfigureArg3};
static const iocshFuncDef drvSyncRTPConfigureFuncDef =
                      {"drvSyncRTPConfigure",4,drvSyncRTPConfigureArgs};
static void drvSyncRTPConfigureCallFunc(const iocshArgBuf *args)
{
    drvSyncRTPConfigure(args[0].sval, args[1].sval, args[2].ival, args[3].ival);
}

/*
 * This routine is called before multitasking has started, so there's
 * no race condition in the test/set of firstTime.
 */
static void
drvSyncRTPRegisterCommands(void)
{
    static int firstTime = 1;
    if (firstTime) {
        iocshRegister(&drvSyncRTPConfigureFuncDef,drvSyncRTPConfigureCallFunc);
        firstTime = 0;
    }
}
epicsExportRegistrar(drvSyncRTPRegisterCommands);


//RTPSyncManager
RTPSyncManager::RTPSyncManager()
{
	mptty = new ttyController_t;
	mCommand = new char(READ_COMMANDMSG_SIZE);
}

int RTPSyncManager::ConnectDevice(const char *portName, const char *hostInfo, unsigned int priority, int noAutoConnect)
{
    /*
     * Create a driver
     */
    SOCKET fd; int i;

    char *cp;
    int port;
    int isCom = 0;
    char protocol[6];

    mptty->fd = INVALID_SOCKET;
    mptty->IPDeviceName = epicsStrDup(hostInfo);
    mptty->portName = epicsStrDup(portName);
    /*
     * Parse configuration parameters
     */
    protocol[0] = '\0';
    if (((cp = strchr(mptty->IPDeviceName, ':')) == NULL)
     || (sscanf(cp, ":%d %5s", &port, protocol) < 1)) {
        printf("drvSyncRTPConfigure: \"%s\" is not of the form \"<host>:<port> [protocol]\"\n",
                                                        mptty->IPDeviceName);
        ttyCleanup(mptty);
        return -1;
    }
    *cp = '\0';
    mptty->IPHostName = epicsStrDup(mptty->IPDeviceName);
    *cp = ':';
    mptty->farAddr.ia.sin_port = htons(port);
    mptty->farAddr.ia.sin_family = AF_INET;
    mptty->flags = 0;
    if ((protocol[0] ==  '\0')
     || (epicsStrCaseCmp(protocol, "tcp") == 0)) {
        mptty->socketType = SOCK_STREAM;
    }
    else if (epicsStrCaseCmp(protocol, "com") == 0) {
        isCom = 1;
        mptty->socketType = SOCK_STREAM;
    }
    else if (epicsStrCaseCmp(protocol, "udp") == 0) {
        mptty->socketType = SOCK_DGRAM;
    }
    else if (epicsStrCaseCmp(protocol, "udp*") == 0) {
        mptty->socketType = SOCK_DGRAM;
        mptty->flags |= FLAG_BROADCAST;
    }
    else {
        printf("drvSyncRTPConfigure: Unknown protocol \"%s\".\n", protocol);
        ttyCleanup(mptty);
        return -1;
    }


    assert(mptty);

    if (mptty->fd != INVALID_SOCKET) {
        printf("%s: Link already open!", mptty->IPDeviceName);
        return asynError;
    } else if(mptty->flags & FLAG_SHUTDOWN) {
        printf("%s: Link shutdown!", mptty->IPDeviceName);
        return asynError;
    }

	/*
	 * Create the socket
	 */
	if ((fd = epicsSocketCreate(PF_INET, mptty->socketType, 0)) < 0) {
		printf("Can't create socket: %s", strerror(SOCKERRNO));
		return asynError;
	}

	/*
	 * Enable broadcasts if so requested
	 */
	i = 1;
	if ((mptty->flags & FLAG_BROADCAST)
			&& (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, (void *)&i, sizeof i) < 0)) {
		printf("Can't set %s socket BROADCAST option: %s", mptty->IPDeviceName, strerror(SOCKERRNO));
		epicsSocketDestroy(fd);
		return asynError;
	}

	/*
	 * Convert host name/number to IP address.
	 * We delay doing this until now in case a device
	 * has just appeared in a DNS database.
	 */
	if (!mptty->haveAddress) {
		if(hostToIPAddr(mptty->IPHostName, &mptty->farAddr.ia.sin_addr) < 0) {
			printf("Unknown host \"%s\"", mptty->IPHostName);
			epicsSocketDestroy(fd);
			return asynError;
		}
		mptty->haveAddress = 1;
	}

	/*
	 * Connect to the remote host
	 * If the connect fails, arrange for another DNS lookup in case the
	 * problem is just that the device has DHCP'd itself an new number.
	 */
	if (connect(fd, &mptty->farAddr.sa, sizeof mptty->farAddr.ia) < 0) {
		printf("Can't connect to %s: %s", mptty->IPDeviceName, strerror(SOCKERRNO));
		epicsSocketDestroy(fd);
		mptty->haveAddress = 0;
		return asynError;
	}
    i = 1;
    if ((mptty->socketType == SOCK_STREAM)
     && (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void *)&i, sizeof i) < 0)) {
        printf("Can't set %s socket NODELAY option: %s", mptty->IPDeviceName, strerror(SOCKERRNO));
        epicsSocketDestroy(fd);
        return asynError;
    }

#if 0
	//NonBlock Mode
    if (setNonBlock(fd, 1) < 0) {
        printf("Can't set %s O_NONBLOCK option: %s", mptty->IPDeviceName, strerror(SOCKERRNO));
        epicsSocketDestroy(fd);
        return asynError;
    }
#endif

    printf("Opened connection to %s\n", mptty->IPDeviceName);
    mptty->fd = fd;
    return asynSuccess;

}

int RTPSyncManager::setNonBlock(SOCKET fd, int nonBlockFlag)
{
    int flags;
    if ((flags = fcntl(fd, F_GETFL, 0)) < 0)
        return -1;
    if (nonBlockFlag)
        flags |= O_NONBLOCK;
    else
        flags &= ~O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0)
        return -1;
    return 0;
}

/*
 * Clean up a ttyController
 */
void RTPSyncManager::ttyCleanup(ttyController_t *tty)
{
    if (tty) {
        if (tty->fd != INVALID_SOCKET)
            epicsSocketDestroy(tty->fd);
        free(tty->portName);
        free(tty->IPDeviceName);
        free(tty);
    }
}

RTPSyncManager::~RTPSyncManager()
{
	delete mptty;
}
unsigned short RTPSyncManager::getCRC(unsigned char *writecmd, int loopcnt) 
{
	int i;

	unsigned short fcsval = FCSINIT;
	
	for(i = 1; i < loopcnt; i++)
	{
		fcsval = ((fcsval >> 8) & 0xff) ^ fcstab[(fcsval ^ writecmd[i]) & 0xff]; 
	};
	
	writecmd[loopcnt] = fcsval & 0xff;
	writecmd[loopcnt + 1] = (fcsval >> 8) & 0xff;
	
	return fcsval;
}

int RTPSyncManager::readMsgCommand(const int node, const int type, const int mul_single, const int index, const int numtoread)
{
	mCommand[0]= SYNC_BYTE;
	mCommand[1]= mul_single; //Multi = 5, Single = 3
	mCommand[2]= 0x00; 
	mCommand[3]= node;  //Node = 0
	mCommand[4]= type; // FLOAT_READ = 0x9D, INT_READ = 0x8D, BOOL_READ = 0x82
	mCommand[5] = (unsigned char)(index % 256); // BOOL_START_INDEX = 485, FLOAT_START_INDEX = 9, INT_START_INDEX = 23
	mCommand[6] = (unsigned char)(index / 256);
	//mCommand[7] = (unsigned char)(numtoread % 256);
	//mCommand[8] = (unsigned char)(numtoread / 256);
	unsigned short check = getCRC((unsigned char*)mCommand, 7);
	
	printf("CRC-Check:%d\n", check);

	//getCRC((unsigned char*)mCommand, sizeof(&mCommand));
	printf("Cmd Size:%d\n", sizeof(mCommand));
	//return send(mptty->fd, (const char*)mCommand, sizeof(mCommand), 0);
	return send(mptty->fd, (const char*)mCommand, 9, 0);
}

int RTPSyncManager::ReadSFloatData(epicsFloat32 &fvalue)
{
	//int recByte = readMsgCommand(0,FLOAT_READ, 3, FLOAT_START_INDEX, 1);
	int recByte = readMsgCommand(0,FLOAT_READ, 3, 95, 1);
	printf("Socket(%p),ReadByte: %d\n", mptty->fd, recByte);

	char ReadData[12];                 // float ÀÐ±â ¸í·É
	ssize_t recvbyte = recv(mptty->fd, (char*)&ReadData, sizeof(ReadData), 0);

	printf("RecvByte:%d\n", recvbyte);

	if(recvbyte < 0)
	{
		printf("Recv-Error: %s\n", strerror(SOCKERRNO));
	}
	//memcpy(&fvalue, (float*)&ReadData[5], sizeof(float));
	
#if 0
	float fval;
	memcpy(&fval, (float*)&ReadData[5], sizeof(float));
	printf("RTP-Value:%f\n",fval);
#else
	memcpy(&fvalue, (epicsFloat32*)&ReadData[5], sizeof(epicsFloat32));
	printf("RTP-Value:%f\n",fvalue);
#endif
	return (0);
}
