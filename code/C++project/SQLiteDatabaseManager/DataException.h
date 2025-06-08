#ifndef _DATAEXCEPTION_H
#define _DATAEXCEPTION_H
#include <exception>
using namespace std;

struct DatabaseException : public exception
{
public:
   const char* what() const throw (){
    return "C++ exception";
   } 
};

#endif //_DATAEXCEPTION_H