#ifndef JSON_RESPONSE_H
#define JSON_RESPONSE_H

class JsonResponse
{
public:
    JsonResponse();

    static QString CreateStatusRespons(const char *status)
    {
        QJsonObject response;
        response["status"] = status;

        return QJsonDocument(response).toJson();
    }

};

#endif // JSON_RESPONSE_H
