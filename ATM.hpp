#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

struct account {
	string name;
	long long balance = 0;
};

class ATM {
private:
	unordered_map<string, pair<string, vector<account>>> info;

public:

	bool create_id(string &id, string &pin) {
		if (info.find(id) != info.end()) {
			cout << "\033[1;31m";
			cout << "id already exist" << endl;
			cout << "\033[0m";
			return false;
		}
		if (pin.size() != 4 or !is_num(pin)) {
			cout << "\033[1;31m";
			cout << "PIN number should be 4 nonnegative numbers" << endl;
			cout << "\033[0m";
			return false;
		}
		info[id] = {pin, vector<account>()};
		cout << "\033[1;32m";
		cout << id << " information is created" << endl;
		cout << "\033[0m";
		return true;
	}

	bool find_id(string &id, string &pin) {
		if (info.find(id) == info.end()) {
			cout << "\033[1;31m";
			cout << "id does not exist" << endl;
			cout << "\033[0m";
			return false;
		}
		if (info[id].first != pin) {
			cout << "\033[1;31m";
			cout << "PIN number is wrong" << endl;
			cout << "\033[0m";
			return false;
		}
		return true;
	}

	void show_accounts(string &id) {
		cout << "\033[1;32m";
		cout << "----------" << endl;
		cout << "card id: " << id << endl;
		auto& acc = info[id].second;
		for (int i = 0; i < acc.size(); i++) {
			cout << "(" << i << "): " << acc[i].name << endl;
		}
		cout << "----------" << endl;
		cout << "\033[0m";
	}

	bool find_accounts(string &id, string &acc_num) {
		if (is_num(acc_num)) {
			int num = stoi(acc_num);
			if (num >= 0 and num < info[id].second.size()) {
				return true;
			}
			else {
				cout << "\033[1;31m";
				cout << "out of bound" << endl;
				cout << "\033[0m";
				return false;
			}
		}
		else {
			cout << "\033[1;31m";
			cout << "command does not exist" << endl;
			cout << "please enter other command" << endl;
			cout << "\033[0m";
			return false;
		}
	}

	void show_account_info(string &id, int acc_num) {
		cout << "\033[1;32m";
		cout << "----------" << endl;
		cout << "card id: " << id << endl;
		cout << "account info:" << endl;
		cout << "  number: " << acc_num << endl;
		cout << "  name: " << info[id].second[acc_num].name << endl;
		cout << "  balance: " << info[id].second[acc_num].balance << endl;
		cout << "----------" << endl;
		cout << "\033[0m";
	}

	bool deposit(string& id, int acc_num, string& money) {
		if (!is_num(money)) {
			cout << "\033[1;31m";
			cout << "input should be nonnegative integer" << endl;
			cout << "\033[0m";
			return false;
		}
		else {
			long long num = stoll(money);
			info[id].second[acc_num].balance += num;
			cout << "\033[1;32m";
			cout << "----------" << endl;
			cout << num << " is deposited into your balance" << endl;
			cout << "----------" << endl;
			cout << "\033[0m";
			return true;
		}
	}

	bool withdraw(string& id, int acc_num, string &money) {
		if (!is_num(money)) {
			cout << "\033[1;31m";
			cout << "input should be nonnegative integer" << endl;
			cout << "\033[0m";
			return false;
		}
		else if (stoll(money) > info[id].second[acc_num].balance) {
			cout << "\033[1;31m";
			cout << "input should be smaller than balance" << endl;
			cout << "\033[0m";
			return false;
		} 
		else {
			long long num = stoll(money);
			info[id].second[acc_num].balance -= num;
			cout << "\033[1;32m";
			cout << "----------" << endl;
			cout << num << " is withdrawn to your balance" << endl;
			cout << "----------" << endl;
			cout << "\033[0m";
			return true;
		}
	}

	void create_account(string &id, string &name) {
		info[id].second.push_back({name, 0});
		cout << "\033[1;32m";
		cout << name << " account is created in " << id << " information" << endl;
		cout << "\033[0m";
	}

	bool is_num(string& str) {
		for (int i = 0; i < str.size(); i++) {
			if (!isdigit(str[i])) return false;
		}
		return true;
	}

};

