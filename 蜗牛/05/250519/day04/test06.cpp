/***********************************************************************************
# File Name:    test06.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 16:08:25 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

class Info {
private:  
    Info() {
        cout << "This is Info's constructor without param" << endl;
    }
};

int main(int argc, char *argv[]) {
    Info info;      // ❌
    return 0;
}
