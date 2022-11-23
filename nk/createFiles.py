#encoding: utf-8;
path = r'/home/wmikeu/code/myleetcode/nk/'

numlist = [];
for i in range(7,102):
    numlist.append(i)

for num in numlist:
    filename = 'BM' + str(num) + '.cpp'

    gFile = open(path + filename, "w")

    lines = ['#include "nk.h"']
    gFile.writelines(lines)
    gFile.close()
    # print('%s文件创建完成' % filename)
