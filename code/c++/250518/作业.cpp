/***************************************************
# File Name:    作业.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月18日 星期日 19时21分42秒
****************************************************/

#include <iostream>
using namespace std;

/****************************************
 *命名空间与类和引用管理库存系统
题目描述
编写一个简单的库存管理程序
使用命名空间 Inventory，管理库存操作。
定义商品库存值为全局变量，通过引用参数对库存进行增减和查询操作。
提供以下功能：
增加库存：函数 addStock 接收库存变量的引用和增加值，直接修改库存值。
减少库存：函数 removeStock 接收库存变量的引用和减少值，如果库存不足，则提示操作失败。
查询库存：函数 getStock 接收库存变量的引用，返回当前库存值。
在 main 函数中模拟以下操作：
初始库存为 50。
增加库存 20，查询库存。
减少库存 30，查询库存。
再减少库存 50，验证库存不足时的处理。

示例输入输出
输入：
初始库存 = 50
增加库存：20
减少库存：30
减少库存：50
输出：
当前库存：70
当前库存：40
库存不足，无法减少！
当前库存：40
 */


#include <iostream>

namespace Inventory {
    // 增加库存（通过引用直接修改原始值）
    void addStock(int& stock, int value) {
        stock += value;
    }

    // 减少库存（引用传递并验证库存量）
    void removeStock(int& stock, int value) {
        if (stock >= value) {
            stock -= value;
        } else {
            std::cout << "库存不足，无法减少！" << std::endl;
        }
    }

    // 查询库存（const引用保证数据安全）
    int getStock(const int& stock) {
        return stock;
    }
}

int main() {
    int currentStock = 50; // 初始库存
    
    // 第一次操作：增加库存20
    Inventory::addStock(currentStock, 20);
    std::cout << "当前库存：" << Inventory::getStock(currentStock) << std::endl;
    
    // 第二次操作：减少库存30
    Inventory::removeStock(currentStock, 30);
    std::cout << "当前库存：" << Inventory::getStock(currentStock) << std::endl;
    
    // 第三次操作：尝试减少库存50
    Inventory::removeStock(currentStock, 50);
    std::cout << "当前库存：" << Inventory::getStock(currentStock) << std::endl;

    return 0;
}
