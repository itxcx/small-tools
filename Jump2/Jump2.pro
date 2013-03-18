TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    setupTcp.c \
    ns_look_up.c \
    host_filter.c \
    handle.c \
    connect_tcp.c

OTHER_FILES +=

HEADERS += \
    setupTcp.h \
    ns_look_up.h \
    host_filter.h \
    handle.h \
    connect_tcp.h \
    sock_map.h

LIBS += -lpthread
