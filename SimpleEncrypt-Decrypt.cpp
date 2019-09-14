//File name: SimpleEncrypt-Decrypt.cpp
//Author: Sophia Boisvert
//Description: this program implements a cipher to encrypt or decrypt a message
//Last changed: 14 September, 2017

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
//decrypts a file based on a key file
void decrypt(ifstream& in_stream, ofstream& out_stream);
//creates a key file and encypts according to the random file. 
void encrypt(ifstream& in_stream, ofstream& out_stream);

int main()
{
 char input;
 char inputfile [33];
 char outputfile [33];
 ifstream in_file;
 ofstream out_file;
 
 do
 {
	cout << "\nWould you like to encrypt or decrypt <E or D>: ";
 	cin >> input;
 }while(input != 'E' && input != 'e' && input != 'd'&& input != 'D');
 
 cout << "Enter name of the input file: ";
 cin >> inputfile;
 in_file.open(inputfile);
	
 if(in_file.fail())
 {
  cout<< "Error opening input file" << endl;
  exit(EXIT_FAILURE);
 }
 
 cout << "Enter name of the output file: ";
 cin >> outputfile;
 out_file.open(outputfile);
	
 if(out_file.fail())
 {
  cout<< "Error opening output file";
  exit(EXIT_FAILURE);
 }
	
 if(input == 'E' || input == 'e')
  encrypt(in_file, out_file);
 else
  decrypt(in_file, out_file);
 
 in_file.close();
 out_file.close();
	
 return 0;
}

void decrypt(ifstream& in_stream, ofstream& out_stream)
{
	
 ifstream key_file;

 char keyfile [33];

 cout << "Enter name of the encryption key file: ";
 cin >> keyfile;
 key_file.open(keyfile);
	
 if(key_file.fail())
 {
  cout<< "Error opening encryption key file";
  exit(EXIT_FAILURE);
 }
	
 char value;
 int keyValue;
 
 while(!in_stream.eof())
 {
  in_stream >> value;
  if(value >= 65 && value <= 90)
   {
    key_file >> keyValue;
    value = ((value-65) + 26 - key%26) % 26 + 65;
    out_stream.put(value);
   }
  else if(value >= 97 && value <= 122)
   {
    key_file >> keyValue;
    value = ((value-97) + 26 - key%26) % 26 + 97;
    out_stream.put(value);
   }
  else if(value >= 48 && value <= 57)
   {
    key_file >> keyValue;
    value = ((value-48) + 10 - key%10) % 10 + 65;
    out_stream.put(value);
   }
  else
   out_stream.put(value);
 
 } 

}
void encrypt(ifstream& in_stream, ofstream& out_stream)
{
 ofstream key_file;
 char keyfile [33];
	
 cout << "Enter name of the encryption key file: ";
 cin >> keyfile;
	
 key_file.open(keyfile);
 if(key_file.fail())
 {
  cout<< "Error opening encryption key file";
  exit(EXIT_FAILURE);
 }
 srand(time(NULL));
	
 char value;
 int keyValue;
	
 while(!in_stream.eof())
 {
  in_stream >> value;
	 
  if(value >= 65 && value <= 90)
   {
    keyValue = rand() % 277 + 3;
    value = ((value-65) + keyValue) % 26 + 65;
    out_stream.put(value);
    key_file << keyValue << " ";
   }
	 
  else if(value >= 97 && value <= 122)
   {
    keyValue = rand() % 277 + 3;
    value = ((value - 97) + keyValue) % 26 + 97;
    out_stream.put(value);
    key_file << keyValue << " ";
   }
	 
  else if(value >= 48 && value <= 57)
   {
    keyValue = rand() % 277 + 3;
    value = ((value - 48) + keyValue) % 10 + 48;
    out_stream.put(value);
    key_file << keyValue << " ";
   }
	 
  else if(ispunct(value))
   out_stream.put(value);
	 
  else
	cout << "invalid value of " << value;
 
 } 
 key_file.close();
}
