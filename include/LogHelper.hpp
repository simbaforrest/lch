#pragma once
/* LogHelper
 * a lightweight logger with dynamic log level control at runtime
 * Option before including this header file:
 *   Turn off all log by defining SUPPRESS_LOG.
 *
 * Dynamically control log level by setting:
 *   LogHelper::GetOrSetLogLevel()
 * to following four types:
 *   LogHelper::LOG_QUIET -> completely quiet
 *   LogHelper::LOG_ERROR -> only log error
 *   LogHelper::LOG_INFO -> log error + info
 *   LogHelper::LOG_DEBUG -> log everything
 *
 * Provide 2 types of log:
 *   1. <log|tag>[l]<e|i|d>
 *      i.e. loge/logi/.../logle/.../logld/.../tage/.../tagld
 *      mix between c++ style and c style; same log speed
 *      with type 2.
 *      example:
 *      loge("an error happened!\n");
 *      logle("another error, par="<<par);
 *
 *   2. c<log|tag><e|i|d>
 *      i.e. cloge/clogi/.../ctage/.../ctagd
 *      totally similar to printf
 *      example:
 *      cloge("an error happened, par=%d\n",par); */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif
#include <time.h>

namespace LogHelper {

	inline std::string getCurrentTimeString() {
		time_t ret = time(0);
		return std::string(asctime(localtime(&ret)));
	}

	enum Level {
		LOG_QUIET=0,
		LOG_ERROR=1,
		LOG_INFO=2,
		LOG_DEBUG=3
	};

	inline int GetOrSetLogLevel(const int l=-1)
	{
		static int level = LOG_INFO;
		if(l<0) return level;
		level = l;
		return level;
	}

#define is_log_quiet  (LogHelper::GetOrSetLogLevel()<=LogHelper::LOG_QUIET)
#define is_error_log  (LogHelper::GetOrSetLogLevel()>=LogHelper::LOG_ERROR)
#define is_info_log   (LogHelper::GetOrSetLogLevel()>=LogHelper::LOG_INFO)
#define is_debug_log  (LogHelper::GetOrSetLogLevel()>=LogHelper::LOG_DEBUG)

#ifndef SUPPRESS_LOG

//logle("something wrong !"<<12.3);
#define logle(A) (is_error_log?(std::cerr<<A<<std::endl,0):(0))
#define logli(A) (is_info_log?(std::cout<<A<<std::endl,0):(0))
#define logld(A) (is_debug_log?(std::clog<<A<<std::endl,0):(0))

#define loge(A) (is_error_log?(std::cerr<<A,0):(0))
#define logi(A) (is_info_log?(std::cout<<A,0):(0))
#define logd(A) (is_debug_log?(std::clog<<A,0):(0))

#define tagle(A) (is_error_log?(std::cerr<<"["<<__FUNCTION__<<" error] "<<A<<std::endl,0):(0))
#define tagli(A) (is_info_log?(std::cout<<"["<<__FUNCTION__<<"] "<<A<<std::endl,0):(0))
#define tagld(A) (is_debug_log?(std::clog<<"["<<__FUNCTION__<<" debug] "<<A<<std::endl,0):(0))

#define tage(A) (is_error_log?(std::cerr<<"["<<__FUNCTION__<<" error] "<<A,0):(0))
#define tagi(A) (is_info_log?(std::cout<<"["<<__FUNCTION__<<"] "<<A,0):(0))
#define tagd(A) (is_debug_log?(std::clog<<"["<<__FUNCTION__<<" debug] "<<A,0):(0))


// c style log
#ifndef CLOG_FILE_I
#define CLOG_FILE_I stdout
#endif
#ifndef CLOG_FILE_E
#define CLOG_FILE_E stderr
#endif
#ifndef CLOG_FILE_D
#define CLOG_FILE_D stderr
#endif

#define cloge(...) {is_error_log?fprintf(CLOG_FILE_E,__VA_ARGS__):0;}
#define ctage(...) {is_error_log?\
	(fprintf(CLOG_FILE_E,"["),\
	fprintf(CLOG_FILE_E,__FUNCTION__),\
	fprintf(CLOG_FILE_E," error] "),\
	fprintf(CLOG_FILE_E,__VA_ARGS__)):0;}
#define clogi(...) {is_info_log?fprintf(CLOG_FILE_I,__VA_ARGS__):0;}
#define ctagi(...) {is_info_log?\
	(fprintf(CLOG_FILE_I,"["),\
	fprintf(CLOG_FILE_I,__FUNCTION__),\
	fprintf(CLOG_FILE_I,"] "),\
	fprintf(CLOG_FILE_I,__VA_ARGS__)):0;}
#define clogd(...) {is_debug_log?fprintf(CLOG_FILE_D,__VA_ARGS__):0;}
#define ctagd(...) {is_debug_log?\
	(fprintf(CLOG_FILE_D,"["),\
	fprintf(CLOG_FILE_D,__FUNCTION__),\
	fprintf(CLOG_FILE_D," debug] "),\
	fprintf(CLOG_FILE_D,__VA_ARGS__)):0;}

#else//SUPPRESS_LOG

#define loge(A)
#define logi(A)
#define logd(A)

#define logle(A)
#define logli(A)
#define logld(A)

#define tage(A)
#define tagi(A)
#define tagd(A)

#define tagle(A)
#define tagli(A)
#define tagld(A)

#define cloge(...)
#define ctage(...)
#define clogi(...)
#define ctagi(...)
#define clogd(...)
#define ctagd(...)

#endif//SUPPRESS_LOG

}//end of LogHelper
