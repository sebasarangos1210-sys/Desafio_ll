TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        MainPrueba.cpp \
        MensajePublicitario.cpp \
        album.cpp \
        artista.cpp \
        cancion.cpp \
        clases_credito_mensajepublicitario.cpp \
        credito.cpp \
        fuentereproduccion.cpp \
        listareproduccion.cpp \
        sesionreproduccion.cpp \
        usuario.cpp

HEADERS += \
    MensajePublicitario.h \
    album.h \
    artista.h \
    cancion.h \
    credito.h \
    fuentereproduccion.h \
    listareproduccion.h \
    sesionreproduccion.h \
    usuario.h
