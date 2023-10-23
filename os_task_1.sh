case $1 in
"-p")
	a="$(ls -F /proc |grep /|tr -d / | sort -V 2> /dev/null )"
	echo PID PPID UID USER COMM
	
	for i in $a
	do
		if [ -e /proc/$i/stat ]
		then
			if [ -e /proc/$i/comm ]
			then
				b="$(cat /proc/$i/stat |cut -f 1,4 -d " " 2> /dev/null )"
				ui="$(id -u $u 2> /dev/null 2> /dev/null )"
				u="$(ls l-dl /proc/$i |cut -f 3 -d " " 2> /dev/null )"
				c="$(cat /proc/$i/comm 2> /dev/null )"
				echo $b $ui "("$u")" $c
			fi
		fi
done;;
"-u")
	echo PID COMM CWD
	u="$(whoami)"
	a="$(ls -F /proc |grep /|tr -d / | sort -V 2> /dev/null)"

	for i in $a
	do
		 if [ -e /proc/$i/comm ]; then
		 	if [ -e /proc/$i/status ]; then
		 		if [ $UID = "$(cat /proc/$i/status |grep -e "Uid" |cut -f2)" ]; then
		 			if [ -e /proc/$i//cwd ]; then
		 				c="$(cat /proc/$i/comm 2> /dev/null)"
		 				p="$(cd /proc/$i/cwd 2> /dev/null ; pwd -P 2> /dev/null)"
		 				echo $i $c $p
		 			fi
		 		fi
		 	fi
		 fi
done;;

*) echo "zla opcja"
esac
