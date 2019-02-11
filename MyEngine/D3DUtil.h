#pragma once
#include <assert.h>
#include <functional>
#include <cstdio>

#define CREATE_FUNC(___TYPE___)		\
static ___TYPE___*create()			\
{									\
	___TYPE___*pRet=new ___TYPE___();\
	if(pRet&&pRet->init())			\
	{								\
		pRet->autorelease();		\
		return pRet;				\
	}								\
	delete pRet;					\
	pRet = NULL;					\
	return pRet;					\
}									

#define _ASSERT__(cond, msg){				\
	if(!(cond)){						\
		printf("Assert failed:%s", msg);\
		assert(cond);					\
	}									\
}

#define SAFE_DELETE(p)	{if(p){delete(p);(p)=NULL;}}

#define OBJ_SAFE_RELEASE(p) {if(p){(p)->release();(p)=NULL;}}

#define SAFE_RELEASE(p)	{if(p){(p)->Release();(p)=NULL;}}

#define SAFE_RELEASEARRAY(p, n)	{for (int i = 0; i != n; i++){(p)[i]->Release(); (p)[i] = NULL;}}

#define MB(p, q){}

