#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
using namespace std;
class play
{
    int no;
    char name[50];
    float ppoints;

    public:

    void adminsetplayer()
    {
        for (int i = 11 ; i < 25; i=i+2)
        {
            cout << "TEAM 1____PLAYER NAME:";
            fflush(stdin);
            gets(name);
            cout << "\tPLAYER POINTS:";
            cin >> ppoints;
            no=i;
            setplayers();
            cout << endl;

            cout << "TEAM 2____PLAYER NAME:";
            fflush(stdin);
            gets(name);
            cout << "\tPLAYER POINTS:";
            cin >> ppoints;
            no=i+1;
            setplayers();
            cout << endl;
        }

    }

    void setplayers()
    {
        ofstream f;
        f.open("Adminplayers.txt",ios::ate|ios::app);
        if(!f.eof())
        f.write((char*)this,sizeof(*this));
        f.close();
    }

    void deleteplayer()
    {
        ofstream o;
        o.open("Adminplayers.txt",ios::out);
        o.close();
    }

    void showplayer(int k)
    {
        if(k%2!=0)
        {
            cout << no << "  " <<name << "\t\t\t\t\t";

        }
        else
        {
            cout << no << "  " << name << endl;
        }

    }

    void showplayer()
    {
        cout << no << "  " << name << endl;
    }

    void readplayers()
    {
        ifstream a;
        a.open("Adminplayers.txt",ios::in);
        for(int i=11 ; i<25 ; i++ )
        {
            a.read((char*)this,sizeof(*this));
            if(!a.eof())
            {
                showplayer(i);
            }
        }
    }

    void searchplayer(int c)
    {
        ifstream in;
        in.open("Adminplayers.txt",ios::in|ios::binary);
        if(!in)
        {
            cout<<"error:File Not Opened";
        }
        else
        {
            in.read((char*)this,sizeof(*this));
            while(!in.eof())
            {
                if(c==no)
                {
                    break;
                }
                in.read((char*)this,sizeof(*this));
            }
            in.close();
        }
    }

    float getpoint()
    {
        return ppoints;
    }
};


class user
{
    int uid;
    char uname[20];
    float balance,gamebalance;
    play players[5];
    float totalpts;

    public:

    void getuserdata(int k)
    {
        uid=k;
        cout << endl;
        for (int i = 0; i < 162; i++)
            cout << "-";
        for (int i = 0; i < 59; i++)
            cout <<" ";
        cout << "Hello User  " << uid <<endl ;

        cout << "User Name:";
        fflush(stdin);
        gets(uname);
        cout << "Enter Balance(Min 1000):";
        try
        {
            cin >> balance;
            if(balance<1000)
                throw 'x';
        }
        catch(...)
        {
            cout << "Please enter proper Balance(min 1000):";
            cin >> balance;
        }

        for (int i = 0; i < 162; i++)
            cout << "-";
    }

    void storeuser()
    {
        if(uid==1)
        {
            ofstream f;
            f.open("user1.txt",ios::out);
            if(!f.eof())
            f.write((char*)this,sizeof(*this));
            f.close();
        }
        else
        {
            ofstream f;
            f.open("user2.txt",ios::out);
            if(!f.eof())
            f.write((char*)this,sizeof(*this));
            f.close();
        }

    }

    void fetchuser(int x)
    {
        if(x==1)
        {
            ifstream a;
            a.open("user1.txt",ios::in);
            a.read((char*)this,sizeof(*this));
            a.close();
        }
        else
        {
            ifstream a;
            a.open("user2.txt",ios::in);
            a.read((char*)this,sizeof(*this));
            a.close();
        }

    }

    void showuser()
    {
        cout << endl ;
        for (int i = 0; i < 162; i++)
            cout << "-";
        for (int i = 0; i < 59; i++)
            cout << " ";
        cout << " Welcomeback " << uname << endl;
        cout << "You are user :" << uid << endl;
        cout << " Your Current Balance :" << balance << endl;
        for (int i = 0; i < 162; i++)
            cout << "-";
    }

    void userfind()
    {
        float newbalance;
        while (balance<1000)
        {
            cout << "Insufficient Balance(Minimum 1000rs), Add Additional Amount:";
            cin >> newbalance;
            balance=balance+newbalance;
        }

        int flag=0,sid;
        int l[5];
        for(int i=0;i<5;i++)
        {
            cout<<"Enter The Player Index : ";
            cin>>l[i];
            while(l[i]<11||l[i]>24)
            {
                cout<<"Please Enter Between 11 to 24: ";
                cin>>l[i];
            }

            for(int j=i-1;j>=0;j--)
            {
                while(l[i]==l[j]||l[i]<11||l[i]>24)
                {
                    cout<<"You've already selected this player!\nRe-enter Index: ";
                    cin>>l[i];
                    flag++;
                }
                if(flag!=0)
                {
                    j=i;
                    flag=0;
                }
            }
            sid=l[i];
            players[i].searchplayer(sid);
            players[i].showplayer();
        }
    }

    float totalUpoints()
    {
        totalpts=0;
        for(int i=0;i<5;i++)
        {
            totalpts += players[i].getpoint();
        }
        cout<<"Total Point Made By Your Selected Team : "<<totalpts<<endl;
        return totalpts;
    }

    void distribute(float allpoint)
    {
        gamebalance=1000;
        balance=balance-1000;
        gamebalance=(totalpts*2000)/allpoint;
        cout << "Gamebalance After Match:" << gamebalance << endl;
        cout<<"YOUR game credits has changed by "<<gamebalance-1000<<endl;
        balance=balance+gamebalance;
        cout<<"your new balance in this app is : "<<balance<<endl;
    }

};


int main()
{
    int showmenu();
    void firstpage();
    system("cls");
    firstpage();
    int c;
    play p;
    user u[2];
    float x=0;
    while (1)
    {
        c=showmenu();
        switch(c)
        {
            case 1:
            p.deleteplayer();
            p.adminsetplayer();
            cout << endl;
            break;

            case 2:
            for (int i = 0; i < 2; i++)
            {
                u[i].getuserdata(i+1);
            }
            cout << endl;
            break;

            case 4:
            x=0;
            int i =0;
            for (  i = 0; i < 2; i++)
            {
                p.readplayers();
                for ( i = 0; i < 162; i++)
                    cout << "-" ;
                cout << "User " << i+1 << ":" << endl;
                u[i].userfind();
                for ( i = 0; i < 162; i++)
                    cout << "-" ;

                u[i].storeuser();
            }
            break;

            case 3:
            for (int i = 0; i < 2; i++)
            {
                u[i].fetchuser(i+1);
            }
            for (int i = 0; i < 2; i++)
            {
                u[i].showuser();
            }

            break;

            case 5:
            for (int i = 0; i < 2; i++)
            {
                for (int i = 0; i < 162; i++)
                    cout << "-" ;
                cout << "User " << i+1 << " : " << endl ;
                x=x+u[i].totalUpoints();
                for (int i = 0; i < 162; i++)
                    cout << "-" ;
            }

            for (int i = 0; i < 2; i++)
            {
                for (int i = 0; i < 162; i++)
                    cout << "-" ;
                cout << "User" << i+1<< " :" << endl ;
                u[i].distribute(x);
                u[i].storeuser();
                for (int i = 0; i < 162; i++)
                    cout << "-" ;
            }
            break;

            case 6:
            exit(0);

            default:
            cout << "Invalid choice!!"<<endl;
        }
    }
}
int showmenu()
{
    cout << endl;
    for (int i = 0; i < 59; i++)
        cout << " " ;
    cout << "1: Admin" << endl;
    for (int i = 0; i < 59; i++)
        cout << " " ;
    cout << "2: New User" << endl;
    for (int i = 0; i < 59; i++)
        cout << " " ;
    cout << "3: Existing User"<< endl;
    for (int i = 0; i < 59; i++)
        cout << " " ;
    cout << "4: Make team" << endl;
    for (int i = 0; i < 59; i++)
        cout << " " ;
    cout << "5: View Result of Match" << endl;
    for (int i = 0; i < 59; i++)
        cout << " " ;
    cout << "6: Exit" << endl;
    cout << "Enter Your choice:  ";
    int c;
    cin >> c;
    return c;
}

void firstpage()
{
    //width:162 chars
    system("cls");

    cout << endl << endl;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 162; j++)
        {
            if(j<61||j>91)
                cout << " " ;
            else
                cout << "-" ;

        }

    }
    for (int j = 0; j < 5; j++)
    {

        if (j==2)
        {
            for (int i = 0; i < 59; i++)
                cout << " " ;
            cout << "||" ;
            for (int i = 0; i < 8; i++)
                cout << " " ;
            cout << "CRICKET FANTACY";
            for (int i = 0; i < 9; i++)
                cout << " " ;
            cout << "||" ;
        }
        else
        {
            for (int i = 0; i < 94; i++)
            {
                if(i==59||i==92)
                    cout << "||";
                else
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 162; j++)
        {
            if(j<61||j>91)
                cout << " " ;
            else
                cout << "-" ;

        }

    }

    cout << endl << endl;

    for (int i = 0; i < 162; i++)
        cout << "-";

    cout << "Project By:-" << endl ;
    cout << "Karan Tanakhia\t19CP065" << endl;
    cout << "Hemang Parekh \t19CP066" << endl;
    cout << "Akshat Trivedi\t19CP075" << endl;

    for (int i = 0; i < 162; i++)
        cout << "-";

    cout << "Press Enter To Continue..."<<endl ;
    getch();
    system("cls");
}
