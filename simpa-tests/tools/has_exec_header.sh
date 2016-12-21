#!/bin/sh

dd if="$1" bs=1 skip=0 count=10  2>/dev/null | egrep '^(#\!/usr/bin|#\!/bin|#\!/usr/local/bin)' 2>&1 > /dev/null

