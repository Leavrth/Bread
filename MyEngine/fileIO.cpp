#include "fileIO.h"

bool oFile::writelog(const char* data) {
	fputs(data, file);
}