#!/bin/sh
set -eu

export ASAN_OPTIONS=detect_leaks=1:halt_on_error=1:abort_on_error=1
export UBSAN_OPTIONS=halt_on_error=1:abort_on_error=1

exec ./cpp_asan_test
