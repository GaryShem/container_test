#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <map>
#include <set>
#include <random>
#include <chrono>
#include <deque>

class Data
{
public:
    int a;
    int b;
    int c;

    explicit Data(int n)
    {
        a = n;
        b = n;
        c = n;
    }

    bool operator<(const Data& rhs) const
    {
        return a < rhs.a;
    }
};

void TestVector(int iterations)
{
    using namespace std::chrono;

    //push_back
    {
        std::vector<int> vec;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            vec.push_back(i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::vector push_back: " << span.count() << " sec" << std::endl;
    }

    //reserve push_back
    {
        std::vector<int> vec;
        vec.reserve(iterations);
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            vec.push_back(i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::vector reserve push_back: " << span.count() << " sec" << std::endl;
    }

    //push_front
    {
        std::vector<int> vec;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations / 50; i++)
        {
            vec.insert(vec.begin(), i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::vector insert 0 (/50 iterations): " << span.count() << " sec" << std::endl;
    }

    //reserve push_front
    {
        std::vector<int> vec;
        vec.reserve(iterations);
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations / 50; i++)
        {
            vec.insert(vec.begin(), i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::vector reserve insert 0 (/50 iterations): " << span.count() << " sec" << std::endl;
    }

    //traversal && find
    {
        std::vector<int> vec;
        vec.reserve(iterations);
        std::vector<int> vec_read;
        vec_read.reserve(iterations);

        for (int i = 0; i < iterations / 50; i++)
        {
            vec.insert(vec.begin(), i);
        }

        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (auto it : vec)
        {
            vec_read.push_back(it);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::vector traversal: " << span.count() << " sec" << std::endl;

        high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

        auto it = std::find(vec.begin(), vec.end(), iterations-1);

        std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
        std::cout << "std::vector find last: " << span.count() << " sec" << std::endl;
    }

    std::cout << std::endl;
}

void TestList(int iterations)
{
    using namespace std::chrono;

    //push_back
    {
        std::list<int> l1;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            l1.push_back(i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::list push_back: " << span.count() << " sec" << std::endl;
    }

    //push_front
    {
        std::list<int> l1;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            l1.push_front(i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::list push_front: " << span.count() << " sec" << std::endl;
    }

    //traversal && find
    {
        std::list<int> l1;

        for (int i = 0; i < iterations; i++)
        {
            l1.push_front(i);
        }

        std::vector<int> vec_read;
        vec_read.reserve(iterations);

        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (auto it : l1)
        {
            vec_read.push_back(it);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::list traversal: " << span.count() << " sec" << std::endl;

        high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

        auto it = std::find(l1.begin(), l1.end(), iterations-1);

        std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
        span = duration_cast<duration<double>>(t4 - t3);
        std::cout << "std::list find last: " << span.count() << " sec" << std::endl;
    }
    std::cout << std::endl;
}

void TestForwardList(int iterations)
{
    using namespace std::chrono;

    //push_front
    {
        std::forward_list<int> fl1;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            fl1.push_front(i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::forward_list push_front: " << span.count() << " sec" << std::endl;
    }

    //traversal && find
    {
        std::forward_list<int> fl1;

        for (int i = 0; i < iterations; i++)
        {
            fl1.push_front(i);
        }

        std::vector<int> vec_read;
        vec_read.reserve(iterations);

        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (auto it : fl1)
        {
            vec_read.push_back(it);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::list traversal: " << span.count() << " sec" << std::endl;

        high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

        auto it = std::find(fl1.begin(), fl1.end(), iterations-1);

        std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();
        span = duration_cast<duration<double>>(t4 - t3);
        std::cout << "std::list find last: " << span.count() << " sec" << std::endl;
    }

    std::cout << std::endl;
}

void TestDeque(int iterations)
{
    using namespace std::chrono;

    //push_back
    {
        std::deque<int> deq;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            deq.push_back(i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::deque push_back: " << span.count() << " sec" << std::endl;
    }

    //push_front
    {
        std::deque<int> deq;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            deq.push_front(i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::deque push_front: " << span.count() << " sec" << std::endl;
    }

    //traversal
    {
        std::deque<int> deq;

        for (int i = 0; i < iterations; i++)
        {
            deq.push_front(i);
        }

        std::vector<int> vec_read;
        vec_read.reserve(iterations);

        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (auto it : deq)
        {
            vec_read.push_back(it);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::deque traversal: " << span.count() << " sec" << std::endl;
    }
    std::cout << std::endl;
}

void TestSet(int iterations)
{
    using namespace std::chrono;

    //insert consecutive values
    {
        std::set<int> s1;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            s1.insert(i);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::set insert consecutive: " << span.count() << " sec" << std::endl;
    }

    //insert random values
    {
        std::set<int> s1;

        std::vector<int> vec;
        vec.reserve(iterations);
        for (int i = 0; i < iterations; i++)
        {
            vec.push_back(i);
        }

        std::random_device rd;
        std::mt19937 mt(rd());
        std::shuffle(vec.begin(), vec.end(), mt);

        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            s1.insert(vec[i]);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::set insert random: " << span.count() << " sec" << std::endl;

        std::vector<int> vec_read;
        vec_read.reserve(iterations);

        high_resolution_clock::time_point t3 = high_resolution_clock::now();

        for (auto it : s1)
        {
            vec_read.push_back(it);
        }

        high_resolution_clock::time_point t4 = high_resolution_clock::now();

        span = duration_cast<duration<double>>(t4 - t3);
        std::cout << "std::set traversal: " << span.count() << " sec" << std::endl;
    }


    std::cout << std::endl;
}

void TestMap(int iterations)
{
    using namespace std::chrono;

    //insert consecutive
    {
        std::map<int, int> m1;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            m1.insert(std::pair<int, int>(i, i));
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::map insert consecutive: " << span.count() << " sec" << std::endl;
    }

    //insert random && traversal
    {
        std::map<int, int> m1;
        high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; i++)
        {
            m1.insert(std::pair<int, int>(i, i));
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

        duration<double> span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "std::map insert random: " << span.count() << " sec" << std::endl;

        std::vector<int> vec_read;
        vec_read.reserve(iterations);

        high_resolution_clock::time_point t3 = high_resolution_clock::now();

        for (auto it : m1)
        {
            vec_read.push_back(it.second);
        }

        high_resolution_clock::time_point t4 = high_resolution_clock::now();

        span = duration_cast<duration<double>>(t4 - t3);
        std::cout << "std::map traversal: " << span.count() << " sec" << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    int iterations = 10000000;
    TestVector(iterations);
    TestList(iterations);
    TestForwardList(iterations);
    TestDeque(iterations);
    TestSet(iterations);
    TestMap(iterations);
    return 0;
}
