TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
QT += core
QT += gui

LIBS = -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
INCLUDEPATH += /usr/local/include/opencv

HEADERS += Headers/Layer.h\
    Headers/Neuron.h\
    Headers/Pattern.h \
    Headers/Sigmoid.h \
    Headers/Backpropagation.h\
    Headers/readMnist.h\
    Headers/opencvpaint.h \
    Headers/Learning.h

FORMS +=


SOURCES +=Src/Main.cpp \
    Src/Neuron.cpp \
    Src/Pattern.cpp \
    Src/Layer.cpp \
    Src/Backpropagation.cpp\
    Src/opencvpaint.cpp\
    Src/learning.cpp

