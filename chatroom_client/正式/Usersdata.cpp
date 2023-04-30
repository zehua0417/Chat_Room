#include"Usersdata.h"

Usersdata::Usersdata() :m_sqlCon(mysql_init(NULL)) {
	//连接数据库
	if (!mysql_real_connect(m_sqlCon, host.c_str(), user.c_str(), pwd.c_str(), db.c_str(), port, NULL, 0)) {
		//数据库连接失败
		printf("数据库连接失败,%s", mysql_error(m_sqlCon));
		return;
	}

	//设置编码
	std::string charsetName = "set names 'GBK'";
	mysql_real_query(m_sqlCon, charsetName.c_str(), charsetName.length());
}

Usersdata::~Usersdata() {
	mysql_close(m_sqlCon);
}

bool Usersdata::insert_user(User& new_user) {
	char sql[1024];
	sprintf(sql, "insert into usersdata (id, user_name, pw) value('%s','%s','%s')",
		new_user.user_id.c_str(), new_user.user_name.c_str(), new_user.user_pwd.c_str());
	if (mysql_query(m_sqlCon, sql)) {
		fprintf(stderr, "failed to insert data; Error: %s\n", mysql_error(m_sqlCon));
		return FALSE;
	}
	return TRUE;
}

bool Usersdata::update_user(User& user) {
	char sql[1024];
	sprintf(sql, "UPDATE usersdata SET  user_name = '%s', pw = '%s'" "where id = %d",
		user.user_name.c_str(), user.user_pwd.c_str(), user.user_id);
	if (mysql_query(m_sqlCon, sql)) {
		fprintf(stderr, "failed to update data; Error: %s\n", mysql_error(m_sqlCon));
		return FALSE;
	}
	return TRUE;
}

bool Usersdata::delete_user(std::string user_id) {
	char sql[1024];
	sprintf(sql, "DELETE FROM usersdata WHERE id = %s", user_id.c_str());
	if (mysql_query(m_sqlCon, sql)) {
		fprintf(stderr, "failed to delete data; Error: %s\n", mysql_error(m_sqlCon));
		return FALSE;
	}
	return TRUE;
}

std::string Usersdata::get_pwd(std::string user_id) {
	char sql[1024];
	sprintf(sql, "SELECT * FROM usersdata WHERE id = %s", user_id.c_str());
	if (mysql_query(m_sqlCon, sql)) {
		fprintf(stderr, "failed to select data; Error: %s\n", mysql_error(m_sqlCon));
		return{};
	}
	MYSQL_RES* res = mysql_store_result(m_sqlCon);
	MYSQL_ROW row = mysql_fetch_row(res);
	std::string pwd = row[2];
	return pwd;
}

std::vector<User> Usersdata::get_users(std::string condition) {
	std::vector<User> userList;
	char sql[1024];
	sprintf(sql, "SELECT * FROM usersdata %s", condition.c_str());
	if (mysql_query(m_sqlCon, sql)) {
		fprintf(stderr, "failed to selete data; Error: %s\n", mysql_error(m_sqlCon));
		return {};
	}
	MYSQL_RES* res = mysql_store_result(m_sqlCon);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res))) {
		User user_infor;
		user_infor.user_id = atoi(row[0]);
		user_infor.user_name = row[1];
		user_infor.user_pwd = row[2];

		userList.push_back(user_infor);
	}

	return userList;
}
bool log_in(std::string input_id, std::string input_pwd) {
	if (Usersdata::GetInstance()->get_pwd(input_id) == input_pwd) {
		printf("success\n");
		return TRUE;
	}
	printf("WRONG\n");
	return FALSE;
}

bool sign_up(std::string input_id, std::string input_name, std::string input_pwd) {
	User user;
	user.user_id = input_id;
	user.user_name = input_name;
	user.user_pwd = input_pwd;
	if (Usersdata::GetInstance()->insert_user(user)) {
		std::cout << "sign_up successfully" << std::endl;
		return TRUE;
	}
	std::cout << "WRONG!" << std::endl;
	return false;
}

