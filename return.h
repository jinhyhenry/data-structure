#ifndef _RETURN_H_
#define _RETURN_H_

#define RETURN_ON_NULL(ptr)\
		if(!ptr) return NULL_PTR;

enum StdRet {
	OK = 0,
	NG,
	TIME_OUT,
	NULL_PTR,
};

#endif