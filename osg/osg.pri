INCLUDEPATH+=\
    $$PWD/include \

LIBS+= \
    -L$$PWD/lib/ -lOpenThreads -losg -losgAnimation -losgDB -losgFX -losgGA -losgManipulator -losgParticle -losgPresentation -losgQOpenGL -losgShadow -losgSim -losgTerrain -losgText -losgUI -losgUtil -losgViewer -losgVolume -losgWidget
