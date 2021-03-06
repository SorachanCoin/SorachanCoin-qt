# Copyright (c) 2009-2010 Satoshi Nakamoto
# Distributed under the MIT/X11 software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

#
# Linux Makefile
#

USE_UPNP:=-
USE_IPV6:=0
USE_LEVELDB=1

BUILD_RELEASE=1
CC=gcc
CXX=g++
xOPT_LEVEL=-O3
VERSION=4

INCLUDEPATHS= \
 -I"/opt/db-4.8.30/include" \
 -I"leveldb/include" \
 -I"leveldb/helpers"

LIBPATHS= \
 -L"/opt/db-4.8.30/lib"

LIBS= \
 -l pthread \
 -l boost_system \
 -l boost_filesystem \
 -l boost_program_options \
 -l boost_thread \
 -l boost_chrono \
 -l ssl \
 -l crypto \
 -l db_cxx

ifeq (${VERSION}, 4)
 DEFS=-w
else
 DEFS=-Wno-delete-incomplete -Wno-deprecated-declarations -Wno-placement-new
endif

ifneq (${USE_IPV6}, -)
 DEFS += -DUSE_IPV6=$(USE_IPV6)
endif

ifneq (${USE_UPNP}, -)
 DEFS += -DUSE_UPNP=$(USE_UPNP)
 LIBS += "/opt/miniupnpc/lib/libminiupnpc.a"
endif

ifeq (${ARCH}, i686)
 EXT_OPTIONS=-msse2
endif

ifneq (${BUILD_RELEASE}, 1)
 DEBUGFLAGS=-g
endif

LIBS+= \
 -l z \
 -l dl \

# Hardening
# Make some classes of vulnerabilities unexploitable in case one is discovered.
#
	# This is a workaround for Ubuntu bug #691722, the default -fstack-protector causes
	# -fstack-protector-all to be ignored unless -fno-stack-protector is used first.
	# see: https://bugs.launchpad.net/ubuntu/+source/gcc-4.5/+bug/691722
	HARDENING=-fno-stack-protector

	# Stack Canaries
	# Put numbers at the beginning of each stack frame and check that they are the same.
	# If a stack buffer if overflowed, it writes over the canary number and then on return
	# when that number is checked, it won't be the same and the program will exit with
	# a "Stack smashing detected" error instead of being exploited.
	HARDENING+=-fstack-protector-all -Wstack-protector

	# Make some important things such as the global offset table read only as soon as
	# the dynamic linker is finished building it. This will prevent overwriting of addresses
	# which would later be jumped to.
	LDHARDENING+=-Wl,-z,relro -Wl,-z,now

	# Build position independent code to take advantage of Address Space Layout Randomization
	# offered by some kernels.
	# see doc/build-unix.txt for more information.
	ifdef PIE
		HARDENING+=-fPIE
		LDHARDENING+=-pie
	endif

	# -D_FORTIFY_SOURCE=2 does some checking for potentially exploitable code patterns in
	# the source such overflowing a statically defined buffer.
	HARDENING+=-D_FORTIFY_SOURCE=2
#

DEFS += -DBOOST_NO_CXX11_SCOPED_ENUMS

# CXXFLAGS
CXXFLAGS= -std=c++1y $(xOPT_LEVEL) $(INCLUDEPATHS) $(DEFS)

# CXXFLAGS can be specified on the make command line, so we use xCXXFLAGS that only
# adds some defaults in front. Unfortunately, CXXFLAGS=... $(CXXFLAGS) does not work.
xCXXFLAGS=$(EXT_OPTIONS) $(DEBUGFLAGS) $(DEFS) $(HARDENING) $(CXXFLAGS)

# LDFLAGS can be specified on the make command line, so we use xLDFLAGS that only
# adds some defaults in front. Unfortunately, LDFLAGS=... $(LDFLAGS) does not work.
xLDFLAGS=$(LDHARDENING) $(LDFLAGS)

OBJS= \
 obj/alert.o \
 obj/version.o \
 obj/checkpoints.o \
 obj/netbase.o \
 obj/addrman.o \
 obj/crypter.o \
 obj/key.o \
 obj/db.o \
 obj/init.o \
 obj/irc.o \
 obj/keystore.o \
 obj/main.o \
 obj/miner.o \
 obj/net.o \
 obj/protocol.o \
 obj/bitcoinrpc.o \
 obj/rpcdump.o \
 obj/rpcnet.o \
 obj/rpcmining.o \
 obj/rpcwallet.o \
 obj/rpcblockchain.o \
 obj/rpcrawtransaction.o \
 obj/script.o \
 obj/sync.o \
 obj/util.o \
 obj/wallet.o \
 obj/walletdb.o \
 obj/noui.o \
 obj/kernel.o \
 obj/pbkdf2.o \
 obj/scrypt.o \
 obj/scrypt-x86.o \
 obj/scrypt-x86_64.o \
 obj/ntp.o \
 obj/stun.o \
 obj/rpccrypt.o \
 obj/base58.o \
 obj/kernel_worker.o \
 obj/ecies.o \
 obj/cryptogram.o \
 obj/ipcollector.o \

all: createdirobj leveldb_build SorachanCoind

ifneq (${USE_LEVELDB}, -) 
 LIBS += "leveldb/libleveldb.a" "leveldb/libmemenv.a"
 DEFS += $(addprefix -I,"leveldb/include") -DUSE_LEVELDB
 DEFS += $(addprefix -I,"leveldb/helpers")
 OBJS += obj/txdb-leveldb.o
 obj/txdb-leveldb.o: leveldb/libleveldb.a
else
 OBJS += obj/txdb-bdb.o
endif

createdirobj:
	@mkdir -p obj

leveldb_build:
	@make -C leveldb
	@make memenv_test -C leveldb

obj/%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

obj/scrypt-x86.o: scrypt-x86.S
	$(CXX) -c $(xCXXFLAGS) -MMD -o $@ $<

obj/scrypt-x86_64.o: scrypt-x86_64.S
	$(CXX) -c $(xCXXFLAGS) -MMD -o $@ $<

SorachanCoind: $(OBJS:obj/%=obj/%)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(LIBPATHS) $^ $(LIBS)

clean:
	rm -rf SorachanCoind
	rm -rf obj/*

FORCE:
