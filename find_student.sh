#In an input file, there are some records of students (Roll | Name | Marks). Find the
#student name and roll number of the student who gets the highest marks.
if [ $# -eq 0 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

input_file="$1"
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found!"
    exit 1
fi

highest_student=$(awk -F'|' 'NR>1 {if ($3 > max) {max=$3; roll=$1; name=$2}} END {print roll, name, max}' "$input_file")
echo "Student with highest marks:"
echo "Roll No | Name  | Marks"
echo "$highest_student"
