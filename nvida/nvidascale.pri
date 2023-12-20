




LIBS+=\
   -luser32 \
   -ld3d11  \
   -ldxgi \
   -lwindowscodecs \
   -ld3dcompiler \

HEADERS += \
    $$PWD/NIS/NIS_Config.h \
    $$PWD/NIS/NIS_Scaler.h \
    $$PWD/code/DX11/AppRenderer.h \
    $$PWD/code/DX11/BilinearUpscale.h \
    $$PWD/code/DX11/DeviceResources.h \
    $$PWD/code/DX11/NVScaler.h \
    $$PWD/code/DX11/NVSharpen.h \
    $$PWD/code/DX11/nvidiaimagescaling.h \
    $$PWD/code/common/Image.h \
    $$PWD/code/third_party/tinyexr/deps/miniz/miniz.h \
    $$PWD/code/third_party/tinyexr/tinyexr.h


SOURCES += \
    $$PWD/code/DX11/AppRenderer.cpp \
    $$PWD/code/DX11/BilinearUpscale.cpp \
    $$PWD/code/DX11/DeviceResources.cpp \
    $$PWD/code/DX11/NVScaler.cpp \
    $$PWD/code/DX11/NVSharpen.cpp \
    $$PWD/code/DX11/nvidiaimagescaling.cpp \
    $$PWD/code/common/Image.cpp \
    $$PWD/code/third_party/tinyexr/deps/miniz/miniz.c










