#pragma once
#include "ThreadPool.h"
#include "TaskMonitor.h"

class RequestHandler
{
private:
    ThreadPool _tpool;

public:
    RequestHandler();
    ~RequestHandler();

    res_type pushRequest(FuncType, int, int);
    res_type pushRequest(FuncTypeArr, int*, int*, TaskMonitor&);
    void interruptPool();
};