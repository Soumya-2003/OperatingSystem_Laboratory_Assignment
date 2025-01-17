#Write a shell script to find the number of characters, words and lines in a set of files
#given by user through the command line argument.
if [ $# -eq 0 ]; then
    echo "No file provided"
    exit 1
fi

for file in "$@"; do
	if [ -f "$file" ]; then
		echo "File: $file"
		wc "$file"
		echo "----------------------------------"
	else
		echo "Error: $file not found!"
	fi
done
