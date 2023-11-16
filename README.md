# 2023 Fall 研究生课程——三维CAD建模课程作业

## 作业要求

1) 定义半边数据结构;
2) 基于半边数据结构，实现五个基本欧拉操作；
3) 基于欧拉操作，实现扫掠操作（必须允许二维区域带多个内环），并将基于扫掠操作构建的实体模型进行真实感图形显示。

## 安装与运行

- **运行环境**：
  - Windows11-WSL2-Ubuntu 22.04
  - x86_64-msft-linux-gcc (GCC) 9.3.0, GNU ld (GNU Binutils) 2.34.0.20200220
  - CMAKE version ≥ 3.20

- **安装与运行**：

```sh 
# 在文件夹目录下执行如下命令
sudo apt-get install build-essential libgl1-mesa-dev libglfw3 libglfw3-dev libglew2.2 libglew-dev libglm-dev
mkdir build && cd build
cmake .. && make
./main
```
- **展示方式**： 使用鼠标左右上下按住拖动，即可旋转展示扫掠生成实体


代码结构：

```sh
.
├── CMakeLists.txt              # cmake文件
├── README.md                   # 说明文档
├── build                       # 编译生成目录（执行命令后生成）
├── include                     # 头文件
│   ├── Display.hpp             # 可视化部分头文件
│   ├── Draw.hpp                # 绘制部分头文件
│   ├── EulerOperation.hpp      # 欧拉操作头文件
│   ├── HalfEdgeStructure.hpp   # 半边结构定义头文件
│   └── Sweep.hpp               # 扫掠操作头文件
└── src                         # 代码源文件
    ├── Display.cpp             # 可视化部分实现代码
    ├── Draw.cpp                # 绘制部分实现代码
    ├── EulerOperation.cpp      # 欧拉操作实现代码
    ├── HalfEdgeStructure.cpp   # 半边结构函数实现代码
    ├── Sweep.cpp               # 扫掠操作实现代码
    └── main.cpp                # 主函数
```

## 结果与心得
如图所示为， 本程序实现的为扫掠操作`sweep()`侧向延伸生成的实体模型，带有两个内环面，一个为矩形面，一个为三角形面,下图为从不同角度所得的实体截图。
- ![image.png](https://yunqichen-images.oss-cn-hangzhou.aliyuncs.com/img/20231115155403.png)
- ![image.png](https://yunqichen-images.oss-cn-hangzhou.aliyuncs.com/img/20231115155421.png)
1. 本扫掠模型各点的颜色为随机生成，所以可能会和图所示颜色有所不同。
2. 本程序维护了一个`Scene`对象，可以包含多个实体，可以参照`./src/Draw.cpp`中的 `SweepSold()` 函数来添加基于扫掠操作实体模型。
3. 本次作业，通过代码实践，让我进一步了解了构建以欧拉操作和扫掠操作为方法的实体模型的实现，更好地理解了相应数据结构和算法，也让我更进一步地清楚了CAD模型构建的种种挑战与机遇。
