
#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "customer.h"

using namespace std;

class CompanyPage : CustomerPage
{
private:
    // variables for companyPage
    bool isPaswordCorrect = false;
    string isNumCorrect = ""; // for product screen , it will keep not found result if proper answer don't come.

    // variables for product
    //  here the program keeps datas about product
#define KDV 18
    // classe's variables
    string productId;
    string productName;
    string producter;
    string deliveryTime;
    string productionDate;
    string price;
    string priceSpecial;
    string stock;
    int stockNum = 0;
    // whis variable stores line number in it when write function works. if we decided to continue to develop this program .
    // and add some more prodcut input datas so new lines this variable keep that and we dont have to edit some different parts of code (searchInProduct function)
    // now it is equal to 9 . if we will increase input datas about product it will increase via write function.
    short lines = 9;
    char addNew;

public:
    void myapp();

private:
    // it stores Product ID which is program running on at the moment.
    string workingOn;
    CustomerPage customer;
    // company page is like an admin and it can manage registered companies.
    void authorization()
    {
        // entrance infos.
        string userName = "mustafa";
        string passWord = "123";
        string username;
        string password;
        // header
        string stuff(30, '-');
        string stuffS(30, '*');
        system("cls");
        cout << stuffS << endl;
        cout << setw(10) << "\t Tech Company" << endl;
        cout << stuffS << endl;

        // here will be done by authentication() <-- it is in private section !!!
        cout << " -please authorize the entrance" << endl;
        cout << "name:";
        cin >> username;
        // cout << endl;

        cout << "password:";
        cin >> password;
        cout << endl;
        if (password == passWord && username == userName)
        {
            isPaswordCorrect = true;
            cout << "access succesful ! " << endl;
            system("PAUSE");
            system("cls");
            companyMainScr();
        }
        else
        {
            cout
                << "wrong username or password please try again...\n"
                << endl;
            system("PAUSE");
            system("cls");
            myapp();
        }
    }
    // company's main screen. it includes in it products , orders, customers
    void companyMainScr()
    {
        system("cls");
        int choosem = 0;
        cout << "\t1-Products " << endl;
        cout << "\t2-Orders " << endl;
        cout << "\t3-customers " << endl;
        cout << "\t4-go back " << endl;
        cout << isNumCorrect << endl;
        cout << " it's time to chose : ";
        cin >> choosem;
        switch (choosem)
        {
        case 1:
            // go product scr  for company
            isNumCorrect = "";
            productScr();
            break;
        case 2:
            // go order scr  for company
            isNumCorrect = "";
            orderScr();
            break;
        case 3:
            // go customer scr for company
            isNumCorrect = "";
            customerScr();
            break;
        case 4:
            // go back to entrance screen                                                   TODO , AUTHANTOTACİON FUNCTİON
            isNumCorrect = "";
            myapp();
            break;

        default:
            isNumCorrect = "*please enter valid number";
            system("cls");
            companyMainScr();
            break;
        }
    }
    // product screen
    void productScr()
    {
        // product screen
        system("cls");
        int choosem = 0;
        string stuff(40, '-');
        cout << stuff << endl;
        cout << " 1. add product " << endl;
        cout << " 2. search in products " << endl;
        cout << " 3. see products " << endl;
        cout << " 4. edit product " << endl;
        cout << " 5. delete product " << endl;
        cout << " 6. go back to main menu" << endl;
        cout << stuff << endl;
        cout << " it's time to chose : ";
        cin >> choosem; // we had better if we control cin against any wrong type input.
        cout << endl;
        cout << isNumCorrect << endl;
        // guidance via choosem input to access funcs.
        switch (choosem)
        {
        case 1:
            isNumCorrect = "";
            system("cls");
            addProduct();
            break;
        case 2:
            isNumCorrect = "";
            system("cls");
            searchInProduct(0);
            break;
        case 3:
            isNumCorrect = "";
            system("cls");
            listing();
            break;
        case 4:
            isNumCorrect = "";
            system("cls");
            editing(0);
            break;
        case 5:
            isNumCorrect = "";
            deleteProduct(0);
            break;
        case 6:
            isNumCorrect = "";
            companyMainScr();
            break;

        default:
            isNumCorrect = "*please enter valid number";
            system("cls");
            productScr();
            break;
        }
    }

    // given orders scr here our functions will be shown
    void orderScr()
    {
        system("cls");
        short choosem = 0;
        cout << " 1.see taken orders \n 2.search in taken orders \n 3.delete an order \n 4.delete all olders \n";
        cin >> choosem;
        customer.remote2(choosem);
        companyMainScr();
    }
    // company's customer page here customer funcs will be shown
    void customerScr()
    {
        system("cls");
        short choosem;
        // here our customers will be shown
        // in customer.h file an function will add customer to a txt and that txt will be read here. then ofcourse manupulating with new functions
        cout << "\t1.add customer" << endl;
        cout << "\t2.searching for customers" << endl;
        cout << "\t3.edit customers" << endl;
        cout << "\t4.removing customers" << endl;
        cout << "\t5.see all customers" << endl;
        cout << "\t6.go back" << endl;
        cin >> choosem;

        if (choosem < 6)
        {
            system("cls");
            customer.remote(choosem);
            customerScr();
        }

        else if (choosem > 6)
        {
            system("cls");
            cout << "\t--please make true choice ! ";
            system("pause");
            customerScr();
        }
        else
            companyMainScr();

        customerScr();
    }

    /**********************************************************************************/
    /****************************FUNCTİONS FOR PRODUCTS********************************/
    /**********************************************************************************/

    // this function is about adding products // collect information and send them to file writer func.
    void addProduct()
    {
        /*
        productId.clear();
        productName.clear();
        producter.clear();
        deliveryTime = "t0";
        productionDate.clear();*/

        cout << "please enter product ID : ";
        cin >> productId;
        // to make them different than others , i gave p head letter
        productId = "p" + productId;
        cout << endl;
        cout << "what is your product name ? ";
        cin >> productName;
        productName = productId + productName;
        cout << endl;
        cout << "produced by who ? ";
        cin >> producter;
        producter = productId + producter;
        cout << endl;
        cout << "what is the estimated time of arrival ? ";
        cin >> deliveryTime;
        // product id added because deliver time can be miserable with other product's deliver times. because it's value isn't uniq as 't4' but it is uniq with IDt4
        deliveryTime = productId + "t" + deliveryTime;
        cout << endl;
        cout << "what was the production date ? ";
        cin >> productionDate;
        productionDate = productId + "d" + productionDate;
        cout << endl;
        cout << "what is your product's price ? ";
        cin >> price;
        price = productId + "$" + price;
        cout << endl;
        cout << "what is your product's special price ? ";
        cin >> priceSpecial;
        priceSpecial = productId + "$" + priceSpecial;
        cout << endl;
        cout << "How many products do you have (stock) ? ";
        cin >> stockNum;
        stock = productId + "N" + to_string(stockNum);
        cout << endl;
        system("cls");
        writeProduct();
    }

    // it will write product informations to a file which are comes from addProduct() to local variables
    void writeProduct()
    {
        // to my txt file design , all data blocks starts with & symbol. one of thems starting is others end.
        lines = 0;
        fstream prdctFile;
        ostringstream tmpstr;  // temp string stream
        tmpstr << "&" << endl; // it is here because in future it will say , this product information chain is started .
        tmpstr << "*Product ID : " << productId;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Product name : " << productName;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Producter : " << producter;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Estimated deliver time : " << deliveryTime;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*production date : " << productionDate;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Price : " << price;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Special price : " << priceSpecial;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Kdv : " << to_string(KDV);
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*In Stock : " << stock;
        lines++;
        tmpstr << "#" << endl;

        prdctFile.open("products.txt", ios::in | ios::app); // ios::app --> open file in append mode

        if (!prdctFile.is_open())
        {
            cout << "your reques interrupted. Retriying...";
            writeProduct();
        }
        else
        {
            prdctFile << tmpstr.str(); // i think we have only one time write right
            prdctFile.close();
        }

        cout << "Do you want to add another product ? " << endl;
        cout << " press 'y' to add or any button to turn back" << endl;
        cin >> addNew;
        if (addNew == 'y')
        {
            addProduct();
        }
        else
        {
            productScr();
        }
    }
    // it shows you product infos , needs only Product ID as input
    // there is function paramater to choose working mode -- work for information || provide information to editing func.
    void searchInProduct(bool style)
    {

        // this func must have a bool value ,
        // when i acces it from another product operator it takes true value and it's working style depends on it.
        // when i acces it from just product menu it returns false and change its working type.

        string productId;
        string temp;
        string temp0;
        fstream read;

        // open products.txt file in read mode
        read.open("products.txt", ios::in);

        // looking for which product
        cout << "please enter product id : ";
        cin >> productId;
        system("cls");
        // to make productId proper format
        productId = "p" + productId;
        // to provide information to edit func // it works when editting func call search func:
        if (style)
            workingOn = productId;
        // reading datas from file to temp0 string
        while (getline(read, temp))
        {
            temp0.append(temp);
        }
        temp.clear();
        // cout specified product informations.
        // found location productId text.
        size_t found = temp0.find(productId);
        // npos's value = -1 so found can't be -1 therefore this if statement searching all string :DD --hope i got it right :DDDDD

        if (found != string::npos)
        {

            // so here if product id is true , the infos about that product will be print
            cout << "Product ID : ";
            // here product id printing
            for (short i = 0; i < productId.length(); i++)
            {
                cout << temp0[found + i];
            }
            cout << "\n";
            // that will keep first star after productId so it means we are starting to print with product name
            size_t firstStar = temp0.find('*', found);
            size_t firstSquare = temp0.find('#', firstStar);

            // printing product name --> product's second line
            for (short i = firstStar + 1; i < firstSquare; i++)
            {
                cout << temp0[i];
            }
            cout << "\n";

            // printing rest of the lines *** lines variable declared top of the class and counted in writeProduct function.
            for (short i = 0; i < lines - 2; i++)
            {
                // prepare locations to find next star and square
                firstStar = temp0.find('*', firstSquare);
                firstSquare = temp0.find('#', firstStar);

                // prints next line
                for (short i = firstStar + 1; i < firstSquare; i++)
                {
                    cout << temp0[i];
                }
                cout << "\n";
            }
        }
        else
        {
            cout << "The product you just entered was not in our list\nentered value : " << productId << endl;
            system("pause");
            productScr();
        }
        read.close();
        cout << "Press Enter to go back ";
        system("pause");

        // working style/mode
        if (style == true)
        {
            style = false;
        }
        else
        {
            productScr();
        }
    }

    // listing function--it lists every product company have. May i can work on it more.   --TODO //
    void listing()
    {
        ifstream read;
        string temp;
        string data;
        read.open("products.txt", ios::in);
        // read data from txt to string
        while (getline(read, temp))
        {
            data.append(temp);
        }
        string b = "#";      // finish data line
        string f = "&";      // finish data block
        short itemCount = 0; // it keeps "&" count . so that means is how much product i have .
        string c;
        for (short i = 0; i < data.length(); i++)
        {
            c = data[i];
            if (c == b)
            {
                cout << c << endl;
            }
            else if (c == f)
            {
                itemCount++;
                cout << c << endl;
            }
            else
                cout << data[i];
        }
        cout << "\n"
             << "--you got " << itemCount << " products on your list.\n"
             << endl;

        read.close();
        temp.clear();
        data.clear();
        system("pause");
        productScr();
    }
    // it edits product
    void editing(bool style)
    {
        ifstream productRead;
        ofstream productWrite;
        // working style/mode
        // go searchInProduct
        if (!style)
        {
            cout << "Which product do you want to edit\n";
            searchInProduct(1);
            editing(1);
        }
        else
        {
            productRead.open("products.txt", ios::in);
            short chosem;
            string temp;
            string edit;
            string data;
            short tmp;
            // write products datas to variable data
            while (getline(productRead, temp))
            {
                data.append(temp);
            }
            temp.clear();

            cout << '\n'
                 << "which property you want to chance \n\n1.ID\n2.Name\n3.Productor\n4.Deliver Time\n5.Production date\n6.Price\n7.Special Price\n8.Stock\n\t---->";
            cin >> chosem;

            switch (chosem)
            {
            case 1: // reID
                productWrite.open("products.txt");
                cout << "\tplease enter old ID --";
                cin >> temp;
                // make temp proper Id format
                temp = "p" + temp;
                cout << "\tplease enter new ID --";
                cin >> edit;
                // make edit proper Id format
                edit = "p" + edit;

                // do it lines-1 times(-1 because of kdv constant and haven't got any uniq number-production ID-)
                for (short i = 0; i < lines - 1; i++)
                {
                    // replacing all ID headers from target product except kdv line because kdv is an constant and do not need uniq header
                    tmp = data.find(temp);
                    data.replace(tmp, temp.length(), edit);
                }
                break;

            case 2: // rename
                productWrite.open("products.txt");
                cout << "\tplease enter old name --";
                cin >> temp;
                temp = workingOn + temp;
                cout << "\tplease enter new name --";
                cin >> edit;
                edit = workingOn + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;

            case 3: // reProductor
                productWrite.open("products.txt");
                cout << "\tplease enter old productor --";
                cin >> temp;
                temp = workingOn + temp;
                cout << "\tplease enter new productor --";
                cin >> edit;
                edit = workingOn + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;

            case 4: // reTime                 we are here
                productWrite.open("products.txt");
                cout << "\tplease enter old deliver Time (day) --";
                cin >> temp;
                temp = workingOn + "t" + temp;
                cout << "\tplease enter new deliver time --";
                cin >> edit;
                edit = workingOn + "t" + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                workingOn.clear();
                break;
            case 5: // reProductionDate
                productWrite.open("products.txt");
                cout << "\tplease enter old production date --";
                cin >> temp;
                temp = workingOn + "d" + temp;
                cout << "\tplease enter new production date --";
                cin >> edit;
                edit = workingOn + "d" + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;
            case 6:
                productWrite.open("products.txt");
                cout << "\tplease enter old price --";
                cin >> temp;
                temp = workingOn + "$" + temp;
                cout << "\tplease enter new price --";
                cin >> edit;
                edit = workingOn + "$" + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;
            case 7:
                productWrite.open("products.txt");
                cout << "\tplease enter old special price --";
                cin >> temp;
                temp = workingOn + "$" + temp;
                cout << "\tplease enter new special price --";
                cin >> edit;
                edit = workingOn + "$" + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;
            case 8:
                productWrite.open("products.txt");
                cout << "\tplease enter old stock --";
                cin >> temp;
                temp = workingOn + "N" + temp;
                cout << "\tplease enter new stock --";
                cin >> edit;
                edit = workingOn + "N" + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;
            default:
                cout << "please enter valid number" << endl;
                editing(1);
                break;
            }

            // here data written proper format
            string b = "#"; // finish data line
            string f = "&"; // finish data block
            string c;
            for (short i = 0; i < data.length(); i++)
            {
                c = data[i];
                if (c == b)
                {
                    productWrite << c << endl;
                }
                else if (c == f)
                    productWrite << c << endl;
                else
                    productWrite << data[i];
            }
            // reset else block to do another process for future
            productRead.close();
            productWrite.close();
            data.clear();
            temp.clear();
            edit.clear();
            tmp = 0;
            chosem = 0;
            productScr();
        }
        productRead.close();
    }
    // it deletes products from products.txt
    void deleteProduct(bool style)
    {
        // verify deletion
        string chosem;
        ifstream productRead;
        ofstream productWrite;

        // working style/mode
        // go searchInProduct

        if (!style)
        {
            cout << "which product you want to delete\n";
            searchInProduct(1);
            deleteProduct(1);
        }
        else
        {
            productRead.open("products.txt", ios::in);

            string temp;
            string data;
            short tmp;
            // write products datas to variable data
            while (getline(productRead, temp))
            {
                data.append(temp);
            }
            temp.clear();
            //
            temp = "&*Product ID : " + workingOn + "#";

            // found stores target datas start location , function will starts deleting from here
            int start = data.find(temp);
            temp = "&";
            // last stores ,next '&' sign --> it means product data chain ended .so function will finishes deleting from here.
            int last = data.find(temp, start + 1);

            // make this minus operation because erase method calculate end of iteration start+lenght=last point
            last -= start;

            // ask for permission to delete.
            cout << "are you sure for deleting " << workingOn << " product ?"
                 << "\n"
                 << "\t(y/n)--";
            cin >> chosem;
            if (chosem == "y")
            {
                // deleting target datas from data string
                data.erase(start, last);
            }
            else
            {
                cout << "operation canceled..." << endl;
                system("pause");
                productScr();
            }

            // write editted data to txt

            // here data written proper format
            productWrite.open("products.txt");
            string b = "#"; // finish data line
            string f = "&"; // finish data block
            string c;
            for (short i = 0; i < data.length(); i++)
            {
                c = data[i];
                if (c == b)
                {
                    productWrite << c << endl;
                }
                else if (c == f)
                    productWrite << c << endl;
                else
                    productWrite << data[i];
            }
        }

        productRead.close();
        productWrite.close();
        productScr();
    }
};