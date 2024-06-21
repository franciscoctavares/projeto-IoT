DEFINES+=PROJECT_CONF_H=\"project-conf.h\"

all: mqtt-example

APPS += mqtt

# Linker size optimization
SMALL = 1

CONTIKI_WITH_IPV6 = 1

CFLAGS += -DUIP_FALLBACK_INTERFACE=rpl_interface
#PROJECT_SOURCEFILES += slip-bridge.c #httpd-simple.c

ifeq ($(PREFIX),)
 PREFIX = fd00::1/64
endif

CONTIKI = ../../contiki

include $(CONTIKI)/Makefile.include
