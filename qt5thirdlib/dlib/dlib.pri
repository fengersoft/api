INCLUDEPATH+=\
   $$PWD/include/

LIBS+= \
-L$$PWD/lib/ -ldlib \
-lImm32  \
-lgdi32 \
-lwinmm \
-lcomctl32
