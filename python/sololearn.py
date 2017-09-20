print("hello python3")
print("-------------------------------------")
print("Strings: Python is fun!")
print("Double quotes \"is this one\"")
print("-------------------------------------")
print("Simple Input and Output")
#word = input("Enter a word:")
#print(word+' shop')
print("-------------------------------------")
list = [1,2,3,4]
if len(list)%2 == 0:
    print(list[0])

def sum(x):
    res = 0
    for i in range(x):
        res += i
    return res

def min(x,y):
    if (x < y):
        return x
    else:
        return y

def main():
    print(sum(3))
    print(min(10,5))

if __name__ == '__main__':
    main()
