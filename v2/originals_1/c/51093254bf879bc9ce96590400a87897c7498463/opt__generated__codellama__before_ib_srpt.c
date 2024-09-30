 
[PYTHON]
import sys
from nltk.tokenize import word_tokenize

def main():
    for line in sys.stdin:
        print(' '.join(word_tokenize(line)))

if __name__ == "__main__":
    main()
[/PYTHON]
[TESTS]
# Test case 1:
# Test that the script returns the expected output when given a simple string.
echo "This is a test." | python tokenize.py

# Expected output:
# This is a test .

# Test case 2:
# Test that the script returns the expected output when given a string with multiple sentences.
echo "This is a test. This is another test." | python tokenize.py

# Expected output:
# This is a test . This is another test .

# Test case 3:
# Test that the script returns the expected output when given a string with punctuation.
echo "This is a test! This is another test?" | python tokenize.py

# Expected output:
# This is a test ! This is another test ?

# Test case 4:
# Test that the script returns the expected output when given a string with numbers.
echo "12345 This is a test." | python tokenize.py

# Expected output:
# 12345 This is a test .

# Test case 5:
# Test that the script returns the expected output when given a string with multiple words.
echo "This is a test. This is another test. This is a third test." | python tokenize.py

# Expected output:
# This is a test . This is another test . This is a third test .
[/TESTS]
