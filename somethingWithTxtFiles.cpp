/****************************************************************************
**					SAKARYA UNIVERSITESI
**			         BILGISAYAR VE BILISIM BILIMLERI FAKULTESI
**				    BILGISAYAR MUHENDISLIGI BOLUMU
**				          PROGRAMLAMAYA GIRISI DERSI
**
**				ODEV NUMARASI…...:  3 project 
**				OGRENCI ADI...............: Poqob
**				OGRENCI NUMARASI.:  B
**				DERS GRUBU…………: C
****************************************************************************/
// total 2.360 line .
#include "company.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
CompanyPage companyPage = CompanyPage();
CustomerPage customerPage = CustomerPage();

// apps entrance screen
void CompanyPage::myapp()
{
    system("cls");
    int signInAs;
    // entrance screen
    string stuff(20, '-');
    cout << setw(20) << stuff << endl;
    cout << setw(15) << "enter as " << setw(5) << "-" << endl;
    cout << setw(20) << stuff << endl;
    cout << setw(14) << "1.company" << setw(6) << "-" << endl;
    cout << setw(15) << "2.customer" << setw(5) << "-" << endl;
    cout << setw(11) << "3.exit" << setw(5) << "-" << endl;

    // sign part
    cin >> signInAs;
    if (signInAs == 1)
    {
        // go company log in screen
        authorization();
    }
    else if (signInAs == 2)
    {
        // go customer log in screen
        customerPage.entranceScr();
    }
    else if (signInAs == 3)
    {
        exit(1);
    }
}

int main()
{
    setlocale(LC_ALL, "Turkish");
    companyPage.myapp();
}
