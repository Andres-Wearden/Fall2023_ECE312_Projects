#!/bin/bash

LIB_DIR="helper_files"
. "$LIB_DIR"/library.sh

declare -a SAMPLE_TEST_CASES=('Test01' \
'Test02');
CPP_FILE_NAME="Project1.cpp"


test_timeout_seconds=3

perform_test_on_this_submission()
{
    enable_throwing_errors

	this_dir=$(pwd)
    total_num=0
    correct_num=0
    submission_name="${PWD##*/}"

    cp "$main_dir/helper_files/Helpers.h" "$main_dir/helper_files/main.cpp" "$main_dir/helper_files/Makefile" .
    if [[ $TA_MODE == true ]]; then
        make > /dev/null 2>&1
    else
        make
    fi
    rm *.h *.cpp Makefile

    for t_dir in "$tests_dir"/*/
    do
        cp "$t_dir/strings.txt" "$t_dir/superstrings.txt" "$t_dir/output.txt" .

        total_num=$(($total_num+1))
        timeout $test_timeout_seconds ./a.out > actual_output.txt || true
        cat output.txt > expected_output.txt
        printf "\n\n\n$t_dir\n" >> output_diff.txt

        if [[ $TA_MODE == true ]]; then
            diff -iuBbN expected_output.txt actual_output.txt >> output_diff.txt &&
                correct_num=$(($correct_num+1)) || true
        else
            diff -iuBbN expected_output.txt actual_output.txt >> output_diff.txt &&
                correct_num=$(($correct_num+1)) || echo "error on $t_dir"
        fi

    done
    rm -rf a.out strings.txt superstrings.txt output.txt actual_output.txt expected_output.txt
    echo "\"$submission_name\", \"$correct_num\", \"$total_num\"" >> "$brief_feedback_file"
}


main "$@"
