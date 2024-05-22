#!/bin/bash -ev
if [ $# != 3 ]
then
	echo "HELP: ./build.sh <build_platform> <host_platform> <target_platform>"
	exit 1
fi
PROG_SUFFIX=
SUFFIX=
if [ "$2" != "$3" ]
then
	RELEASE=release_$2_cross_$3
else
	RELEASE=release_$2_native
fi
mkdir -p test include $RELEASE
cp -r include_generic/* platform_$1/include/* include
bin/$1_native/scpp$PROG_SUFFIX scpp/main.c test/scpp.i
bin/$1_native/scpp$PROG_SUFFIX platform_$2/scc_main.c test/scc.i
bin/$1_native/scpp$PROG_SUFFIX platform_$2/asm/main.c test/asm.i
bin/$1_native/scc$PROG_SUFFIX test/scpp.i test/scpp.asm
bin/$1_native/scc$PROG_SUFFIX test/scc.i test/scc.asm
bin/$1_native/scc$PROG_SUFFIX test/asm.i test/asm.asm
bin/$1_native/asm$PROG_SUFFIX test/scpp.asm test/scpp$PROG_SUFFIX
bin/$1_native/asm$PROG_SUFFIX test/scc.asm test/scc$PROG_SUFFIX
bin/$1_native/asm$PROG_SUFFIX test/asm.asm test/asm$PROG_SUFFIX
cp -r platform_$2/include/* include
test/scpp$PROG_SUFFIX scpp/main.c test/scpp.i
test/scpp$PROG_SUFFIX platform_$3/scc_main.c test/scc.i
test/scpp$PROG_SUFFIX platform_$3/asm/main.c test/asm.i
test/scc$PROG_SUFFIX test/scpp.i test/scpp.asm
test/scc$PROG_SUFFIX test/scc.i test/scc.asm
test/scc$PROG_SUFFIX test/asm.i test/asm.asm
test/asm$PROG_SUFFIX test/scpp.asm $RELEASE/scpp$SUFFIX
test/asm$PROG_SUFFIX test/scc.asm $RELEASE/scc$SUFFIX
test/asm$PROG_SUFFIX test/asm.asm $RELEASE/asm$SUFFIX
