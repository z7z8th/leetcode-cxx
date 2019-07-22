#!/bin/bash

find . -regextype posix-extended -type d -regex '.*\.(git|vscode)' -prune -o -type f -regex '(.*\.(o|exe|obj|ilk|pdb))|\./objs/.*' -print -exec rm {} \;

