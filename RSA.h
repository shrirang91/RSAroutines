#include "BigInt.h"

#ifndef RSA_H_
#define RSA_H_

namespace RSAUtil
{

/****************************************************************************************
 * A class that implements 32-bit encryption using RSA public key encryption.  This class
 * provides methods for generating the public and private keys (Alternately, the public
 * key can be explicitly set) and for RSA encryption and decryption.
 * P and Q are generated randomly (using srand() from <cstdlib>), but they can be
 * specified in the constructor if desired.  (This feature is used mostly for testing.)
 * Additional helper functions are provided for finding gcd, testing for primality and
 * finding the modular inverse of a number.
 *
 * @class: RSA
 * @namespace: RSAUtil
 * @file: RSA.h
 * @author: Cynthia Sturton
 * @version: 1.0.0.0
 * @date: 10/03/2006
 * **************************************************************************************
 */
class RSA
{
private:
	//17 bit randomly generated prime numbers. p != q.
	unsigned int p, q;
	//modulus, n=p*q.
	BigInt n;
	//totient, phi=(p-1)(q-1).
	BigInt phi;
	//public key.  gcd(e, phi) == 1.
	BigInt e;
	//private key. [ed == 1] mod n.
	BigInt d;

	//Calculate the public and private keys.
	void calcE();
	void calcD();


public:

	/************************************************************************************
	 * Constructors.  Generates p & q, s.t. p!=q && p and q are both prime.
	 * If one int is given as a parametr, it is assigned to p and no checking
	 * is done on its validity (primeness).  If two ints are given, the first is
	 * p, the second is q and no testing is done for validity.  The constructor
	 * initializes n and phi.
	 * **********************************************************************************
	 */
	RSA();
	RSA(int);
	RSA(int, int);
	virtual ~RSA();

	/*
	 * *********************************************************************************
	 * Accessor methods.
	 * *********************************************************************************
	 */
	BigInt getPublicKey();
	BigInt getPrivateKey();
	BigInt getModulus() const;
	//Returns phi, the totient of the modulus.
	BigInt getPHI() const;
	int getP() const;
	int getQ() const;

	/*
	 * *********************************************************************************
	 * Modifier methods.
	 * *********************************************************************************
	 */

	/*
	 * ********************************************************************************
	 * The publiic key may be explicitly assigned.  No validation checking is
	 * performed.
	 * @parameter unsigned int: The integer to use as the public key.
	 * ********************************************************************************
	 */
	void setPublicKey(unsigned int);
	 // overloaded function for BigInt created by Raghunathan Srinivasan
	 void setPublicKey(BigInt B);

	/*
	 * *********************************************************************************
	 * Performs public-key encryption/decryption on given message.  Message must
	 * be <= 32 bits.  Automatic conversion from std::bitset<> or int to BigInt is
	 * possible.
	 * *********************************************************************************
	 */
	BigInt encrypt(BigInt);
	BigInt decrypt(BigInt);

/* The following 4 functions inserted by Raghunathan Srinivasan */



    void setN(BigInt B);
  // Rest of functions deleted for Project

};


/*
 * **************************************************************************************
 * Helper functions.  These functions can be accessed as part of RSAUtil namespace.
 * Any access to the RSA or BigInt objects are done through their public methods.
 * **************************************************************************************
 */

/*
 * *******************************************************************************
 * Uses the extended Euclidian algorithm to find the modular inverse,
 * b such that [ab == 1] mod m.
 * @parameter BigInt: This is 'a' in the above equation.
 * @parameter BigInt: This is 'm' in the above equation.
 * @returns BigInt: This is 'b' in the above equation.
 * *******************************************************************************
 */
BigInt modInverse(BigInt, BigInt);

/*
 * *******************************************************************************
 * Tests for Primality.  This function first checks for divisibility by the first
 * 100 primes and then, if the integer passes that test, uses the Miller-Rabin
 * algorithm for testing for compositeness.
 * @parameter int: The integer to be tested for primality.
 * @returns bool: False if the number is composite, True if the number is believed
 * 	to be prime with ??% certainty.
 * *******************************************************************************
 */
bool isPrime(int);

/*
 * ********************************************************************************
 * Uses the Miller-Rabin algorithm to test for possible primality.  Tests with five
 * different possible witnesses for a certainty of ??%.
 * @parameter int: The integer to be tested for primality.
 * @returns bool: False if the number is composite, True if the number is believed
 * to be prime.
 * *********************************************************************************
 */
bool isPrimeMR(int);

/*
 * *********************************************************************************
 * Checks for divisibility by the first 100 primes.
 * @parameter int: The integer to be tested for primality.
 * @returns bool: False if the number is divisible by one of the first 100 primes,
 * 	True if the number is not divisible by one of the first 100 primes.
 * *********************************************************************************/
bool isPrimeDiv(int);

/*
 * *******************************************************************************
 * Recursive function performs Euclidian algorithm for finding the greatest common
 * divisor of two integers.
 * @parameter int: The first integer.
 * @parameter int: The second integer.
 * @returns int: The greatest common divisor of the first and the second integers.
 * *******************************************************************************
 */
int gcd(int, int);

/*
 * *********************************************************************************
 * Recursive function performs Euclidian algorithm for finding the greatest common
 * divisor of two integers.
 * @parameter BigInt: The first integer.
 * @parameter BigInt: The second integer.
 * @returns BigInt: The greatest common divisor of the first and the second integers.
 * **********************************************************************************
 */
BigInt gcd(BigInt, BigInt);


}

#endif /*RSA_H_*/
