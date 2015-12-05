// ------------------------------------------------ Poly.cpp -------------------------------------------------------
// Scott Ferguson CSS 343
// 10-1-2015
// 10-10-2015
// --------------------------------------------------------------------------------------------------------------------
// Purpose - To provide the functions for Poly.h. This program is designed to dynamically store and use polynomials as arrays
// --------------------------------------------------------------------------------------------------------------------
// Assumptions-Polynomials will be stored as coefficient and power.
// The index corresponds to the power and the value at the index is the coefficient
// Only Integers will be stored in the polynomials 
// The power will always be >= 0
// --------------------------------------------------------------------------------------------------------------------

#include "Poly.h"

// ------------------------------------Poly()-----------------------------------------------
// Description: Constructor for the polynomial, no integers given
// Creates new object with length one and value 0
// ---------------------------------------------------------------------------------------------------
Poly::Poly() {
   holdSize = 1;
   coefficients = new int[1]; 
   coefficients[0] = 0;
} // eoPoly()

// ------------------------------------Poly(int)-----------------------------------------------
// Description: Constructor for the polynomial, one integer given
// Creates new object with length one and value equal to the value given
// ---------------------------------------------------------------------------------------------------
Poly::Poly(int coeff) {
   holdSize = 1;
   coefficients = new int[1];
   coefficients[0] = coeff;
} // eoPoly(int)

// ------------------------------------Poly(int, int)-----------------------------------------------
// Description: Constructor for the polynomial, two integers given
// Creates new object with length equal to power and the value at power equal to coeff
// ---------------------------------------------------------------------------------------------------
Poly::Poly(int coeff, int power) {
   holdSize = (power + 1);
   coefficients = new int[holdSize];

   for(int i = 0;i<holdSize; i++) { // set all indexes to be equal to 0
      coefficients[i] = 0;
   }
   
   coefficients[power] = coeff; // set coeff at power
} // eoPoly(int, int)

// ------------------------------------Poly(Poly)-----------------------------------------------
// Description: Constructor for the polynomial, Poly object given
// Creates new object that is equal to the object given
// ---------------------------------------------------------------------------------------------------
Poly::Poly(const Poly &orig) {
   holdSize = orig.holdSize;
   coefficients = new int[holdSize]; // change the size of the array to match the new one

   for (int i = 0; i < holdSize; i++) { // copy array values to new array
      coefficients[i] = orig.coefficients[i]; 
   }
} // eoPoly(Poly)

// ------------------------------------~Poly(void)-----------------------------------------------
// Description: Deconstructor for the Poly object
// Deletes and frees the memory of the Poly object
// ---------------------------------------------------------------------------------------------------
Poly::~Poly(void) {
   delete []coefficients; 
   coefficients = NULL;
} // eo~Poly(void)

// ------------------------------------operator==-----------------------------------------------
// Description: overloaded ==
// Returns true if lhs == rhs, else false
// ---------------------------------------------------------------------------------------------------
bool Poly::operator==(const Poly& rhs) const {
     return (coefficients == rhs.coefficients);
} // eooperator==

// ------------------------------------operator!=-----------------------------------------------
// Description: overloaded !=
// Returns true if lhs != rhs, else false
// ---------------------------------------------------------------------------------------------------
bool Poly::operator!=(const Poly& rhs) const {
   return !(*this == rhs);
} // eooperator!=

// ------------------------------------operator=-----------------------------------------------
// Description: overloaded =
// Sets lhs to equal rhs
// ---------------------------------------------------------------------------------------------------
Poly& Poly::operator=(const Poly& rhs){
   if (&rhs != this) { // if they are not equal
      delete [] coefficients;
      coefficients= NULL;
      holdSize = rhs.holdSize;
      coefficients = new int[holdSize]; // make it the correct size

      for (int i = 0; i < holdSize; i++) {
         coefficients[i] = rhs.coefficients[i];
	  }
   }
   return *this;
} // eooperator=

// ------------------------------------operator>>-----------------------------------------------
// Description: overloaded >>
// Takes in two values and uses setCoeff() to place them in the Poly object
// -1 -1 to stop
// ---------------------------------------------------------------------------------------------------
istream& operator>>(istream &input, Poly &polyObj) {
   int coeff;
   int power;

   for(int i = 0; i < polyObj.holdSize; i++) { // set all values to 0
      polyObj.coefficients[i] = 0;
   }

   while(input >> coeff >> power) { // get the input from the user
      if ((coeff == -1) && (power == -1)){ // stop when -1 -1 is inputed
         break;
	  }
      polyObj.setCoeff(coeff,power); // use setCoeff() to place the values
   }
   return input;                       
} // eooperator>>

// ------------------------------------operator<<-----------------------------------------------
// Description: overloaded <<
// Prints out the values of the array
// Prints in the form (sign)(coefficient)(x^)(power)
// ---------------------------------------------------------------------------------------------------
ostream& operator<<(ostream &output, const Poly &polyObj) {
   bool emptyArray = true; // check to see if the array is only 0's

   for(int i = polyObj.holdSize - 1; i >= 0; --i) { // go through the array in descending order
      if(polyObj.coefficients[i] != 0) {
		  
         emptyArray = false; // there was a non-zero value
         output << " ";

         if (polyObj.coefficients[i] > 0) // if positive put "+" before it
            output << "+";
			
		 // makes sure the correct rules are followed
		 // e.g. coefficient of 1 = x
         if(i == 1) { 
            output  << polyObj.coefficients[i] << "x";
		 }
         else if (i == 0) { // coefficient = 0
            output  << polyObj.coefficients[i];
		 }
         else {
            output  << polyObj.coefficients[i] << "x^" << i;
		 }
      }
   }

   if (emptyArray) { // no non-zero terms, print out 0
      output << " 0";
   }
   return output;
} // eooperator<<

// ------------------------------------operator+-----------------------------------------------
// Description: overloaded +
// Adds the content of two arrays into a third 
// current = lhs + rhs
// ---------------------------------------------------------------------------------------------------
Poly Poly::operator+(const Poly& rhs) const{
	// find which array is longer
	int largerSize;
	if (holdSize > rhs.holdSize){
        largerSize = holdSize;
    }
    else {
        largerSize = rhs.holdSize;
    }
	
	Poly sum(0, largerSize); // make a new object of the larger size
	for (int i = 0; i < rhs.holdSize; i++ ){ // add the values from rhs to the new array
		sum.coefficients[i] += rhs.coefficients[i];
	}
	for (int i = 0; i < holdSize; i++){ // add the values from lhs to the new array
		sum.coefficients[i] += coefficients[i];
	}
	return sum;
} // eooperator+

// ------------------------------------operator-------------------------------------------------
// Description: overloaded -
// Subtracts the content of two arrays into a third 
// current = lhs - rhs
// ---------------------------------------------------------------------------------------------------
Poly Poly::operator-(const Poly& rhs) const{
	// find which array is longer
	int largerSize;
	if (holdSize > rhs.holdSize){
        largerSize = holdSize;
    }
    else {
        largerSize = rhs.holdSize;
    }
	Poly sub(0, largerSize); // make a new object of the larger size
	for (int i = 0; i < holdSize; i++){ // add the values from lhs to the new array
		sub.coefficients[i] += coefficients[i];
	}
	for (int i = 0; i < rhs.holdSize; i++){
		sub.coefficients[i] -= rhs.coefficients[i]; // subtract the values from the new array by rhs
	}
	return sub;
} // eooperator-

// ------------------------------------operator*------------------------------------------------
// Description: overloaded *
// Multiplies the content of two arrays into a third 
// current = lhs * rhs
// ---------------------------------------------------------------------------------------------------
Poly Poly::operator*(const Poly& rhs) const {
	int maxLength = (holdSize + rhs.holdSize); //Size of new array

	Poly mult(0,maxLength); //New Poly object of the required size

	for(int i = 0;i < holdSize;i++) {//Populate mult with calculations
		for(int j = 0; j < rhs.holdSize; j++) {
				mult.coefficients[i+j] += (coefficients[i] * rhs.coefficients[j]);
		}
	}
	return mult;
} // eooperator*

// ------------------------------------operator+=------------------------------------------------
// Description: overloaded +=
// Adds the content of two arrays into the first
// lhs = lhs + rhs
// ---------------------------------------------------------------------------------------------------
Poly& Poly::operator+=(const Poly& rhs){
   *this = *this + rhs;
   return *this;
} // eooperator+=

// ------------------------------------operator-=------------------------------------------------
// Description: overloaded -=
// Subtracts the content of two arrays into the first
// lhs = lhs - rhs
// ---------------------------------------------------------------------------------------------------
Poly& Poly::operator-=(const Poly& rhs){
   *this = *this - rhs;
   return *this;
} // eooperator-=

// ------------------------------------operator*=------------------------------------------------
// Description: overloaded *=
// Multiplies the content of two arrays into the first
// lhs = lhs * rhs
// ---------------------------------------------------------------------------------------------------
Poly& Poly::operator*=(const Poly& rhs){
	*this = *this * rhs;
	return *this;
} // eooperator*=

// ------------------------------------getCoeff(int)------------------------------------------------
// Description: Takes in a power and returns the coefficient at that power
// ---------------------------------------------------------------------------------------------------
int Poly::getCoeff(int power){
	if ((power >= 0) && (power < holdSize)){ // make sure the requested coefficient is in the array
		return coefficients[power];
	} else {
		return 0;
	}
} // eogetCoeff(int)

// ------------------------------------setCoeff(int, int)------------------------------------------------
// Description: Takes in two integers and sets the coefficient at the power
// ---------------------------------------------------------------------------------------------------
 void Poly::setCoeff(int coeff, int power){
	if (power >= 0){ // not making a negative power
		int holdIntermediate;
		int hold[holdSize + 1]; // new array to copy values too
		
		for (int i = 0; i <= holdSize; i++){ // copy values
			hold[i] = coefficients[i];
		}
		holdIntermediate = holdSize; // hold on the the temp array's size
		int holdHighest;
		// find out if the new power is larger than the array
		if (holdSize < power){
			holdHighest = power;
		} else {
			holdHighest = holdSize;
		} // holdHighest is now how long the new array needs to be
		coefficients = new int[holdHighest + 1]; // set the new array
		for (int i = 0; i <= holdHighest; i++){ // make the new array's values equal to 0
			coefficients[i] = 0; 
		}
		for (int i = 0; i <= holdIntermediate; i++){
		coefficients[i] = hold[i]; // set the new array equal to the temp array
		}
		coefficients[power] = coeff; // set the new value
	}
 } // eosetCoeff(int, int)
 