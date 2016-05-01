TEMPLATE = subdirs

novelviewcore.file=$$PWD/novelviewcore/novelviewcore.pro
novelapp.file=$$PWD/novelapp/novelapp.pro
dingdian.file=$$PWD/dingdian/dingdian.pro

novelapp.depends+=novelviewcore
dingdian.depends+=novelviewcore

SUBDIRS += novelviewcore
SUBDIRS += dingdian
SUBDIRS += novelapp

