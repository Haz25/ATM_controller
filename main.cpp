#include <iostream>
#include <string>
#include "ATM.hpp"
using namespace std;

ATM atm;
enum ATM_mod {DEFAULT, 
			  CREATION, 
			  CHECK, 
			  ACCOUNT, 
			  ACCOUNT_DETAIL, 
			  ACCOUNT_DEPOSIT, 
			  ACCOUNT_WITHDRAW, 
			  ACCOUNT_CREATION};

int main() {
	string cmd;
	ATM_mod mod = DEFAULT;
	string id, pin;
	int acc_num;
	while (1) {
		cout << "------ ATM ------" << endl;
		if (mod == DEFAULT) {
			cout << "\033[1;34m";
			cout << "-- Menu --" << endl;
			cout << "\033[0m";
			cout << "please input command" << endl;
			cout << "(1): insert card" << endl;
			cout << "(=): create card informarion" << endl;
			cout << "(-): exit" << endl;

			cin >> cmd;
			if (cmd == "1") {
				mod = CHECK;
			}
			else if (cmd == "=") {
				mod = CREATION;
			}
			else if (cmd == "-") {
				cout << "exit program" << endl;
				break;
			}
			else {
				cout << "\033[1;31m";
				cout << "command does not exist" << endl;
				cout << "please enter other command" << endl;
				cout << "\033[0m";
			}
		}
		else if (mod == CREATION) {
			cout << "\033[1;34m";
			cout << "-- Add new information in ATM --" << endl;
			cout << "\033[0m";
			cout << "please enter new ID and PIN number of card" << endl;
			cout << "(-): exit" << endl;
			cin >> cmd;
			if (cmd == "-") {
				mod = DEFAULT;
				continue;
			}
			else id = cmd;
			cin >> pin;
			if (atm.create_id(id, pin)) {
				mod = DEFAULT;
			}
		}
		else if (mod == CHECK) {
			cout << "\033[1;34m";
			cout << "-- Check ID and PIN number --" << endl;
			cout << "\033[0m";
			cout << "please enter ID and PIN number of card" << endl;
			cout << "(-): exit" << endl;
			cin >> cmd;
			if (cmd == "-") {
				mod = DEFAULT;
			}
			else {
				id = cmd;
				cin >> pin;
				if (atm.find_id(id, pin)) {
					mod = ACCOUNT;
				}
			}
		}
		else if (mod == ACCOUNT) {
			cout << "\033[1;34m";
			cout << "-- Account info --" << endl;
			cout << "\033[0m";
			cout << "enter numer of account to select" << endl;
			atm.show_accounts(id);
			cout << "(=): create an account" << endl;
			cout << "(-): exit" << endl;

			cin >> cmd;
			if (cmd == "=") {
				mod = ACCOUNT_CREATION;
			}
			else if (cmd == "-") {
				mod = DEFAULT;
			}
			else if (atm.find_accounts(id, cmd)) {
				acc_num = stoi(cmd);
				mod = ACCOUNT_DETAIL;
			}
		}
		else if (mod == ACCOUNT_DETAIL) {
			cout << "\033[1;34m";
			cout << "-- Account detail --" << endl;
			cout << "\033[0m";
			atm.show_account_info(id, acc_num);
			cout << "Choose one of the actions" << endl;
			cout << "(1): deposit" << endl;
			cout << "(2): withdraw" << endl;
			cout << "(-): exit" << endl;

			cin >> cmd;
			if (cmd == "1") {
				mod = ACCOUNT_DEPOSIT;
			}
			else if (cmd == "2") {
				mod = ACCOUNT_WITHDRAW;
			}
			else if (cmd == "-") {
				mod = ACCOUNT;
			}
			else {
				cout << "\033[1;31m";
				cout << "command does not exist" << endl;
				cout << "please enter other command" << endl;
				cout << "\033[0m";
			}
		}
		else if (mod == ACCOUNT_DEPOSIT) {
			cout << "\033[1;34m";
			cout << "-- Deposit the money --" << endl;
			cout << "\033[0m";
			cout << "please enter the money" << endl;
			cout << "(-): exit" << endl;
			cin >> cmd;
			if (cmd == "-") {
				mod = ACCOUNT_DETAIL;
			} else if (atm.deposit(id, acc_num, cmd)) {
				mod = ACCOUNT_DETAIL;
			}
		}
		else if (mod == ACCOUNT_WITHDRAW) {
			cout << "\033[1;34m";
			cout << "-- Withdraw the money --" << endl;
			cout << "\033[0m";
			cout << "please enter the money" << endl;
			cout << "(-): exit" << endl;
			cin >> cmd;
			if (cmd == "-") {
				mod = ACCOUNT_DETAIL;
			} else if (atm.withdraw(id, acc_num, cmd)) {
				mod = ACCOUNT_DETAIL;
			}
		}
		else if (mod == ACCOUNT_CREATION) {
			cout << "\033[1;34m";
			cout << "-- Create account --" << endl;
			cout << "\033[0m";
			cout << "enter name of account" << endl;
			cout << "(-): exit" << endl;
			cin >> cmd;
			if (cmd != "-") {
				atm.create_account(id, cmd);
			}
			mod = ACCOUNT;
		}
		else {
			cout << "\033[1;31m" << endl;
			cout << "something wrong" << endl;
			cout << "\033[0m" << endl;
			break;
		}
	}

	return 0;
}