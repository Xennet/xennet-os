#ifndef FRONT_END_STUB_H
#define FRONT_END_STUB_H

#include "json_request.h"
#include "module_api.h"
#include "json_response.h"

class FrontEndStub: public ModuleAPI
{
    FrontEndStub():ModuleAPI("FrontEndStub"){}

public:

    static FrontEndStub &Instance()
    {
        static FrontEndStub instance;

        return instance;
    }
    void InitAPIs()
    {
        // todo: replace these handlers with real API calls taken
        // from various modules, e.g NodesModule, WalletModule ect.
        // every command will have the module name as prefix.
        // e.g "node.start" "wallet.setConfig"

        AddHandler("node.start", [](QJsonValue &argument) -> QString
        {
           //return CreateStatusRespons{std::string("node #" + argument.toString().toStdString() +" started").c_str()};
            return JsonResponse::CreateStatusRespons("started");
        });
        AddHandler("node.stop", [](QJsonValue &argument) -> QString
        {
            return JsonResponse::CreateStatusRespons("stopped");
        });
        AddHandler("node.setConfig", [](QJsonValue &argument) -> QString
        {
            if(argument.isObject())
            {
                QJsonObject argObject = argument.toObject();
                //QJsonArray nodeId = argObject.value("node_id");
                //QJsonObject config = argObject.value("config");

                // TODO set config

                return JsonResponse::CreateStatusRespons("success");
            }
            // TODO: schema validation
            return JsonResponse::CreateStatusRespons("ERROR: invalid request");
        });
    }


};

#endif // FRONT_END_STUB_H
