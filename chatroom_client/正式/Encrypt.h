#ifndef ENCRYPT_H
#define ENCRYPT_H
#include"header.h"
#include<openssl/sha.h>
#include<openssl/md5.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>

class Encrypt {//rasʵ�ַǶԳƼ���
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
	static Encrypt* GetInstance() { //����ģʽ
		static Encrypt Encrypt;
		return &Encrypt;
	}
	//������Կ��
	bool init_key();
	void get_keys_ram();
	bool get_keys_disk();
	//��Կ����
	std::string pub_encrypt(const std::string& input);
	//˽Կ����
	std::string pri_decrypt(const std::string& input);
	//����ǩ��
	//��֤ǩ��
};

#endif
