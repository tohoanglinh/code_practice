#!/bin/python3

def hackerrank_in_a_string():
    print("Hello")

    string = "hackerworld"
    sample_string = "hackerrank"

    print(sample_string[0])
    print(sample_string[2])

    # find sample_string[0]
    for i in string:
        if (i == sample_string[0]):
            print("found")

if __name__ == '__main__':
    hackerrank_in_a_string()