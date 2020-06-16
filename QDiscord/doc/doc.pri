include(../config.pri)

OTHER_FILES += $$PWD/mainpage.dox
OTHER_FILES += $$PWD/installing.dox
OTHER_FILES += $$PWD/usage.dox
OTHER_FILES += $$PWD/versioning.dox
OTHER_FILES += $$PWD/examples.dox

docs.commands += "QT_INSTALL_DOCS=$$[QT_INSTALL_DOCS] QDISCORD_LIBRARY_MAJOR=$${QDISCORD_LIBRARY_MAJOR} QDISCORD_LIBRARY_MINOR=$${QDISCORD_LIBRARY_MINOR} doxygen"
docs.CONFIG += phony
QMAKE_EXTRA_TARGETS += docs
