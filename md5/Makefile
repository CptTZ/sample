######################################################################
# Copyright (C) 2016. Shanghai Feixun Communication Co.,Ltd.
#
# DISCREPTION   : This file is use to generate DownloadID.
# AUTHOR        : maoyuan.li <maoyuan.li@feixun.com.cn>
# CREATED DATE  : 2016-10-28
# MODIFIED DATE : 
######################################################################

all: libDownloadID_X86.so libDownloadID_X64.so
#all: libDownloadID_X64.so

libDownloadID_X64.so: DownloadID_X64.o md5_X64.o
	$(CC) -shared -fPIC -o $@ $^

DownloadID_X64.o: DownloadID.c
	$(CC) -fPIC -c $^ -o $@

md5_X64.o: md5.c
	$(CC) -fPIC -c $^ -o $@
	
libDownloadID_X86.so: DownloadID_X86.o md5_X86.o
	$(CC) -shared -m32 -fPIC -o $@ $^

DownloadID_X86.o: DownloadID.c
	$(CC) -fPIC -m32 -c $^ -o $@

md5_X86.o: md5.c
	$(CC) -fPIC -m32 -c $^ -o $@

install:
	cp libDownloadID_X64.so ~/mylib
	cp libDownloadID_X86.so ~/mylib
	cp libDownloadID_X86.so ./test/x86
	cp libDownloadID_X64.so ./test/x64

clean:
	rm -f *.o .*.depend *.a *.so

