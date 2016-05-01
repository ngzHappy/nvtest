TEMPLATE = subdirs

novelviewcore.file=$$PWD/novelviewcore/novelviewcore.pro
novelapp.file=$$PWD/novelapp/novelapp.pro

novelapp.depends+=novelviewcore

SUBDIRS += novelviewcore \
    dingdian
SUBDIRS += novelapp

