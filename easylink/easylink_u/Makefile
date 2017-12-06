EXE = easylink
OBJS = easylink.o list.o session.c

#stdlibc++ known issue: 
#If your program  needs libstdc++, please turn off code optimization
#CFLAGS += -O0

CFLAGS += -I$(ROOTDIR)/user/nvram -I$(ROOTDIR)/user/nvram -I$(ROOTDIR)/user/shared -I$(ROOTDIR)/user/shared/include
LDFLAGS += -L$(ROOTDIR)/user/nvram -lnvram -L$(ROOTDIR)/user/shared -lshared

all: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LDFLAGS) $(CFLAGS)

romfs:
	$(ROMFSINST) /bin/$(EXE)

clean:
	@rm -rf $(EXE)  *.o
