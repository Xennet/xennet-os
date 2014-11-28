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
        // todo: this function should be takend from the NodeModuleApi
        // module name will always be the prefix of all it's function
        JsonHandler startHandler = [](QJsonValue &argument) -> std::string
        {
            if(argument.isString())
            {
               return "node #" + argument.toString().toStdString() +" started";
            }
            return "ERROR! invalid argument:  " + argument.toString().toStdString();

        };
        AddHandler("start", startHandler);
    }

};

#endif // FRONT_END_STUB_H
