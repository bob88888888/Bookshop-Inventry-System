#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class System {
protected:
    string Dir;
    int choice;

public:
    System(){
        Dir = ("/Users/bobya/CLionProjects/BookshopInventry/book.csv");
        choice=0;
    }

    void setChoice(int choice) {
        this->choice = choice;
    }

    int getChoice(){
        return choice;
    }

    virtual void detail(){
        cout << "Enter detail of the book" << endl;
    }

};

class addBook : public System{
private:

    string Title;
    string ISBN;
    string Author;
    string Year;
    string Quantity;
    string Price;

public:
    addBook(){
        Title="";
    }

    void detail(){
        cout << "What is the title of the book?" << endl;
        string title;
        cin >> title;
        Title = title;

        cout << "What is the ISBN of the book?" << endl;
        string isbn;
        cin >> isbn;
        ISBN = isbn;

        cout << "Who is the author of the book?" << endl;
        string author;
        cin >> author;
        Author = author;

        cout << "What year is the book published?" << endl;
        string year;
        cin >> year;
        Year = year;

        cout << "How many of these book you would like to add to the inventory?" << endl;
        string quantity;
        cin >> quantity;
        Quantity = quantity;

        cout << "What is the price of the book?" << endl;
        string price;
        cin >> price;
        Price = price;
    }

    void addToCSV(){
        //open file in append mode
        ofstream file;
        file.open(Dir, ios::app);

        file << Title << "," << ISBN << "," << Author << "," << Year << "," << Quantity << "," << Price << endl;
        cout << "Book detail is written to file" << endl;
        file.close();
    }
};

class changePrice : public System {
private:
    string Price;
    string Title;
    string dir;

public:
    changePrice() {
        Price = "£0";
        Title = "";
        dir = this->Dir;

    }

    void getBook() {
        cout << "Enter the title of the book you want to change the price of: " << endl;
        string title;
        cin >> title;
        Title = title;

        vector<string> lines;
        string line;
        ifstream file;
        file.open(Dir);

        if (file.fail()) {
            cout << "Error with opening file" << endl;
        }
        while (getline(file, line)) {
            lines.push_back(line);
            //each line is an element in the vector. Element 1 is line 1, followed by line2 and so on
        }
        file.close();

        bool showed = false;
        for (string &row: lines) {
            if (row.find(Title) != string::npos) {
                int comma = 0;
                for (int i = 0; i < row.length(); i++) {
                    if (row[i] == ',' && !showed) {
                        comma += 1;
                        if (comma == 5) {
                            cout << "The current price of the book is " << row.substr(i + 1) << " pounds" << endl;
                            showed = true;

                        }
                    }
                }
            }
            //stops program from running the print statement again if statement is printed once
            else{
                break;
            }
        }
    }

    void setPrice(){
        vector<string> lines;
        string line;
        ifstream file;
        file.open(Dir);

        if (file.fail()) {
            cout << "Error with opening file" << endl;
        }

        while (getline(file, line)) {
            lines.push_back(line);
            //each line is an element in the vector. Element 1 is line 1, followed by line2 and so on
        }
        file.close();

        for (string& row : lines){
            if (row.find(Title) != string::npos){
                int comma = 0;
                for(int i = 0; i < row.length();i++){
                    if(row[i] == ','){
                        comma += 1;
                        if(comma == 5){

                            string current = row.substr(i+1);

                            cout << "Enter the price you want to change it to:" << endl;
                            string newprice;
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
                            cout << "The change of the price of the book has been updated" << endl;
                        }
                    }
                }
            }
        }
    }
};

class checkAvailability : public System{
private:
    string Title;
    bool found;

public:
    checkAvailability(){
        Title = "";
        found = false;
    }

    void detail(){
        cout << "Enter the title of the book you want to look for: " << endl;
        string title;
        cin >> title;
        Title = title;
    }

    void findBook(){
        vector<string> lines;
        string line;

        ifstream file;
        file.open(Dir);

        if (file.fail()) {
            cout << "Error with opening file" << endl;
        }

        while (getline(file, line)) {
            lines.push_back(line);
            //each line is an element in the vector. Element 1 is line 1, followed by line2 and so on
        }

        file.close();

        for (const string &book: lines) {
            if (book.find( Title) != string::npos){
                found = true;
                cout << "The book " << Title << " is available in the inventory" << endl;
                cout << book << endl;
            }
        }
        if (!found){
            cout << "The book " << Title << " is not available in the inventory" << endl;
        }
    }
};

class deleteBook : public System{
private:
    string Title;
    int Quantity;

public:
    deleteBook(){
        Title = "";
        Quantity = 0;

    }

    void Detail(){
        cout << "Enter the book you want to remove: " << endl;
        string book;
        cin >> book;
        Title = book;

        cout << "How many of " << Title << " book do you want to remove?" << endl;
        int quan;
        cin >> quan;
        Quantity = quan;
    }

    void deleteFromCSV(){
        vector<string> lines;
        fstream file;
        string line;

        file.open(Dir);
        int count = 0;

        if (file.fail()){
            cout << "Error opening file" << endl;
        }

        while (getline(file, line)){
            lines.push_back(line);
        }

        file.close();
        for (string& l:lines){
            count += 1;
            if(l.find(Title) != string::npos){
                int comma = 0;
                for(int i = 0; i < l.length(); i++) {
                    if (l[i] == ',') {
                        comma += 1;
                        if(comma == 4){
                            string current = l.substr(i+1);
                            int intCurrent = stoi(current);
                            if((intCurrent - Quantity) <= 0){
                                lines.erase(lines.begin()+(count-1));
                                cout << "There are not enough books in the inventory and therefore the series of book is deleted from the inventory" << endl;
                                break;
                            }
                            else{
                                string LeftInInventory = to_string(intCurrent - Quantity);
                                l.replace(i + 1, 1, LeftInInventory);
                                break;
                            }
                        }
                    }
                }

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
        cout << "The corresponding books are removed" << endl;
    }

};


int main() {
    while (true){
        cout << "What do you want to do?(type 1 to add a book, type 2 to check the availability of a book, type 3 to change"
                " the price of a book, type 4 to remove books in the inventory):" << endl;
        int choice;
        //addBook newObject;
        cin >> choice;

        System s1;
        s1.setChoice(choice);
        choice = s1.getChoice();

        if (choice == 1) {
            addBook add;
            add.detail();
            add.addToCSV();
        }

        else if(choice == 3){
            changePrice c1;
            c1.getBook();
            c1.setPrice();
        }

        else if(choice == 2){
            checkAvailability check1;
            check1.detail();
            check1.findBook();
        }

        else if(choice == 4){
            deleteBook d1;
            d1.detail();
            d1.deleteFromCSV();
        }

        cout << "Is there anything else you want to do?(enter Y for yes or N for no)" << endl;
        string again;
        cin >> again;
        if(again == "Y"){
            continue;
        }
        else if(again == "N"){
            break;
        }
    }
    return 0;
}
