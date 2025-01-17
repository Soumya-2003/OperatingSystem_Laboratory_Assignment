# Write a shell script to calculate the first n numbers of the Fibonacci series .i.e. 0 1 1 2
#3 5 8... and store the result in an output file.
output_file="fibonacci_output.txt"
generate_fibonacci() {
    n=$1  
    a=0
    b=1
    
    echo "Fibonacci Series (First $n terms):" > "$output_file"
    echo -n "$a $b " >> "$output_file"
    
    for ((i=3; i<=n ;i++)); do
    	fib=$((a+b))
    	echo -n "$fib " >> $output_file
    	a=$b
    	b=$fib
    done
}
echo -n "Enter the number of terms: "
read n

if [[ ! "$n" =~ ^[0-9]+$ ]] || [[ "$n" -lt 1 ]]; then
    echo "Please enter a valid positive integer."
    exit 1
fi

generate_fibonacci "$n"
