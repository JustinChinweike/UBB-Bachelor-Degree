"""
Created on Sep 29, 2016

@author: http://www.python-course.eu/global_vs_local_variables.php
"""

"""
    NB!
    Uncomment each of the sections separated by ### below,
    one at a time and run them
"""


# def f():
#     print(s)
#
#
# s = 'I hate spam'
# f()

#############################

# def f():
#     # PyCharm complains that 's' shadows the name from the outer scope
#     # Of course it does, that's the whole point :)
#     s = "Me too."
#     print(s)
#
#
# s = "I hate spam."
# f()
# print(s)

#############################

# def f():
#     """
#     Variables created or changed inside functions
#     are local, unless declared global
#     """
#     print(s)
#     s = "Me too."
#     print(s)
#
#
# s = "I hate spam."
# f()
# print(s)

#############################

# def f():
#     global s
#     print(s)
#     s = "That's clear."
#     print(s)
#
#
# s = "Python is great again!"
# f()
# print(s)

#############################

# def f():
#     s = "I am globally not known"
#     print(s)
#
#
# f()
# print(s)

#############################
"""
    Exercise:
    What happens in the example below? 
"""
# def foo(x, y):
#     global a
#     a = 42
#     x,y = y,x
#     b = 33
#     b = 17
#     c = 100
#     print(a,b,x,y)
#     '''
#         NB!
#         Learn to use the locals() and globals() functions to figure out what's what
#          
#         print(locals())
#         print(globals())
#     '''
#  
# a,b,x,y = 1,15,3,4
# foo(17,4)
# print(a,b,x,y)
