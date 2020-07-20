#!/bin/bash
#
# @date 2020/07/20
# @author changyanlong q531365872 github.com/numberwolf
#

commitMsg=${1:-"push at `date`"}

git add -A
git commit -m "${commitMsg}"
git push origin master
