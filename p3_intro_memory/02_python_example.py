import time

t1 = time.time()

size = 1000
x = []

for i in range(size):
    row = []
    for j in range(size):
        row.append(i+j)

    x.append(row)
t2 = time.time()

# print(x)
print(t2-t1)

