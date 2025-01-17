#Write a shell script to select greatest and lowest numbers from a set of numbers which are present in a file.
if [ $# -eq 0 ]; then
    echo "No file provided"
    exit 1
fi

input_file="$1"
if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found!"
    exit 1
fi

read lowest highest < <(awk 'NR==1 {min=$1; max=$1} {if ($1 < min) min=$1; if($1 > max) max=$1} END {print min, max}' "$input_file")
echo "Lowest number: $lowest"
echo "Greatest number: $highest"
