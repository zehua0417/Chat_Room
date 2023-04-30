#pragma once
#include"header.h"

typedef struct User {
	std::string user_id;
	std::string user_name;
	std::string user_pwd;
}User;

class Usersdata {
private:
	MYSQL* m_sqlCon;
	std::string host = "162.14.74.178";
	std::string user = "root";
	std::string pwd = "lizehua21";
	std::string db = "chatroom_usersdata";
	unsigned int port = 3306;
public:
	Usersdata();
	~Usersdata();

	bool insert_user(User& new_user);
	bool update_user(User& user);
	bool delete_user(std::string user_id);
	std::string get_pwd(std::string use_id);
	std::vector<User>get_users(std::string condition = "");

	//µ¥ÀıÄ£Ê½
	static Usersdata* GetInstance() {
		static Usersdata Usersdata;
		return &Usersdata;
	}
};

/**
 * @brief µÇÂ¼º¯Êı
 * @param input_id µÇÂ¼¿òÊäÈëµÄid
 * @param input_pwd µÇÂ¼¿òÊäÈëµÄÃÜÂë
 *
 * @return TRUE µÇÂ¼³É¹¦
 *		   FALSE µÇÂ½Ê§°Ü
 */
bool log_in(std::string input_id, std::string input_pwd);
/**
 * @brief ×¢²á
 */
bool sign_up(std::string input_id, std::string input_name, std::string input_pwd);
bool log_off();