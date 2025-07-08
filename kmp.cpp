#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 构建KMP算法的next数组
vector<int> buildNext(const string& pattern) {
    int m = pattern.length();
    vector<int> next(m, 0);
    
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        
        if (pattern[i] == pattern[j]) {
            j++;
        }
        
        next[i] = j;
    }
    
    return next;
}

// KMP搜索算法
vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> positions;
    if (pattern.empty()) return positions;
    
    vector<int> next = buildNext(pattern);
    int n = text.length();
    int m = pattern.length();
    
    for (int i = 0, j = 0; i < n; i++) {
        // 不匹配时，根据next数组调整模式串指针
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        
        // 当前字符匹配成功
        if (text[i] == pattern[j]) {
            j++;
        }
        
        // 完全匹配
        if (j == m) {
            positions.push_back(i - m + 1); // 记录匹配位置（起始索引）
            j = next[j - 1]; // 寻找下一个匹配
        }
    }
    
    return positions;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    
    vector<int> positions = kmpSearch(text, pattern);
    
    if (positions.empty()) {
        cout << "未找到匹配" << endl;
    } else {
        cout << "在文本中发现模式串的位置：" << endl;
        for (int pos : positions) {
            cout << "索引 " << pos << endl;
        }
    }
    
    return 0;
} 