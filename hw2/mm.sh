target_path="/ssd/ssd3/ljy/systt/gradebook_2024CMN17.10CSE30601_HW2_2024-06-17-20-30-04"

for dir in "$target_path"/*/; do
    # Check if hw2.c exists in the directory
    if [ -f "$dir/hw2.c" ]; then
        echo "File hw2.c found in directory: $dir"
        last_path=$(basename "$dir")
        echo "$last_path"
        # Perform your next actions here
        cp "$dir/hw2.c" ./
        make
        mv ./bmpfilter ./execu/"$last_path"_bmpfilter
        rm hw2.c
    fi
done