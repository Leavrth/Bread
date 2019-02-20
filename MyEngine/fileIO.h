#pragma once
#include <cstdio>

class basefile {
public:
	explicit basefile(const char* fileName, const char* mode = "a+"):file(std::fopen(fileName, mode)),isopen(true) {
		if (file == NULL) isopen = false;
	}
	virtual ~basefile() { std::fclose(file); }
protected:
	std::FILE* file;
	bool isopen;
};

class iFile : public basefile {
public:
	explicit iFile(const char* fileName) :basefile(fileName, "r") {}
	~iFile() {}

};

class oFile : public basefile {
public:
	explicit oFile(const char* fileName) :basefile(fileName, "a") {}
	~oFile() {}
	bool writelog(const char* data);
};

