#include <time.h>
#define NTIMES 10000

#include "lch.hpp"

const char LogMode[4][10] = {
	{"LOG_QUIET"},
	{"LOG_ERROR"},
	{"LOG_INFO"},
	{"LOG_DEBUG"}
};

namespace test {
	struct Test{
		void operator()() {
			logle("logle"<<12);
			logli("logli"<<13);
			logld("logld"<<14);

			loge("loge\\n\n");
			logi("logi\\n\n");
			logd("logd\\n\n");

			//c style
			cloge("test cloge: %d\n", 10);
			ctage("test ctage: %f\n", 22.2);
			clogi("test clogi: %d\n", 10);
			ctagi("test ctagi: %f\n", 22.2);
			clogd("test clogd: %d\n", 10);
			ctagd("test ctagd: %f\n", 22.2);
		}
	};
}

int main(int argc, const char **argv)
{
	using namespace LogHelper;
	int t;
	test::Test tt;
	GLogControl::Instance().level = LOG_ERROR;
	for(int cnt=0; cnt<NTIMES; ++cnt) {
		const int sw = cnt % 4;
		switch(sw) {
		case 0: GLogControl::Instance().level = LOG_QUIET; break;
		case 1: GLogControl::Instance().level = LOG_ERROR; break;
		case 2: GLogControl::Instance().level = LOG_INFO; break;
		case 3: GLogControl::Instance().level = LOG_DEBUG; break;
		};
		//std::cout<<"-----------------------------"<<sw<<std::endl;
		tt();
	}
	t = clock();

	std::cout
#ifdef SUPPRESS_LOG
		<<"Suppressed Log "
#else
		<<"Log "
#endif
		<<NTIMES
		<<" times took me "<<t
		<<" clicks ("<<((float)t)/CLOCKS_PER_SEC
		<<" seconds)."<<std::endl;
	return 0;
}
