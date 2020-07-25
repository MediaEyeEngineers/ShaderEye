#!/bin/bash
#
# @date 2020/07/20
# @author changyanlong q531365872 github.com/numberwolf
#

commitMsg=${1:-"push at `date`"}
targetBranch=${2:-"develop"}

git add -A
git commit -m "${commitMsg}"
git push origin ${targetBranch}

echo "FIN"
