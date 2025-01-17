#Write a shell script to check if a given date is valid or not.
is_valid_date() {
    day=$1
    month=$2
    year=$3
    
    if ! [[ $day =~ ^[0-9]+$ && $month =~ ^[0-9]+$ && $year =~ ^[0-9]+$ ]]; then
        echo "Invalid date format! Please enter numeric values."
        return 1
    fi
    
    if (( month < 1 || month > 12 )); then
        echo "Invalid month! Must be between 1 and 12."
        return 1
    fi
    
    case $month in
        1|3|5|7|8|10|12) max_days=31 ;;
        4|6|9|11) max_days=30 ;;
        2) max_days=28;;
        *) echo "Invalid month!"; return 1 ;;
    esac
    
    if (( day < 1 || day > max_days )); then
        echo "Invalid day! Must be between 1 and $max_days for the given month."
        return 1
    fi

    echo "The date $day-$month-$year is valid."
    return 0
}

read -p "Enter date (DD MM YYYY): " day month year
is_valid_date "$day" "$month" "$year"
