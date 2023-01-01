#include "RequestHandler.h"
#include "ThreadPool.h"
#include "TaskMonitor.h"

RequestHandler::RequestHandler()
{
    _tpool.start();
}

RequestHandler::~RequestHandler()
{
    _tpool.stop();
}

res_type RequestHandler::pushRequest(FuncType f, int id, int arg)
{
    return _tpool.push_task(f, id, arg);
}

res_type RequestHandler::pushRequest(FuncTypeArr f, int *beg, int *end, TaskMonitor &monitor)
{
    return _tpool.push_task(f, beg, end, monitor);
}

void RequestHandler::interruptPool()
{
    _tpool.interrupt();
}
