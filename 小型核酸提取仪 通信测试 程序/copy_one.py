
#coding:gbk

import random
import serial
import time


result1=[]         #收集的， 收发数据不同处
result2 = []       # 收集的，乱码信息
times_set=int(raw_input("Input how many times you want test\n"))
times_now=1
times_ok=0
times_error=0

while True:
    #要求输入端口编号
    com=raw_input('Input the number of COM, EX:COM5\n')
    #要求输入波特率
    baud=int(raw_input('Input the  Baud,EX:9600\n'))

    try:
        #设置端口
        ser = serial.Serial(com,baud)
        break
        #判断端口是否可用，并输出端口号
    except serial.SerialException:
        print "The %s can't find,please input again"

while times_now !=times_set+1:
    benchmark = {}
    benchmark['x3f'] = 'x3f', random.randint(0, 1500)
    benchmark['y1f'] = 'y1f', random.randint(0, 1000)
    benchmark['y2f'] = 'y2f', random.randint(0, 1500)
    benchmark['fla'] = 'fla', random.randint(1, 6)
    benchmark['alb'] = 'alb', random.randint(1, 6)
    benchmark['tlc'] = 'tlc', random.randint(1, 1500)
    benchmark['tld'] = 'tld', random.randint(0, 1500)
    benchmark['vjv'] = 'vjv', random.randint(1, 6)
    benchmark['fhe'] = 'fhe', random.randint(1, 6)
    benchmark['thg'] = 'thg', random.randint(0, 1500)
    benchmark['ahf'] = 'ahf', random.randint(1, 6)
    benchmark['thi'] = 'thi', random.randint(0, 1500)
    benchmark['fjm'] = 'fjm', random.randint(1, 6)
    benchmark['ajn'] = 'ajn', random.randint(1, 6)
    benchmark['tjo'] = 'tjo', random.randint(0, 1500)
    benchmark['tjq'] = 'tjq', random.randint(0, 1500)
    benchmark['tjt'] = 'tjt', random.randint(0, 1500)
    benchmark['f1A'] = 'f1A', random.randint(1, 6)
    benchmark['a1B'] = 'a1B', random.randint(1, 6)
    benchmark['t1C'] = 't1C', random.randint(0, 1500)
    benchmark['t1D'] = 't1D', random.randint(0, 1500)
    benchmark['t1E'] = 't1E', random.randint(0, 1500)
    benchmark['f2G'] = 'f2G', random.randint(1, 6)
    benchmark['a2H'] = 'a2H', random.randint(1, 6)
    benchmark['t2I'] = 't2I', random.randint(0, 1500)
    benchmark['t2J'] = 't2J', random.randint(0, 1500)
    benchmark['t2K'] = 't2K', random.randint(0, 1500)
    benchmark['f3M'] = 'f3M', random.randint(1, 6)
    benchmark['a3N'] = 'a3N', random.randint(0, 1500)
    benchmark['t3O'] = 't3O', random.randint(0, 1500)
    benchmark['t3P'] = 't3P', random.randint(0, 1500)
    benchmark['t3Q'] = 't3Q', random.randint(0, 1500)
    benchmark['t3R'] = 't3R', random.randint(0, 1500)
    benchmark['ftS'] = 'ftS', random.randint(1, 6)
    benchmark['atT'] = 'atT', random.randint(1, 6)
    benchmark['ttU'] = 'ttU', random.randint(0, 1500)
    benchmark['ttV'] = 'ttV', random.randint(0, 1500)
    benchmark['ttW'] = 'ttW', random.randint(0, 1500)
    benchmark['fsY'] = 'fsY', random.randint(1, 6)
    benchmark['asZ'] = 'asZ', random.randint(1, 6)
    benchmark['tsz'] = 'tsz', random.randint(0, 1500)
    benchmark['t0k'] = 't0k', random.randint(29, 102)
    benchmark['t1k'] = 't1k', random.randint(29, 102)
    benchmark['t2k'] = 't2k', random.randint(29, 102)
    benchmark['t3k'] = 't3k', random.randint(29, 102)
    benchmark['t4k'] = 't4k', random.randint(29, 102)
    benchmark['t5k'] = 't5k', random.randint(29, 102)
    benchmark['t6k'] = 't6k', random.randint(29, 102)
    benchmark['t7k'] = 't7k', random.randint(29, 102)
    benchmark['w0r'] = 'w0r', random.randint(0, 1)
    benchmark['w1r'] = 'w1r', random.randint(0, 1)
    benchmark['w2r'] = 'w2r', random.randint(0, 1)
    benchmark['w3r'] = 'w3r', random.randint(0, 1)
    benchmark['w4r'] = 'w4r', random.randint(0, 1)
    benchmark['w5r'] = 'w5r', random.randint(0, 1)
    benchmark['w6r'] = 'w6r', random.randint(0, 1)
    benchmark['w7r'] = 'w7r', random.randint(0, 1)
    #向下位机输出数据
    for i in benchmark:
        ser.write(':%s=%s\r\n'%(benchmark[i][0],benchmark[i][1]))
    ser.write(':sss=4\r\n')

    #向屏幕显示输出的数据

    j=1
    if(times_set > 0):
        for i in benchmark:
            print ':%s=%s       '%(benchmark[i][0],benchmark[i][1]),
            j=j+1
            if j==5:
                print'\r'
                j=1
        print ':sss=4\r'
    else:
        print "Test %d is running"%times_now


    #接收回传的数据
    recmessage = []    #串口接收到的原始信息
    cmpmessage = {}    #整理后的串口接收数据，即有用数据

    while ('sss=4' not in ''.join(recmessage)):
        s=ser.read(1)
        print s
        if s != '':
             recmessage.append(s)

    #  输出回传的原始数据

    j=1
    for i in ''.join(recmessage):
        if (i != '\n')and(i != '\r'):
            print i,
        else:
            j=j+1
            if(j == 5):
                print '\r'
                j=1
            else:
                print '     ',


    #解析原始的数据
    result2.append('In test %d,some string can not be analysis:'%times_now)
    while True:
        try:
            i = recmessage.index(':')
            result2=result2 + recmessage[0:i] + ['\n']
            del recmessage[0:i+1]
            i = recmessage.index(':')
            k = recmessage.index('=')
            j = recmessage.index('\r')
            if(j>i)or(k>i):
                result2 = result2 + recmessage[0:i] + ['\n']
                del recmessage[0:i]
            else:
                cmpmessage[''.join(recmessage[0:k])] = ''.join(recmessage[0:k]), ''.join(recmessage[k + 1:j])
                del recmessage[0:j + 1]
        except ValueError:
            break

    #对比输出和回传的数据，并输出、保存结果
    j=0
    deldict=[]
    print"\nIn test %d:" % times_now
    result1.append("In test %d:" % times_now)
    for i in benchmark:
        if cmpmessage.get(i) == None:
            print "     the message: '%s' can't find in receive message"%i
            result1.append("     the message:%s can't find in receive message"%i)
            j=j+1
        elif int(benchmark[i][1])!=int(cmpmessage[i][1]):
            print "     the values of '%s' are not equeal"%i
            print '          ',benchmark[i][0],'=',benchmark[i][1]
            print '          ',cmpmessage[i][0],'=',cmpmessage[i][1]
            result1.append("     the values of '%s' are not equeal"%i)
            result1.append("          output is: %s=%s!     " %(benchmark[i][0],benchmark[i][1]))
            result1.append("          input is:%s=%s!" % (cmpmessage[i][0],cmpmessage[i][1]))
            deldict.append(i)
            j=j+1
        else:
            deldict.append(i)
    for i in deldict:
        cmpmessage.pop(i)
        benchmark.pop(i)

    for i in cmpmessage:
        print '     The data  is avaiable in input:'
        print '          ',cmpmessage[i][0],'=',cmpmessage[i][1]
        result1.append('     The data  is avaiable in input,but not in output:')
        result1.append("          %s=%s"%(cmpmessage[i][0],cmpmessage[i][1]))

    #如果没有错误，则：
    if j==0:
        times_ok=times_ok+1
        print '     All OK!'
        result1.append("     All OK!")
    times_error=times_error+j
    print '     In this test,there are %d  faults!' %j
    print '\nSo far,there is %d times which is all-OK!'%times_ok
    print 'So far,there are %d  faults!\n' %times_error
    # 次数加一
    times_now=times_now+1
    del benchmark
    del cmpmessage

    if times_set < 0:
        time.sleep(10)
print'\nThe total result are:'

s=[]
j=0
for i in result2:
    if (i == '\r')or(i == '\n'):
        if j ==0:
            print '     ',
            print  ''.join(s)
            s = []
        j=1
    else:
        if j==1:
            j=0
        s.append(i)

for i in result1:
    print i

while True:
    pass



