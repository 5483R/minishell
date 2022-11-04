#!/bin/bash
while true
do
	leaks minishell | grep bytes
	sleep 1
	clear
done

