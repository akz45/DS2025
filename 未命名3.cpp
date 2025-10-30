#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
using namespace std;

// ������״ͼ�����������
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    if (n == 0) return 0;
    
    vector<int> left(n, -1);  // ��¼ÿ��������ߵ�һ�����������ӵ�����
    vector<int> right(n, n); // ��¼ÿ�������ұߵ�һ�����������ӵ�����
    stack<int> stk;          // ����ջ���洢�������������ָ߶ȵ���
    
    // ����left����
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            left[i] = stk.top();
        }
        stk.push(i);
    }
    
    // ���ջ������right����
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
    
    // ����������
    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        int width = right[i] - left[i] - 1;
        maxArea = max(maxArea, heights[i] * width);
    }
    return maxArea;
}

// ������ɲ������ݲ�����
void test() {
    srand(time(0));
    for (int t = 0; t < 10; ++t) {
        int len = rand() % 105 + 1; // ����1~105
        vector<int> heights(len);
        for (int i = 0; i < len; ++i) {
            heights[i] = rand() % 105; // �߶�0~104
        }
        int area = largestRectangleArea(heights);
        cout << "�������� " << t + 1 << "������=" << len << "��������=" << area << endl;
    }
}

int main() {
    test();
    return 0;
}

