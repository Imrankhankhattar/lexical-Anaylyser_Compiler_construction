#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
string NumTable[30];
string IdntfrTable[30];
int Numpointer=0,Idnpointer=0;
void addTo_NumTable(string value)
{
    int s=1;
    for (int i=0; i<Numpointer; i++)
    {
        if(NumTable[i]==value)
        {
            //cout<<"Tokken < "<<value<< "  "<<i<<" >"<<endl;
            s=0;
            break;
        }
    }
    if(s)
    {
        NumTable[Numpointer]=value;
        cout<<"Tokken < "<<value<< "  "<<Numpointer<<" >"<<endl;
        Numpointer++;
    }
}
void Display()

{
    cout<<"\t\t\t\t=================NUMBER TABLE================="<<endl<<endl;
    cout<<"\t\t\t\tNUMBER"<<"\t\t\t|\t\tADDRESS"<<endl<<endl;

    for (int j=0; j<Numpointer; j++)
    {
        cout<<"\t\t\t\t"<<NumTable[j]<<"\t\t\t|"<<"\t\t"<<j+100<<endl;
    }
    cout<<endl<<endl;
    cout<<"\t\t\t\t===============IDENTIFIERS TABLE==============="<<endl<<endl;
    cout<<"\t\t\t\tIDENTIFIER"<<"\t\t|\t\tADDRESS"<<endl<<endl;

    for (int j=0; j<Idnpointer; j++)
    {
        cout<<"\t\t\t\t"<<IdntfrTable[j]<<"\t\t\t|"<<"\t\t"<<j<<endl;
    }
}

void addTo_idntfrTable(string value)
{
    int s=1,i;
    for (i=0; i<Idnpointer; i++)
    {
        if(IdntfrTable[i]==value)
        {
            s=0;
            break;
        }
    }
    if(s==1)
    {

        IdntfrTable[Idnpointer]=value;
        cout<<"Tokken < "<<value<< "  "<<Idnpointer<<" >"<<endl;
        Idnpointer++;
   }
}

bool isletter(char ch)
{
    if ((ch>='a' && ch <='z')||(ch>='A' && ch<='Z')||ch=='_')
        return true;
    else
    {
        return false;
    }
}
bool isdelemiter(char ch)
{
    if (ch==' '||ch=='\t'|| ch=='\n'|| ch==';'||ch==',')
        return true;
    else
    {
        return false;
    }
}
bool isDigit(char ch)
{
    if (ch>='0' && ch <='9')
        return true;
    else
    {
        return false;
    }

}

void LexicalAnalyser(string str)
{
    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
                             "do","double","else","main","extern","float","for","goto",
                             "if","int","long","register","return","short","endl",
                             "cout","static","true","switch","typedef","union",
                             "unsigned","void","volatile","while"
                            };

    int state=0;
    int i=0,allow=1;
    string lexime="";
    char tempchar='\0';
    int value=0;
    while(str[i]!='\0')
    {
        allow=1;
        tempchar=str[i];
        switch(state)
        {
        case 0:
            if(isletter(tempchar))
            {
                state=1;
            }
            else if (isDigit(tempchar))
            {
                state=2;
            }
            else if (tempchar=='{')
            {
                lexime=tempchar;
                state=0;
                cout<<"Tokken < "<<"OP,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if (tempchar=='/')
            {
                lexime=tempchar;
                state=0;
                cout<<"Tokken < "<<"DOP,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if (tempchar=='}')
            {
                lexime=tempchar;
                state=0;
                cout<<"Tokken < "<<"CP,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if (tempchar=='(')
            {
                lexime=tempchar;
                state=0;
                cout<<"Tokken < "<<"OPs,   "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if (tempchar==')')
            {
                lexime=tempchar;
                state=0;
                cout<<"Tokken < "<<"CPs,   "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if (tempchar=='|')
            {
                state=3;
                value=900;

            }else if (tempchar=='&')
            {
                state=3;
                value=800;

            }else if (tempchar=='=')
            {
                state=3;
                value=700;

            }
            else if (tempchar=='*')
            {

                state=3;
                value=600;


            }
            else if (tempchar=='-')
            {
                state=3;
                value=500;

            }

            else if (tempchar=='+')
            {
                state=3;
                value=400;

            }

            else if (tempchar=='!')
            {
                state=3;
                value=300;

            }

            else if (tempchar=='<')
            {
                state=3;
                value=200;

            }
            else if (tempchar=='>')
            {
                state=3;
                value=100;
                //cout<<"F:"<<flag<<endl;

            }
            else if(isdelemiter(tempchar))
            {
                allow=0;
            }
            else
            {
                cout<<"Invalid Tokken"<<endl;
                break;
            }
            break;
        case 1:

            if(!(isletter(tempchar)||isDigit(tempchar)))

            {
                state=0;
                int index;
                int check=0;
                for(index = 0; index < 32; ++index)
                {
                    if(keywords[index]==lexime)
                    {
                        cout<<"Tokken < "<<"KW,  "<<lexime<< " >"<<endl;
                        check=1;
                        lexime="";
                        break;
                    }

                }
                if(check==0)
                {
                    //cout<<"Tokken < "<<"ID,  "<<lexime<< " >"<<endl;
                    addTo_idntfrTable(lexime);
                    lexime="";
                    continue;
                }

                else
                {
                    allow=1;
                    continue;
                }

            }
            break;
        case 2:
            if(!isDigit(tempchar))
            {
                state=0;
                if(isletter(tempchar))
                {
                    cout<<"Syntax Error::Variable name cannot start with number!!! "<<endl;
                    lexime="";
                    break;
                }
                else
                {
                    //cout<<"Tokken < "<<"IL,  "<<lexime<< " >"<<endl;
                    addTo_NumTable(lexime);
                    lexime="";
                    continue;
                }

            }
            break;
        case 3:
            if(tempchar=='=' && value==200)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"LTE,  "<<lexime<< " >"<<endl;
                allow=0;
                lexime="";
            }

            else if(tempchar=='=' && value==100)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"GTE,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if(tempchar=='=' && value==300)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"NET,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if(tempchar=='+' && value==400)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"IO,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if(tempchar=='-' && value==500)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"DO,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
            else if(tempchar=='*' && value==600)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"PO,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
             else if(tempchar=='=' && value==700)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"CO,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
else if(tempchar=='&' && value==800)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"RO,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }
else if(tempchar=='|' && value==900)
            {
                state=0;
                lexime=lexime+tempchar;
                cout<<"Tokken < "<<"RO,  "<<lexime<< " >"<<endl;
                lexime="";
                allow=0;
            }

            else
            {

                if(str[i-1]=='<'||str[i-1]=='>')
                {
                    state=0;
                    lexime="";
                    allow=0;
                    continue;
                }
                else
                {
                    if(value==100)
                    {
                        state=0;
                        cout<<"Tokken < "<<"GT,  "<<lexime<< " >"<<endl;
                        lexime="";
                        allow=0;
                        continue;
                    }
                    if(value==300)
                    {
                        state=0;
                        cout<<"Tokken < "<<"NOT,  "<<lexime<< " >"<<endl;
                        lexime="";
                        allow=0;
                        continue;
                    }
                    if(value==400)
                    {
                        state=0;
                        cout<<"Tokken < "<<"AO,  "<<lexime<< " >"<<endl;
                        lexime="";
                        allow=0;
                        continue;
                    }
                    if(value==500)
                    {
                        state=0;
                        cout<<"Tokken < "<<"AO,  "<<lexime<< " >"<<endl;
                        lexime="";
                        allow=0;
                        continue;
                    }
                    if(value==600)
                    {
                        state=0;
                        cout<<"Tokken < "<<"AO,  "<<lexime<< " >"<<endl;
                        lexime="";
                        allow=0;
                        continue;
                    } if(value==700)
                    {
                        state=0;
                        cout<<"Tokken < "<<"AO,  "<<lexime<< " >"<<endl;
                        lexime="";
                        allow=0;
                        continue;
                    }if(value==800)
                    {
                        state=0;
                        cout<<"Tokken < "<<"AND,  "<<lexime<< " >"<<endl;
                        lexime="";
                        allow=0;
                        continue;
                    }if(value==900)
                    {
                        state=0;
                        cout<<"Tokken < "<<"OR,  "<<lexime<< " >"<<endl;
                        lexime="";
                        allow=0;
                        continue;
                    }
                    state=0;
                    cout<<"Tokken < "<<"LT,  "<<lexime<< " >"<<endl;
                    lexime="";
                    allow=0;
                    continue;

                }
            }
            break;
        }

        if(allow)
            lexime=lexime+tempchar;
        i++;
    }

}

int main()
{
    string input;
    fstream newfile;
    cout<<"Input Program: "<<endl;
    newfile.open("programe.txt",ios::in);
    if (newfile.is_open())
    {
        string tp;
        while(getline(newfile, tp))
        {
            cout << tp<<endl;
            if(tp[0]=='/' && tp[1]=='/')
                continue;
            input=input+tp;
        }

        newfile.close();
    }
    cout<<"\n***Tokens:*** \n"<<endl;
    LexicalAnalyser(input);

    Display();

    return 0;
}
