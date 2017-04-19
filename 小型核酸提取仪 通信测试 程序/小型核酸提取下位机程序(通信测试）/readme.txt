1,加入软复位功能；
2，X轴加减速点变为 40个；
3，Y轴速度太快，修改成1半；
4，

1,DeviceVibration.c 中处理的 MoveProcess()
2,Timer5 中断处理函数中处理ADC值
3，Moto.c 中XACC[XACCNUM] X轴速度加速点
目前用的2000 每秒的脉冲数；  下面注释掉了每秒3200脉冲数   1600每秒的脉冲数；


