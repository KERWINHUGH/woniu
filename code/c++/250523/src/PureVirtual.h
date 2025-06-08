/***************************************************
# File Name:    多态纯虚函数实现泡茶流程.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月23日 星期五 16时02分56秒
****************************************************/
#ifndef _PURE_VIRTUAL
#define _PURE_VIRTUAL

class AbstractDrinking{
public:
	virtual void Boil() = 0;
	virtual void Brew() = 0;
	virtual void Pour() = 0;
	virtual void Addthings() = 0;
	~AbstractDrinking(){}
};

class Produce{
public:
	static void Production(AbstractDrinking *drink);
};

class Coffe : public AbstractDrinking{
	virtual void Boil();
	virtual void Brew();
	virtual void Pour();
	virtual void Addthings();
};

class Tea : public AbstractDrinking{
	virtual void Boil();
	virtual void Brew();
	virtual void Pour();
	virtual void Addthings();
};

void test();

#endif
