#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-or-later
# copyright 2025 mannikim <mannikim[at]proton[dot]me>
# this file is part of vrng.h
# see the bottom of the `vrng.h` file for the license text

# adds a prefix to all vrng functions and macros

prefix="vrng_"
header="// VRNG DEF"

awk -v prefix="$prefix" -v header="$header" '
BEGIN { rep = 0 }; 
{
	if (rep) { 
		# functions
		if ($0 ~ /^\w+\(/) {
			sub(//,prefix)
		}
		# macros
		if ($0 ~ /#define \w+\(/) { 
			match($0, /#define (\w+)\(/, m)
			name = m[1]
			sub(name, prefix name)
		}
	} 
	if ($0 ~ header) {
		rep = 1
	}
	print 
} 
' vrng.h
