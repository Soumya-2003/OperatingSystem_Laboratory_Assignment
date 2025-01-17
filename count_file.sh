#Write a shell script to find the numbers of files are present within a directory and their
#names. Store the output in a file and display it.
if [ $# -eq 0 ]; then
	echo "directory path not given"
	exit 1
fi

dir_path=$1
if [ ! -d $dir_path ]; then
	echo "Error: $dir_path not found!"
	exit 1
fi

output_file="file_list.txt"
file_count=$(find "$dir_path" -maxdepth 1 -type f | wc -l)
file_list=$(find "$dir_path" -maxdepth 1 -type f)

echo "Directory: $dir_path" > "$output_file"
echo "Total number of files: $file_count" >> "$output_file"
echo "File Names:" >> "$output_file"
echo "$file_list" >> "$output_file"
cat "$output_file"
