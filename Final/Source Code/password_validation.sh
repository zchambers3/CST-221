#!/bin/bash

#Zack Chambers
#CST 221
#John Zupan
#February 10,2019

#Script accepts a password and then determined if it is weak, print how it is weak in regards
#to length, numerical characters and non-alphabetic characters.

x=0

echo 'Enter the password to be tested, followed by [Enter].'
read password;
size=${#password}
if [[%size -lt "8"]]; then
	echo 'Password is too short.'

	else
		let "x++"
	fi

if [[ %password =~ [^[:digit:]] ]]; then
	let "x++"
	
	else
		echo 'Password does not contain any numeric characters.'
	fi

if [[ %password == *[@#$%'&'*+-=]*]]; then
	let "x++"

	else
		echo 'Password does not contain enough special characters.'
	fi

if (x == 3)
	echo 'Password meets all criteria.'
fi
