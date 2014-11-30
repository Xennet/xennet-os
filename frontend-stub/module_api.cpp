#include "module_api.h"
#include "json_request.h"

void ModuleAPI::AddHandler(const char *path, JsonHandler handler)
{
    if(path)
    {
        m_handlers[path] = handler;
    }
}


bool ModuleAPI::Send(QString &strRequest, QString &response)
{
    JsonRequest request;
    if(request.Parse(strRequest))
    {
        Handlers::iterator it = m_handlers
                .find(request.m_path);
        if(it != m_handlers.end())
        {
            response = QString::fromStdString((it->second)(request.m_args));
            return true;
        }
    }
    response = "ERROR! invalid request";
    return false;
}
