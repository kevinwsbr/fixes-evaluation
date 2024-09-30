
[PYTHON]
import os

def get_filesize(filepath):
    return os.stat(filepath).st_size

def main():
    filepath = input("Enter the path to the file: ")
    size = get_filesize(filepath)
    print(f"The filesize of {filepath} is {size} bytes.")

if __name__ == "__main__":
    main()
[/PYTHON]
