#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "includes.h"

typedef std::function<std::string(QJsonValue&)> JsonHandler;
typedef std::map<std::string, JsonHandler> Handlers;


#endif // REQUEST_HANDLER_H
