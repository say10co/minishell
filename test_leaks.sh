#!/bin/bash
while [ 1 ]
do
  res=$(leaks minishell 2> /dev/null | grep '\leaked bytes.$')
  if [[ $res ]];
	then
		printf " %s\n" "$res"
	else
		echo "ok"
	fi
  sleep 1
done
