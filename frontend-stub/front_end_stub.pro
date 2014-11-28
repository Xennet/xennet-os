QT       += core websockets
QT       -= gui

TARGET = front_end_stub
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    mockup_server.cpp \
    json_request.cpp \
    module_api.cpp \
    front_end_stub.cpp

HEADERS += \
    mockup_server.h \
    json_request.h \
    front_end_stub.h \
    module_api.h \
    json_request_handler.h \
    includes.h

OTHER_FILES += test_client.html
