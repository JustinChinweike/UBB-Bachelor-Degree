"""
Created on Sep 23, 2016

@author: Arthur
"""

"""
    Read a number and check whether it is prime
"""
x = input("Give the number: ")
x = int(x)

isPrime = True
for i in range(2, x // 2):
    if x % i == 0:
        isPrime = False

if isPrime:
    print("Number is prime!")
else:
    print("Number is not prime!")

"""
    NB!
    Let's break program flow as soon as we know it's not a prime
"""
x = input("Give the number: ")
x = int(x)

isPrime = True
i = 2
while isPrime and i <= x // 2:
    i += 1
    if x % i == 0:
        isPrime = False

if isPrime:
    print("Number is prime!")
else:
    print("Number is not prime!")

"""
    Open question!
    How can you check the functions above do what they are supposed to?
"""
