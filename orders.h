#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <filesystem>
using namespace std;

class Orders
{

private:
    // classe's variables
    string customerId;
    string productIdWhollbeMinus;
    fstream file;
    string workinOn;
    stringstream orderTemplate;
    short lines = 9;

public:
    // remote function for customer class
    void remote(short whichFuncIllRun, string id)
    {
        // all cases functions takes id as paramatre because same functions can manipule more than one files/customer's orders.
        switch (whichFuncIllRun)
        {
        case 1: // 1. give orders
            addOrder(id);
            removeOrders(id);
            writeOrders(id);
            minusProductStockNum();
            break;
        case 2:
            // go search func with 0 value so it means work normal mode, just write what we are search
            searchInOrders(id);
            break;
        case 3:
            // go delete function with 0 value so it means i call you from console not from another function .
            deleteOrder(id, 0);
            removeOrders(id);
            writeOrders(id);
            break;
        case 4: // listing given orders in id.txt file
            listOrders(id);
            break;
        case 5:
            removeOrders(id); // remove orders from orders.txt

            break;
        default:
            // it is here because of zero posibility
            cout << "please enter valid number.\n";
            system("pause");
            break;
        }
    }
    // remote function for company class
    void remote2(short whichFuncIllRun)
    {
        string idd;
        switch (whichFuncIllRun)
        {
        case 1: // list all orders
            listMainOrders();
            break;
        case 2: // make search for orders
            searchInOrderstxt();
            break;
        case 3:
            cout << "Which customer's order you want to remove (as number) ?" << endl;
            cin >> idd;
            idd = "C" + idd;
            removeOrders(idd); // remove an orders from orders.txt
            break;
        case 4: // delete all orders
            deleteAllOrders();
            break;
        default:
            break;
        }
    }

private:
    // this function works when we want to give order , it lists products
    void seeProducts()
    {
        // open file in read mode
        file.open("products.txt", ios::in);
        // local variables
        string temp;
        string data;
        if (file.good())
        {
            // read data from txt to string
            while (getline(file, temp))
            {
                data.append(temp);
            }
            string b = "#";      // finish data line
            string f = "&";      // finish data block
            short itemCount = 0; // it keeps "&" count . so that means is how much product i have .
            string c;
            // cout data string to console in proper format.
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
                 << "-- " << itemCount << " products available now.\n"
                 << endl;

            file.close();
            temp.clear();
            data.clear();
        }
        else
        {
            cout << "products.txt couldn't opened.";
            seeProducts();
        }
    }

    // it is backround function , it will find related product's data when we are ordering product.
    void searchProducts()
    {
        string productId;
        string temp;
        string temp0;
        fstream read;
        short lines = 9;
        // orderTemplate.clear();
        //  open products.txt file in read mode
        read.open("products.txt", ios::in);

        // clearin order template to prepare next working , .clear() can't work with it i have to use this
        // the reason clear() doesnt work is that clear() clears erorrs :D not contents.
        orderTemplate.str("");

        // looking for which product
        cout << "please enter product id (as number): ";
        cin >> productId;
        system("cls");
        // to make productId proper format
        productId = "p" + productId;
        // provide this information (product Id) for minusing product stock num operation. for every ordering
        productIdWhollbeMinus = productId;

        // reading datas from file to temp0 string
        while (getline(read, temp))
        {
            temp0.append(temp);
        }
        temp.clear();

        // found location productId text.
        size_t found = temp0.find(productId);

        // npos's value = -1 so found can't be -1 therefore this if statement searching all string :DD --hope i got it right :DDDDD
        if (found != string::npos)
        {
            // so here if product id is true , the infos about that product will be print
            cout << "*Product ID : ";
            orderTemplate << "&\n";
            orderTemplate << "*Product ID : ";
            // here product id line printing --id#
            for (short i = 0; i < productId.length(); i++)
            {
                cout << temp0[found + i];
                orderTemplate << temp0[found + i];
            }
            cout << "#\n";
            orderTemplate << "#\n";

            // that will keep first star after productId so it means we are starting to print with product name
            size_t firstStar = temp0.find('*', found);
            size_t firstSquare = temp0.find('#', firstStar);

            // printing product name --> product's second line
            for (short i = firstStar; i < firstSquare + 1; i++)
            {
                cout << temp0[i];
                orderTemplate << temp0[i];
            }
            cout << "\n";
            orderTemplate << "\n";

            // printing rest of the lines *** lines variable declared top of the class and counted in writeProduct function.
            for (short i = 0; i < lines - 2; i++)
            {
                // prepare locations to find next star and square
                firstStar = temp0.find('*', firstSquare);
                firstSquare = temp0.find('#', firstStar);

                // prints next line
                for (short i = firstStar; i < firstSquare + 1; i++)
                {
                    cout << temp0[i];
                    orderTemplate << temp0[i];
                }
                cout << "\n";
                orderTemplate << "\n";
            }
        }
        else
        {
            cout << "The product you just entered was not in list\nentered value : " << productId << endl;
            system("pause");
        }
        temp0.clear();
        read.close();
        system("pause");
    } // are we gonna explore america . //yes we are :d

    // it is give order function
    void addOrder(string Id)
    {
        // make customer id proper format.--> opens customers order list.
        customerId = Id + ".txt";

        // list tech company's products
        seeProducts();

        // open file which contain orders in it.
        // i opened file after seeProducts() because when see products working file object is busy already.--previously i open the file out of while loop
        // also before of seeProducts function so it throws error--an file object can't open two txt files in succesion.
        file.open(customerId, ios::app);
        string verify;
        cout << "\t----ordering---\t\n"
             << endl;
        // choose which product you want to order
        searchProducts();
        // verifiying order request
        cout << "please verify your order,write 'verify'.\n----";
        cin >> verify;
        if (verify == "verify")
        {
            // write choosed product to customer's order txt file --customerId.txt
            // a little bit control about is data written to file or not.
            if (file.good())
            {
                file << orderTemplate.str();
                cout << "Your order has been taken\n.";
            }

            else
            {
                cout << "something goes wrong please renter program.\n\t\ttechnical glitch...";
                file.close();
                system("pause");
                system("exit");
            }
        }
        else
        {
            cout << "\n\torder canceled.";
        }
        system("pause");
        // close the file
        file.close();
    }

    // it is search function for searching in order list.
    void searchInOrders(string id)
    {
        // open customerid.txt file in read mode
        file.open((id + ".txt"), ios::in);

        string productId;
        string temp;
        string temp0;
        // looking for which product.
        cout << "please enter product id (as number): ";
        cin >> productId;
        system("cls");
        // to make productId proper format
        productId = "p" + productId;
        workinOn = productId;
        // reading datas from file to temp0 string
        while (getline(file, temp))
        {
            temp0.append(temp);
        }
        temp.clear();

        // cout specified product informations.
        //----------------------------------------------------------------------//

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
            cout << "The product you just entered was not in given orders list\nentered value : " << productId << endl;
        }
        file.close();
        system("pause");
    }

    void deleteOrder(string id, bool style)
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
            searchInOrders(id); // go search and attepmt workinOn a value-->product ID
            deleteOrder(id, 1); // come this func with true value --> means pass else block because you have workinOn (which product we are working on) id.
        }
        else
        {
            // open id.txt file in read mode
            productRead.open((id + ".txt"), ios::in);
            // local variables
            string temp;
            string data;
            short tmp;
            // write products datas to variable data
            while (getline(productRead, temp))
            {
                data.append(temp);
            }
            temp.clear();
            // use temp again for data saving.
            // prepare temp to found first data block dataline.
            temp = "&*Product ID : " + workinOn + "#";

            // found stores target datas start location , function will starts deleting from here
            int start = data.find(temp);
            temp = "&";
            // last stores ,next '&' sign --> it means product data chain ended .so function will finishes deleting from here.
            int last = data.find(temp, start + 1);

            // make this minus operation because erase method calculate end of iteration start+lenght=last point
            last -= start;

            // ask for permission to delete.
            cout << "are you sure for deleting " << workinOn << " product ?"
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
            }

            // write editted data to txt

            // here data writing in proper format
            productWrite.open((id + ".txt"));
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
    }

    void listOrders(string id)
    {
        // opening customer order file.
        file.open(id + ".txt", ios::in);
        string temp;
        string data;
        // a little bit controlling.
        if (file.good())
        {
            // read data from txt to data string
            while (getline(file, temp))
            {
                data.append(temp);
            }
            string b = "#";      // finish data line
            string f = "&";      // finish data block
            short itemCount = 0; // it keeps "&" count . so that means is how much product i have .
            string c;
            // cout data string to console in proper format.
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
            file.close();
            temp.clear();
            data.clear();
            system("pause");
        }
        else
        {
            cout << id << ".txt couldn't opened.";
            system("pause");
        }
    }

    //*******************************************************//
    //********************gang bang**************************//
    //*******************************************************//
    //**********i congrat myself , well done to me***********//

    // it returns true if customer is special  --> this function used by pricing() function.
    // returns false if customer is common
    bool customerType(string id)
    {
        fstream file;
        // customers.txt searching for common or special
        // string common=id+"T"+"common"; unnecessary
        string special = id + "T" + "special";

        // temp variables for read task
        string temp;
        string temp0;
        file.open("customers.txt", ios::in);

        // reading datas from file to temp0 string
        while (getline(file, temp))
        {
            temp0.append(temp);
        }
        temp.clear();
        file.close();
        // return true if you found id+special keyword , if you didn't find return false.
        if (temp0.find(special))
            return true;
        else
            return false;
    }

    // this function returns price as double . to sum up it reads all id$price information and add them together then returns them.
    double pricing(string id)
    {
        fstream file;
        // opening id.txt file for reading data to in
        file.open(id + ".txt", ios::in);

        // temp variables for read task
        string temp;
        string temp0;
        double price = 0;

        // variables looking var in txt
        string special = "*Special price";
        string common = "*Price";
        // firstly program will find string special's found for which line we are working on. to prevent confuse about prices.
        // then after special's location program will start searching for dollar symbol. in txt file price is written after $ symbol.
        // task is simple , find Special price line with uniq id then find dollar symbol , then read price finally stop reading when reach '#' symbol.
        // save price in temp file then try to convert it to double :DDDDD
        string dollar = "$";

        // reading datas from file to temp0 string
        while (getline(file, temp))
        {
            temp0.append(temp);
        }
        temp.clear();
        file.close();

        // here a while loop may be required--> it'll work how many products list have . --> '&' counter
        string end = "&"; // next for loop will find end sign that means : I have as many products as end sign
        string c;         // c is a temp variable, will equal to temp0's character then next character then then then...
        short count = 0;  // stores which product id.txt file has . next steps our function will make search for prices . functions will need how many product are there in list.
        for (int i = 0; i < temp0.length(); i++)
        {
            c = temp0[i];
            if (c == end)
                count++;
        } // im writing code like goddless

        // pricing...
        short founded = 0;
        if (customerType(id))
        {
            // true special pricing...
            for (short i = 0; i < count; i++)
            {
                // here for special
                int found = temp0.find(special, founded);
                founded = found + 1;
                // dollar symbol after special's location
                int firstDollar = temp0.find(dollar, found);
                // square symbol after special string
                int firstSquare = temp0.find('#', found);

                for (short i = firstDollar + 1; i < firstSquare; i++)
                {
                    temp.push_back(temp0[i]);
                }
                // converting string to double and add up all special prices  .
                price += stod(temp);
                temp.clear();
            }
        }
        else
        {
            // same steps , actually i copied and pasted same code in if .the only change is in found. Now we are finding common string
            // false, only Price pricing...
            for (short i = 0; i < count; i++)
            {
                // here for special
                int found = temp0.find(common, founded);
                founded = found + 1;
                // dollar symbol after common's location
                int firstDollar = temp0.find(dollar, found);
                // square symbol after common string
                int firstSquare = temp0.find('#', found);

                for (short i = firstDollar + 1; i < firstSquare; i++)
                {
                    temp.push_back(temp0[i]);
                }
                // converting string to double and add up all common prices  .
                price += stod(temp);
                temp.clear();
            }
        }
        return price;
    }

    // here, given orders writted to orders.txt by this func. orders file is main file for company it includes price data and ordered products data in it.
    void writeOrders(string id)
    {
        // opened in append mode because we are adding something new :D
        file.open("orders.txt", ios::app);
        stringstream template1;
        template1 << "&" << endl;
        template1 << "*Orderer ID : " << id << "#" << endl;
        template1 << "*Order date : " << id << "T" << __DATE__ << "#" << endl;
        template1 << "*Order total : " << id << "$" << pricing(id) << "#" << endl;
        template1 << "*Order file : " << id << ".txt"
                  << "#" << endl;
        template1 << "*Order owner : "
                  << "tech company#" << endl;
        file << template1.str(); // swrite template1 to file
        template1.str("");       // clear template1 to prepare next calling.
        file.close();
    }

    // it returns product's start and end location in order.txt as string.--->(start,end)
    string searchInOrdersTxt(string id)
    {
        // temp varibles for reading data from file to strings .
        string temp;
        string temp0;
        int start; // start of target data block
        int end;   // end of target data block
        string location;
        // open file in read mode
        file.open("orders.txt", ios::in);
        // reading datas from file to temp0 string
        while (getline(file, temp))
        {
            temp0.append(temp);
        }
        temp.clear();
        file.close();
        // for saving memory use temp variable again. next task is found location where data starts and end.
        temp = "*Orderer ID : " + id + "#";

        // now here is important.in if's condition i said , if you find id in any location
        //(so it means not -1 because -1 is not a location. locations must be nature numbers which is start from 0.)
        // run.
        // if id couldn't found in temp0 then this query -.find()- returns -1.
        if (temp0.find(id) != -1)
        {
            start = temp0.find(temp);                                   // start is equal to begining of searched data. it points '*' . start-1 points '&' so it means the data block we wanted to detect.
            end = temp0.find("&", start);                               // end will find next product's start sign '&'. end-1 points our target block last character it is '#'
            location = to_string(start) + "," + to_string(end - start); // converting integers to string,i made end-start becase erase methods second parametr is distance.
        }
        else
        {
            location = "0,0"; // it means didn't found.
        }

        return location;
    }

    // if we remove an order in id.txt , then this func. delete that customers order data from orders.txt
    // and replace it with new id.txt . and ofcourse new pricing.
    void removeOrders(string id)
    {
        // local variables
        // location var. keeps target customer's data block's start and end information.
        string location = searchInOrdersTxt(id);
        string temp;
        string temp0;
        int start; // target block's starting location
        int end;   // target blocks end distance.

        // in condition part, if location 0,0 -which is mine define in searchInOrdersTxt()- target customer id didn't found so pass if block.
        if (location != "0,0")
        { // read location data before of comma is start position , after from comma is end distance.
            for (short i = 0; i < location.length(); i++)
            { // when you see coma stop and pass else block then make equal which you read to start and clear that you read from temp .
                // then continue to read when reading is done make equal which you got to end . finally clear temp str because we will use it next steps again and again.
                if (location[i] != ',')
                {
                    temp.push_back(location[i]);
                }
                else
                {
                    start = stoi(temp);
                    temp.clear();
                }
            }
            end = stoi(temp);
            temp.clear();
            // erasing time
            file.open("orders.txt", ios::in);
            // reading datas from file to temp0 string
            while (getline(file, temp))
            {
                temp0.append(temp);
            }

            // the main task is here guysssssss erasinggggg. we had wrote lot's of lines for this line . epic moment... respect for me...
            // start -1 because data blocks start with & symbol but start doesnt cover . start-1 is covering & symbol.
            // we pulled back the start (start location information) so if we want to remove all data block we must add 1 to distance (end)
            temp0.erase(start - 1, end + 1); // erasing on str.
            // close read file
            file.close();

            // open orders file in out mode.
            file.open("orders.txt", ios::out);
            // write str to file as data line . one line . no formating for readability.
            file << temp0;
            // close write file
            file.close();
            // format our one line data . -data block gains readability-
            formating("orders.txt");
        }
    }
    // minusing product stock number by 1 for every order.
    void minusProductStockNum()
    {
        // local variables
        // productIdWhollbeMinus comes from searcProducts method
        int inte;
        string temp;
        string temp0;
        string target = "*In Stock : " + productIdWhollbeMinus; // first data block target to find.
        int trgt;                                               // first target start location
        int trgt2;
        // open file in read mode and write to string .
        file.open("products.txt", ios::in);
        // writing to string
        while (getline(file, temp))
        {
            temp0.append(temp);
        }
        // clear temp for using at another steps
        temp.clear();
        // close file to complate writing.
        file.close();
        // find target string in products txt file.
        trgt = temp0.find(target);
        // find product id from trgt location .
        trgt2 = temp0.find(productIdWhollbeMinus, trgt); // now trgt2 has our target data block's stock information's id's start location.
        // using trgt to store first # sign to provide when will reading opeartion stops .
        trgt = temp0.find("#", trgt2);
        // here , pulling trgt2's location after product Id because we want to obtain stock number information. --> in file *In Stock : p02N25000#
        trgt2 += productIdWhollbeMinus.length() + 1; //+1 because of data line include N char before stock num after product Id. we must pass N to obtain stock num.

        // here stock number space is here . Between trgt2 and trgt.
        // pull stock num data to temp string
        for (short i = 0; i < trgt - trgt2; i++)
        {
            char c = temp0[trgt2 + i];
            temp.push_back(c);
        }
        // convert temp string -which includes stock num data- to integer -inte variable-
        inte = stoi(temp);
        // minusing inte variable by 1 , so it means we are decreasing stock number.
        inte--;
        // controling stock number, if it will be zero , so write products.txt to out of stock
        if (inte > 0)
        {
            temp = to_string(inte);
        }
        else
        {
            temp = " out of stock#\n";
        }
        // replacing editted(new) stock num or "out of stock"
        temp0.replace(trgt2, temp.length(), temp);
        // open file out mode to write
        file.open("products.txt", ios::out);
        file << temp0;
        file.close();
        // formating written data to gain readibility.
        formating("products.txt");
    };

    // formating document format. it make file readable.
    void formating(string fileNameTxt)
    {
        // local variables
        string temp0;
        string temp;
        // open file in read mode
        file.open(fileNameTxt, ios::in);
        // read file to local string
        while (getline(file, temp))
        {
            temp0.append(temp);
        }
        file.close();

        // open file in out mode .
        file.open(fileNameTxt, ios::out);
        string b = "#"; // finish data line
        string f = "&"; // finish data block
        string c;
        // write string in proper format to file
        for (short i = 0; i < temp0.length(); i++)
        {
            c = temp0[i];
            if (c == b)
            {
                file << c << endl;
            }
            else if (c == f)
                file << c << endl;
            else
                file << temp0[i];
        }
        file.close();
    }
    // open file in out mode then close technicly it looses it's datas because of out mode.
    void deleteAllOrders()
    {
        file.open("orders.txt", ios::out);
        file.close();
    };
    // printing main order list to screen
    void listMainOrders()
    {
        string temp0;
        string temp;
        // open orders file in read mode.
        file.open("orders.txt", ios::in);

        while (getline(file, temp))
        {
            temp0.append(temp);
        }

        // close write file
        file.close();
        // here our given orders will be shown
        // in customer.h file , an function will operate on an txt file an order scr function can manipulate that txt file.
        cout << "\b\t****taken orders****\n-total:\n";

        string b = "#"; // finish data line
        string f = "&"; // finish data block
        string c;
        // write string in proper format to console
        for (int i = 0; i < temp0.length(); i++)
        {
            c = temp0[i];
            if (c == b)
            {
                cout << c << endl;
            }
            else if (c == f)
                cout << c << endl;
            else
                cout << temp0[i];
        }
        system("pause");
    }
    // searching operation in main order list
    void searchInOrderstxt()
    {
        // local variables
        string id;
        string location;
        string temp;
        string temp0;
        int start;
        int end;
        // interface
        cout << endl
             << " Which customer's order you want to see (id as number) ?\n\t\t--";
        // choosem
        cin >> id;
        // make proper format the id
        id = "C" + id;
        // location variable has target customers order space.
        location = searchInOrdersTxt(id);
        // first value is location , second value is distance!!
        if (location != "0,0")
        {
            // read location data before of comma is start position , after from comma is end distance.
            for (short i = 0; i < location.length(); i++)
            { // when you see coma stop and pass else block then make equal which you read to start and clear that you read from temp .
                // then continue to read when reading is done make equal which you got to end . finally clear temp str because we will use it next steps again and again.
                if (location[i] != ',')
                {
                    temp.push_back(location[i]);
                }
                else
                {
                    start = stoi(temp);
                    temp.clear();
                }
            }
            end = stoi(temp);
            temp.clear();

            file.open("orders.txt", ios::in);
            // reading datas from file to temp0 string
            while (getline(file, temp))
            {
                temp0.append(temp);
            }
            file.close();

            // printing to screen the data block in proper format
            string b = "#"; // finish data line
            string f = "&"; // finish data block
            string c;
            for (short i = 0; i < end; i++)
            {
                c = temp0[start + i];
                if (c == b)
                {
                    cout << c << endl;
                }
                else if (c == f)
                {
                    cout << c << endl;
                }
                else
                    cout << temp0[start + i];
            }
        }
        else
        {
            cout << "\n there is no customer with this id number... " << id << endl;
        }
        system("pause");
    }
};
