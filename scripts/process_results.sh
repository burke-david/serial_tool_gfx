#!/bin/bash

# Create a variable that contains the build/test/results directory
results_dir="build/test/results"

#  Create a variable that contains the build/test/process directory
process_dir="build/test/process"

script_dir="scripts"

# Create a variable containing a markdown file in the process_dir called results.md
results_md="$process_dir/results.md"

# Initialize counters
total_tests=0
total_passed=0
total_failed=0
total_ignored=0

# Run the test.sh script
$script_dir/test.sh

# Iterate over all *.pass and *.fail files
for file in "$results_dir"/*.pass "$results_dir"/*.fail; do
  # Check if the file exists before trying to process it
  if [ -f "$file" ]; then
    # Extract the counts from the file
    total=$(awk -F': ' '/:total:/ {print $2}' "$file")
    passed=$(awk -F': ' '/:passed:/ {print $2}' "$file")
    failed=$(awk -F': ' '/:failed:/ {print $2}' "$file")
    ignored=$(awk -F': ' '/:ignored:/ {print $2}' "$file")

    # Add the counts to the totals
    ((total_tests+=total))
    ((total_passed+=passed))
    ((total_failed+=failed))
    ((total_ignored+=ignored))
  fi
done

# Create the process directory if it does not exist
if [ ! -d "$process_dir" ]; then
  mkdir -p "$process_dir"
fi

# Create the results markdown file
touch "$results_md"

# Write the test results to the results markdown file
echo "TEST RESULTS:" > "$results_md"
echo "Total tests: $total_tests" >> "$results_md"
echo "Passed: $total_passed" >> "$results_md"
echo "Failed: $total_failed" >> "$results_md"
echo "Ignored: $total_ignored" >> "$results_md"

# Add an extra blank line to the results markdown file
echo "" >> "$results_md"

# Run test coverage analysis
# Use the "ceedling gcov:all" command to generate the coverage report
ceedling gcov:all


# if the gcov command fails, print an error message else generate the coverage report
if [ $? -ne 0 ]; then
  echo "Error: gcov command failed."
else
  # Use the "ceedling utils:gcov" command to generate the coverage report and dump to the results markdown file
  ceedling utils:gcov >> "$results_md"
fi


