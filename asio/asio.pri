DEFINES += ASIO_STANDALONE
INCLUDEPATH += \
    $$PWD/include \
    $$PWD/include/asio \
    $$PWD/include/asio/detail \
    $$PWD/include/asio/execution \
    $$PWD/include/asio/experimental \
    $$PWD/include/asio/generic \
    $$PWD/include/asio/impl \
    $$PWD/include/asio/ip \
    $$PWD/include/asio/local \
    $$PWD/include/asio/posix \
    $$PWD/include/asio/ssl \
    $$PWD/include/asio/traits \
    $$PWD/include/asio/ts \
    $$PWD/include/asio/windows \
WSAStartup
LIBS +=\
   -lws2_32 \
   -lMswsock
