#include <iostream>
#include "myString.h"
using namespace std;

//length calculator
int myString::length(const char* _str) {
	int ct = 0;
	for (int i = 0; _str[i] != '\0'; i++) {
		ct++;
	}
	return ct;
}

//default constructor
myString::myString() : str(new char[1]), l(0), cap(1) {
	str[0] = '\0';
}
//parametrized contructors
myString::myString(char ch) {   //myString s2('A') will create "A" 
	this->l = 1;
	this->cap = 1;
	this->str = new char[l + 1]; // +1 for null
	str[0] = ch;
	str[1] = '\0';
}

myString::myString(const char* _str) {  //myString s3("hello");  se "hello" bane ga
	int l_str = length(_str);
	str = new char[l_str + 1];
	for (int i = 0; i < l_str; i++) {
		this->str[i] = _str[i];
	}
	str[l_str] = '\0';
	this->l = l_str;
	this->cap = l_str;
}

myString::myString(char ch, int size) {  //myString s1('a',5) se "aaaaa" banega
	this->str = new char[size + 1];  //+1 for null
	this->l = size;
	this->cap = size;
	for (int i = 0; i < size; i++) {
		str[i] = ch;
	}
	str[size] = '\0';
}


myString::myString(int size) {
	this->l = size;
	this->cap = size;
	this->str = new char[size + 1];
}

//copy contructor
myString::myString(const myString& _str) {
	this->str = new char[_str.l + 1];
	for (int i = 0; i < _str.l; i++) {
		this->str[i] = _str.str[i];
	}
	this->str[_str.l] = '\0';
	this->cap = _str.l;
	this->l = _str.l;
}

//display function
void myString::display() {
	for (int i = 0; str[i] != '\0'; i++) {
		cout << str[i];
	}
	cout << endl;
}

//shallow copy
void myString::replace_first(char ch) {
	this->str[0] = ch;
}

void myString::trim() {
	//from start
	if (this->str[0] == ' ' || this->str[0] == '\t' || this->str[0] == '\n') {
		for (int i = 0; i < this->l; i++) {
			if (!(this->str[i] == ' ' || this->str[i] == '\t' || this->str[i] == '\n')) {
				break;
			}

			//left shift
			for (int k = 0; k < this->l; k++) {
				str[k] = str[k + 1];
			}
			i--;
			this->l--;
		}
	}

	//from end
	if (this->str[l - 1] == ' ' || this->str[l - 1] == '\t' || this->str[l - 1] == '\n')
		for (int i = this->l - 1; i >= 0; i--) {
			if (!(this->str[i] == ' ' || this->str[i] == '\t' || this->str[i] == '\n')) {
				break;
			}
			//simple length km krdo
			this->l--;
			this->str[this->l] = '\0';
		}
}

//integer to string
myString myString::itos(int num) {
	this->l = 0;
	int temp;
	temp = num;
	while (temp > 0) {
		temp = temp / 10;
		this->l++;
		this->cap++;
	}
	myString temp_str(this->l);
	int i = 0;
	while (num > 0) {
		int digit = num % 10;
		//convert each digit to char
		//aik temp array bane baar bar jiska size l ho aur wo barhta rahe
		temp_str.str[l - i - 1] = digit + '0';
		num = num / 10;
		i++;
	}
	temp_str.str[l] = '\0';

	return temp_str;
}

//string to integer
int myString::stoi(const char* _str) {
	int l_str = length(_str);
	int integer = 0;
	for (int i = 0; i < l_str; i++) {
		//har char to int me convert kro
		int digit = _str[i] - '0';
		integer = (integer * 10) + digit;
	}
	return integer;
}

//=====equality functions=====
bool myString::isEqual(const myString& s2) {
	if (this->l != s2.l) {
		return false;
	}
	for (int i = 0; i < s2.l; i++) {
		if (this->str[i] != s2.str[i]) {
			return false;
		}
	}

	return true;
}

//overloading the same func
bool myString::operator==(const myString& s2) {
	if (this->l != s2.l) {
		return false;
	}
	for (int i = 0; i < s2.l; i++) {
		if (this->str[i] != s2.str[i]) {
			return false;
		}
	}

	return true;
}

bool myString::isNotEqual(const myString& s2) {
	if (this->l != s2.l) {
		return true;
	}
	for (int i = 0; i < s2.l; i++) {
		if (this->str[i] != s2.str[i]) {
			return true;
		}
	}

	return false;
}

//overloading the same func
bool myString::operator!=(const myString& s2) {
	if (this->l != s2.l) {
		return true;
	}
	for (int i = 0; i < s2.l; i++) {
		if (this->str[i] != s2.str[i]) {
			return true;
		}
	}

	return false;
}

bool myString::isLesser(const myString& s2) {
	//agr equal ha to
	if (this->isEqual(s2)) {
		cout << "they are equal\n";
		return false;
	}
	for (int i = 0; str[i] != '\0' || s2.str[i] != '\0'; i++) {
		if (this->str[i] > s2.str[i]) {
			return false;
		}
		else if (this->str[i] < s2.str[i]) {
			return true;  //agr char chota hoga then calling obj then return true
		}
		//wrna i barhta hi rahe ga
	}

	return false;
}

//overloading it
bool myString::operator<(const myString& s2) {
	//agr equal ha to
	if (this->isEqual(s2)) {
		cout << "they are equal\n";
		return false;
	}
	for (int i = 0; str[i] != '\0' || s2.str[i] != '\0'; i++) {
		if (this->str[i] > s2.str[i]) {
			return false;
		}
		else if (this->str[i] < s2.str[i]) {
			return true;  //agr char chota hoga then calling obj then return true
		}
		//wrna i barhta hi rahe ga
	}

	return false;
}

bool myString::isGreater(const myString& s2) {
	//agr equal ha to
	if (this->isEqual(s2)) {
		cout << "they are equal\n";
		return false;
	}
	for (int i = 0; str[i] != '\0' || s2.str[i] != '\0'; i++) {
		if (this->str[i] > s2.str[i]) {
			return true;
		}
		else if (this->str[i] < s2.str[i]) {
			return false;  //agr char chota hoga then calling obj then return true
		}
		//wrna i barhta hi rahe ga
	}

	return false;
}

//overloading it
bool myString::operator>(const myString& s2) {
	//agr equal ha to
	if (this->isEqual(s2)) {
		cout << "they are equal\n";
		return false;
	}
	for (int i = 0; str[i] != '\0' || s2.str[i] != '\0'; i++) {
		if (this->str[i] > s2.str[i]) {
			return true;
		}
		else if (this->str[i] < s2.str[i]) {
			return false;  //agr char chota hoga then calling obj then return true
		}
		//wrna i barhta hi rahe ga
	}

	return false;
}

//====find funcs===
int myString::find_first(char ch) {
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] == ch) {
			return i;
		}
	}
	return -1;
}

int myString::find_first(const myString& s2) {

	for (int i = 0; i < this->l; i++) {
		bool found = false;
		if (this->str[i] == s2.str[0]) {
			for (int j = 0; j < s2.l; j++) {
				if (this->str[i + j] != s2.str[j]) {
					found = false;
					break;
				}
				found = true;
			}
		}
		if (found == true) {
			return i;
		}

	}
	return -1;
}

int myString::find_last(char ch) {
	int idx = -1;
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] == ch) {
			idx = i;
		}
	}
	return idx;

}

int myString::find_last(const myString& s2) {
	int idx = -1;
	for (int i = 0; i < this->l; i++) {
		bool found = false;
		if (this->str[i] == s2.str[0]) {
			for (int j = 0; j < s2.l; j++) {
				if (this->str[i + j] != s2.str[j]) {
					found = false;
					break;
				}
				found = true;
			}
		}
		if (found == true) {
			idx = i;
		}

	}
	return idx;
}

int* myString::find_all(char ch, int& C) {
	int caps = 1;
	int* count = new int[caps];
	int idx = 0;
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] == ch) {

			if (C == caps) { //agr capacity aur count same hojaye then regrow
				int* temp = new int[caps + 1];
				for (int i = 0; i < caps; i++) {
					temp[i] = count[i];
				}
				caps++;
				delete[]count;
				count = new int[caps];
				//copy
				for (int i = 0; i < caps; i++) {
					count[i] = temp[i];
				}
				delete[]temp;
			}
			count[idx] = i;
			idx++;

			C++;

		}
	}
	return count;
}

int* myString::find_all(const myString& s2, int& C) {
	int caps = 1;
	int* count = new int[caps];
	int idx = 0;
	for (int i = 0; i < this->l; i++) {
		bool found = false;
		if (this->str[i] == s2.str[0]) {
			for (int j = 0; j < s2.l; j++) {
				if (this->str[i + j] != s2.str[j]) {
					found = false;
					break;
				}
				found = true;
			}
		}
		if (found == true) {
			if (C == caps) { //agr capacity aur count same hojaye then regrow
				int* temp = new int[caps + 1];
				for (int i = 0; i < caps; i++) {
					temp[i] = count[i];
				}
				caps++;
				delete[]count;
				count = new int[caps];
				//copy
				for (int i = 0; i < caps; i++) {
					count[i] = temp[i];
				}
				delete[]temp;
			}
			count[idx] = i;
			idx++;

			C++;


		}

	}
	return count;
}

//====remove funcs=====
void myString::remove_at(int idx) {
	for (int j = idx; j < this->l; j++) {
		this->str[j] = this->str[j + 1];
	}
	this->l--;
}

void myString::remove_first(char ch) {
	int idx = 0;
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] == ch) {
			idx = i;
			break;
		}
	}
	//yaha se left shift
	for (int j = idx; j < this->l; j++) {
		this->str[j] = this->str[j + 1];
	}
	this->l--;
}

void myString::remove_last(char ch) {
	int idx = 0;
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] == ch) {
			idx = i;
		}
	}
	//yaha se left shift
	for (int j = idx; j < this->l; j++) {
		this->str[j] = this->str[j + 1];
	}
	this->l--;
}

void myString::remove_all(char ch) {
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] == ch) {
			//left shift
			for (int j = i; j < this->l; j++) {
				this->str[j] = this->str[j + 1];

			}
			this->l--;
			i--;
		}
	}
}

//=====insert funcs=====
void myString::insert_at(int idx, char ch) {// Add a character at given position
	if (this->cap == this->l) {
		//regrow
		this->cap = this->cap * 2;
		char* temp = new char[this->cap + 1]; //+1 for null

		//copy
		for (int i = 0; i < this->l; i++) {

			temp[i] = this->str[i];

		}
		for (int i = this->l; i >= idx; i--) {
			temp[i + 1] = temp[i];
		}

		temp[idx] = ch;
		this->l++;

		delete[]str;
		this->str = new char[this->cap + 1];

		for (int i = 0; i < this->l; i++) {
			str[i] = temp[i];
		}
		str[this->l] = '\0';
	}
	else {
		//right shift
		for (int i = this->l; i >= idx; i--) {
			str[i + 1] = str[i];
		}
		str[idx] = ch;
	}

}

void myString::insert_at(int idx, const myString& s2) {// Add a string at given position
	int s2_l = length(s2.str);
	if (this->l + s2.l > this->cap) {
		//regrow
		this->cap = this->l + s2.l;
		char* temp = new char[this->cap + 1]; //+1 for null

		//copy
		for (int i = 0; i < this->l; i++) {

			temp[i] = this->str[i];

		}

		for (int i = this->l; i >= idx; i--) {

			temp[i + s2.l] = temp[i];
		}

		//add the substr after making space for it
		for (int i = 0; i < s2.l; i++) {
			temp[i + idx] = s2.str[i];
			this->l++;
		}

		//copy in str
		delete[]str;
		this->str = new char[this->cap + 1];

		for (int i = 0; i < this->l; i++) {
			str[i] = temp[i];
		}
		str[this->l] = '\0';

		delete[]temp;
	}
	else {
		//ab cap barhane ki zaroorat ni because upper condition false hogi to else me ayega
		//right shifting
		for (int i = this->l; i >= idx; i--) {

			this->str[i + s2.l] = this->str[i];
		}

		//add the substr after making space for it
		for (int i = 0; i < s2.l; i++) {
			this->str[i + idx] = s2.str[i];
			this->l++;
		}
		str[this->l] = '\0';
	}
}

//==== upper / lower funcs ====
void myString::to_upper() {
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] >= 'a' && this->str[i] <= 'z') {
			if (this->str[i] != ' ') {
				this->str[i] = this->str[i] - 32;

			}
		}
	}
}

void myString::to_lower() {
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] >= 'A' && this->str[i] <= 'Z') {
			if (this->str[i] != ' ') {
				this->str[i] = this->str[i] + 32;
			}
		}
	}
}

//==split func===
myString* myString::split(char delim, int& count) {
	count = 1;
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] == delim) {
			count++;
		}
	}

	myString* split_strs = new myString[count];
	int* length = new int[count]();
	for (int i = 0; i < count; i++) {
		length[i] = 0;
	}
	int idx = 0;
	for (int i = 0; i < this->l; i++) {
		if (this->str[i] != delim) {
			length[idx]++;
		}
		else {
			idx++;
		}
	}

	// memory alloc
	for (int i = 0; i < count; i++) {
		split_strs[i].str = new char[length[i] + 1];  //+1 null k liye
		split_strs[i].l = length[i];
	}

	//splitting
	idx = 0;
	int start = 0;
	int end = 0;
	for (int i = 0; i <= this->l; i++) {
		if (this->str[i] != delim && this->str[i] != '\0') {
			end++;

		}
		else {
			for (int j = 0; j < end; j++) {
				split_strs[idx].str[j] = this->str[start + j];
			}
			split_strs[idx].str[end] = '\0'; //hr splitted substr k end pe null rakhwado
			split_strs[idx].l = end;
			idx++;
			start = i + 1;
			end = 0;
		}

	}

	delete[] length;
	return split_strs;
}

//==tokenize==
myString* myString::tokenize(const char* delimiter, int& count) {
	int delim_l = 0;
	while (delimiter[delim_l] != '\0') {
		delim_l++;
	}
	count = 1; //count 1 se start kia because no of tokens = num of delms + 1
	for (int i = 0; i <= this->l - delim_l; i++) {
		bool match = true;
		for (int j = 0; j < delim_l; j++) {
			if (this->str[i + j] != delimiter[j]) {
				match = false;
				break;
			}
		}
		if (match == true) {
			count++;
			i += delim_l - 1;   //agr match hojaye then skip the delimeter taake dobara count na ho
			// - 1 isliye because for loop automatically +1 krega
		}
	}
	myString* split_strs = new myString[count];
	int str_idx = 0;
	int start = 0;
	for (int i = 0; i <= this->l; i++) {
		if (i <= this->l - delim_l) {
			bool match = true;
			for (int j = 0; j < delim_l; j++) {
				if (this->str[i + j] != delimiter[j]) {
					match = false;
					break;
				}
			}

			if (match == true) {
				int length = i - start;
				split_strs[str_idx].str = new char[length + 1]; //+1 for null
				split_strs[str_idx].l = length;

				//copy it
				for (int j = 0; j < length; j++) {
					split_strs[str_idx].str[j] = this->str[start + j];
				}
				split_strs[str_idx].str[length] = '\0';
				str_idx++;
				start = i + delim_l;
				i += delim_l - 1;
			}
		}
		//end wala split
		if (i == this->l) {
			int length = i - start;
			split_strs[str_idx].str = new char[length + 1];
			split_strs[str_idx].l = length;

			for (int j = 0; j < length; j++) {
				split_strs[str_idx].str[j] = this->str[start + j];
			}
			split_strs[str_idx].str[length] = '\0';
		}
	}

	return split_strs;
}

//concat , append
myString myString::concat(const myString& s2) {
	int s2_l = length(s2.str);
	myString temp(this->l + s2_l);
	for (int i = 0; i < this->l; i++) {
		temp.str[i] = this->str[i];
	}
	for (int i = 0; i < s2_l; i++) {
		temp.str[this->l + i] = s2.str[i];
	}
	temp.str[this->l + s2_l] = '\0';
	temp.l = this->l + s2_l;
	return temp;
}

//overloading it
myString myString::operator+(const myString& s2) {
	int s2_l = length(s2.str);
	myString temp(this->l + s2_l);
	for (int i = 0; i < this->l; i++) {
		temp.str[i] = this->str[i];
	}
	for (int i = 0; i < s2_l; i++) {
		temp.str[this->l + i] = s2.str[i];
	}
	temp.str[this->l + s2_l] = '\0';
	temp.l = this->l + s2_l;
	return temp;
}

void myString::append(const myString& s2) {
	int s2_l = length(s2.str);
	char* temp = new char[(this->l + s2_l) + 1];
	for (int i = 0; i < this->l; i++) {
		temp[i] = this->str[i];
	}
	for (int i = 0; i < s2_l; i++) {
		temp[this->l + i] = s2.str[i];
	}
	temp[this->l + s2_l] = '\0';

	delete[]this->str;
	this->str = new char[this->l + s2_l + 1];
	for (int i = 0; i < this->l + s2_l; i++) {
		this->str[i] = temp[i];
	}
	this->str[this->l + s2_l] = '\0';
	this->l = this->l + s2_l;
	delete[]temp;
}

//==all substr search==
int* myString::all_sub_search(const char* substr, int& C) {
	int substr_l = length(substr);
	int caps = 1;
	int* count = new int[caps];
	int idx = 0;
	for (int i = 0; i < this->l; i++) {
		bool found = false;
		if (this->str[i] == substr[0]) {
			for (int j = 0; j < substr_l; j++) {
				if (this->str[i + j] != substr[j]) {
					found = false;
					break;
				}
				found = true;
			}
		}
		if (found == true) {
			if (C == caps) { //agr capacity aur count same hojaye then regrow
				int* temp = new int[caps + 1];
				for (int i = 0; i < caps; i++) {
					temp[i] = count[i];
				}
				caps++;
				delete[]count;
				count = new int[caps];
				//copy
				for (int i = 0; i < caps; i++) {
					count[i] = temp[i];
				}
				delete[]temp;
			}
			count[idx] = i;
			idx++;

			C++;
		}
	}
	return count;
}

char myString::operator[](int i) const {
	return str[i];
}

char& myString::operator[](int i) {
	return this->str[i];
}

void myString::clear() {
	delete[] this->str;
	this->str = new char[1];
	this->str[0] = '\0'; //sirf null rakwao
	this->l = 0;
	this->cap = 1;
}

// Output operator (<<)
ostream& operator<<(ostream& os, const myString& obj) {
	for (int i = 0; i < obj.l; i++) {
		os << obj.str[i];
	}
	return os;
}

// Input operator (>>)
istream& operator>>(istream& is, myString& obj) {
	for (int i = 0; i < obj.l; i++) {
		is >> obj.str[i];
	}
	return is;
}

myString& myString ::operator=(const myString& _str) {
	if (this == &_str) {
		return *this;
	}
	delete this->str;
	this->str = new char[_str.l + 1];
	for (int i = 0; i < _str.l; i++) {
		this->str[i] = _str.str[i];
	}
	this->str[_str.l] = '\0';
	this->cap = _str.l;
	this->l = _str.l;
	return *this;
}


myString::~myString() {
	delete[]this->str;
}