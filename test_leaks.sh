#!/bin/bash
while [ 1 ]
do
  res=$(leaks minishell 2> /dev/null | grep '\leaked bytes.$')
	printf ">>> %s\n" "$res"
  sleep 1
done
