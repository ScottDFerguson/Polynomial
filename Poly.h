// ------------------------------------------------ Poly.h -------------------------------------------------------
// Scott Ferguson CSS 343
// 10-1-2015
// 10-10-2015
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To provide the structure for Poly.cpp. This program is designed to dynamically store and use polynomials as arrays
// --------------------------------------------------------------------------------------------------------------------
// Assumptions-Polynomials will be stored as coefficient and power.
// The index corresponds to the power and the value at the index is the coefficient
// Only Integers will be stored in the polynomials 
// --------------------------------------------------------------------------------------------------------------------
#include <iostream>
using namespace std;

class Poly
{
   // overloaded <<
   // prints in the form (sign)(coefficient)(x^)(power)
   friend ostream& operator<<(ostream &, const Poly&);

   // overloaded >>: takes 2 integers as coefficient and power respectively, -1 -1 to stop
   friend istream& operator>>(istream&, Poly&);
   
//---------------------------------------------------------

// public functions
public:

   //Constructors and Destructor
   Poly();
   Poly(int);
   Poly(int, int);
   Poly(const Poly&);
   ~Poly();

   // get and set methods
   void setCoeff(int,int); 
   int getCoeff(int);  
   
   //boolean comparison operators
   bool operator==(const Poly&) const;
   bool operator!=(const Poly&) const;

   //assignment operators
   Poly operator+(const Poly&) const;
   Poly operator-(const Poly&) const;
   Poly operator*(const Poly&) const;

   //assignment operators
   Poly& operator=(const Poly&);
   Poly& operator+=(const Poly&);
   Poly& operator-=(const Poly&);
   Poly& operator*=(const Poly&);

private:
   int* coefficients; //pointer to the array
   int holdSize; //size of array
};