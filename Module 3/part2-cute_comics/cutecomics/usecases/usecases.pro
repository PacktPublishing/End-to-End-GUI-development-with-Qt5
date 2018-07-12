TEMPLATE = subdirs

include(usecases.pri)

SUBDIRS += \
    usecases_add_panel_to_page

DISTFILES += $$PWD/features/* \
    features/add_character_to_characters_list.feature
