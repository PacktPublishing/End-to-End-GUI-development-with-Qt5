# part2-cute_comics.pro
TEMPLATE = subdirs

SUBDIRS += \
    cutecomics/entities \
    cutecomics/usecases \
    cutecomics/gui \
    ccpanels \
    cccomposer \
    ccscripter

QML_IMPORT_PATH += $$PWD
