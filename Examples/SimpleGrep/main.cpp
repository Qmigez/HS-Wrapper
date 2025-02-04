/*
    Example usage "SimpleGrep"
*/

#include <iostream>
#include <fstream>
#include <format>
#include <iterator>

#include "HSWrapper/AbstractHandler.h"

#include "HSWrapper/Compile/Database.h"

/*
    class used for hadling matching result
*/
class EventHandler : public HS::AbstractHandler {
public:
    EventHandler(std::string pattern) : pattern_(pattern) {}
    HS::HandlerTypePtr getHandler() const final {
        return &handle;
    }
    void* getCtx() final {
        return pattern_.data();
    }
private:
    static int handle(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags, void *ctx) {
        std::cout << std::format("Match for pattern \"{}\" at offset {}", static_cast<char*>(ctx), to) << std::endl;
        return 0;
    }
private:
    std::string pattern_;
};
/*
    reads data from file
*/
std::string readData(const char* pathToFile);



int main(int argc, char* argv[]) {    
    if (argc != 3) {
        std::cout << std::format("Usage: {} <pattern> <input file>\n", argv[0]) << std::endl;
        return -1; 
    }
    /*
        reading input data
    */
    std::string data = readData(argv[2]);
    std::string pattern(argv[1]);

    /*
        compiling database
        throw HS::CompileException if fails
    */
    HS::Database db = HS::Database::compile(
        {
            pattern, // std::string pattern representation
            {HS::FLAG::DOTALL}, // std::vector<HS::FLAG> compile flags defined in Enums.h
            0 // pattern id
        }, // HS::Pattern = representation of pattern
        HS::MODE::BLOCK, // compile mode
        HS::PlatformInfo() // default platform = nullptr = native platform
    );

    /*
        scratch allocation
        throw HS::RuntimeException if fails
    */
    
    HS::Scratch scratch = db.allocScratch();
    
    /*
        Creation HS::AbstractHandler child for handling matchng event
        on event handler print message about matched expression and offset 
    */

    EventHandler eh(pattern);
    /*
        Scaning for pattern
    */
    db.scan(data, 0, scratch, eh);
    
    /*
        No cleanup:) radostno
    */
    return 0;
}




std::string readData(const char* pathToFile) {
    std::ifstream in(pathToFile, std::ios::binary);
    std::string out(std::istreambuf_iterator<char>{in}, {});
    return out;
}