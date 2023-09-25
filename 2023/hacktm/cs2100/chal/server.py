#!/usr/bin/env python3
from tempfile import NamedTemporaryFile
from subprocess import check_output, Popen, STDOUT, DEVNULL


def print_banner():
    print("""
       _____  _____ ___  __  ___   ___  
      / ____|/ ____|__ \/_ |/ _ \ / _ \ 
     | |    | (___    ) || | | | | | | |
     | |     \___ \  / / | | | | | | | |
     | |____ ____) |/ /_ | | |_| | |_| |
      \_____|_____/|____||_|\___/ \___/ 
    """)


def main():
    print_banner()
    s = input("Please enter your code (hex-encoded):\n")
    # Remove all whitespace
    s = ''.join(s.split())
    try:
        d = bytes.fromhex(s)
        print(d)
    except ValueError:
        print("Invalid hex!")
        exit()

    with NamedTemporaryFile() as temp_file:
        temp_file.write(d)
        temp_file.flush()
        filename = temp_file.name

        print("\nOutput:")
        with Popen(["./main", filename], stderr=STDOUT, stdin=DEVNULL) as process:
            process.wait()


if __name__ == "__main__":
    main()
