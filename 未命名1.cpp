#include <cmath> 
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

class Complex {
private:
    double real;   
    double imag;  

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    double getReal() const { return real; }
    double getImag() const { return imag; }
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }
    double getModulus() const {
        return sqrt(real * real + imag * imag);
    }
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};
void shuffleVector(std::vector<Complex>& vec) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::random_shuffle(vec.begin(), vec.end());
}
int findComplex(const std::vector<Complex>& vec, const Complex& target) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return i;
        }
    }
    return -1;
}
void insertComplex(std::vector<Complex>& vec, int pos, const Complex& c) {
    if (pos < 0 || pos > vec.size()) {
        std::cout << "����λ����Ч��" << std::endl;
        return;
    }
    vec.insert(vec.begin() + pos, c);
}
void deleteComplex(std::vector<Complex>& vec, int pos) {
    if (pos < 0 || pos >= vec.size()) {
        std::cout << "ɾ��λ����Ч��" << std::endl;
        return;
    }
    vec.erase(vec.begin() + pos);
}
void uniqueVector(std::vector<Complex>& vec) {
    std::sort(vec.begin(), vec.end(), [](const Complex& a, const Complex& b) {
        if (a.getReal() != b.getReal()) {
            return a.getReal() < b.getReal();
        }
        return a.getImag() < b.getImag();
    });
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}
void bubbleSort(std::vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            double modJ = vec[j].getModulus();
            double modJ1 = vec[j + 1].getModulus();
            if (modJ > modJ1 || (modJ == modJ1 && vec[j].getReal() > vec[j + 1].getReal())) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}
void merge(std::vector<Complex>& vec, int left, int mid, int right) {
    std::vector<Complex> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        double modI = vec[i].getModulus();
        double modJ = vec[j].getModulus();
        if (modI < modJ || (modI == modJ && vec[i].getReal() < vec[j].getReal())) {
            temp.push_back(vec[i++]);
        } else {
            temp.push_back(vec[j++]);
        }
    }
    while (i <= mid) {
        temp.push_back(vec[i++]);
    }
    while (j <= right) {
        temp.push_back(vec[j++]);
    }
    for (int k = 0; k < temp.size(); ++k) {
        vec[left + k] = temp[k];
    }
}
void mergeSort(std::vector<Complex>& vec, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(vec, left, mid);
    mergeSort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}
void testSortEfficiency() {
	std::vector<Complex> vec1;
	std::vector<Complex> vec2,vec3;
    int n = 1000; 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double>dis(0,100);
    for(int k=0;k<n;++k){
    	double r =dis(gen);
    	double i =dis(gen);
    	vec1.push_back(Complex(r,i));
	}
    vec2 = vec1;
    vec3 = vec1;
    mergeSort(vec1, 0, vec1.size() - 1);
    std::vector<Complex> sortedVec = vec1;
    std::cout << "=== ð������Ч�ʲ��� ===" << std::endl;
    vec1 = sortedVec;
    clock_t start = clock();
    bubbleSort(vec1);
    clock_t end = clock();
    std::cout << "���������" << (end - start) / (double)CLOCKS_PER_SEC << " ��" << std::endl;
    vec1 = vec2;
    start = clock();
    bubbleSort(vec1);
    end = clock();
    std::cout << "���������" << (end - start) / (double)CLOCKS_PER_SEC << " ��" << std::endl;
    std::reverse(vec1.begin(), vec1.end());
    start = clock();
    bubbleSort(vec1);
    end = clock();
    std::cout << "���������" << (end - start) / (double)CLOCKS_PER_SEC << " ��" << std::endl;
    std::cout << "\n=== �鲢����Ч�ʲ��� ===" << std::endl;
    vec1 = sortedVec;
    start = clock();
    mergeSort(vec1, 0, vec1.size() - 1);
    end = clock();
    std::cout << "���������" << (end - start) / (double)CLOCKS_PER_SEC << " ��" << std::endl;
    vec1 = vec2;
    start = clock();
    mergeSort(vec1, 0, vec1.size() - 1);
    end = clock();
    std::cout << "���������" << (end - start) / (double)CLOCKS_PER_SEC << " ��" << std::endl;
    std::reverse(vec1.begin(), vec1.end());
    start = clock();
    mergeSort(vec1, 0, vec1.size() - 1);
    end = clock();
    std::cout << "���������" << (end - start) / (double)CLOCKS_PER_SEC << " ��" << std::endl;
}
std::vector<Complex> rangeSearch(const std::vector<Complex>& vec, double m1, double m2) {
    std::vector<Complex> result;
    for (const auto& c : vec) {
        double mod = c.getModulus();
        if (mod >= m1 && mod <= m2) {
            result.push_back(c);
        }
    }
    return result;
}
int main() {
    std::vector<Complex> vec;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < 10; ++i) {
        double r = std::rand() % 10;
        double im = std::rand() % 10;
        vec.push_back(Complex(r, im));
        // �����ظ�Ԫ��
        if (i % 3 == 0) {
            vec.push_back(Complex(r, im));
        }
    }

    std::cout << "��ʼ������" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << "��ģ��" << c.getModulus() << "��" << std::endl;
    }

    // ��������
    shuffleVector(vec);
    std::cout << "\n���Һ�������" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << std::endl;
    }

    // ���Բ���
    Complex target(5, 5);
    int pos = findComplex(vec, target);
    if (pos != -1) {
        std::cout << "\n�ҵ�Ŀ�� " << target << "��λ�ã�" << pos << std::endl;
    } else {
        std::cout << "\nδ�ҵ�Ŀ�� " << target << std::endl;
    }

    // ���Բ���
    insertComplex(vec, 2, Complex(10, 10));
    std::cout << "\n�����������" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << std::endl;
    }

    // ����ɾ��
    deleteComplex(vec, 2);
    std::cout << "\nɾ����������" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << std::endl;
    }

    // ����Ψһ��
    uniqueVector(vec);
    std::cout << "\nΨһ����������" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << "��ģ��" << c.getModulus() << "��" << std::endl;
    }

    // ��������Ч��
    testSortEfficiency();

    // �����������
    std::vector<Complex> sortedVec = vec;
    mergeSort(sortedVec, 0, sortedVec.size() - 1);
    std::cout << "\n���������������������ң���" << std::endl;
    for (const auto& c : sortedVec) {
        std::cout << c << "��ģ��" << c.getModulus() << "��" << std::endl;
    }

    double m1 = 5, m2 = 10;
    std::vector<Complex> rangeVec = rangeSearch(sortedVec, m1, m2);
    std::cout << "\nģ�� [" << m1 << ", " << m2 << "] ֮���Ԫ�أ�" << std::endl;
    for (const auto& c : rangeVec) {
        std::cout << c << "��ģ��" << c.getModulus() << "��" << std::endl;
    }

    return 0;
}
