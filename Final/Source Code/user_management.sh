#!/bin/bash

#Zack Chambers
#CST 221
#John Zupan
#February 10, 2019

#Add users to the system from a file, creating respective home directories as they are created.
#Deleting a user, deletes their home directory.

#Run: ./user_management.sh users.txt

group="testGroup"

if grep -q $group /etc/group
then
	echo "group exists"
else
	groupadd $group
fi

filename="users.txt"
while read -r username password
do
	name="$username"
	pass="$password"
	echo "Username: $name"
	echo "Password: $pass"

	if [ $(id -u) -eq 0 ]; then
		egrep "^$name" /etc/passwd >/devl/null
		if [ $? -eq 0 ]; then
			echo "$name exists!"
			exit 1
		else
			useradd -m -p $pass $name
			[ $? -eq 0 ] && echo "User has been added to system!" || echo "Failed to add a user!"
		fi
	else
		echo "Only root may add a user to the system"
		exit 2
	fi
	usermod -aG $group $name
done < "$filename"

filename="users.txt"
while read -r username password
do
	name="$username"
	pass="$password"
	userdel -r $name
	echo "User Deleted."
done < "$filename"

if grep -q $group /etc/group
then
	groupdel $group
else
	echo "Group does not exist."
fi
