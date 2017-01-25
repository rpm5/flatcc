#!/usr/bin/env bash

set -e
cd `dirname $0`/..
./scripts/build.sh

valgrind="valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes"

mkdir -p build/tmp/leakcheck-full
$valgrind \
    bin/flatcc_d -a -o build/tmp/leakcheck-full --prefix zzz --common-prefix \
    hello test/monster_test/monster_test.fbs
