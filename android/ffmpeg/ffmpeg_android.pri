 INCLUDEPATH += $$PWD/include
    LIBS += -L$$PWD/lib/arm64-v8a \
                    -lavcodec \
                    -lavfilter \
                    -lavformat \
                    -lavutil \
                    -lswscale