#Write a shell script to collect n number of years from command line argument and
#calculates which years are leap years.
is_leap_year() {
	year=$1
	if (( year % 400 == 0 )) || (( year % 4 == 0 && year % 100 != 0 )); then
        echo "$year is a Leap Year"
    else
        echo "$year is NOT a Leap Year"
    fi
}

if [ $# -eq 0 ]; then
    echo "Year not provided"
    exit 1
fi

for year in "$@"; do
    is_leap_year "$year"
done
