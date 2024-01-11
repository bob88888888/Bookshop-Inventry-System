#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class System{
protected:
    string Dir = ("/Users/bobya/CLionProjects/BookshopInventry/book.csv");

public:
    void addBook() {
        vector<string> lines;
        string line;
        ifstream readFile;
        readFile.open(Dir);
        if (readFile.fail()) {
            cout << "Error with opening file" << endl;
        }
        while (getline(readFile, line)) {
            lines.push_back(line);
            //each line is an element in the vector. Element 1 is line 1, followed by line2 and so on
        }

        readFile.close();

        ofstream file;
        file.open(Dir, ios::app);//append mode
        if (file.fail()) {
            cout << "Error with opening file" << endl;
        }

        cout << "What is the title of the book?" << endl;
        string title;
        cin >> title;

        cout << "What is the ISBN of the book?" << endl;
        string ISBN;
        cin >> ISBN;

        cout << "Who is the author of the book?" << endl;
        string author;
        cin >> author;

        cout << "What year is the book published?" << endl;
        string year;
        cin >> year;

        cout << "How many of these book you would like to add to the inventory?" << endl;
        string quantity;
        cin >> quantity;

        cout << "What is the price of the book?" << endl;
        string price;
        cin >> price;

        file << title << "," << ISBN << "," << author << "," << year << "," << quantity << "," << price << endl;
        cout << "Book details written to file" << endl;
        file.close();
    }

    void changePrice() {
        vector<string> lines;
        string line;
        ifstream file;
        file.open(Dir);

        if (file.fail()) {
            cout << "Error with opening file" << endl;
        }

        cout << "Enter the title of the book where you want to edit: " << endl;
        string title;
        cin >> title;

        while (getline(file, line)) {
            lines.push_back(line);
            //each line is an element in the vector. Element 1 is line 1, followed by line2 and so on
        }
        file.close();
        for (const auto& row : lines){
            if (row.find( title) != string::npos){
                int comma = 0;
                for(int i; i < row.length();i++){
                    if(row[i] ==  *","){
                        comma += 1;
                        if(comma == 5){
                            cout << row[i::] << endl;
                        }
                    }

                }

            }
        }
    }

    void checkAvailability() {
        vector<string> lines;
        string line;

        ifstream file;
        file.open(Dir);

        if (file.fail()) {
            cout << "Error with opening file" << endl;
        }

        cout << "Enter the name of the book you want to look for: " << endl;
        string name;
        cin >> name;

        while (getline(file, line)) {
            lines.push_back(line);
            //each line is an element in the vector. Element 1 is line 1, followed by line2 and so on
        }

        file.close();

        bool found = false;
        for (const string &book: lines) {
            if (book.find( name) != string::npos){
                found = true;
                cout << "The book " << name << " is available in the inventory" << endl;
                cout << book << endl;
            }
        }
        if (!found){
            cout << "The book " << name << " is not available in the inventory" << endl;
        }
    }

    void deleteBook(){
       fstream file;
       file.open(Dir);
       string line;
       int count = 0;

       if (file.fail()){
           cout << "Error opening file" << endl;
       }

       vector<string> lines;
       while (getline(file, line)){
           lines.push_back(line);
       }

       file.close();

       cout << "Enter the book you want to delete: " << endl;
       string book;
       cin >> book;

       for (const string &i:lines){
           count += 1;
           if(i.find(book) != string::npos){
               lines.erase(lines.begin()+(count-1));
               break;
           }
       }

       ofstream writeFile;
       writeFile.open(Dir);

       if(writeFile.fail())
       {
           cout << "Error opening the file for writing" << endl;
       }

       count = 0;
        for (const string &i:lines){
            writeFile << lines[count] << endl;
            count++;
        }
    }

};
int main() {
    System s1;
    //s1.addBook();
    //s1.checkAvailability();
    s1.changePrice();
    //s1.deleteBook();
    return 0;
}
