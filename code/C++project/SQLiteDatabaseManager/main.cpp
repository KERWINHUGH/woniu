#include <iostream>
#include "DataException.h"
#include "singleton.h"
#include <vector>
using namespace std;

int main(){
    // vector<int> vec;
    // vec.push_back(1);
    // vec.push_back(2);
    // vec.push_back(3);
    // vec.erase(vec.begin()+2); 
    cout << "11111111111111" << endl;
    try
    {
        throw DatabaseException();
    }
    catch(DatabaseException& e)
    {
        cout << "DataBaseException caught" << endl;
        cout << e.what() << endl;
    }
    cout << "2222222222222222222" << endl;
    return 0;
}