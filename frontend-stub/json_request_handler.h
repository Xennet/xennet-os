#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "includes.h"
#include <functional>

typedef std::function<QString(QJsonValue&)> JsonHandler;
typedef std::map<std::string, JsonHandler> Handlers;


#endif // REQUEST_HANDLER_H
