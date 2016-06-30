#pragma once

#include <cstdlib> //std::getenv
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm> //std::transform
#include <cctype> //std::tolower

namespace global_ini {

inline std::map<std::string, std::string>& get_ini() {
	static std::map<std::string, std::string> ini;
	return ini;
}

//load ini from environment variable
void iniLoad(const char** envp, const char *prefix="", const bool doOverWrite=false) {
	static std::map<std::string, std::string>& ini = get_ini();
	const std::string str_prefix = prefix;
	std::cout << "[iniLoad] from environmental variables with prefix="<< str_prefix <<":" << std::endl;
	for (; *envp != 0; ++envp) {
		std::string env = *envp;
		if (env.find(str_prefix.c_str()) != 0) continue;
		env = env.substr(str_prefix.length());
		if (ini.find(env) == ini.end() || doOverWrite) {
			std::string key, value;
			size_t eqPos = env.find("=");
			if (eqPos == std::string::npos || eqPos == 0) {
				continue;
			}
			key = env.substr(0, eqPos);
			value = env.substr(eqPos + 1);
			ini[key] = value;
			std::cout << "${" << key << "}=" << value << std::endl;
		}
	}
}

//load ini from ini file
bool iniLoad(const std::string &iniFileName) {
	static std::map<std::string, std::string>& ini = get_ini();
	std::cout << "[iniLoad] try from: " << iniFileName << std::endl;
	std::ifstream in(iniFileName);
	if(!in.is_open()) {
		std::cout<<"... but not found!"<<std::endl;
		return false;
	}
	while(in) {
		std::string line;
		std::getline(in, line);
		if(line.empty() || line[0]=='#') continue;
		std::string key, value;
		size_t eqPos = line.find("=");
		if(eqPos == std::string::npos || eqPos == 0) {
			std::cout<<"# ignore line:"<<line<<std::endl;
			continue;
		}
		key = line.substr(0,eqPos);
		value = line.substr(eqPos+1);
		const char* val_env = std::getenv(key.c_str());
		if (val_env) {
			value = std::string(val_env);
			std::cout << "${" << key << "}=" << value << std::endl;
		} else {
			std::cout << key << "=" << value << std::endl;
		}
		ini[key]=value;
	}
	return true;
}

template<class T>
T iniGet(const std::string &key, const T &default_value) {
	static std::map<std::string, std::string>& ini = get_ini();
	std::map<std::string, std::string>::const_iterator itr=ini.find(key);
	if(itr!=ini.end()) {
		std::stringstream ss;
		ss<<itr->second;
		T ret;
		ss>>ret;
		return ret;
	}
	return default_value;
}

template<> std::string iniGet(const std::string &key, const std::string &default_value) {
	static std::map<std::string, std::string>& ini = get_ini();
	std::map<std::string, std::string>::const_iterator itr=ini.find(key);
	if(itr!=ini.end()) {
		return itr->second;
	}
	return default_value;
}

//handle false/true
template<> bool iniGet(const std::string &key, const bool &default_value) {
	static std::map<std::string, std::string>& ini = get_ini();
	std::map<std::string, std::string>::const_iterator itr = ini.find(key);
	if (itr != ini.end()) {
		std::string val = itr->second;
		std::transform(val.begin(), val.end(), val.begin(), static_cast<int(*)(int)>(std::tolower));
		if (val == "false") return false;
		else if (val == "true") return true;
		else {
			std::stringstream ss;
			ss << itr->second;
			bool ret;
			ss >> ret;
			return ret;
		}
	}
	return default_value;
}
}//global_ini