#include <iostream>
#include "rtpDevManager.h"

devRTP devRTPRead ={5, NULL, NULL, read_init, NULL, read_rtp};
devRTP devRTPWrite ={5, NULL, NULL, write_init,getIoIntInfo, write_rtp};

epicsExportAddress(dset,devRTPRead);
epicsExportAddress(dset,devRTPWrite);

long read_init (void *)
{
	pasynManager->registerPort("Test",ASYN_MULTIDEVICE,1,0,0);
	return (0);
}

long read_rtp (void *)
{
	return (0);
}

long write_init (void *)
{
	return (0);
}

long getIoIntInfo(int cmd, dbCommon *prec, IOSCANPVT *iopvt)
{
	return (0);
}

long write_rtp (void *)
{
	return (0);
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
