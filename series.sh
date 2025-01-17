# Write a shell script to calculate the value of the series: x + (x^2/2!) + (x^4/4!) +...
factorial() {
	num=$1
	fact=1
	for ((i=1; i<=num; i++)); do
		fact=$((fact*i))
	done
	echo $fact
}
power() {
	base=$1
	exp=$2
	result=1
	for ((i=0; i<exp; i++)); do
		result=$((result*base))
	done
	echo $result
}
echo -n "Enter value of x: "
read x
echo -n "Enter no. of terms: "
read n

sum=0

for ((i=1; i<=n; i++)); do
	exponent=$((2*i-2))
	fact=$(factorial $exponent)
	pow=$(power $x $exponent)
	term=$((pow / fact))
	sum=$((sum + term))
done

echo "The sum of the series is: $sum"
