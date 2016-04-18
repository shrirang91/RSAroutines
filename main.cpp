#include <cmath>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <unistd.h>
#include "RSA.h"
#include "BigInt.h"

#define RAND_GEN 0x7FFFFFFF

using namespace RSAUtil;
using namespace std;

BigInt getDecryptedMessageFromRSA_obj(BigInt m, RSA RSA_obj)
{
	return RSA_obj.decrypt(m);
}

int main(int argc, char*argv[])
{
	RSA* myRSA[10];
	BigInt message, cipher, deciphered;
//int primeNumber[] = {30011, 30013, 30029, 30047, 30059, 30071, 30089, 30091, 30313, 30851,36787,36791,36793,36809,36821,36833,36847,36857,36871,36877};
	int primeNumber[] = {36787,36791,36793,36809,36821,36833,36847,36857,36871,36877,37691,37693,37699,37717,37747,37781,37783,37799,37811,37813};
	int nonPrimeNumber[] = {36782,36792,36792,36802,36822,36832,36842,36852,36872,36872,37692,37692,37692,37722,37742,37712,37782,37792,37812,37814};

	// Generating random message
	//message = int(((double) rand() / RAND_MAX)*RAND_GEN);

	 cout << "Encryption and Decryption using RSA routines" << endl;
	 cout << "1) With instances of the RSA class without giving arguments" <<  endl;
	for (int i = 0; i < 10; i++)
	{
		myRSA[i] = new RSA();
		usleep(860000);
		message = int(((double) rand() / RAND_MAX)*RAND_GEN);
		cipher = myRSA[i]->encrypt(message);
		deciphered = myRSA[i]->decrypt(cipher);
			cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() <<  endl;
	}
	 cout <<  endl;

	 cout << "\n2) With instances of the RSA class by passing a large prime number" <<  endl;
	for (int i = 0; i < 5; i++)
	{
		myRSA[i] = new RSA(primeNumber[i]);
		usleep(860000);
		message = int(((double) rand() / RAND_MAX)*RAND_GEN);
		cipher = myRSA[i]->encrypt(message);
		deciphered = myRSA[i]->decrypt(cipher);
		 cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() <<  endl;
	}
	 cout <<  endl;

	 cout << "\n2) With instances of the RSA class by passing 2 large prime numbers" <<  endl;
	for (int i = 0; i < 5; i++)
	{
		myRSA[i] = new RSA(primeNumber[i], primeNumber[10-i]);
		usleep(860000);
		message = int(((double) rand() / RAND_MAX)*RAND_GEN);
		cipher = myRSA[i]->encrypt(message);
		deciphered = myRSA[i]->decrypt(cipher);
		 cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() <<  endl;
	}
	 cout <<  endl;

	 cout << "\n2) With instances of the RSA class by passing 2 large non prime numbers" <<  endl;
	for (int i = 0; i < 10; i++)
	{
		myRSA[i] = new RSA(nonPrimeNumber[i], nonPrimeNumber[19 - i]);
		usleep(860000);
		message = int(((double) rand() / RAND_MAX)*RAND_GEN);
		cipher = myRSA[i]->encrypt(message);
		deciphered = myRSA[i]->decrypt(cipher);
		 cout << "message: " << message.toHexString() << "\tcipher: " << cipher.toHexString() << "\tdeciphered: " << deciphered.toHexString() <<  endl;
	}
	 cout <<  endl;

	 cout << "Challenge response scheme 0" <<  endl;
	RSA rsa1, rsa2;
	// Get public key and modulus of rsa1 object
	BigInt rsa1PubKey = rsa1.getPublicKey();
	BigInt rsa1N = rsa1.getModulus();

	// Set public key and modulus of rsa1 to rsa2
	rsa2.setPublicKey(rsa1PubKey);
	rsa2.setN(rsa1N);

	// Generating random message
	message = int(((double) rand() / RAND_MAX)*RAND_GEN);

	BigInt enc = rsa2.encrypt(message);
	BigInt dec = rsa1.decrypt(enc);

	 cout << "Original Text:" << message.toHexString() << "\tDecrypted Text:" << dec.toHexString() <<  endl;
	if (message.operator==(dec))
		 cout << "Challenge response scheme 0: Successful" <<  endl;
	else
		 cout << "Challenge response scheme 0: Failed" <<  endl;
	 cout <<  endl;

	 cout << "Blind signature" <<  endl;
	RSA RSA_obj;
	// Get RSA_obj's public key and modulus
	BigInt bN = RSA_obj.getModulus();
	BigInt bpub = RSA_obj.getPublicKey();

	// Generate random number and its inverse
	double AliceRandomNumber = double(((double) rand() / RAND_MAX)*RAND_GEN);
	BigInt rnd(AliceRandomNumber);
	BigInt AliceRandomNumber_Invers = RSAUtil::modInverse(rnd, bN);

	// Generate random message
	message = int(((double) rand() / RAND_MAX)*RAND_GEN);

	// Encryp the random number with RSA_obj's public key
	BigInt encryptedRandom = RSAUtil::modPow(rnd, bpub, bN);

	// Multiply the encrypted random number with the original message
	BigInt mToRSA_obj = encryptedRandom.operator*(message).operator%(bN);

	// Get the decrypted message from RSA_obj
	BigInt mFromRSA_obj = getDecryptedMessageFromRSA_obj(mToRSA_obj, RSA_obj);

	// Retrieve the signature from the message
	BigInt signature = mFromRSA_obj.operator*(AliceRandomNumber_Invers).operator%(bN);

	BigInt check = RSAUtil::modPow(signature, bpub, bN);

	 cout << "message: " << message.toHexString() << "\tsignature: " << signature.toHexString() << "\tdeciphered: " << check.toHexString() <<  endl;

	 cout << "Blind signature: ";
	if(message.operator==(check))
		 cout << "Successful" <<  endl;
	else
		 cout << "Failed" <<  endl;

	return 0;
}
