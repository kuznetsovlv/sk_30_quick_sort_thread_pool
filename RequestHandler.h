#pragma once
#include "ThreadPool.h"

class RequestHandler
{
private:
    ThreadPool _tpool;

public:
    RequestHandler();
    ~RequestHandler();

    res_type pushRequest(FuncType, int, int);
    void interruptPool();
};