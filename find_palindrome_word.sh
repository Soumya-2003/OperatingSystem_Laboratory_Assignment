# a)Write a shell script to find out the palindrome word from a file (omit . or ; or , after the word)
echo -n "Enter the filename: "
read filename

if [ ! -f "$filename" ]; then
    echo "File does not exist!"
    exit 1
fi

is_palindrome() {
	word=$1
	length=${#word}
	
	for ((i=0, j=length-1; i<j; i++, j--)); do
		if [ "${word:i:1}" != "${word:j:1}" ]; then
            return 1
        fi
    done
    return 0
}

echo "Palindrome words found:"
cat "$filename" | tr -d '.,;' | tr ' ' '\n' | while read word; do
    if is_palindrome "$word"; then
        echo "$word"
    fi
done
