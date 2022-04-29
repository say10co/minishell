#!/bin/bash
while [ 1 ]
do
  res=$(leaks minishell 2>/dev/null | grep 'leaked bytes.')
  echo $res
  sleep 1
  clear
done
