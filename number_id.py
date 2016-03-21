#coding:utf8

import sys

def read_dict(dict_file):
    ret_dict ={}
    with open(dict_file, 'r') as df:
        for line in df:
            key, points = line.rstrip('\n').split('\t')
            points = [int(x) for x in points.split(',')]
            points.insert(0, 0)
            points.append(1000000)
            ret_dict[int(key)] = points
    return ret_dict

def main():
    point_dict = read_dict("points.dict")
    with open("test.in", "r") as fin:
        for line in fin:
            key, num = [int(x) for x in line.rstrip('\n').split('\t')]
            points = point_dict[key]
            num_id = -1
            for i, x in enumerate(points[:-1]):
                if num >= x and num < points[i + 1]:
                    num_id = i
                    break
            if num_id == -1:
                print >> sys.stderr, "wrong"
                continue
            print num_id

if __name__ == "__main__":
    main()
