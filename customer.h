#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "orders.h"
using namespace std;

class CustomerPage : Orders
{
private:
    // classe's variables
    string cID;
    string cName;
    string cPhoneNum;
    string cPersonInCharge;
    string cCategory; // cCatagory for pricing , common means standart prices appy to you , spcial means special prices apply to you.
    short cCategoryT;
    string cAdress;
    string isNumCorrect = "";
    fstream customers;
    string workingOn;

    short lines = 6; // now it is equal to 9 . if we will increase input datas about product it will increase via write function.
    Orders order;

public:
    // entrance screen for customer page
    void entranceScr()
    {
        bool loggedIn; // bool control for am i logged in
        system("cls");
        int choosem = 0;
        cout << "\t1-LogIn " << endl;
        cout << "\t2-Register " << endl;
        cout << "\t3-Exit Program " << endl;
        cin >> choosem;
        switch (choosem)
        {
        case 1:
            system("cls");
            // loggedIn equal to auth. func. which returns a bool and makes a query.
            loggedIn = authorization();
            if (loggedIn = true)
                cMainScr();
            else
            {
                cout << "please retry to logIn..." << endl;
                system("pause");
                system("cls");
                entranceScr();
            }

            break;
        case 2:
            system("cls");
            cRegister();
            entranceScr();
            break;
        case 3:
            exit(1);
            break;
        default:
            system("cls");
            entranceScr();
            break;
        }
    }
    // remote search's task is simple , it is allow us to move in customer.txt from out of private/this class
    // remote for customer class.
    void remote(short whichFuncIllRun)
    {
        switch (whichFuncIllRun)
        {
        case 1:
            cRegister();
            break;
        case 2:
            cSearch(0);
            break;
        case 3:
            cEdit(0);
            break;
        case 4:
            cRemove(0); // accesing remove func from out of class with 0 value .
            break;
        case 5:
            cList();
            break;
        }
    }
    // remote function for company class to orders class
    void remote2(short choosem)
    {
        system("cls");
        order.remote2(choosem);
    }

private:
    // authontacate customer entrance if style is 0 ,not verified---if 1 ,verified
    // it verifies logIn , if style is 0 so go search func. and search input id . if there is come back authorization func with true value.--> access to main scr
    bool authorization()
    {

        cSearch(1);
        // so it means cSearch find customer which means verified
        // also cSearch attempt customer id value to workingOn variable that means in orders.h some methods needs customer id information .
        // this step provides id information to orders.h file methods.
        // if cSearch worked fine , then workingOn has some characters in it . so it's size or lenght cant be 0. it means access are verified.
        if (workingOn.size() != 0)
        {
            return true;
        }
        else
            return false;
        }

    // register new customer
    void cRegister()
    {

        cout << "please enter customer ID : ";
        cin >> cID;
        // to make them different than others , i gave c head letter
        cID = "C" + cID;
        cout << endl;

        cout << "please enter customer name : ";
        cin >> cName;
        cName = cID + cName;
        cout << endl;

        cout << "please enter phone number : ";
        cin >> cPhoneNum;
        cPhoneNum = cID + "N" + cPhoneNum;
        cout << endl;

        cout << "please enter person in charge : ";
        cin >> cPersonInCharge;
        cPersonInCharge = cID + cPersonInCharge;
        cout << endl;

        cout << "customer type : common(1),special(2) : ";
        cin >> cCategoryT;
        if (cCategoryT == 2)
            cCategory = cID + "T" + "special";
        else
            cCategory = cID + "T" + "common";
        cout << endl;

        cout << "please enter adress : ";
        cin >> cAdress;
        cAdress = cID + "W" + cAdress;
        cout << endl;
        system("cls");
        cWrite();
    }
    // writing datas to file
    void cWrite()
    {
        // lines are increasing for every data line input.
        lines = 0;
        ostringstream tmpstr; // temp string stream
        // it(&) is here because in future it will say , this product information chain is started .
        tmpstr << "&" << endl;
        tmpstr << "*Customer ID : " << cID;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Customer name : " << cName;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Customer phone number : " << cPhoneNum;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Person in charge : " << cPersonInCharge;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Customer type : " << cCategory;
        lines++;
        tmpstr << "#";
        tmpstr << '\n';
        tmpstr << "*Adress : " << cAdress;
        lines++;
        tmpstr << "#" << endl;
        customers.open("customers.txt", ios::in | ios::app); // ios::app --> open file in append mode

        // printing customer to customers.txt
        if (!customers.is_open())
        {
            cout << "your reques interrupted. Retriying...";
            cWrite();
            system("pause");
            system("cls");
        }
        else
        {
            customers << tmpstr.str();
            customers.close();
            cout << "-successful\n";
            system("pause");
        }
    }
    // customer main screen.
    void cMainScr()
    {
        system("cls");
        int choosem = 0;
        string stuff(40, '-');
        cout << stuff << endl;
        cout << " 1. give orders " << endl;
        cout << " 2. search in orders " << endl;
        cout << " 3. delete orders " << endl;
        cout << " 4. see given orders " << endl;
        cout << " 5. my data " << endl;
        cout << " 6. delete my orders " << endl;
        cout << " 7. exit program " << endl;
        cout << stuff << endl;
        cout << " it's time to chose : ";
        cin >> choosem; // we had better if we control cin against any wrong type input.--like space
        cout << endl;
        cout << isNumCorrect << endl;

        // accesing remote function in order.h
        if (choosem < 5)
        {
            system("cls");
            // choosem parmater is for which function remote will run , workingOn for provide id information to remote function's subfunctions.
            order.remote(choosem, workingOn);
        }

        else if (choosem > 5)
        {
            // get rid of stream....
            if (choosem == 7)
                exit(1);
            // if here we choose 6 it'll go orders.h file's remote function with value 5 and id.
            else if (choosem == 6)
                order.remote(choosem - 1, workingOn);
            // another posibilities are not in our scope.
            else
            {
                system("cls");
                cout << "\t--please make true choice !\n ";
                system("pause");
            }
        }
        else
        {
            // the choosem=5 posibility go to customer search function to see customer data.
            cout << stuff << endl
                 << "\t\t" << workingOn << "\t\t" << endl
                 << stuff << endl;
            cSearch(0);
        }
        // if order operations are done , then turn back this screen again.
        cMainScr();
    }
    // edit customer informations
    void cEdit(bool style)
    {
        // working style/mode
        // go customer search function to edit customer informations.
        if (style == false)
        {
            cout << "Which customer do you want to edit\n";
            // go cSearch method with 1 value so it means , give which product we are working on information to workingOn variable.
            cSearch(1);
            // come back to edit function with value 1. it means i have information  which product i'll manipulate.
            cEdit(1);
        }
        else
        {
            // open customers.txt in input mode so we can read data from in
            customers.open("customers.txt", ios::in);
            // local variables
            short chosem;
            string temp;
            string edit;
            string data;
            short tmp;
            // write customers'es datas to variable data
            while (getline(customers, temp))
            {
                data.append(temp);
            }
            temp.clear();
            // closing reading file
            customers.close();
            // screen output
            cout << '\n'
                 << "which property you want to chance \n\n1.ID\n2.Name\n3.Phone number\n4.Person in charge\n5.Customer type\n6.Adress\n7.Cancel\n\t---->";
            cin >> chosem;

            // at below , may i can fetch neccesed old values from file but when i was writing this secion , i haven't got enough knowledge :')
            switch (chosem)
            {
            case 1: // reID
                customers.open("customers.txt", ios::out);
                cout << "\tplease enter old ID --";
                cin >> temp;
                // make temp proper Id format
                temp = "C" + temp;
                cout << "\tplease enter new ID --";
                cin >> edit;
                // make edit proper Id format
                edit = "C" + edit;

                // do it lines times-->6
                for (short i = 0; i < lines; i++)
                {
                    // replacing all ID headers from target customer
                    tmp = data.find(temp);
                    data.replace(tmp, temp.length(), edit);
                }
                break;

            case 2: // rename
                customers.open("customers.txt", ios::out);
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

            case 3: // rePhoneNumber
                customers.open("customers.txt", ios::out);
                cout << "\tplease enter old phone number --";
                cin >> temp;
                temp = workingOn + "N" + temp;
                cout << "\tplease enter new phone number --";
                cin >> edit;
                edit = workingOn + "N" + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;

            case 4: // rePersonInCharge
                customers.open("customers.txt", ios::out);
                cout << "\tplease enter old person --";
                cin >> temp;
                temp = workingOn + temp;
                cout << "\tplease enter new person --";
                cin >> edit;
                edit = workingOn + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                workingOn.clear();
                break;
            case 5: // reCustomerType
                customers.open("customers.txt", ios::out);
                cout << "\tplease enter old customer type --";
                cin >> temp;
                temp = workingOn + "T" + temp;
                cout << "\tplease enter new customer type --";
                cin >> edit;
                edit = workingOn + "T" + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;
            case 6:
                customers.open("customers.txt", ios::out);
                cout << "\tplease enter old adress --";
                cin >> temp;
                temp = workingOn + "W" + temp;
                cout << "\tplease enter new adress --";
                cin >> edit;
                edit = workingOn + "W" + edit;
                // replacing
                tmp = data.find(temp);
                data.replace(tmp, temp.length(), edit);
                break;
            case 7:
                break;

            default:
                cout << "please enter valid number" << endl;
                cEdit(1);
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
                    customers << c << endl;
                }
                else if (c == f)
                    customers << c << endl;
                else
                    customers << data[i];
            }
            // reset else block to do another process for future
            data.clear();
            temp.clear();
            edit.clear();
            tmp = 0;
            chosem = 0;
            customers.close();
        }
    }
    // make search in customers
    void cSearch(bool style)
    {
        // local variables
        string id;
        string temp;
        string temp0;
        id.clear();
        temp0.clear();
        temp.clear();
        // open file in read mode
        customers.open("customers.txt", ios::in);

        // looking for which customer
        cout << "please enter customer id(as number) : ";
        cin >> id;
        system("cls");
        // to make customer id proper format
        id = "C" + id;

        // reading datas from file to temp0
        while (getline(customers, temp))
        {
            temp0.append(temp);
        }
        temp.clear();

        // cout specified customer informations.
        // found location id text.

        int found = temp0.find(id);

        // npos's value = -1 so found can't be -1 therefore this if statement searching all string
        if (found != string::npos)
        {

            // so here if customer id is true ,datas about customer will be printed
            cout << "Customer ID : ";
            // here customer id printing
            for (short i = 0; i < id.length(); i++)
            {
                cout << temp0[found + i];
            }
            cout << "\n";
            // that will keep first star after customer id so it means we are starting to print with customer name
            int firstStar = temp0.find('*', found);
            int firstSquare = temp0.find('#', firstStar);

            // printing customer name --> Customer data chain's second line
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

                // prints next column
                for (short i = firstStar + 1; i < firstSquare; i++)
                {
                    cout << temp0[i];
                }
                cout << "\n";
            }

            // to provide information to edit func // it works when editting func call search func. with value 1-true
            if (style)
                workingOn = id;
        }
        else
        {
            cout << "The customer ID you just entered was not in our list\nentered value : " << id << endl;
            if (style == true)
                entranceScr();
        }
        customers.close();
        system("pause");
    }
    // listing customers
    void cList()
    {
        // local variables
        string temp;
        string data;
        // open file in read mode to read datas to string
        customers.open("customers.txt", ios::in);

        while (getline(customers, temp))
        {
            data.append(temp);
        }

        string b = "#";      // finish data line sign
        string f = "&";      // finish data block sign
        short itemCount = 0; // it keeps "&" count . so that means is how much customer you have .
        // to my txt file design , all data blocks starts with & symbol. one of thems starting is others end.
        string c;
        // printing data to console in proper format , line by line for each customer data .
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
             << "--you got " << itemCount << " customers on your list.\n"
             << endl;

        customers.close();
        temp.clear();
        data.clear();
        system("pause");
    }
    // remove customer
    void cRemove(bool style)
    {
        // again same design , come cRemove with zero value then go cSearch func. to gain workingOn-customer Id- information
        // then turn back cRemove with value 1 also with customer Id information. so function can find and delete target customer.
        string chosem;
        if (!style)
        {
            cout << "which customer you want to delete\n";
            cSearch(1);
            cRemove(1);
        }
        else
        {
            // open file in read mode
            customers.open("customers.txt", ios::in);
            // local variables
            string temp;
            string data;
            short tmp;
            // write customers's datas to variable data
            while (getline(customers, temp))
            {
                data.append(temp);
            }
            temp.clear();
            // use temp again for data saving.
            // temp is equal to target customer's data block's start line , it means find target customer in customers.txt to play on it.
            temp = "&*Customer ID : " + workingOn + "#";

            // found stores target datas start location , function will starts deleting from here
            int start = data.find(temp);
            temp = "&";
            // last stores ,next '&' sign --> it means product data chain ended .so function will finishes deleting from here.
            int last = data.find(temp, start + 1);

            // make this minus operation because erase method calculate end of iteration start+lenght=last point
            last -= start;

            // ask for permission to delete.
            cout << "are you sure for deleting " << workingOn << " customer ?"
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
            customers.close();

            // write editted data to txt
            // here data written proper format
            customers.open("customers.txt", ios::out);
            string b = "#"; // finish data line
            string f = "&"; // finish data block
            string c;
            for (short i = 0; i < data.length(); i++)
            {
                c = data[i];
                if (c == b)
                {
                    customers << c << endl;
                }
                else if (c == f)
                    customers << c << endl;
                else
                    customers << data[i];
            }
        }
        customers.close();
    }
};