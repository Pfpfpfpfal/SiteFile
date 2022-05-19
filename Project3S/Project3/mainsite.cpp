#include <iostream>
#include <fstream>
#include <string>

#include "Header.h"
#include "stack.h"
#include "queue.h"
#include "singllist.h"
#include "list.h"

using namespace std;

#define len(a) (ll)a.size()


void bracket(string s) {
	char open[4] = { '(', '[', '{', '<' };
	char close[4] = { ')', ']', '}', '>' };

	Node* root = nullptr;

	bool er = false;

	string WrongPairBracket = "";
	string Wrong = "";
	for (int i = 0; i < len(s); ++i) {
		ll id = -1;
		for (int j = 0; j < 4; ++j) {
			if (close[j] == s[i])
				id = j;
		}

		if (id == -1) {
			for (int j = 0; j < 4; ++j) {
				if (open[j] == s[i])
					id = j;
			}
			if (id != -1) {
				push(root, i);
			}
		}
		else {
			if (root != nullptr && open[id] == s[*peek(root)]) {
				pop(root);
			}
			else if (root != nullptr) {
				er = true;
				WrongPairBracket += to_string(*peek(root) + 1) + ' ' + to_string(i + 1) + " | ";
				pop(root);
			}
			else if (root == nullptr) {
				er = true;
				Wrong += to_string(i + 1) + ' ';
			}
		}
	}

	if (er || peek(root) != nullptr) {
		cout << "<p>" + s + "</p>";
		cout << "<p>Error\n</p>";
		if (len(WrongPairBracket) != 0) {
			cout << "<p>Wrong pair:\n</p>"; cout << WrongPairBracket;
		}

		if (len(Wrong) != 0 || peek(root) != nullptr)
			cout << "<p>Unnecessary brackets:\n</p>";
		if (len(Wrong) != 0)
			cout << Wrong + "\n";
		if (peek(root) != nullptr) {
			Show(root);
		}
	}
	else
		cout << "<p>No errors detected</p>";
}

void show_content_stack();
//void show_menu();
//void show_header();
void show_content_queue();
void show_content_SingleLinkedList();
void show_content_LinkedList();

int main() {
	cout << "Content-type: text/html; charset=Windows-1251\n\n";
	ifstream f("index.html");
	if (f.is_open())
	{
		auto sz = 65536;
		auto buf = new char[sz];
		while (!f.eof()) {
			f.getline(buf, sz);
			if (!strcmp(buf, "<!--#stack#-->")) {
				show_content_stack();
			}
			else if (!strcmp(buf, "<!--#queue#-->")) {
				show_content_queue();
			}
			else if (!strcmp(buf, "<!--#SingleLinkedList#-->")) {
				show_content_SingleLinkedList();
			}
			else if (!strcmp(buf, "<!--#LinkedList#-->")) {
				show_content_LinkedList();
			}
			cout << buf;
		}
		delete[] buf;
		f.close();
	}
	else {
		cout << "�� ������� ������� ��������";
	}
}


void show_content_stack() {
	char* data = nullptr;
	get_form_data(data);
	char* str = new char[50];


	if (data && strlen(data) > 0)
	{
		char* value = nullptr;
		get_param_value(value, "expression", data);
		str = value;
	}

	cout << "<h3> ������� �������������� ���������: </h3>";
	cout << "<form method='get' action='Project3.cgi'>";
	cout << "<input type='text' name='expression' maxlength='50' size='50'>";
	cout << "<input type='submit' value='���������'>";
	cout << "</form>";
	string res = "";
	for (int i = 0; i <= strlen(str); i++)
		res += str[i];

	bracket(res);
	delete[] data;
}

string Packing(string x) {
	return "<div>" + x + "</div>";
}

void show_content_queue() {
	char* data = nullptr;
	get_form_data(data);
	char* str = new char[50];


	if (data && strlen(data) > 0)
	{
		char* value = nullptr;
		get_param_value(value, "NameFile", data);
		str = value;
	}

	cout << "<h4>������� �������� ����� �� �������� ���� ������� ������: </h4>";
	cout << "<form method='get' action='mainsite.cgi'>";
	cout << "<input type='text' name='NameFile' maxlength='50' size='50'>";
	cout << "<input type='submit' value='���������'>";
	cout << "</form>";
	string res = "";
	for (int i = 0; i <= strlen(str); i++)
		res += str[i];

	ifstream fin(res);
	if (!fin.is_open()) {
		cout << "<p>file not open</p>";
		return;
	}

	queue credit, contribution;
	string dt;
	men tmp;
	while (!fin.eof()) {
		getline(fin, dt);
		tmp = Parse(dt);
		if (tmp.goal == "credit")
			credit.push(tmp);
		else
			contribution.push(tmp);
	}
	credit.show();
	contribution.show();

	credit.clear();
	contribution.clear();
	dt.clear();
	delete[] data;
}

void show_content_SingleLinkedList() {
	char* data = nullptr;
	get_form_data(data);
	char* str = new char[50];

	if (data && strlen(data) > 0) {
		char* value = nullptr;
		get_param_value(value, "UnicNumber", data);
		str = value;
	}
	cout << "<h5> ������� ����� ����� ��������� � ������ �� ���: </h5>";
	cout << "<form method='get' action='mainsite.cgi'>";
	cout << "<input type='text' name='UnicNumber' maxlength='50' size='50'>";
	cout << "<input type='submit' value='���������'>";
	cout << "</form>";
	string res = "";
	for (int i = 0; i <= strlen(str); i++)
		res += str[i];
	int num = atoi(res.c_str());

	SingleLinkedList q;
	ifstream fin("UnicList.txt");
	q.ReadData(fin);

	if (!('0' <= res[0] && res[0] <= '9')) {
		cout << Packing("���� �����");
	}
	else {
		if (!q.count(num)) {
			q.add(num);
			cout << Packing("The number " + res + " was not in the list");
		}
		else {
			cout << Packing("The number " + res + " was in the list");
		}
	}
	cout << "List of numbers: ";
	q.Show();

	ofstream fout("UnicList.txt");
	q.SaveData(fout);
	q.clear();
	delete[] data;
}

void show_content_LinkedList() {
	char* data = nullptr;
	get_form_data(data);
	char* str = new char[50];

	if (data && strlen(data) > 0) {
		char* value = nullptr;
		get_param_value(value, "Sum", data);
		str = value;
	}
	cout << "<h6> ������� ��� �����, ����� ������, ������� ����� �������: </h6>";
	cout << "<form method='get' action='mainsite.cgi'>";
	cout << "<input type='text' name='Sum' maxlength='50' size='50'>";
	cout << "<input type='submit' value='���������'>";
	cout << "</form>";
	string x = "", y = "";
	int pos = 0;
	for (pos = 0; pos < strlen(str) && str[pos] != ' '; ++pos)
		x += str[pos];
	pos++;
	for (; pos <= strlen(str) && str[pos] != '\0'; ++pos)
		y += str[pos];

	LinkedList ans = CreateNumber(x) + CreateNumber(y);
	cout << "<div>";
	ans.RevShow();
	cout << "</div";
	return;
}