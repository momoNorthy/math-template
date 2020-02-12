#include <iostream>
#include <fstream>
#include <io.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
enum struct logtime_t
{
    output,
    input
};

class MathManager
{
    std::size_t count;

public:
    MathManager(std::size_t = 0);
    int logger(char const * = "log");
    inline void add() { ++count; }
    inline int level_to_count(std::size_t level) { return level * 10; }
    int count_to_level();
    void game();
    int readLog(char const * = "log"); //����read�Ľ��
};
MathManager::MathManager(std::size_t count) : count{count}
{
    ; //����һ����������ִ���塣
}
int MathManager::logger(char const *filename)
{
    std::ofstream file;
    file.open(filename);
    if (!file.is_open())
    {
        return false;
    }
    file << count;
    return 1;
}
int MathManager::count_to_level()
{
    if (this->count < 10)
    {
        return 0; //���δ���ʮ���⣬����0.
    }
    return this->count / 10;
}

void MathManager::game()
{

    do
    {
        std::fstream logtime = std::fstream("logtime", logtime.in | logtime.out | logtime.app);
        int bestSec = 100000;
        std::clock_t start, end;
        start = std::clock();
        //--------LOAD LOG---------//
        if (!(_access("log", 0) == -1))
        {
            count = readLog();
        }
        if (!(_access("logTime", 0) == -1))
            logtime >> bestSec;

        std::cout << "hello,���Ѿ���" << count_to_level() << "����Ŷ!"
                  << "��߼�¼" << bestSec << "�룡������Ϸ�ɣ�";
        //-------GENERATE RANDOM NUMBER AND THE SYMBOL---//
        char symbol;
        int a, b;
        std::srand(time(nullptr));
        a = (std::rand() % 10000 + 1);
        b = (std::rand() % 10000 + 1);
        int symbol_type = (std::rand() % 2); //0+1-2x3��
        switch (symbol_type)
        {
        case 0:
            symbol = '+';
            break;
        case 1:
            symbol = '-';
            break;
        }
        std::cout << "�������ˣ�" << a << '+' << b << "= (����-5245�˳�)";
        int people;
        std::cin >> people;
        if (people == -5245)
            break;
        int answer;

        answer = a + b;

        if (people == answer)
        {
            add();
            std::cout << "����ˣ���" << std::endl;
            end = std::clock();
            std::cout << "������" << ((end - start) / CLOCKS_PER_SEC) << "�롣";
            logger();
        }
        else
            std::cout << "����ˣ�Ӧ����" << answer << std::endl;
        if (bestSec > ((end - start) / CLOCKS_PER_SEC))
        {
            logtime.close();
            std::ofstream ofs = std::ofstream("logtime", ofs.out | ofs.trunc);
            if (!ofs)
            {
                std::cout << "fail!" << std::endl;
            }
            ofs << ((end - start) / CLOCKS_PER_SEC);
        }

    } while (true);
    logger();
}
int MathManager::readLog(char const *file)
{
    std::ifstream ifs = std::ifstream(file, ifs.in);
    std::size_t a;
    ifs >> a;
    return a;
}
