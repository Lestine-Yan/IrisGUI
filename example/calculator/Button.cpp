#include"Button.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cwctype>

/**
 * 提取并解析一个正实数（支持科学记数法，如 1.11603e+07、2e-3）
 * 要求必须以数字 0-9 开头（符合题设，不会出现 .5）
 * @param s 宽字符串
 * @param i 当前下标（会被更新到数字之后的位置）
 * @return 解析出的数值
 */
static double parseNumber(const std::wstring& s, size_t& i) {
    size_t start = i;

    while (i < s.size() && (std::iswdigit(s[i]) || s[i] == L'.')) {
        ++i;
    }
    if (i < s.size() && (s[i] == L'e' || s[i] == L'E')) {
        ++i;  
        if (i < s.size() && (s[i] == L'+' || s[i] == L'-')) {
            ++i;  
        }
        while (i < s.size() && std::iswdigit(s[i])) {
            ++i;
        }
    }

    std::wstring numStr = s.substr(start, i - start);
    return std::stod(numStr);
}

/**
 * 计算四则运算表达式（宽字符串），结果保留 9 位小数
 * @param expr 表达式，包含数字0-9、小数点'.'、运算符+-* /、
 *             科学记数法（如 1.11603e+07，支持小写e/E，指数可带正负号）
 *             第一个操作数可以是负数，后续均为正数
 * @return 计算结果（宽字符串）
 */
std::wstring calculate(const std::wstring& expr) {
    if (expr.empty()) {
        return L"0.000000000";
    }

    std::vector<double> nums;
    std::vector<wchar_t> ops;

    size_t i = 0;
    double cur;

    if (expr[i] == L'-') {
        ++i;  
        cur = -parseNumber(expr, i);
    }
    else {
        cur = parseNumber(expr, i);
    }

    while (i < expr.size()) {
        wchar_t op = expr[i++];                
        double nextNum = parseNumber(expr, i); 

        if (op == L'*' || op == L'/') {
            if (op == L'*') {
                cur *= nextNum;
            }
            else {
                cur /= nextNum;
            }
        }
        else if (op == L'+' || op == L'-') {
            nums.push_back(cur);
            ops.push_back(op);
            cur = nextNum;
        }
    }
    nums.push_back(cur);

    double result = nums[0];
    for (size_t j = 0; j < ops.size(); ++j) {
        if (ops[j] == L'+') {
            result += nums[j + 1];
        }
        else {
            result -= nums[j + 1];
        }
    }

    std::wostringstream woss;
    woss << result;
    return woss.str();
}

namespace IrisGUI {
	Button::Button(const std::string& className, std::wstring c, std::wstring& s)
		: Div(className,c), m_c(c), m_s(s) {
	}

	void Button::onMouseDown(const ExMessage& msg) 
	{
		if (m_c[0] == '=') {
			m_s = calculate(m_s);
		}
        else if (m_c[0] == 'a') {
            m_s = L"";
        }
        else if (m_c[0] == 'd') {
            m_s = m_s.substr(0, m_s.size() - 1);
        }
        else {
            m_s += m_c;
        }
	}
}