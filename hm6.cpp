#include <cmath>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <unistd.h>
#include "RSA.h"
#include "BigInt.h"

#define RAND_GEN32 0x7FFFFFFF
#define RAND_GEN16 0xFFFF

using namespace RSAUtil;
using namespace std;

BigInt getDecryptedMessageFromRSA_obj(BigInt m, RSA RSA_obj)
{
	return RSA_obj.decrypt(m);
}

int main(int argc, char*argv[])
{
	RSA* _RSA_obj[10];
	BigInt _message, _encrypt, _decrypt;
	int _primeNumber[] = { 40343 , 40351,  40357,  40361,  40387,  40423 , 40427  ,40429 , 40433 ,40459,  40471,  40483 , 40487 , 40493 , 40499 , 40507,  40519,  40529 , 40531};
	int _nonPrimeNumber[] = {36782,36792,36792,36802,36822,36832,36842,36852,36872,36872,37692,37692,37692,37722,37742,37712,37782,37792,37812,37814};


cout << "1)------------------Encryption and Decryption using RSA----------------------"<<"\n";

//------------No arguments RSA --------------------------------------------
	   cout << "a) 10 instances of RSA routine(argument-less) encryption-decryption"<<"\n";
	for (int i = 0; i < 10; i++)
	{
		_RSA_obj[i] = new RSA();
		//usleep(60000);
		_message = int(((double) rand() / RAND_MAX)*RAND_GEN32);
		_encrypt = _RSA_obj[i]->encrypt(_message);
		_decrypt = _RSA_obj[i]->decrypt(_encrypt);

    cout << "Message: " << _message.toHexString() << "\t\tEncrypted: " << _encrypt.toHexString() << "\t\tDecrypted: " << _decrypt.toHexString()<<"\n";
	}
	cout<<"\n";
//------------1 prime number RSA --------------------------------------------
	   cout << "b) 5 RSA instances(1 prime number(>30,000) as argument) encryption-decryption "<<"\n";
	for (int i = 0; i < 5; i++)
	{
		_RSA_obj[i] = new RSA(_primeNumber[i]);
		usleep(450000);
		_message = int(((double) rand() / RAND_MAX)*RAND_GEN32);
		_encrypt = _RSA_obj[i]->encrypt(_message);
		_decrypt = _RSA_obj[i]->decrypt(_encrypt);

    cout << "Message: " << _message.toHexString() << "\t\tEncrypted: " << _encrypt.toHexString() << "\t\tDecrypted: " << _decrypt.toHexString()<<"\n";
	}
	cout<<"\n";
//------------2 prime numbers RSA --------------------------------------------
   cout << "c) 5 RSA instances(2 prime numbers(>30,000) as arguments) encryption-decryption "<<"\n";
	 for (int i = 0; i < 5; i++)
 	{
 		_RSA_obj[i] = new RSA(_primeNumber[i], _primeNumber[10-i]);
 		usleep(560000);
 		_message = int(((double) rand() / RAND_MAX)*RAND_GEN32);
 		_encrypt = _RSA_obj[i]->encrypt(_message);
	_decrypt = _RSA_obj[i]->decrypt(_encrypt);
 		 cout << "Message: " << _message.toHexString() << "\tEncrypted: " << _encrypt.toHexString() << "\tDecrypted: " << _decrypt.toHexString()<<"\n";
 	}
	cout<<"\n";

//--------------2 non prime numbers RSA-------------------------------------
cout << "d) 5 RSA instances(2 non prime numbers(>30,000) as arguments) encryption-decryption "<<"\n";
for (int i = 0; i < 10; i++)
{
 _RSA_obj[i] = new RSA(_nonPrimeNumber[i], _nonPrimeNumber[10-i]);
 usleep(50000);
 _message = int(((double) rand() / RAND_MAX)*RAND_GEN32);
 _encrypt = _RSA_obj[i]->encrypt(_message);
 _decrypt = _RSA_obj[i]->decrypt(_encrypt);
	cout << "Message: " << _message.toHexString() << "\tEncrypted: " << _encrypt.toHexString() << "\tDecrypted: " << _decrypt.toHexString()<<"\n";
}
cout<<"\n";

//--------------challenge response scheme---------------------------------------
cout << "2)--------------------Challenge response scheme--------------------" <<  "\n";
RSA rsa1, rsa2;
// Get public key and modulus of rsa1 object
BigInt rsa1PubKey = rsa1.getPublicKey();
BigInt rsa1N = rsa1.getModulus();

// Set public key and modulus of rsa1 to rsa2
rsa2.setPublicKey(rsa1PubKey);
rsa2.setN(rsa1N);

// Generating random message
_message = int(((double) rand() / RAND_MAX)*RAND_GEN32);

BigInt enc = rsa2.encrypt(_message);
BigInt dec = rsa1.decrypt(enc);

cout << "Plain Text:" << _message.toHexString() << "\tDecrypted Text:" << dec.toHexString() <<  "\n";
if (_message.operator==(dec))
	cout << "Challenge response scheme is Successful" <<  "\n";
else
	cout << "Challenge response scheme is Unsuccessful" <<  "\n";
cout <<  "\n";


//--------------Blind signature---------------------------------------

cout << "3)------------------Blind signature---------------------" <<  "\n";
RSA RSA_obj;
// Get RSA_obj's public key and modulus
BigInt bN = RSA_obj.getModulus();
BigInt bpub = RSA_obj.getPublicKey();

// Generate random number and its inverse
double AliceRandomNumber = double(((double) rand() / RAND_MAX)*RAND_GEN32);
BigInt rnd(AliceRandomNumber);
BigInt AliceRandomNumber_Invers = RSAUtil::modInverse(rnd, bN);

// Generate random message
_message = int(((double) rand() / RAND_MAX)*RAND_GEN32);

// Encryp the random number with RSA_obj's public key
BigInt encryptedRandom = RSAUtil::modPow(rnd, bpub, bN);

// Multiply the encrypted random number with the original message
BigInt mToRSA_obj = encryptedRandom.operator*(_message).operator%(bN);

// Get the decrypted message from RSA_obj
BigInt mFromRSA_obj = getDecryptedMessageFromRSA_obj(mToRSA_obj, RSA_obj);

// Retrieve the signature from the message
BigInt signature = mFromRSA_obj.operator*(AliceRandomNumber_Invers).operator%(bN);

BigInt check = RSAUtil::modPow(signature, bpub, bN);

cout << "message: " << _message.toHexString() << "\tsignature: " << signature.toHexString() << "\tdecrypted: " << check.toHexString() <<  "\n";

cout << "\nBlind signature: ";
if(_message.operator==(check))
	cout << "Blind signature Successful" <<"\n";
else
	cout << "Blind signature Unsuccessful" << "\n";

//--------------------------------------
cout<<"\n";
return 0;
}
