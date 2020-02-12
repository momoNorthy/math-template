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
    int readLog(char const * = "log"); //返回read的结果
};
MathManager::MathManager(std::size_t count) : count{count}
{
    ; //功能一完整，无需执行体。
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
        return 0; //如果未答对十道题，返回0.
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

        std::cout << "hello,你已经是" << count_to_level() << "级了哦!"
                  << "最高纪录" << bestSec << "秒！来玩游戏吧！";
        //-------GENERATE RANDOM NUMBER AND THE SYMBOL---//
        char symbol;
        int a, b;
        std::srand(time(nullptr));
        a = (std::rand() % 10000 + 1);
        b = (std::rand() % 10000 + 1);
        int symbol_type = (std::rand() % 2); //0+1-2x3÷
        switch (symbol_type)
        {
        case 0:
            symbol = '+';
            break;
        case 1:
            symbol = '-';
            break;
        }
        std::cout << "问题来了：" << a << '+' << b << "= (输入-5245退出)";
        int people;
        std::cin >> people;
        if (people == -5245)
            break;
        int answer;

        answer = a + b;

        if (people == answer)
        {
            add();
            std::cout << "答对了！！" << std::endl;
            end = std::clock();
            std::cout << "你用了" << ((end - start) / CLOCKS_PER_SEC) << "秒。";
            logger();
        }
        else
            std::cout << "答错了，应该是" << answer << std::endl;
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
