"""
Created on Sep 26, 2016

@author: Arthur
"""

"""
    List
"""

myList = [1, 2, 3]
print(myList)

print(myList[1])

print('The list has', len(myList), 'elements')
print('Tha first element is', myList[0], 'and the last one is', myList[len(myList) - 1])

x = myList
print(myList, x)

"""
    What happens here?
"""
x[1] = '?'
print(myList, x)

"""
    List slicing
"""
myList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
print(myList[:2])
print(myList[2:])
myList[5:] = ['a', 'b', 'c']
print(myList)

myList = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
myList[1:9] = 'x'
print(myList)

"""
    Tuple
"""
tup = 1, 2, 'a'
print(tup)
print(tup[1])

for e in tup:
    print(e)

"""
    What happens if we uncomment this line?
"""
# tup[1] = 'x'

"""
    Dictionary
"""
d = {'num': 1, 'den': 2}
print(d)

print(d['num'])
d['num'] = 99
print(d['num'])

if 'num' in d:
    print('We have num!')

del d['num']

if 'num' in d:
    print('We have num!')
