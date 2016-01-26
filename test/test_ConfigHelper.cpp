#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "lch.hpp"

using namespace std;
using helper::GConfig;

int main(int argc, char **argv )
{
	for(int i=0; i<argc; ++i) {
		logli(i<<":"<<argv[i]);
	}
	logli("---------------");
	LogHelper::GLogControl::Instance().level = LogHelper::LOG_INFO;

	using namespace ConfigHelper;
	Config& cfg = GConfig::Instance();
	if(!cfg.autoLoad("test_ConfigHelper.cfg",DirHelper::getFileDir(argv[0]))) {
		logli("[main] no test_ConfigHelper.cfg file loaded");
	}
	logli("Before reset");
	logli(cfg.getRoot().str());
	if(argc>1) {
		cfg.reset(argc-1,argv+1);
		logli("After reset");
				logli(cfg.getRoot().str());
	}

	logli("parsed cfg is:");
	ConfigNode& cn = *cfg;
	cn.print(std::cout);
	logli("-------------");
	{
		double val = cfg.get("distCoeffs:@6",1.28);
		logli("distCoeffs:@6="<<val);
		logli("testStr="<<cfg.get("testStr","testttttt"));
	}
	{
		std::vector<double> val;
		(*cfg)["distCoeffs"]>>val;
		logli("distCoeffs=");
		helper::print(std::cout, val, ", ");
		logli("");
	}
	{
		logli("testMap:key1="<<(double)(*cfg)["testMap"]["key1"]);
		logli("testMap:key2="<<(int)(*cfg)["testMap"]["key2"]);
		logli("testMap:key3="<<(*cfg)["testMap"]["key3"].str());
		logli("testMap:key4="<<(int)(*cfg)["testMap"]["key4"]);
		logli("testMap:key5=");
		std::vector<int> key5;
		(*cfg)["testMap"]["key5"]>>key5;
		helper::print(std::cout, key5, " ");
		logli("");
	}
	//std::string varStr=(std::string)(*cr.root->at("MarkerSet::optimizeMethod")->as<ConfigHelper::ConfigNodeSimple>());
	//logli("MarkerSet::optimizeMethod="<<varStr);
	return 0;
}
