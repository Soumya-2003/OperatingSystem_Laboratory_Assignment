#Write a shell script to take student records (Roll, Name, Marks) as a input file and
#update the marks of a student according to the user choice.
FILE="students1.txt"
if [ ! -f "$FILE" ]; then
	echo "Roll Name Marks" > "$FILE"
	echo "1001 John 85" >> "$FILE"
    echo "1002 Alice 90" >> "$FILE"
    echo "1003 Bob 78" >> "$FILE"
    echo "1004 Charlie 88" >> "$FILE"
    echo "Student records file created: students.txt"
fi

display_records() {
	echo "----------------------------"
    echo "Current Student Records:"
    cat "$FILE"
    echo "----------------------------"
}

update_marks() {
	echo -n "Enter Roll Number of the student to update: "
    read roll
    
    # Check if the roll number exists
    grep -q "^$roll " "$FILE"
    if [ $? -ne 0 ]; then
        echo "Error: Student with Roll Number $roll not found!"
        return
    fi
    
    echo -n "Enter new marks: "
    read new_marks
    
    awk -v r="$roll" -v m="$new_marks" '
    $1 == r { $3 = m }
    { print }' "$FILE" > temp.txt && mv temp.txt "$FILE"

    echo "Marks updated successfully!"
}

while true; do
    echo "1. Display Student Records"
    echo "2. Update Student Marks"
    echo "3. Exit"
    echo -n "Enter your choice: "
    read choice

    case $choice in
        1) display_records ;;
        2) update_marks ;;
        3) echo "Exiting..."; exit ;;
        *) echo "Invalid choice! Please enter a valid option." ;;
    esac
done
