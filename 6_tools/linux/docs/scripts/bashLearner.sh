#!/bin/bash
# This is a memo file for shell script grammer and tricks

die()
{
  local _ret=$2
  echo $_ret
  test -n "$_ret" || _ret=1
  test "$_PRINT_HELP" = yes && print_help >&2
  echo "$1" >&2
  exit ${_ret}
}

die "yes" 1


