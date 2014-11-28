#ifndef MODULE_API_H
#define MODULE_API_H

#include <string>
#include "json_request_handler.h"

class ModuleAPI
{
protected:
    std::string m_moduleName;
    Handlers m_handlers;
public:
    ModuleAPI(const char *moduleName):m_moduleName(moduleName){;}
    void AddHandler(const char *path, JsonHandler &handler);
    bool Send(QString &strRequest, QString &response);
};

#endif // MODULE_API_H
