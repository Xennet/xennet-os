#ifndef FRONT_END_STUB_H
#define FRONT_END_STUB_H

#include "json_request.h"
#include "module_api.h"

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

        AddHandler("node.start", [](QJsonValue &argument) -> std::string
        {
           return "{'response': 'node #" + argument.toString().toStdString() +" started";
        });
        AddHandler("node.stop", [](QJsonValue &argument) -> std::string
        {
           return "{'response':node #" + argument.toString().toStdString() +" stopped";
        });
    }

};

#endif // FRONT_END_STUB_H
