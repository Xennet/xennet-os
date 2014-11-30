#include "json_request.h"

bool JsonRequest::Parse(QString &strRequest)
{
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strRequest.toUtf8(), &err);
    if(err.error == err.NoError)
    {
        QJsonObject jsonRequest = jsonDoc.object();
        QJsonValue path = jsonRequest.value("command");

        if(path.isString())
        {
            QString str = path.toString();
            if(!str.isEmpty())
            {
                m_path = str;
                m_args = jsonRequest.value("arg");
                return true;
            }
        }
    }
    return false;
}

