TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp \
    poller.cpp \
    eventloop.cpp \
    event.cpp \
    socket.cpp \
    listener.cpp \
    tcpserver.cpp \
    connection.cpp \
    buffer.cpp \
    tcpclient.cpp \
    http_message.cpp \
    httpclient.cpp \
    time_event.cpp \
    timer.cpp \
    demo/tiny_proxy.cpp \
    demo/qq_crawler.cpp

HEADERS += \
    poller.h \
    utils.h \
    eventloop.h \
    event.h \
    socket.h \
    listener.h \
    tcpserver.h \
    connection.h \
    buffer.h \
    thread_safe_queue.h \
    tcpclient.h \
    chatroom.h \
    http_message.h \
    httpclient.h \
    time_event.h \
    timer.h \
    time_event_compare.h \
    tcp_address.h \
    demo/tiny_proxy.h \
    demo/qq_crawler.h

