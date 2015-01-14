#include <iostream>
#include "rdbConnManager.h"

//drvRDBConnInit IOC Shell command registration
static const iocshArg drvRDBConnInitArg0 = {"dbname", iocshArgString};
static const iocshArg drvRDBConnInitArg1 = {"user", iocshArgString};
static const iocshArg drvRDBConnInitArg2 = {"password", iocshArgString};
static const iocshArg drvRDBConnInitArg3 = {"hostaddr", iocshArgString};
static const iocshArg drvRDBConnInitArg4 = {"port", iocshArgString};
static const iocshArg *drvRDBConnInitArgs[] = {
			&drvRDBConnInitArg0, &drvRDBConnInitArg1, &drvRDBConnInitArg2, &drvRDBConnInitArg3,
			&drvRDBConnInitArg4 };
static const iocshFuncDef drvRDBConnInitFuncDef = 
	{ "drvRDBConnInit", 5, drvRDBConnInitArgs };

static void drvRDBConnInitCallFunc(const iocshArgBuf *args)
{
	drvRDBConnInit(args[0].sval,args[1].sval,args[2].sval,args[3].sval,args[4].sval);
};

static void drvRDBConnInitRegisterCommands(void)
{
	static int firstTime = 1;
	if(firstTime)
	{
		iocshRegister(&drvRDBConnInitFuncDef, drvRDBConnInitCallFunc);
		firstTime = 0;
	};
}
epicsExportRegistrar(drvRDBConnInitRegisterCommands);

static RDBManager mRdbManager;

//drvRDBConnInit
epicsShareFunc int drvRDBConnInit(const char *dbname, const char *user, const char *password, 
		const char *hostaddr, const char *port )
{
	mRdbManager.Connect(dbname, user, password, hostaddr, port);

	//epicsAtExit();
	return 0;
};

int RdbpostgreSQLDebug = 0;
epicsExportAddress(int, RdbpostgreSQLDebug);

devRdbpostgreSQLSoft rdbReadpostgreSQL={ 5, NULL, NULL, init_record, getIoIntInfo, read_rdb };
devRdbpostgreSQLSoft rdbWritepostgreSQL={ 5, NULL, NULL, init_record, NULL, write_rdb };

epicsExportAddress(dset,rdbReadpostgreSQL);
epicsExportAddress(dset,rdbWritepostgreSQL);

long init_record(void	*precord)
{
	rdbpostgreSQLRecord	*prdbpostgreSQL = (rdbpostgreSQLRecord*)precord;

    if(recGblInitConstantLink(&prdbpostgreSQL->inp,DBF_DOUBLE,&prdbpostgreSQL->val))
         prdbpostgreSQL->udf = FALSE;

    return(0);
}

long read_rdb(void	*precord)
{
	rdbpostgreSQLRecord	*prdbpostgreSQL = (rdbpostgreSQLRecord*)precord;
    long status;
	epicsTimeStamp currTime;
	epicsTimeGetCurrent (&currTime);

	if(RdbpostgreSQLDebug)
		printf("Scan(%d)\n",prdbpostgreSQL->scan);

    status = dbGetLink(&(prdbpostgreSQL->inp),DBF_DOUBLE, &(prdbpostgreSQL->val),0,0);
    /*If return was succesful then set undefined false*/
    if(!status) prdbpostgreSQL->udf = FALSE;

	//ReadValue(const char *table, const char *field)
	prdbpostgreSQL->val = mRdbManager.ReadValue(prdbpostgreSQL->tabl,prdbpostgreSQL->fild);

    return(0);
}

long write_rdb(void	*precord)
{
	rdbpostgreSQLRecord	*prdbpostgreSQL = (rdbpostgreSQLRecord*)precord;
    long status;

	if(RdbpostgreSQLDebug)
		printf("Scan(%d)\n",prdbpostgreSQL->scan);

    status = dbGetLink(&(prdbpostgreSQL->inp),DBF_DOUBLE, &(prdbpostgreSQL->val),0,0);

    /*If return was succesful then set undefined false*/
    if(!status) prdbpostgreSQL->udf = FALSE;


	mRdbManager.WriteValue(prdbpostgreSQL);
#if 0
	switch(rdbpostgreSQL->qry)
	{
		case queryUpdate:
			mRdbManager.WriteValue(prdbpostgreSQL->tabl,prdbpostgreSQL->fild);
			break;
		case queryInsert:
			break;
	}
#endif

    return(0);
}
long getIoIntInfo(int cmd, dbCommon *pr, IOSCANPVT *iopvt)
{
#if 0
	//long int (*)(int, dbCommon*, io_scan_list**)
    devPvt *pdevPvt = (devPvt *)pr->dpvt;
    asynStatus status;

    /* If initCommon failed then pdevPvt->poctet is NULL, return error */
    if (!pdevPvt->poctet) return -1;

    if (cmd == 0) {
        /* Add to scan list.  Register interrupts */
        asynPrint(pdevPvt->pasynUser, ASYN_TRACE_FLOW,
            "%s devAsynOctet::getIoIntInfo registering interrupt\n",
            pr->name);
        status = pdevPvt->poctet->registerInterruptUser(
           pdevPvt->octetPvt,pdevPvt->pasynUser,
           pdevPvt->asynCallback,pdevPvt,&pdevPvt->registrarPvt);
        if(status!=asynSuccess) {
            printf("%s devAsynOctet registerInterruptUser %s\n",
                   pr->name,pdevPvt->pasynUser->errorMessage);
        }
    } else {
        asynPrint(pdevPvt->pasynUser, ASYN_TRACE_FLOW,
            "%s devAsynOctet::getIoIntInfo cancelling interrupt\n",
             pr->name);
        status = pdevPvt->poctet->cancelInterruptUser(pdevPvt->octetPvt,
             pdevPvt->pasynUser,pdevPvt->registrarPvt);
        if(status!=asynSuccess) {
            printf("%s devAsynOctet cancelInterruptUser %s\n",
                   pr->name,pdevPvt->pasynUser->errorMessage);
        }
    }
    *iopvt = pdevPvt->ioScanPvt;
#endif
    return 0;
}

template <typename T> string valtostr(const T& t) { 
	ostringstream os; os<<t; 
	return os.str(); 
} 

//RDBManager
RDBManager::RDBManager()
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

connection * RDBManager::Connect(const string info)
{
	connection *conn = 0;
	try{
		//conn = new connection("dbname=epics_db user=postgres password=qwer1234 hostaddr=127.0.0.1 port=5432");
		mpConn = new connection(info.c_str());
		if (mpConn->is_open()) {
			cout << "Opened database successfully: " << mpConn->dbname() << endl;
		} else {
			cout << "Can't open database" << endl;
		}
	}catch (const std::exception &e){
		cerr << e.what() << std::endl;
	};

	return (mpConn);
}

connection * RDBManager::Connect(const char *dbname, const char *user, const char *password,
			const char *hostaddr, const char* port)
{
	//connection *mpConn = 0;
	string conn_info = string("dbname=")+string(dbname)+string(" ")+string("user=")+string(user)+string(" ")+string("password=")+string(password)+string(" ")\
						+string("hostaddr=")+string(hostaddr) + string(" ")+ string("port=")+string(port);
	try{
		cout << conn_info << endl;
		mpConn = new connection(conn_info.c_str());
		if (mpConn->is_open()) {
			cout << "Opened database successfully: " << mpConn->dbname() << endl;
		} else {
			cout << "Can't open database" << endl;
		}
	}catch (const std::exception &e){
		cerr << e.what() << std::endl;
	};

	return (mpConn);
}

float RDBManager::ReadValue(const char *table, const char *field)
{
	//string sql = "select data_float from epics_table where id=1";
	string sql = string("select ") + string(field) + string (" from ") + string(table) + string(" where id = 1");

	nontransaction N(*mpConn);
	result R(N.exec(sql.c_str()));

	float data = 0.0;
	for (result::const_iterator c = R.begin(); c!=R.end(); ++c)
	{
		//cout << "DATA_FLOAT: " << c[0].as<float>() << endl;
		data = c[0].as<float>();
	}

	return data;
}

int RDBManager::WriteValue(const void *precord)
{
	rdbpostgreSQLRecord	*prdbpostgreSQL = (rdbpostgreSQLRecord*)precord;

	switch(prdbpostgreSQL->qry)
	{
		case queryUpdate:
			updateValue(precord);
			break;
		case queryInsert:
			//insertValue(prdbpostgreSQL->tabl,prdbpostgreSQL->fild);
			break;
	};

	return(0);
}


int RDBManager::updateValue(const void *precord)
{
	rdbpostgreSQLRecord	*prdbpostgreSQL = (rdbpostgreSQLRecord*)precord;
	string field = string (prdbpostgreSQL->fild);
	string table = string (prdbpostgreSQL->tabl);
	string sval = valtostr(prdbpostgreSQL->val);
	string sql = string("update ") + table + string (" set ") + field + string("=")+ sval+ string(" where id = 1");

	try {
		work w(*mpConn);
		w.exec(sql.c_str());
		w.commit();
	}catch(const exception &e)
	{
		cerr << e.what() << endl;
		return -1;
	}
	return (0);
};

RDBManager::~RDBManager()
{

}
