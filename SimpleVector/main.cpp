#include "SimpleVector.h"
#include <vector>
#include <string>

using namespace std;

template <typename V>
void printv(V& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(int argc, char const* argv[])
{
    SimpleVector<int> v1(6);
    v1.push_back(1); // push_back 확인
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(6);
    v1.pop_back(); // pop_back 확인
    SimpleVector<int> v2(v1); // 복사생성자 호출
    SimpleVector<int> v3 = v1; // 복사생성자 호출
    SimpleVector<int> v4{5, 4, 3, 2, 1}; // 리스트 초기화
    SimpleVector<int> v5{1, 2, 3, 4, 5}; // 리스트 초기화
    SimpleVector<int> v6;
    SimpleVector<int> v7;
    vector<int> v8;
    SimpleVector<string> v9{"hi", "hello", "bye", "thanks"}; // 다른 타입 확인
    SimpleVector<int> v10;

    v1[1] = 6; // 인덱스 접근 확인, 수정 후 깊은복사 확인

    v4.sortData(); // sortData() 확인

    v5.sortData([](auto a, auto b) -> auto
    {
        return a > b;
    }); // sortData(비교함수) 확인

    // 반복자 확인(사실은 그냥 포인터)
    for (auto it = v1.begin(); it != v1.end(); it++)
    {
        v6.push_back(*it);
    }

    // push_back 멤버함수를 구현했어도 back_inserter는 불가능
    // value_type 지정 필요.(std::iterator_traits의 요소)
    transform(v1.begin(), v1.end(), back_inserter(v7),
              [](auto el) -> auto { return 2 * el; });

    transform(v1.begin(), v1.end(), back_inserter(v8),
              [](auto el) -> auto { return 2 * el; });

    // capasity 증가 확인
    for (int i = 0; i < 20; i++)
    {
        v10.push_back(i + 1);
    }

    cout << "v1: ";
    printv(v1);
    cout << "v2: ";
    printv(v2);
    cout << "v3: ";
    printv(v3);
    cout << "v4: ";
    printv(v4);
    cout << "v5: ";
    printv(v5);
    cout << "v6: ";
    printv(v6);
    cout << "v7: ";
    printv(v7);
    cout << "v8: ";
    printv(v8);
    cout << "v9: ";
    printv(v9);
    cout << "v10: ";
    printv(v10);
    return 0;
}
