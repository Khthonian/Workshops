import sys


def create_file_with_lines(filename, numLines):
    with open(filename, "w") as file:
        for i in range(1, numLines + 1):
            file.write(f"{i}\n")


filename = "./input.txt"

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Give a number of lines.")
    else:
        param = int(sys.argv[1])
        create_file_with_lines(filename, param)
