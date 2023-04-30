#ifndef ENCRYPT_H
#define ENCRYPT_H
#include"header.h"
#include<openssl/sha.h>
#include<openssl/md5.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>

class Encrypt {//ras实现非对称加密
private:
	RSA* m_rsa;
	RSA* m_pubkey;
	RSA* m_prikey;
	int m_keylength;
	BIGNUM* m_e;
	FILE* const m_pubkey_file;
	FILE* const m_prikey_file;
public:
	Encrypt();
	~Encrypt();
	static Encrypt* GetInstance() { //单例模式
		static Encrypt Encrypt;
		return &Encrypt;
	}
	//生成密钥对
	bool init_key();
	void get_keys_ram();
	bool get_keys_disk();
	//公钥加密
	std::string pub_encrypt(const std::string& input);
	//私钥解密
	std::string pri_decrypt(const std::string& input);
	//数据签名
	//验证签名
};

#endif
