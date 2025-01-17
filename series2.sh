#!/bin/bash

# Function to calculate power (floating point)
power() {
    echo "scale=6; $1 ^ $2" | bc
}

# Read inputs
echo -n "Enter value of x: "
read x
echo -n "Enter the number of terms: "
read n

sum=1  # The first term of the series is always 1

for ((i=2; i<=n; i++)); do
    exponent=$i  # Current exponent in the term
    base=$(echo "scale=6; $x / 2" | bc)  # Compute (x/2) using bc
    term=$(power "$base" "$exponent")  # Compute (x/2)^i using power function

    # Alternate sign for even and odd powers
    if (( i % 2 == 0 )); then
        sum=$(echo "scale=6; $sum + $term" | bc)
    else
        sum=$(echo "scale=6; $sum - $term" | bc)
    fi
done

# Print the result
echo "The sum of the series is: $sum"

