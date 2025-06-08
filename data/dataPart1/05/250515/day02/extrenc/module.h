#ifndef MODULE_H
#define MODULE_H

#include <stdio.h>

#if __cplusplus		// 在C++环境中
extern "C" {
#endif
	void func1();
	int func2(int a,int b);
#if __cplusplus
}
#endif
#endif //
