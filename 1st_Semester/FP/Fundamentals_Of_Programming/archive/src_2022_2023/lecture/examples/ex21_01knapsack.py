#
# 0-1 Knapsack problem
#

W = 10
values_data = [5, 3, 10, 4, 2]
weights_data = [2, 3, 4, 3, 6]


#
# Version 1 - non dynamic programming
#
def knapsack(W: int, values, weights: list, index: int):
    # Basic case - no more room or we've gone through all items
    if W == 0 or index < 0:
        return 0

    # Item we are currently does not fit in knapsack
    if weights[index] > W:
        return knapsack(W, values, weights, index - 1)
    else:
        # Maximum between the decision of including it or not
        return max(values[index] + knapsack(W - weights[index], values, weights, index - 1),
                   knapsack(W, values, weights, index - 1))


#
# Version 2 - dynamic programming
#

# Pretty-print auxiliary table, this should help follow the algorithm's steps
from texttable import Texttable


def pretty_print(v: list):
    t = Texttable()
    t.header(['X'] + list(range(W + 1)))
    for i in range(len(v)):
        t.add_row([i] + v[i])
    print(t.draw())


def knapsack_dp(W: int, values, weights: list):
    V = [[0 for x in range(W + 1)] for x in range(len(values) + 1)]

    # Go over every item
    for i in range(len(values) + 1):
        # Go over every possible weight
        for j in range(W + 1):
            if i == 0 or j == 0:
                V[i][j] = 0
            elif weights[i - 1] > j:
                # Current item does not fit, do not include it
                V[i][j] = V[i - 1][j]
            else:
                # Maximum between skipping the item and including it
                V[i][j] = max(V[i - 1][j], values[i - 1] + V[i - 1][j - weights[i - 1]])
    pretty_print(V)
    return V[len(values)][W]


print(knapsack_dp(W, values_data, weights_data))
