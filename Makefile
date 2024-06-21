DEFINES+=PROJECT_CONF_H=\"project-conf.h\"

all: mqtt_node

APPS += mqtt

# Linker size optimization
SMALL = 1

CONTIKI_WITH_IPV6 = 1

ifeq ($(PREFIX),)
 PREFIX = fd00::1/64
endif

CONTIKI = ../../contiki

include $(CONTIKI)/Makefile.include
