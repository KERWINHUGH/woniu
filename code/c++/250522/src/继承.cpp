/***************************************************
# File Name:    继承.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月22日 星期四 10时52分19秒
****************************************************/

#include <iostream>
using namespace std;

class IndexPage{
public:
	void Head(){
		cout << "网页头部" << endl;
	}
	void LeftNavigation(){
		cout << "左侧导航菜单" << endl;
	}
	void MainBody(){
		cout << "网页主题部分内容" << endl;
	}
	void Footer(){
		cout << "网页底部" << endl;
	}
private:
	string m_pTitle;	//网页标题
};

class NewsPage : public IndexPage{
public:
	void MainBody(){
		cout << "新闻网网页主题内容" << endl;
	}
};

void test1(){
	NewsPage *newspage = new NewsPage;
	newspage->Head();
	newspage->MainBody();
	newspage->LeftNavigation();
	newspage->Footer();
}

void test2(){
	NewsPage *newspage = new NewsPage;
	newspage->Head();
	newspage->IndexPage::MainBody();
	newspage->LeftNavigation();
	newspage->Footer();	
}

int main(int argc, char *argv[]) {
	test1();
	cout << "-------------------------------------" << endl;
	test2();
    return 0;
}
