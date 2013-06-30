TEMPLATE      = lib
CONFIG        += plugin
HEADERS       = %ProjectName:l%.h controlblock.h
SOURCES       = %ProjectName:l%.cpp
FORMS         = %ProjectName:l%editor.ui
TARGET        = $$qtLibraryTarget(%ProjectName:l%plugin)

target.path = ../plugins
INSTALLS += target
