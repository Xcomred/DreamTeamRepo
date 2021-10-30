#include <cctype> //isdigit()
#include <cstring> //strlen
//ligma
//ryan is leaking
#include "HugeInt.h"
using std::endl;
using std::cout;

HugeInt::HugeInt(long value)
{
    cout <<"HugeInt(long) called" << endl;
    number = new unsigned char[30];

    for(int i = 0; i < 30; i++) //sets the array to 0's
    {
        number[i] = '0';
    } 

    for(int i = 29; value > 0 && i >= 0; i--)
    {
        number[i] = value % 10 + '0';
        value = value / 10;
    }
    computeSize();
}

//Set the size of the number of an HugeInt object
void HugeInt::computeSize()
{
    int count = 0;
    int incr = 0;

    for (int i = 0; i < 30; i++)
    {
        if (number[i] != '0')
        {
            break;
        }
        incr++;
    }

    for (incr; incr < 30; incr++)
    {
        count++; // cout << number[incr]; ->operator
    }

    size = count;

   if (size == 0)
    {
        size++;
    }
    
}

HugeInt::HugeInt(const char* string)
{
    cout <<"HugeInt(const char*) called" << endl;

    number = new unsigned char[30];
    for(int i = 0; i < 30; i++)
    {
        number[i] = '0';
    }

    int length = strnlen(string, 30);
    //Complete the code here to set number[i]
    length = length - 1;

    for(int i = 29; length >= 0 && i >= 0; i--)
    {
        number[i] = string[length];
        length--;
    }

    computeSize();
}

HugeInt::HugeInt(const HugeInt& copy) 
{
   cout <<"HugeInt(const HugeInt& copy) called" << endl;

   number = new unsigned char[30];
   for (int i = 0; i < 30; i++)
   {
       number[i] = copy.number[i] + '0';
   }
   computeSize();
}
    
HugeInt::~HugeInt()
{

    cout <<"~HugeInt() called" << endl;
    delete []number;

}

HugeInt& HugeInt::operator=(const HugeInt& right)
{
    cout <<"operator=(const HugeInt&)  called" << endl;
    HugeInt local(right);
    
    unsigned char* temp = this->number;
    this->number = local.number;
    local.number = temp;

  
    unsigned char temp_len = this->size;
    this->size = local.size;
    local.size = temp_len; 

    return *this;
}


HugeInt HugeInt::operator+(const HugeInt& right)
{
    cout << "operator+(const HugeInt&)" << endl;
    HugeInt result;
    int carry = 0;
    for(int i = 29; i >= 0; i--) 
    {
        int jacob = ((number[i] - '0') + ((right.number)[i] - '0') + carry); 
        if (jacob > 9)
        { 
            carry = jacob / 10;
            jacob = jacob % 10;
            result.number[i] = jacob + '0';
        }
        else
        {
            carry = 0;
            result.number[i] = jacob + '0';
        }
    }
    result.computeSize();
    return result;
}

HugeInt HugeInt::operator-(const HugeInt& right)
{
    cout << "operator-(const HugeInt&)" << endl;
    HugeInt result;
    int carry = 0;
    for(int i = 29; i >= 0; i--) 
    {
        int jacob = ((number[i] - '0') - ((right.number)[i] - '0') + carry); //my aquaintance -> my friend now
        if (jacob > 9)
        { 
            carry = jacob / 10;
            jacob = jacob % 10;
            result.number[i] = jacob + '0';
        }
        else
        {
            carry = 0;
            result.number[i] = jacob + '0';
        } 
    }
    
    result.computeSize();
    return result;
}

HugeInt HugeInt::operator*(const HugeInt& right)
{
    cout << "operator*(const HugeInt&)" << endl;
    HugeInt result;
    int carry = 0;
    for (int o = 0; o <= 29; o++)
    {
        for(int i = 29; i >= 0; i--) 
        {
            int jacob = ((number[i] - '0') * ((right.number)[o] - '0') + carry); 
            if (jacob > 9)
            { 
                carry = jacob / 10;
                jacob = jacob % 10;
                result.number[i] = result.number[i] + jacob;
                cout << result.number[i] << endl;
            }
            else
            {
                carry = 0;
                result.number[i] = jacob;
            }
        }
    }
    result.computeSize();
    return result;
}

HugeInt HugeInt::operator/(const HugeInt& right)
{
    cout << "operator/(const HugeInt&)" << endl;
    HugeInt result;

    int dividend = 0;
    int divider = 0;
    int incr = 0;
    int o = 0;

    for (int i = 0; i <= 29; i++) // filters 0's
    {
        
        if (right.number[i] != '0')
        {
            break;
        } 
        incr++;
    }   

    for (incr; incr <= 29; incr++) // gets 765321 and puts in int
    {
        divider = (divider * 10) + (right.number[incr] - '0');
    }
//
    for (int count = 0; count <= 29; count++)
    {
        o++;
        if (dividend < divider) // divider is 765321 //if dividend is less than divider, 0 is places are array position, dividend is moved a spot over and 9 is added.
        {   
            result.number[count] = 0;  
            dividend = (dividend * 10) + (number[o] - '0');
        }
        else
        {
            result.number[count] = (dividend / divider);
            dividend = dividend % divider;
            dividend = (dividend * 10) + (number[o] - '0');
        }
    }

    result.computeSize();

    return result;
}

HugeInt HugeInt::operator%(const HugeInt& right)
{
    cout << "operator%(const HugeInt&)" << endl;
    HugeInt result;
    int carry = 0;
    for (int o = 29; o >= 0; o--)
    {
        for(int i = 29; i >= 0; i--) 
        {
            int jacob = ((number[i] - '0') % ((right.number)[o] - '0') + carry); //my aquaintance
            if (jacob > 9)
            { 
                carry = jacob / 10;
                jacob = jacob % 10;
                result.number[i] = jacob;
                cout << result.number[i] << endl;
            }
            else
            {
                carry = 0;
                result.number[i] = jacob;
            // cout << result.number[i] << endl;
            }
        }
    } 
    result.computeSize();
    return result;
}

HugeInt& HugeInt::operator++()
{
    HugeInt hugint;
    cout << "operator++()" << endl;
    return *this;
}

HugeInt HugeInt::operator++(int)
{
    HugeInt hugint;
    //increase (*this) by 1
    cout << "operator++(int)" << endl;
    return hugint;

}

unsigned char& HugeInt::operator[](int pos)
{
    HugeInt hugint(pos);

    cout << "operator[](int)" << endl;
    return hugint[pos];
} 

HugeInt::operator long double()
{
    HugeInt hugint; //
    cout << "operator long double()" << endl;
    return hugint; //
}

bool HugeInt::operator<=(const HugeInt& right) {

    cout << "operator<=(const HugeInt& )" << endl;

    return true; //
    
}

bool HugeInt::operator>=(const HugeInt& right) {

    cout << "operator>=(const HugeInt& )" << endl;

    return true; //
    
}

ostream& operator<<(ostream& out, const HugeInt& n)
{
    cout << "operator<<(ostream&, const HugeInt& )" << endl;
    cout << "Value ";

    int incr = 0;
    for(int i = 0; i < 30; i++) //filters leading 0's
    {
        if (n.number[i] != '0')
        {
            break;
        }
        if (i == 29)
        {
            cout << n.number[i];
        } 
        incr++;
    } 

    for (incr; incr < 30; incr++) //prints numbers after leading 0's
    {
        cout << n.number[incr];
    }

    cout << " || Size " << n.size << endl;
    out << "\n";
    return out;
}

istream& operator>>(istream& in, HugeInt& n)
{
    cout << "operator>>(istream&, HugeInt& )" << endl;
    //Converting a string to char* can be done with c_str() member function of string type
    return in; 
}
