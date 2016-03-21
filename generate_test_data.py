#coding:utf8

import random
import sys

def main():
    for _ in range(10000):
        num = random.randint(1, 10000)
        point_num = random.randint(1, 100)
        points = sorted(random.sample(range(5000), point_num))
        print "%d\t%s" % (num, ','.join([str(x) for x in points]))


if __name__ == '__main__':
    main()
