#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
using namespace std;

// 计算柱状图中最大矩形面积
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    if (n == 0) return 0;
    
    vector<int> left(n, -1);  // 记录每个柱子左边第一个更矮的柱子的索引
    vector<int> right(n, n); // 记录每个柱子右边第一个更矮的柱子的索引
    stack<int> stk;          // 单调栈，存储柱子索引，保持高度递增
    
    // 计算left数组
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            left[i] = stk.top();
        }
        stk.push(i);
    }
    
    // 清空栈，计算right数组
    while (!stk.empty()) stk.pop();
    for (int i = n - 1; i >= 0; --i) {
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            right[i] = stk.top();
        }
        stk.push(i);
    }
    
    // 计算最大面积
    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        int width = right[i] - left[i] - 1;
        maxArea = max(maxArea, heights[i] * width);
    }
    return maxArea;
}

// 随机生成测试数据并测试
void test() {
    srand(time(0));
    for (int t = 0; t < 10; ++t) {
        int len = rand() % 105 + 1; // 长度1~105
        vector<int> heights(len);
        for (int i = 0; i < len; ++i) {
            heights[i] = rand() % 105; // 高度0~104
        }
        int area = largestRectangleArea(heights);
        cout << "测试用例 " << t + 1 << "：长度=" << len << "，最大面积=" << area << endl;
    }
}

int main() {
    test();
    return 0;
}

