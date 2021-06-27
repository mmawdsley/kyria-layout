#!/usr/bin/env bash

set -o nounset
set -o errexit

qmk flash -kb kyria/rev1 -km mmawdsley -bl dfu
