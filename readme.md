# HS Wrapper
RAII wrapper for hyperscan library

## цель 
HS Wrapper предоставляет интерфейс для работы с библиотекой hyperscan.  
цель:  
    создать обёртку библиотеки hypersсan для обеспечение автоматического управления ресурсами  

## дополнительные требования:  
    1. независимость от файлов hyperscan после сборки (заголовочные файлы (.h) и файлы библиотек (.so))
    2. используемое именование функций и классов должно однозначно отсылать к используемым в реализации


## сборка
```cmd
    meson setup build --buildtype=release [-Dexamples=enabled]
    cd build
    meson install --destdir dir
```
-Dexamples=enabled - опцианально, при включении собирает (и устанавливает) примеры использования  
dir - каталог установки
каталог установки: 

|заголовочных файлов | dir/include |   
|файлы библиотек | dir/lib |  
|примеров | dir/examples | 


## пример
создание базы и обработка ошибок компиляции
```
#include <string>
#include <iostream>
#include <format>

#include "HSWrapper/AbstractHandler.h"
#include "HSWrapper/Enums.h"
#include "HSWrapper/Exception.h"


#include "HSWrapper/Compile/Database.h"

#include "HSWrapper/Runtime/Scratch.h"
/*
    класс обертка для описания поведения при выполнении паттерна
*/
class ExampleHandler : public HS::AbstractHandler {
public:
    /// @brief возвращает указатель на функцию, вызываемую при совпадении
    /// @return 
    HS::HandlerTypePtr getHandler() const final {
        return &handle;
    }
    /// @brief возвращает указатель на контекст (5-й параметр функции)
    /// @return указатель на строку в которую записывается результат
    void* getCtx() final {
        return &res_;
    };
    std::string getMatchingResult() const {
        return res_;   
    }

private:
    static int handle(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void *ctx) {
        *static_cast<std::string*>(ctx) += std::format("{}:{}:{}:{}\n", id, from, to, flags);
        return 0;
    }
private:
    std::string res_;
};



int main() {
    std::string data = "aa_ab";
    std::string goodPattern = "1:/ab/s";
    std::string badPattern = "2:/a[/s";
    /*
        компиляция базы 
    */
    HS::Database db = HS::Database::compileMulti(
        {
            HS::Pattern(goodPattern), // конструктор который принимает формат 'id:/pattern/flags'
            HS::Pattern("aa", {HS::FLAG::CASELESS, HS::FLAG::DOTALL}, 2) // конструктор который принимает параметры по отдельности
        }, // std::vector HS::Pattern которые будут компилироваться
        HS::MODE::BLOCK, // режим компиляции 
        HS::PlatformInfo() // платформа компиляции (по умолчанию текущая)
    ); // бросает HS::CompileException при ошибке

    /*
        аллокация scratch
    */
    HS::Scratch sc = db.allocScratch(); // аллокация scratch - части HS::Database поскольку любой scratch привязан к единственной базе
    /*
        сканирование
    */
    ExampleHandler eh;
    db.scan(
        data, // набор данных для сканирования
        0, // дополнительные флаги 
        sc, // scratch
        eh // обработчик событий нахождения
    );

    std::cout << std::format("Scanning results:\n{}", eh.getMatchingResult()) << std::endl;

    /*
        попытка скомпилировать неккоректный паттерн
    */
    try {
        HS::Database db2 = HS::Database::compile(
            HS::Pattern(badPattern),
            HS::MODE::BLOCK,
            HS::PlatformInfo()
        );
    } catch (HS::CompileException& e) {
        std::cout << std::format("Catched HS::CompileException\n\twhat: {}", e.what()) << std::endl;
    }

    return 0;
}
```