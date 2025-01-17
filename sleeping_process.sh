#Write a shell script to display the process which are sleeping(The status of process is S)
echo "Sleeping processes (Status: S)"
ps -e -o pid,user,stat,cmd | awk '$3 ~ /^S/ {print $0}'
