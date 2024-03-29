QT       += core websockets
QT       -= gui

TARGET = front_end_stub
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += \
    main.cpp \
    mockup_server.cpp \
    json_request.cpp \
    module_api.cpp \
    front_end_stub.cpp \
    json_response.cpp

HEADERS += \
    mockup_server.h \
    json_request.h \
    front_end_stub.h \
    module_api.h \
    json_request_handler.h \
    includes.h \
    json_response.h

OTHER_FILES += test_client.html
