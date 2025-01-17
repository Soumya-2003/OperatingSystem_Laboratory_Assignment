#Write a shell script to determine the Grade as per WBUT rule. Students name, roll no
#and marks are taken from an input file and output will store as student name , roll no,
#marks and grade format in a file.( using case)
#!/bin/bash

# Check if input file is provided
if [ $# -eq 0 ]; then
    echo "No input file provided"
    exit 1
fi

input_file="$1"
output_file="graded_students.txt"

# Check if the input file exists
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found!"
    exit 1
fi

# Function to determine grade based on marks
calculate_grade() {
    marks=$1
    case $marks in
        9[0-9]|100) echo "O (Outstanding)";;
        8[0-9]) echo "E (Excellent)";;
        7[0-9]) echo "A (Very Good)";;
        6[0-9]) echo "B (Good)";;
        5[0-9]) echo "C (Average)";;
        4[0-9]) echo "D (Pass)";;
        *) echo "F (Fail)";;
    esac
}

echo "Name | Roll No | Marks | Grade" > "$output_file"

while IFS='|' read -r name roll marks; do
    # Trim spaces
    name=$(echo "$name" | xargs)
    roll=$(echo "$roll" | xargs)
    marks=$(echo "$marks" | xargs)

    # Skip header line (optional)
    if [[ "$name" == "Name" || "$roll" == "Roll No" ]]; then
        continue
    fi

    # Calculate grade
    grade=$(calculate_grade "$marks")

    # Store the result in the output file
    echo "$name | $roll | $marks | $grade" >> "$output_file"
done < "$input_file"

# Display the results
cat "$output_file"


