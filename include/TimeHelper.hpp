#pragma once

#ifdef OPENCV_FOUND
	#include "opencv2/opencv.hpp"
#else// OPENCV_FOUND
	#if defined WIN32 || defined _WIN32 || defined WINCE
		#include "Winnt.h"
	#elif defined __linux || defined __linux__
		#include <time.h>
	#elif defined __MACH__ && defined __APPLE__
		#include <mach/mach_time.h>
	#endif
#endif//OPENCV_FOUND

namespace TimeHelper {
#ifdef OPENCV_FOUND
	using cv::getTickCount;
	using cv::getTickFrequency;
#else
	inline int64 getTickCount(void)
	{
	#if defined WIN32 || defined _WIN32 || defined WINCE
		LARGE_INTEGER counter;
		QueryPerformanceCounter( &counter );
		return (int64)counter.QuadPart;
	#elif defined __linux || defined __linux__
		struct timespec tp;
		clock_gettime(CLOCK_MONOTONIC, &tp);
		return (int64)tp.tv_sec*1000000000 + tp.tv_nsec;
	#elif defined __MACH__ && defined __APPLE__
		return (int64)mach_absolute_time();
	#else
		struct timeval tv;
		struct timezone tz;
		gettimeofday( &tv, &tz );
		return (int64)tv.tv_sec*1000000 + tv.tv_usec;
	#endif
	}

	inline double getTickFrequency(void)
	{
	#if defined WIN32 || defined _WIN32 || defined WINCE
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		return (double)freq.QuadPart;
	#elif defined __linux || defined __linux__
		return 1e9;
	#elif defined __MACH__ && defined __APPLE__
		static double freq = 0;
		if( freq == 0 )
		{
			mach_timebase_info_data_t sTimebaseInfo;
			mach_timebase_info(&sTimebaseInfo);
			freq = sTimebaseInfo.denom*1e9/sTimebaseInfo.numer;
		}
		return freq;
	#else
		return 1e6;
	#endif
	}
#endif//OPENCV_FOUND

	/**
	\brief helper class for measuring time elapse
	*/
	struct Timer {
		int scale;
		double startTick;

		enum {
			UNIT_S = 1,		//second
			UNIT_MS = 1000	//millisecond
		};

		std::string unit_name() const {
			switch(scale) {
			case 1:
				return "s";
			case 1000:
				return "ms";
			}
			return "";
		}

		/**
		constructor

		@param scale time scale, 1 means second, 1000 means milli-second,
		1/60.0 means minutes, etc.
		*/
		Timer(const int scale = UNIT_S) {
			this->scale = scale;
			startTick = 0;
		}

		/**
		start record time, similar to matlab function "tic";

		@return the start tick
		*/
		inline double tic() {
			return startTick = (double)getTickCount();
		}

		/**
		return duration from last tic, in (second * scale), similar to matlab function "toc"

		@return duration from last tic,  in (second * scale)
		*/
		inline double toc() {
			return ((double)getTickCount() - startTick) / getTickFrequency() * scale;
		}
		inline double toc(std::string tag) {
			double time = toc();
			std::cout << tag << " " << time << unit_name() << std::endl;
			return time;
		}

		/**
		equivalent to { toc(); tic(); }

		@return duration from last tic,  in (second * scale)
		*/
		inline double toctic() {
			double ret = ((double)getTickCount() - startTick) / getTickFrequency() * scale;
			tic();
			return ret;
		}
		inline double toctic(std::string tag) {
			double time = toctic();
			std::cout << tag << " " << time << unit_name() << std::endl;
			return time;
		}
	};

	struct ScopedTimer : public Timer {
		std::string tag;

		ScopedTimer(const int scale = UNIT_S, const std::string& tag_="") : Timer(scale), tag(tag_) {
			tic();
		}

		~ScopedTimer() {
			double time = toc();
			std::cout << tag << " " << time << unit_name() << std::endl;
		}
	};
}//TimeHelper