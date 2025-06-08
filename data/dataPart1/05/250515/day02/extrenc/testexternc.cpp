#include <iostream>
using namespace std;

extern "C" void func1();
extern "C" int func2(int a, int b);

int main(int argc, char *argv[]) {
	func1();
	cout << func2(10, 20) << endl;
	return EXIT_SUCCESS;
}
