#include <iostream>
#include <pqxx/pqxx>
#include "rdbConnManager.h"

RDBManager::RDBManager()
{
	//init_record();

	try{
		connection C("dbname=epics_db user=postgres password=qwer1234 \
				hostaddr=127.0.0.1 port=5432");
		if (C.is_open()) {
			cout << "Opened database successfully: " << C.dbname() << endl;
		} else {
			cout << "Can't open database" << endl;
		}
		C.disconnect ();
	}catch (const std::exception &e){
		cerr << e.what() << std::endl;
	}
}

RDBManager::~RDBManager()
{

}

int RdbpostgreSQLDebug = 0;
epicsExportAddress(int, RdbpostgreSQLDebug);

devRdbpostgreSQLSoft rdbReadpostgreSQL={ 5, NULL, NULL, init_record, NULL, read_rdb };
devRdbpostgreSQLSoft rdbWritepostgreSQL={ 5, NULL, NULL, init_record, NULL, write_rdb };

epicsExportAddress(dset,rdbReadpostgreSQL);

long init_record(void	*precord)
{
	RDBManager *pManager = new RDBManager();
	rdbpostgreSQLRecord	*prdbpostgreSQL = (rdbpostgreSQLRecord*)precord;
	char *dopts = NULL;

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

	double scale;

	if(RdbpostgreSQLDebug)
		printf("Scan(%d)\n",prdbpostgreSQL->scan);

    status = dbGetLink(&(prdbpostgreSQL->inp),DBF_DOUBLE, &(prdbpostgreSQL->val),0,0);
    /*If return was succesful then set undefined false*/
    if(!status) prdbpostgreSQL->udf = FALSE;
    return(0);
}

long write_rdb(void	*precord)
{
	rdbpostgreSQLRecord	*prdbpostgreSQL = (rdbpostgreSQLRecord*)precord;
    long status;
	epicsTimeStamp currTime;
	epicsTimeGetCurrent (&currTime);

	double scale;

	if(RdbpostgreSQLDebug)
		printf("Scan(%d)\n",prdbpostgreSQL->scan);

    status = dbGetLink(&(prdbpostgreSQL->inp),DBF_DOUBLE, &(prdbpostgreSQL->val),0,0);
    /*If return was succesful then set undefined false*/
    if(!status) prdbpostgreSQL->udf = FALSE;
    return(0);
}

