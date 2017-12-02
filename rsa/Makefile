#
# Makefile for rsa stuff
#

#include $(TOPDIR)/config.mk

ALL	 = rsa
LIB   = rsa.a
OBJS += bignum.o rsa.o base64.o read.o #decryto.o

$(ALL): $(OBJS) test.o

#########################################################################

.depend: Makefile $(OBJS:.o=.c)
	     $(CC) -M $(CFLAGS) $(OBJS:.o=.c) > $@

sinclude .depend

#########################################################################

