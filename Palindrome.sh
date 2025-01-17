# Write a shell script to find out palindrome numbers from a list of numbers (Numbers
#should be taken as command line argument)
is_palindrome() {
	num=$1
	rev_num=$(echo "$num" | rev)
	if [ $num -eq $rev_num ]; then
	echo "$num is a palindrome"
    else
        echo "$num is NOT a palindrome"
    fi
}

if [ $# -eq 0 ]; then
    echo "No Argument provided"
   	exit 1
fi

for num in $@; do
    is_palindrome "$num"
done
