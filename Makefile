CONTIKI_PROJECT = test

all: $(CONTIKI_PROJECT)

CONTIKI_TARGET_SOURCEFILES += dht22.c tsl256x.c

CONTIKI = ../../contiki
include $(CONTIKI)/Makefile.include