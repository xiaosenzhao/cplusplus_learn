#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

template <typename T>
class StreamGuard {
public:
    StreamGuard() {
        _file = new T();
    }

    template<typename... Args>
    StreamGuard(const std::string& file_name, Args&&... args) {
        _file = new T(file_name, std::forward<Args>(args)...);
    }

    StreamGuard<T>(const StreamGuard<T>&) = delete;
    StreamGuard<T>& operator=(const StreamGuard<T>&) = delete;

    ~StreamGuard() {
        if (_file->is_open()) {
            _file->close();
        }
        _file->~T();
    }

    T* operator->() {
        return _file;
    }

private:
    std::string _file_name;
    T* _file;
};

void ofstream_write() {
    StreamGuard<std::ofstream> myfile;
    myfile->open("example.txt");
    *(myfile.operator->()) << "Writing this to a file\n";
}

void ifstream_read1() {
    StreamGuard<std::ifstream> myfile("example.txt", std::ifstream::in|std::ifstream::binary);
    if (myfile->is_open()) {
        //get length
        myfile->seekg(0, myfile->end);
        int size = myfile->tellg();

        char* contents = new char[size];
        myfile->seekg(0, myfile->beg);
        myfile->read(contents, size);
        std::cout << contents << std::endl;

        delete [] contents;
    }
}

void ifstream_read2() {
    StreamGuard<std::ifstream> file("example.txt");
    std::string contents((std::istreambuf_iterator<char>(*(file.operator->()))),
                std::istreambuf_iterator<char>());
    std::cout << contents << std::endl;
}

void ifstream_read3() {
    StreamGuard<std::ifstream> file("example.txt");
    std::vector<char> contents((std::istreambuf_iterator<char>(*(file.operator->()))),
            std::istreambuf_iterator<char>());
}

void ifstream_read4() {
    StreamGuard<std::ifstream> file("example.txt");
    std::stringstream buff;
    buff << file->rdbuf();
    std::string contents(buff.str());
    std::cout << contents << std::endl;
}

int main(void) {
    ofstream_write();

    ifstream_read1();
    ifstream_read2();
    ifstream_read3();
    ifstream_read4();

    return 0;
}
