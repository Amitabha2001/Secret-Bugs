#include<iostream>
#include<conio.h>
#include<Assembly++.hpp>

using namespace std;


const int DIRECTX = 1;
const int DIRECT3D = 2;
int eax = DIRECTX;
int ebx = DIRECT3D;
const int X = 30;
const int Y = 50;
const int Z = 100;
const int U = 1;
void DO( )
{
int y = 0;
cout << y;
}
void main( )
{
int ax = 10;
int bx = 20;
int cx = 30;
string str = 'Welcome.hello';
MessageINT samp;
MessageINT samp01;
MessageSTRING samp02;
ax += bx;
str += 'Hi';
bx -= eax;
cx *= ax;
bx /= cx;
samp02.AddParam('HI');
samp02.Dispach( );
if (ax = bx)
{
cout << 'Yo! ax = bx' << endl;
if (bx = cx)
{
bx += cx;
}
}
bx = samp01.GetReturn();
x:
goto x;
str = str.substr(3,1);
cout << 'Welcome.head' << endl;
cout << 'Welcome.head : ';
cin >> cx;
cx = cx % 10;
stk.push(cx);
cx += ax;
cout << cx << endl;
cx = stk.pop();
str = samp02.GetParamValue(0);
exit(1);
}