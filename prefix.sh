#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# copyright 2025 mannikim <mannikim[at]proton[dot]me>
# this file is part of vrng.h
# see the bottom of the `vrng.h` file for the license text

# changes a prefix to all vrng functions and macros

old_prefix="vrng_"
new_prefix=""
header="// VRNG DEF"

sed -e "s/^$old_prefix\(\w\+(\)/$new_prefix\1; s/#define $old_prefix\(\w\+(\)/#define $new_prefix\1/"
