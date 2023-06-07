#!/usr/bin/env bash

set -o nounset
set -o errexit

qmk flash -kb splitkb/kyria/rev1 -km mmawdsley -bl dfu
