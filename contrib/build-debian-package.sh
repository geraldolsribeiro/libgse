#!/bin/sh
set -eu

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
ROOT_DIR="$(CDPATH= cd -- "${SCRIPT_DIR}/.." && pwd)"
LOG="${SCRIPT_DIR}/debian-build.log"

rm -rf "${SCRIPT_DIR}/build"
rm -f "${SCRIPT_DIR}"/*.deb "${SCRIPT_DIR}"/*.changes "${SCRIPT_DIR}"/*.buildinfo

cd "${ROOT_DIR}"

build_cmd="cd contrib && debuild -us -uc"
printf '%s\n' "Running: ${build_cmd}"
sh -c "${build_cmd}" | tee "${LOG}"
