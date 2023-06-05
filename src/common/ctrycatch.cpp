#include "qcommon.h"
#include "ctrycatch.h"
#include <exception>
#include <string>


struct exception_handler_head_t
{
    exception_try_record_t* head;
    Exception_type lastexception;
    std::string lastexceptionmessage;
};

thread_local exception_handler_head_t exception_head;

exception_try_record_t* CTryCatch_AddNewHandler(exception_try_record_t* new_handler)
{
    exception_try_record_t* tmp = exception_head.head;
    exception_head.head = new_handler;
    return tmp;
}

void CTryCatch_RemoveTopHandler()
{
    exception_head.head = exception_head.head->next;
}

void CTryCatch_Throw(Exception_type exception, const char* exceptionmsg)
{
    exception_try_record_t* iter = exception_head.head;
    while(iter != nullptr)
    {
        if(iter->type == exception)
        {
            break;
        }
        iter = iter->next;
    }
    if(iter == nullptr)
    {
        std::terminate();
        return;
    }
    exception_head.head = iter;
    exception_head.lastexceptionmessage = exceptionmsg;
    longjmp(iter->context, (int)exception);
}
