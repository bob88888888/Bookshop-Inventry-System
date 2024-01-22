#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

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
        cout << "Book detail is written to file" << endl;
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

        cout << "Enter the title of the book that you want to change the price of: " << endl;
        string title;
        cin >> title;

        while (getline(file, line)) {
            lines.push_back(line);
            //each line is an element in the vector. Element 1 is line 1, followed by line2 and so on
        }
        file.close();
        for (auto& row : lines){
            if (row.find( title) != string::npos){
                int comma = 0;
                for(int i = 0; i < row.length();i++){
                    if(row[i] ==  ','){
                        comma += 1;
                        if(comma == 5){
                            cout << "The current price of the book is " << row.substr(i+1) << " pounds" << endl;
                            string current = row.substr(i+1);
                            cout << "Enter the price you want to change it to:" << endl;
                            string newprice;
                            //newprice = round(newprice * 100) / 100;
                            cin >> newprice;

                            double currentPrice = stof(current);
                            row.replace(i + 1, current.length(), newprice);

                            ofstream writeFile;
                            writeFile.open(Dir);

                            if(writeFile.fail())
                            {
                                cout << "Error opening the file for writing" << endl;
                            }

                            int count = 0;
                            for (const string &update:lines){
                                writeFile << lines[count] << endl;
                                count++;
                            }
                            cout << "The change is made" << endl;
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
       string line;
       file.open(Dir);
       int count = 0;

       if (file.fail()){
           cout << "Error opening file" << endl;
       }

       vector<string> lines;
       while (getline(file, line)){
           lines.push_back(line);
       }

       file.close();

       cout << "Enter the book you want to remove: " << endl;
       string book;
       cin >> book;

       cout << "How many of " << book << " do you want to remove?" << endl;
       int quan;
       cin >> quan;

       for (const string& l:lines){
           count += 1;
           if(l.find(book) != string::npos){
               int comma = 0;
               for(int i = 0; i < l.length(); i++) {
                   if (l[i] == ',') {
                       comma += 1;
                       if(comma == 4){
                           string current = l.substr(i+1);
                           int intCurrent = stoi(current);
                           if((intCurrent - quan) <= 0){
                               lines.erase(lines.begin()+(count-1));
                               break;
                           }
                           else{
                               string strQuan = to_string(quan);
                               l.replace(i + 1, current.length(), strQuan);
                           }
                           //cout << l[i+1] << endl;
                       }
                   }
               }

           }
       }
       cout << "Book is deleted from the inventory" << endl;

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

    cout << "What do you want to do?(type 1 to add a book, type 2 to check the availability of a book, type 3 to change"
            " the price of a book, type 4 to delete a book in the inventory):" << endl;
    int choice;
    cin >> choice;

    if(choice == 1){
        s1.addBook();
    }
    else if(choice == 2){
        s1.checkAvailability();
    }
    else if(choice == 3){
        s1.changePrice();
    }
    else if(choice == 4){
        s1.deleteBook();
    }
    return 0;
}
