#include "BigInt.h"
#include <string>
#include <iostream>
#include <limits>
#include <bitset>
#include <cstdlib>


namespace RSAUtil
{



/* 
 * A class for handling large (64 bit) integers.  
 * Implemented via a bitset.
*/
BigInt::BigInt()
{
	n = 0x0;
}


BigInt::BigInt(int upper, int lower)
{
	n = upper;
	n <<= (32);
	n|=lower;
}

BigInt::BigInt(int lower)
{
	n = lower;
}

BigInt::BigInt(std::bitset<BIGINT_SIZE> num)
{
	n = num;
}
BigInt::~BigInt()
{
}

bool BigInt::isZero(){
	 return n.none();
}

//passes the BigInt into an array of unsigned longs.  If the array is
//not large enough the high order bits get cut off.
//The resulting array has low order bits placed in the low indexed longs.
//This can be printed correctly in hex for example:
//std::cout.setf(std::ios_base::showbase);
//std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
//unsigned long lArr[3];
//decrypt.toULong(lArr, 3);
//std::cout<<"decrypt: "<<lArr[2]<<lArr[1]<<lArr[0]<<std::endl;

	
void BigInt::toULong(unsigned long* arr, int size) const{
	std::bitset<BIGINT_SIZE> temp;
	for(int i=0; i<size; i++){
		temp = n >> (i*32);
		temp &= 0xFFFFFFFF;
		arr[i] = temp.to_ulong();
	}
}
std::string BigInt::toString() const
{
	return n.to_string<char, std::char_traits<char>, std::allocator<char> >();
}

std::string BigInt::toHexString() const
{
	std::string response = "0x";
	std::string nStr = n.to_string<char, std::char_traits<char>, std::allocator<char> >();
	int limit = nStr.length();
	int halfword = 1;
	
	for(int i=0;i<limit;){
		if((nStr.substr(i, 16) == "0000000000000000") && (response == "0x")){
			i=i+16;
		}
		else{
			for(int j=0;j<4;j++){
				response += binToHex(nStr.substr(i, 4));
				if(halfword%4 == 0){
					response += " ";
				}
				halfword++;
				i=i+4;
			}
		}
	}//end for loop.
	
	if(response=="0x"){
		response += "00";
	}
	return response;
}

//Reference a particular bit at position pos.
int BigInt::operator[](int pos) const{
	if(pos >= 0 && pos < BIGINT_SIZE){
		return n[pos];
	}
	else{
		return -1;
	}
}

//Multiply two BigInts.
BigInt BigInt::operator*(BigInt op){
	BigInt response;
	std::bitset<BIGINT_SIZE> answer;
	std::bitset<BIGINT_SIZE> a = n;
	
	//If either n or op.n = 0, don't bother.
	if(n.none() || op.n.none()){
		return response;	
	}
	
	for(unsigned int i = 0; i < op.n.size(); i++){
		// If ith bit in op.n = 1, add response += n, and shift n << 1.
		if(op.n.test(i)){
			answer = add(answer, a);
			a <<= 1;
		}
		// Else, shift n << 1.
		else{
			a <<= 1;
		}
	}//end for loop.

	response = answer;
	return response;
}

// Multiplication and assignment.
BigInt& BigInt::operator*=(BigInt op){
	BigInt response;
	std::bitset<BIGINT_SIZE> answer;
	
	//If either n or op.n = 0, don't bother.
	if(n.none() || op.n.none()){
		n = 0x00;
		return *this;	
	}
	
	for(unsigned int i = 0; i < op.n.size(); i++){
		// If ith bit in op.n = 1, add response += n, and shift n << 1.
		if(op.n.test(i)){
			answer = add(answer, n);
			n <<= 1;
		}
		// Else, shift n << 1.
		else{
			n <<= 1;
		}
	}//end for loop.

	*this = answer;
	return *this;
}

// Add two BigInts
BigInt BigInt::operator+(BigInt op){
	BigInt response;
	response = add(n, op.n);
	return response;	
}

// Compare two BigInts.  This code is dependent on BIGINT_SIZE = 96.
bool BigInt::operator>=(BigInt op){
	std::bitset<BIGINT_SIZE> opUpper, opMid, opLower, nUpper, nMid, nLower;
	unsigned long opUppL, opMidL, opLowL, nUppL, nMidL, nLowL;
	opUpper = op.n >> 64;
	nUpper = n >> 64;
	opUppL = opUpper.to_ulong();
	nUppL = nUpper.to_ulong();
	if(nUppL > opUppL){
		return true;
	}
	if(nUppL < opUppL){
		return false;
	}
	//nUppL == opUppL
	opMid = op.n >> 32;
	opMid &= 0xFFFFFFFF;
	nMid = n >> 32;
	nMid &= 0xFFFFFFFF;
	opMidL = opMid.to_ulong();
	nMidL = nMid.to_ulong();
	if(nMidL > opMidL){
		return true;
	}
	if(nMidL < opMidL){
		return false;
	}
	//nMidL == opMidL
	opLower = op.n;
	opLower&= 0xFFFFFFFF;
	nLower = n;
	nLower &= 0xFFFFFFFF;
	opLowL = opLower.to_ulong();
	nLowL = nLower.to_ulong();
	if(nLowL >= opLowL){
		return true;
	}
	return false;
}

//This code is dependent on BIGINT_SIZE = 96.
bool BigInt::operator>(BigInt op){
	std::bitset<BIGINT_SIZE> opUpper, opMid, opLower, nUpper, nMid, nLower;
	unsigned long opUppL, opMidL, opLowL, nUppL, nMidL, nLowL;
	opUpper = op.n >> 64;
	nUpper = n >> 64;
	opUppL = opUpper.to_ulong();
	nUppL = nUpper.to_ulong();
	if(nUppL > opUppL){
		return true;
	}
	if(nUppL < opUppL){
		return false;
	}
	//nUppL == opUppL
	opMid = op.n >> 32;
	opMid &= 0xFFFFFFFF;
	nMid = n >> 32;
	nMid &= 0xFFFFFFFF;
	opMidL = opMid.to_ulong();
	nMidL = nMid.to_ulong();
	if(nMidL > opMidL){
		return true;
	}
	if(nMidL < opMidL){
		return false;
	}
	//nMidL == opMidL	
	opLower = op.n;
	 opLower&= 0xFFFFFFFF;
	nLower = n;
	nLower &= 0xFFFFFFFF;
	opLowL = opLower.to_ulong();
	nLowL = nLower.to_ulong();
	if(nLowL > opLowL){
		return true;
	}
	return false;
}

//This is very much dependent on BIGINT_SIZE.
//If the size != 96, this code will have to change.
bool BigInt::operator<=(BigInt op){
	std::bitset<BIGINT_SIZE> opUpper, opMid, opLower, nUpper, nMid, nLower;
	unsigned long opUppL, opMidL, opLowL, nUppL, nMidL, nLowL;
	opUpper = op.n >> 64;
	nUpper = n >> 64;
	opUppL = opUpper.to_ulong();
	nUppL = nUpper.to_ulong();
	if(nUppL < opUppL){
		return true;
	}
	if(nUppL > opUppL){
		return false;
	}
	//nUppL == opUppL
	opMid = op.n >> 32;
	opMid &= 0xFFFFFFFF;
	nMid = n >>32;
	nMid &= 0xFFFFFFFF;
	opMidL = opMid.to_ulong();
	nMidL = nMid.to_ulong();
	if(nMidL < opMidL){
		return true;
	}
	if(nMidL > opMidL){
		return false;
	}
	//nMidL == opMidL
	opLower = op.n;
	 opLower&= 0xFFFFFFFF;
	nLower = n;
	nLower &= 0xFFFFFFFF;
	opLowL = opLower.to_ulong();
	nLowL = nLower.to_ulong();
	if(nLowL <= opLowL){
		return true;
	}
	return false;
}

//Depends on BIGINT_SIZE
bool BigInt::operator<(BigInt op){
	std::bitset<BIGINT_SIZE> opUpper, opMid, opLower, nUpper, nMid, nLower;
	unsigned long opUppL, opMidL, opLowL, nUppL, nMidL, nLowL;
	opUpper = op.n >> 64;
	nUpper = n >> 64;
	
	opUppL = opUpper.to_ulong();
	nUppL = nUpper.to_ulong();
	if(nUppL < opUppL){
		return true;
	}
	if(nUppL > opUppL){
		return false;
	}
	//nUppL == opUppL
	opMid = op.n >> 32;
	opMid &= 0xFFFFFFFF;
	
	nMid = n >>32;
	nMid &= 0xFFFFFFFF;
	
	opMidL = opMid.to_ulong();
	nMidL = nMid.to_ulong();
	if(nMidL < opMidL){
		return true;
	}
	if(nMidL > opMidL){
		return false;
	}
	//nMidL == opMidL
	opLower = op.n;
	opLower&= 0xFFFFFFFF;
	nLower = n;
	nLower &= 0xFFFFFFFF;
	opLowL = opLower.to_ulong();
	nLowL = nLower.to_ulong();
	if(nLowL < opLowL){
		return true;
	}
	return false;
}

// Divide two BigInts.  Any remainder is discarded. *this/dvsr.
BigInt BigInt::operator/(BigInt divisor){
	BigInt response;
	BigInt quotient;
	BigInt dividend = *this;
	BigInt origDivisor = divisor;
	int idx = BIGINT_SIZE -1;
	
	if(dividend<divisor){
		response = 0;
	}
	else{
		//Find the leftmost bit in dividend.
		while(!dividend[idx]){
			idx--;
		}
		//Left align the divisor with the dividend.
		while(!divisor[idx]){
			divisor <<= 1;
		}
		//Perform binary division.
		do{
			if(dividend >= divisor){
				dividend = dividend-divisor;
				quotient <<= 1;
				quotient |= 0x01;
			}
			else{
				quotient <<= 1;
			}
			divisor >>= 1;
		}while(divisor >= origDivisor);
			
		response = quotient;	
	}

	return response;
}

bool BigInt::operator==(BigInt op){
	return (n==op.n);
}

// Find the modulo when dividing two BigInts. *this/divisor.
BigInt BigInt::operator%(BigInt divisor){
	BigInt response;
	BigInt quotient;
	BigInt dividend = *this;
	BigInt origDivisor = divisor;
	int idx = BIGINT_SIZE -1;
		
	if(divisor.isZero()){
		response = 0;
	}
	else if(dividend<divisor){
		response = dividend;
	}
	else{
		//Find the leftmost bit in dividend.
		while(!dividend[idx] ){
			idx--;
		}
		//Left align the divisor with the dividend.
		while(!divisor[idx]){
			divisor <<= 1;
		}
		//Perform binary division.
		do{
			if(dividend >= divisor){
				dividend = dividend-divisor;
				quotient <<= 1;
				quotient |= 0x01;
			}
			else{
				quotient <<= 1;
			}
			divisor >>= 1;
		}while(dividend >= origDivisor);
			
		response = dividend;	
	}
	return response;
}



// Shift left
BigInt& BigInt::operator<<=(int shift){
	n <<= shift;
	return *this;
}

// Shift right
BigInt& BigInt::operator>>=(int shift){
	n>>=shift;
	return *this;
}

// Bitwise OR with assignment.
BigInt& BigInt::operator|=(BigInt op){
	n|=op.n;
	return *this;
}

// Bitwise AND with assignment.
BigInt& BigInt::operator&=(BigInt op){
	n&=op.n;
	return *this;
}

// Flip every bit.
BigInt& BigInt::flip(){
	n.flip();
	return *this;
}


// Subtract two BigInts.  Won't throw an error if n<op.n.
BigInt BigInt::operator-(BigInt op){
	BigInt response;
	response = subtract(n, op.n);
	return response;
}
	




// Calculate this^y using fast exponentiation.
BigInt BigInt::exp(int y){
	BigInt BIy, response;
	BIy = y;
	response = exp(BIy);
	return response;
}

// Calculate this^y using fast exponentiation.
BigInt BigInt::exp(BigInt y){
	BigInt result;
	std::bitset<BIGINT_SIZE> bity;
	result = 1;
	bity = y.n;
	for(int i=BIGINT_SIZE-1; i>=0; i--){
		if(bity.test(i)){
			result = result*result;
			result = result*n;
		}
		else{
			result = result*result;
		}
	}
	return result;
}
std::bitset<BIGINT_SIZE> BigInt::getN() const {
	return n;
}

//x^y mod m using fast exponentiation.
BigInt modPow(BigInt x, BigInt y, BigInt m){
	
	BigInt result;
	std::bitset<BIGINT_SIZE> bity;
	int startIdx = BIGINT_SIZE - 1;
	result = 1;
	bity = y.getN();
	
	
	//ignore leading 0's and check for y==0.
	while((startIdx>=0) && (!(bity.test(startIdx)))){
		startIdx--;
	}
	for(int i=startIdx; i>=0; i--){
		if(bity.test(i)){
			result = result*result;
			result = result % m;
			result = result*x.getN();
			result = result % m;
		}
		else{
			result = result*result;
			result = result % m;
		}
	}
	return result;
}


std::string binToHex(std::string bin){
	std::string response;
	long val = std::strtol(bin.c_str(),0,2);
	
	switch(val){
		case 0:
			response = "0";
			break;
		case 1:
			response = "1";
			break;
		case 2:
			response = "2";
			break;
		case 3:
			response = "3";
			break;
		case 4:
			response = "4";
			break;
		case 5:
			response = "5";
			break;
		case 6:
			response = "6";
			break;
		case 7:
			response = "7";
			break;
		case 8:
			response = "8";
			break;
		case 9:
			response = "9";
			break;
		case 10:
			response = "A";
			break;
		case 11:
			response = "B";
			break;
		case 12:
			response = "C";
			break;
		case 13:
			response = "D";
			break;
		case 14:
			response = "E";
			break;
		case 15:
			response = "F";
			break;
		default:
			response = "X";
	}
		
	
	return response;
}

// Add two bitsets.  Any carry out gets lost.
std::bitset<BIGINT_SIZE> add(std::bitset<BIGINT_SIZE> op1, std::bitset<BIGINT_SIZE> op2){
	std::bitset<BIGINT_SIZE> answer;
	int carryIn = 0;
	
	for(int i=0; i<BIGINT_SIZE; i++){
		answer[i] = op1[i] ^ op2[i] ^ carryIn;
		carryIn = (op1[i] & op2[i]) | (carryIn & (op1[i] | op2[i]));
	}
		
	return answer;
}

// Subtract two bitsets.  op1 >= op2.
std::bitset<BIGINT_SIZE> subtract(std::bitset<BIGINT_SIZE> op1, std::bitset<BIGINT_SIZE> op2){
	std::bitset<BIGINT_SIZE> answer;
	int borrowIn = 0;
	
	for(int i=0; i<BIGINT_SIZE; i++){
		answer[i] = op1[i] ^ op2[i] ^ borrowIn;
		borrowIn = (~op1[i] & op2[i]) | (~op1[i] & borrowIn) | (op2[i] & borrowIn);
	}
	return answer;
}

}
