#include "searchthread.h"

SearchThread::SearchThread()
{

}

void SearchThread::do_work()
{
    emit result(1);
}
