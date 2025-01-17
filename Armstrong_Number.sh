# Write a Shell Script to collect n numbers from command line argument and check
#which are the Armstrong numbers.

is_armstrong() {
	num=$1
	sum=0
	temp=$num
	num_digits=${#num}
	local digit
	
	while [ $temp -gt 0 ]; do
        digit=$((temp % 10))
        sum=$((sum + digit ** num_digits))  
        temp=$((temp / 10))
    done
    
    if [ $sum -eq $num ]; then
        echo "$num is an Armstrong number"
    else
        echo "$num is NOT an Armstrong number"
    fi
}

if [ $# -eq 0 ]; then
    echo "Please provide numbers as command-line arguments."
    exit 1
fi

# Iterate over all command-line arguments
for num in "$@"; do
    is_armstrong $num
done
