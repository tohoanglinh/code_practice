#!/bin/python3

def angry_professor():
    # print("Angry Professor")

    # Get number of test cases from input
    numberOfTestCases = input()
    numberOfTestCases = int(numberOfTestCases)
    # print("Number of test cases = " + str(numberOfTestCases))

    # For loop that contains information of each test case
    for t in range(0, numberOfTestCases):
        # print("Test case number " + str(t))

        numberOfStudents, cancelThreshold = input().split()
        numberOfStudents = int(numberOfStudents)
        cancelThreshold = int(cancelThreshold)
        # print("Case " + str(t) + ": Number of students = " + str(numberOfStudents))
        # print("Case " + str(t) + ": Canceled threshold = " + str(cancelThreshold))

        onTimeCounter = 0

        arrivalTime = input().split()
        for studentIndex in range(0, numberOfStudents):
            if (int(arrivalTime[studentIndex]) <= 0):
                onTimeCounter += 1

        if (onTimeCounter < cancelThreshold):
            # Class is canceled. Too many students are late.
            print("YES")
        else:
            # Class continues.
            print("NO")

if __name__ == '__main__':
    # call angry_professor function
    angry_professor()
