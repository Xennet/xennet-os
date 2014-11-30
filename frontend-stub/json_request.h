#ifndef JSONMESSAGE_H
#define JSONMESSAGE_H

#include "includes.h"

class JsonRequest
{
public:
    JsonRequest(){;}

    bool Parse(QString &strRequest);
    QString m_path;
    QJsonValue m_args;
};

#endif // JSONMESSAGE_H
