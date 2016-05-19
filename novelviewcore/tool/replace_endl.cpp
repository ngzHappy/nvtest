
#include <iostream>
#include <fstream>
#include <string>

int main(int argc,char ** argv) {

    if (argc>=3) {
        std::ifstream ifs(argv[1]);
        std::ofstream ofs(argv[2],std::ios::binary);

        if (false==ifs.is_open()) { return -2; }
        if (false==ofs.is_open()) { return -3; }

        std::string line;
        while (std::getline(ifs,line)) {
            ofs<<line<<"\n";
        }

        return 0;
    }

    return -1;

}
