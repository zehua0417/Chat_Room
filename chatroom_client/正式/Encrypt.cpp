#include "Encrypt.h"
extern "C" {
#include<openssl/applink.c> 
};

Encrypt::Encrypt()
	:m_rsa(RSA_new()),
	m_prikey_file(fopen("./privateKey.pem", "r")),
	m_pubkey_file(fopen("./publicKey.pem", "r")) {
	m_e = BN_new();
	BN_set_word(m_e, 66666);
	if (!get_keys_disk()) {
		std::cout << "please check if you lost ypur keys!!!" << std::endl;
		return;
	}
		//if (!init_key()) {
		//	perror("error: init keys error!");
		//	return;
		//}
	//get_keys_ram();
	m_keylength = RSA_size(m_prikey);
}

Encrypt::~Encrypt() {
	RSA_free(m_rsa);
	BN_free(m_e);
	fclose(m_prikey_file);
	fclose(m_pubkey_file);
}

bool Encrypt::init_key() {
	//创建密钥对
	if (!RSA_generate_key_ex(m_rsa, 16, m_e, NULL)) {
		perror("error: fail to generate key\n");
		return false;
	}
	else printf("key generate successfully;\nstart writing keys...\n");
	//将密钥写入磁盘
	PEM_write_RSAPrivateKey(m_prikey_file, m_rsa, NULL, NULL, 0, NULL, NULL);
	PEM_write_RSAPublicKey(m_pubkey_file, m_rsa);
	printf("write keys successfully");
	return true;
}

void Encrypt::get_keys_ram()
{
	m_prikey = RSAPrivateKey_dup(m_rsa);
	m_pubkey = RSAPublicKey_dup(m_rsa);
}

bool Encrypt::get_keys_disk(){
	if (PEM_read_RSAPrivateKey(m_prikey_file, &m_prikey, NULL, NULL) &&
		PEM_read_RSAPublicKey(m_pubkey_file, &m_pubkey, NULL, NULL)) {
		return TRUE;
	}
	printf("NO KEY FILES!");
	return FALSE;
}

std::string Encrypt::pub_encrypt(const std::string& input) {
	char* buf = new char[m_keylength];
	RSA_public_encrypt(input.size(), (const unsigned char*)input.data(), (unsigned char*)buf, m_pubkey, RSA_PKCS1_PADDING);
	return std::string(buf);
}

std::string Encrypt::pri_decrypt(const std::string& input){
	char* buf = new char[m_keylength];
	int len = RSA_private_decrypt(input.size(),(const unsigned char*)input.data(), (unsigned char*)buf, m_prikey,RSA_PKCS1_PADDING);
	return std::string(buf, len);
}

