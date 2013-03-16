TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    setupTcp.c \
    handle.c \
    ns_look_up.c \
    host_filter.c \
    connect_tcp.c

HEADERS += \
    setupTcp.h \
    handle.h \
    ns_look_up.h \
    host_filter.h \
    connect_tcp.h

LIBS += -lpthread
