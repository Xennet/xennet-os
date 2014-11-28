#include <QtCore/QCoreApplication>
#include "mockup_server.h"
#include "json_request.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MocupServer *server = new MocupServer(1234);
    QObject::connect(server, &MocupServer::closed, &a, &QCoreApplication::quit);

    return a.exec();
}

