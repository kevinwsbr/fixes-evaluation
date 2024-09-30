[PYTHON]
import os

def main():
    # Get the current working directory
    current_dir = os.getcwd()
    print("Current directory:", current_dir)

if __name__ == "__main__":
    main()
[/PYTHON]
[TESTS]
# Test case 1:
current_dir = os.getcwd()
print("Current directory:", current_dir)

# Test case 2:
new_dir = "new_directory"
os.chdir(new_dir)
current_dir = os.getcwd()
print("Current directory:", current_dir)

# Test case 3:
os.chdir(current_dir)
current_dir = os.getcwd()
print("Current directory:", current_dir)
[/TESTS]
