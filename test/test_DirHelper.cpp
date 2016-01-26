#include "lch.hpp"

int main(int argc, const char **argv)
{
#ifdef _WIN32
	tagli("Currently under Windows OS!");
#else
	tagli("Currently under UNIX-like OS!");
#endif

	tagli("filesep="<<DirHelper::filesep);

	logli("FullFile:");
	std::string folderA("parent");
	std::string folderB("child");
	std::string fileC("file.ext");
	tagli("folderA="<<folderA);
	tagli("folderB="<<folderB);
	tagli("fileC="<<fileC);
	std::string combined = DirHelper::FullFile()<<folderA<<folderB<<fileC;
	tagli("combined="<<combined);

	folderA+=DirHelper::filesep;
	folderB+=DirHelper::filesep;
	tagli("folderA="<<folderA);
	tagli("folderB="<<folderB);
	tagli("fileC="<<fileC);
	combined = DirHelper::FullFile()<<folderA<<folderB<<fileC;
	tagli("combined="<<combined);

	logli("fileparts:");
	std::string path, name, ext;
	DirHelper::fileparts(combined, &path, &name, &ext);
	tagli("path="<<path);
	tagli("name="<<name);
	tagli("ext="<<ext);
	return 0;
}
