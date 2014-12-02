#include "mockup_server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <string>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>

#include "front_end_stub.h"
using namespace std;

QT_USE_NAMESPACE

MocupServer::MocupServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_clients()
{
    bool SSL = false;//temp
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Mockup Server"),
                SSL ? QWebSocketServer::SecureMode
                    : QWebSocketServer::NonSecureMode, this);

    if(SSL)
    {
        QSslConfiguration sslConfiguration;
        QFile certFile(QStringLiteral("./localhost.cert"));
        QFile keyFile(QStringLiteral("./localhost.key"));
        certFile.open(QIODevice::ReadOnly);
        keyFile.open(QIODevice::ReadOnly);
        if(!certFile.isOpen() || !keyFile.isOpen())
        {
            qDebug() << "ERROR! cannot open cert files";
        }
        QSslCertificate certificate(&certFile, QSsl::Pem);
        QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
        certFile.close();
        keyFile.close();
        sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfiguration.setLocalCertificate(certificate);
        sslConfiguration.setPrivateKey(sslKey);
        sslConfiguration.setProtocol(QSsl::TlsV1SslV3);
        m_pWebSocketServer->setSslConfiguration(sslConfiguration);
    }


    // init the front end stub module
    FrontEndStub::Instance().InitAPIs();

    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "MocupServer listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &MocupServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &MocupServer::closed);
        connect(m_pWebSocketServer, &QWebSocketServer::sslErrors,
                this, &MocupServer::onSslErrors);
    }
}

MocupServer::~MocupServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void MocupServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &MocupServer::processTextMessage);
    //connect(pSocket, &QWebSocket::binaryMessageReceived, this, &MocupServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &MocupServer::socketDisconnected);

    m_clients << pSocket;
}
void MocupServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        QString response;
        FrontEndStub::Instance().Send(message, response);
        pClient->sendTextMessage(response);
    }
    //m_pWebSocketServer->close();
}
void MocupServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}
void MocupServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
void MocupServer::onSslErrors(const QList<QSslError> &)
{
    qDebug() << "Ssl errors occurred";
}
