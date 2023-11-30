#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class function{
protected:
    virtual void addBook() = 0;

    virtual void checkAvailability() = 0;

    virtual void modifyBookRecord() = 0;

    virtual void deleteBookRecord() = 0;
};

class Read_file{
protected:
    string line;
    ifstream myfile;
    string Dir = ("/Users/bobya/CLionProjects/BookshopInventry/book.txt");

protected:
    void printLine() {
        myfile.open(Dir);

        if (!myfile.is_open()) {
            cout << "Error opening file." << endl;// Return a non-zero value to indicate an error
        }

        while (getline(myfile, line)){
            cout << line << endl;
        }
        myfile.close();
    }
};

class System: public function{
protected:
    string line;
    ifstream myfile;
    string Dir = ("/Users/bobya/CLionProjects/BookshopInventry/book.txt");

public:
    void addBook() override{

    }

};
int main() {
    Read_file f1;
    f1.printLine();
    return 0;
}
