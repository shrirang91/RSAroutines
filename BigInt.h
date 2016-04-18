#ifndef BIGINT_H_
#define BIGINT_H_
#include <string>
#include <bitset>

namespace RSAUtil
{
	#define BIGINT_SIZE 96
	
	/*
	 * **********************************************************************************
	 * A class for representing 64 bit integers.  This is a wrapper class for a
	 * std::bitset<BIGINT_SIZE>.  It provides common operators for dealing with
	 * integers.  
	 *  
	 * @class: BigInt
	 * @namespace: RSAUtil
	 * @file: BigInt.h
	 * @author: Cynthia Sturton
	 * @version: 1.0.0.0
	 * @date: 10/03/2006
	 * **********************************************************************************
	 */

class BigInt
{
private:
	//The BIGINT_SIZE bit number represented by this class.
	std::bitset<BIGINT_SIZE> n;	
	
	
public:
	/*
	 * *******************************************************************************
	 * Constructors.  Initializes the bitset n with the given parameter.
	 * BigInt(): n is initialized to 0.
	 * BigInt(int, int): The first int is the second 32 bits of n.
	 * 					The second int is the low 32 bits of n.
	 * 					Using this method the BigInt can only be initialized to an
	 * 					integer of 64 bits.
	 * BigInt(int): The given int is the low order 32 bits of n.
	 * BigInt(std::bitset<BIGINT_SIZE>: n is initialized to the given bitset.
	 * *******************************************************************************
	 */
	BigInt();
	BigInt(int, int); 
	BigInt(int);
	BigInt(std::bitset<BIGINT_SIZE>);
	virtual ~BigInt();
	
	/*
	 * ******************************************************************************
	 * Overloaded operators for dealing with 96 bit numbers.
	 * ******************************************************************************
	 */
	 
	/*
	 * *****************************************************************************
	 * Overloaded addition operator.  Any carry-out is discarded.
	 * @parameter BigInt: Second operand in addition calculation.
	 * @returns BigInt: The result of adding this BigInt with the given BigInt.
	 * *****************************************************************************
	 */
	BigInt operator+(BigInt);
	
	/*
	 * ******************************************************************************
	 * Overloaded multiplication operator.  Any carry-out is discarded.
	 * @parameter BigInt: Second operand in multiplication calculation.
	 * @returns BigInt: The result of multiplying this BigInt with the given BigInt.
	 * ******************************************************************************
	 */
	BigInt operator*(BigInt);
	
	/*
	 * ******************************************************************************
	 * Overloaded multiplication oprator with assignment.  Any carry-out is discarded.
	 * @parameter BigInt: Second operator in multiplication calculation.
	 * @returns BigInt&: A reference to this BigInt after it has been multiplied by
	 * 	the given BigInt.
	 * *******************************************************************************
	 */
	BigInt& operator*=(BigInt);
	
	/*
	 * *******************************************************************************
	 * Overloaded xor operator.  Performs bitwise xor.
	 * @parameter BigInt: Second operator in the xor operation.
	 * @returns Bigint: The result of xor-ing this BigInt with the given BigInt.
	 * *******************************************************************************
	 */
	BigInt operator^(BigInt);
	
	/*
	 * ********************************************************************************
	 * Overloaded subtraction operator.  No checking for overflow is performed.
	 * Subtracting a larger number from a smaller number will result in a two's
	 * complement representation of a negative number.  However, BigInt does not handle
	 * negative numbers, and will always interpret any bitset as a positive integer.
	 * @parameter BigInt: The second operand in the subtraction operation.
	 * @returns BigInt: The result of subtracting the given BigInt from this BigInt.
	 * ********************************************************************************
	 */
	BigInt operator-(BigInt);
	
	/*
	 * *********************************************************************************
	 * Overloaded comparison operators.  All comparisons are unsigned.
	 * @parameter BigInt:	The second operand in the comparison.
	 * @returns bool:	The result of the comparison 
	 * 					thisBigInt <compare operator> givenBigInt.
	 * ********************************************************************************
	 */
	bool operator>=(BigInt);
	bool operator>(BigInt);
	bool operator<=(BigInt);
	bool operator<(BigInt);
	
	/*
	 * ********************************************************************************
	 * Overloaded division operator.
	 * @parameter BigInt:	The divisor in the division operation.
	 * @returns BigInt:		The quotient resulting from dividing this BigInt by the
	 * 						given BigInt.
	 * *******************************************************************************
	 */
	BigInt operator/(BigInt);
	
	/*
	 * ******************************************************************************
	 * Overloaded modulus operator.
	 * @parameter BigInt:	The divisor in the division operation.
	 * @returns BigInt:		The remainder resulting from dividing this BigInt by the
	 * 						given BigInt.
	 * *****************************************************************************
	 */
	BigInt operator%(BigInt);
	
	/*
	 * ******************************************************************************
	 * Overloaded logical shift right operator with assignment.
	 * @parameter int:	The shift amount.
	 * @returns BigInt&:	A reference to this BigInt after the shift has been done.
	 * ******************************************************************************
	 */
	BigInt& operator>>=(int);
	
	/*
	 * ******************************************************************************
	 * Overloaded logical shift left operator with assignment.
	 * @parameter int: The shift amount.
	 * @returns BigInt&:	A reference to this BigInt after the shift has been done.
	 * ******************************************************************************
	 */
	BigInt& operator<<=(int);
	
	/*
	 * *******************************************************************************
	 * Overloaded bit-wise OR with assignment.
	 * @parameter BigInt: The second operand in the OR operation.
	 * @returns BigInt&:	A reference to this BigInt after the bit-wise OR has been
	 * 						done.
	 * *******************************************************************************
	 */
	BigInt& operator|=(BigInt);
	
	/*
	 * *******************************************************************************
	 * Overloaded bit-wise AND with assignment.
	 * @parameter BigInt:	The second operand in the AND operation.
	 * @returns BigInt&:	A reference to this BigInt after the bit-wise AND has been
	 * 						done.
	 * ********************************************************************************
	 */
	BigInt& operator&=(BigInt);
	
	/*
	 * ********************************************************************************
	 * Overloaded equals operator.
	 * @parameter BigInt:	The operand with which to compare this BigInt.
	 * @returns bool:		True if the two BigInts have the same value.
	 * ********************************************************************************
	 */
	bool operator==(BigInt);
	
	/*
	 * *********************************************************************************
	 * Overloaded indexing operator.
	 * @parameter int:	The index of the underlying bitset to get.
	 * @returns int:	The bit (as an integer, 1 or 0) of the underlying bitset at the
	 * 					indicated index.
	 * *********************************************************************************
	 */
	int operator[](int) const;
	
	/*
	 * *********************************************************************************
	 * flip.  Flips every bit in the underlying bitset.
	 * @returns BigInt&:	A reference to this BigInt after every bit has been flipped.
	 * *********************************************************************************
	 */
	BigInt& flip();
	
	/*
	 * *********************************************************************************
	 * getN.  Returns the underlying bitset of this BigInt.
	 * @returns std::bitset<BIGINT_SIZE>:	The bitset of this BigInt.
	 * *********************************************************************************
	 */
	std::bitset<BIGINT_SIZE> getN() const;
	
	/*
	 * *********************************************************************************
	 * exp.		Performs fast exponentiation. This BigInt ^ given BigInt.
	 * @parameter BigInt:	The exponent.
	 * @returns BigInt:		The result of raising this BigInt to the power of the given
	 * 						BigInt.
	 * *********************************************************************************
	 */
	BigInt exp(BigInt);
	
	/*
	 * *********************************************************************************
	 * exp.		Performs fast exponentiation. This BigInt ^ given int.
	 * @parameter int:	The exponent.
	 * @returns BigInt:		The result of raising this BigInt to the power of the given
	 * 						BigInt.
	 * *********************************************************************************
	 */
	BigInt exp(int);
	
	/*
	 * ********************************************************************************
	 * isZero.	Tests whether this BigInt has all zero bits.
	 * @returns bool:	True if none of the bits of BigInt are set, false otherwise.
	 * *********************************************************************************
	 */
	bool isZero();
	
	/*
	 * *********************************************************************************
	 * toString.  Returns the binary representation of BigInt as a string.
	 * @returns std::string:	Binary representation of this BigInt.
	 * *********************************************************************************
	 */
	std::string toString() const;		
	
	/*
	 * *********************************************************************************
	 * toHexString().	Returns the hexadecimal representation of BigInt as a string.
	 * @returns std::string:	Hex representation of this BigInt.
	 * *********************************************************************************
	 */
	std::string toHexString() const;	
	
	/*
	 * *********************************************************************************
	 * toULong.		Convert BigInt to an array of unsigned longs.
	 * @parameter unsigned long*:	Pointer to an array of unsigned longs.  This array
	 * 							will be filled by the BigInt.  The lowest 32 bits of 
	 * 							this BigInt will be in index 0 of the array.
	 * @parameter int:	Size of the array.
	 * *********************************************************************************
	 */
	void toULong(unsigned long*, int) const;				



	
};
	
	/*
	 * *********************************************************************************
	 * modPow.	Performs modular exponentiation.  If the three parameters are a, b, m
	 * 		(in that order) then this function returns [a^b] mod m.
	 * @parameter BigInt:	The first operand.
	 * @parameter BigInt:	The exponent.
	 * @parameter BigInt:	The modulus.
	 * @returns BigInt:		The result of performing [a^b] mod m.
	 * *********************************************************************************
	 */
	BigInt modPow(BigInt, BigInt, BigInt);
	
	/*
	 * *********************************************************************************
	 * binToHex.	Converts a string representing a number in binary to a string
	 * 				representing that number in hex.
	 * @parameter std::string:	The binary representation of a number.
	 * @returns std::string:	The hexadecimal representation of a number.
	 * *********************************************************************************/
	std::string binToHex(std::string);
	
	/*
	 * **********************************************************************************
	 * add.	Performs bit-wise addition on the two bitsets.  Checking for overflow is not
	 * 		done and any overflow is lost.
	 * @parameter std::bitset<BIGINT_SIZE>:	The first operand.
	 * @parameter std::bitset<BIGINT_SIZE>:	The second operand.
	 * @returns std::bitset<BIGINT_SIZE>:	The result of the bitwise addition.
	 * **********************************************************************************/
	std::bitset<BIGINT_SIZE> add(std::bitset<BIGINT_SIZE>, std::bitset<BIGINT_SIZE>);
	
	/*
	 * *********************************************************************************
	 * subtract.	Performs bit-wise subtraction on the two bitsets.  No checking is 
	 * 			done to ensure the first operand is larger than the second.  If it is not
	 * 			the result will be a negative number in two's complement.
	 * @parameter std::bitset<BIGINT_SIZE>:	The first operand (op1).
	 * @parameter std::bitset<BIGINT_SIZE>:	The second operand (op2).
	 * @returns std::bitset<BIGINT_SIZE>:	The result of performing op1 - op2.
	 * **********************************************************************************
	 */
	std::bitset<BIGINT_SIZE> subtract(std::bitset<BIGINT_SIZE>, std::bitset<BIGINT_SIZE>);
	


}

#endif /*BIGINT_H_*/
