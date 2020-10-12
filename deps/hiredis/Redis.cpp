#include "Redis.h"
#include "../json/Json.h"

#define MAX_STRING_LEN 1024
#define PING_TIME	10
#define DATABASE_CONFIG "config/redis.json"

Redis::Redis(const char* disks)
	:_pingTime(0)
	,_isConnected(false)
{
	initConfig(disks);
}

Redis::~Redis()
{

}

bool Redis::initConfig(const char* disks)
{
	FILE* reader = NULL;
	errno_t err = fopen_s(&reader, DATABASE_CONFIG, "rb");
	if (!reader || err) {
		return false;
	}
	char buf[1024] = {0};
	fread(buf, 1, 1024, reader);
	fclose(reader);
	JsonObject json;
	if (!json.parse(buf))
	{
		return false;
	}
	if (!json.has(disks))
	{
		return false;
	}
	JsonObject config(json.getObject(disks));

	if (!config.has("host") || !config.has("port"))
	{
		return false;
	}
	_host = config.getString("host");
	_port = config.getInt("port");
	return true;
}

bool Redis::connect()
{
	_isConnected = false;
	_mutex.lock();
	mysql_init(&_myConn);
	mysql_set_character_set(&_myConn, "utf8");
	if (mysql_real_connect(&_myConn, _host.c_str(), _username.c_str(), _password.c_str(), _dbname.c_str(), _port, NULL, 0))
	{
		_pingTime = time(0) + PING_TIME;
		_isConnected = true;
	}
	_mutex.un_lock();
	return _isConnected;
}

bool Redis::isConnected()
{
	return _isConnected;
}

void Redis::close()
{
	_mutex.lock();
	_pingTime = 0;
	_isConnected = false;
	mysql_close(&_myConn);
	_mutex.un_lock();
}

bool Redis::ping()
{
	if (!_isConnected)
	{
		return false;
	}
	if (_pingTime == 0)
	{
		return true;
	}
	time_t now = time(0);
	if (_pingTime >= now)
	{
		return true;
	}
	_pingTime = now + PING_TIME;
	_mutex.lock();
	_isConnected = mysql_ping(&_myConn) == 0;
	_mutex.un_lock();
	return _isConnected;
}

const char * Redis::error()
{
	return mysql_error(&_myConn);
}

