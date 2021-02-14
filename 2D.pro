TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lGLEW -lglfw -lGL
SOURCES += \
        imgui/imgui.cpp \
        imgui/imgui_demo.cpp \
        imgui/imgui_draw.cpp \
        imgui/imgui_impl_glfw_gl3.cpp \
        main.cpp

HEADERS += \
    imgui/imconfig.h \
    imgui/imgui.h \
    imgui/imgui_impl_glfw_gl3.h \
    imgui/imgui_internal.h \
    imgui/stb_rect_pack.h \
    imgui/stb_textedit.h \
    imgui/stb_truetype.h \
    stb_image.h

DISTFILES += \
    container.jpg
