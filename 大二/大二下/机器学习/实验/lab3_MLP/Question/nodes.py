"""
计算图节点类型

节点必须实现以下方法：
- `__init__`：初始化节点
- `forward`：反向传播的第1步，从前置节点获取输出，更新自身输出，并将梯度设为零
- `backward`：反向传播的第2步，假设已进行前向传播并调用了后续节点的backward方法，计算图输出关于节点输入的导数，将这些导数加到输入节点的d_out数组中
- `get_predecessors`：返回节点的父节点列表

节点必须具有以下属性：
- `node_name`：节点名称（字符串）
- `out`：节点输出
- `d_out`：图输出关于节点输出的导数

"""

import numpy as np

class ValueNode(object):
    """计算图中没有输入的节点，仅持有一个值"""
    def __init__(self, node_name):
        self.node_name = node_name
        self.out = None
        self.d_out = None

    def forward(self):
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        pass

    def get_predecessors(self):
        return []

class VectorScalarAffineNode(object):
    """计算一个将向量映射到标量的仿射函数的节点"""
    def __init__(self, x, w, b, node_name):
        """
        参数:
        x: 节点，其 `x.out` 是一个一维的 numpy 数组
        w: 节点，其 `w.out` 是一个与 `x.out` 相同大小的一维 numpy 数组
        b: 节点，其 `b.out` 是一个 numpy 标量（即 0 维数组）
        node_name: 节点的名称（字符串）
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.x = x
        self.w = w
        self.b = b

    def forward(self):
        self.out = np.dot(self.x.out, self.w.out) + self.b.out
        self.d_out = np.zeros(self.out.shape)
        return self.out

    def backward(self):
        d_x = self.d_out * self.w.out
        d_w = self.d_out * self.x.out
        d_b = self.d_out
        self.x.d_out += d_x
        self.w.d_out += d_w
        self.b.d_out += d_b

    def get_predecessors(self):
        return [self.x, self.w, self.b]

class SquaredL2DistanceNode(object):
    """ 计算两个数组之间的 L2 距离（平方差之和）的节点"""
    def __init__(self, a, b, node_name):
        """
        参数:
        a: 节点，其 `a.out` 是一个 numpy 数组
        b: 节点，其 `b.out` 是一个与 `a.out` 形状相同的 numpy 数组
        node_name: 节点的名称（字符串）
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.a = a
        self.b = b
        self.a_minus_b = None

    def forward(self):
        self.a_minus_b = self.a.out - self.b.out
        self.out = np.sum(self.a_minus_b ** 2)
        self.d_out = np.zeros(self.out.shape) #此处为初始化，下同
        return self.out

    def backward(self):
        d_a = self.d_out * 2 * self.a_minus_b
        d_b = -self.d_out * 2 * self.a_minus_b

        self.a.d_out += d_a
        self.b.d_out += d_b
        return self.d_out

    def get_predecessors(self):
        return [self.a, self.b]

class L2NormPenaltyNode(object):
    """ 计算 l2_reg * ||w||^2 节点，其中 l2_reg 为标量， w为向量"""
    def __init__(self, l2_reg, w, node_name):
        """
        参数:
        l2_reg: 一个大于等于0的标量值（不是节点）
        w: 节点，其 w.out 是一个 numpy 向量
        node_name: 节点的名称（字符串）
        """
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.l2_reg = np.array(l2_reg)
        self.w = w
        ## TODO
        ## Hint：实现对应的forward，backword，get_predecessors接口即可

    def forward(self):
        self.out = self.l2_reg * np.sum(self.w.out ** 2)
        self.d_out = np.zeros(self.out.shape)
        return self.out
    
    def backward(self):
        d_w = self.d_out * 2 * self.l2_reg * self.w.out
        self.w.d_out += d_w
        return self.d_out
    
    def get_predecessors(self):
        return [self.w]
    

class SumNode(object):
    """ 计算 a + b 的节点，其中 a 和 b 是 numpy 数组。"""
    def __init__(self, a, b, node_name):
        """
        参数:
        a: 节点，其 a.out 是一个 numpy 数组
        b: 节点，其 b.out 是一个与 a 的形状相同的 numpy 数组
        node_name: 节点的名称（一个字符串）
        """
        ## TODO
        ## Hint：实现对应的forward，backword，get_predecessors接口即可
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.a = a
        self.b = b

    def forward(self):
        self.out = self.a.out + self.b.out
        self.d_out = np.zeros(self.out.shape)
        return self.out
    
    def backward(self):
        d_a = self.d_out
        d_b = self.d_out
        self.a.d_out += d_a
        self.b.d_out += d_b
        return self.d_out
    
    def get_predecessors(self):
        return [self.a, self.b]


class AffineNode(object):
    """实现仿射变换 (W,x,b)-->Wx+b 的节点，其中 W 是一个矩阵，x 和 b 是向量
        参数：
        W: 节点，其 W.out 是形状为 (m,d) 的 numpy 数组
        x: 节点，其 x.out 是形状为 (d) 的 numpy 数组
        b: 节点，其 b.out 是形状为 (m) 的 numpy 数组（即长度为 m 的向量）
    """
    ## Hint：实现对应的forward，backword，get_predecessors接口即可
    def __init__(self, W, x, b, node_name):
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.W = W
        self.x = x
        self.b = b

    def forward(self):
        self.out = np.dot(self.W.out, self.x.out) + self.b.out
        self.d_out = np.zeros(self.out.shape)
        return self.out
    
    def backward(self):
        d_W = np.outer(self.d_out, self.x.out)
        d_x = np.dot(self.W.out.T, self.d_out)
        d_b = self.d_out
        self.W.d_out += d_W
        self.x.d_out += d_x
        self.b.d_out += d_b
        return self.d_out
    
    def get_predecessors(self):
        return [self.W, self.x, self.b]
    

class TanhNode(object):
    """节点 tanh(a)，其中 tanh 是对数组 a 逐元素应用的
        参数：
        a: 节点，其 a.out 是一个 numpy 数组
    """
    ## TODO
    ## Hint：实现对应的forward，backword，get_predecessors接口即可
    ## tanh函数直接调np.tanh即可
    def __init__(self, a, node_name):
        self.node_name = node_name
        self.out = None
        self.d_out = None
        self.a = a

    def forward(self):
        self.out = np.tanh(self.a.out)
        self.d_out = np.zeros(self.out.shape)
        return self.out
    
    def backward(self):
        d_a = self.d_out * (1 - self.out ** 2)
        self.a.d_out += d_a
        return self.d_out
    
    def get_predecessors(self):
        return [self.a]