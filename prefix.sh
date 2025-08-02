#!/bin/sh
# adds a prefix to all vrng functions and macros
# this can't handle changing function calls. thankfully, we have no such cases

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
