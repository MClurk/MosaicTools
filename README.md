MosaicTools
===========

图片打码小工具，详见readme描述，需要OpenCV库

这是一个给图片打码的小工具，有两种模式可供选择。
一种是Stroke模式，通过画笔绘制打码区域，适合不规则形状区域。会显示画笔轮廓帮使用者准确控制，并可使用类ps绘图工具中常见的快捷键[和]控制画笔大小，预设半径15像素。
另一模式是Rectangle模式，通过拖动矩形方框确定矩形打码区域。
不同模式通过Shift键进行切换，并且显示文字提示所在模式。
实时局部计算马赛克，才不会做事先全部打码再替换画笔区域这种没效率的事情呢！
使用Ctrl或e键切换至橡皮，擦除不需要的马赛克。
代码中使用了opencv库中的某些基本操作函数和基础数据结构。
参数一个，为图像路径字符串，如/home/mclurk/图片/mosaic/maoshu.jpg
