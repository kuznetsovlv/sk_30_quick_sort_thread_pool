#include "RequestHandler.h"
#include "ThreadPool.h"

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

void RequestHandler::interruptPool()
{
    _tpool.interrupt();
}
