#ifndef __REDIS_H__
#define __REDIS_H__
#include <Windows.h>
#include <string>
#include <iostream>
#include <time.h>
#include "hiredis.h"


using namespace std;

class Redis
{
public:
	Redis(const char* disks);
	~Redis();
	bool initConfig(const char* disks);
	bool connect();
	bool isConnected();
	void close();
	bool ping();
	const char* error();
private:
	string _host;
	int	   _port;
	//------
	redisContext* _connect;
	Mutex	_mutex;
	time_t  _pingTime;
	bool	_isConnected;
};

#endif