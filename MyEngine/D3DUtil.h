#pragma once
#include <assert.h>
#include <functional>
#include <cstdio>

struct _checkMsg{
		bool ischeck = false;
		short checknx;
		short checkny;
};

#define SAFE_DELETE(p)	{if(p){delete(p);(p)=NULL;}}

#define SAFE_RELEASE(p)	{if(p){(p)->Release();(p)=NULL;}}

#define SAFE_RELEASEARRAY(p, n)	{for (int i = 0; i != n; i++){(p)[i]->Release(); (p)[i] = NULL;}}
