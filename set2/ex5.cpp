#include <ex.h>

void split_string(const std::string& str, vector<string>& cont, char delim)
{
	std::size_t current = 0, previous = 0;
	current = str.find(delim);
	while (current != std::string::npos) {
		cont.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}

cookie parse_string(const std::string& str)
{
	vector<string> parse_results;
	cookie output;
	split_string(str, parse_results, '&');
	for(auto& res: parse_results) {
		vector<string> kv;
		split_string(res, kv, '=');
		output[kv[0]] = kv[1];
	}
	return output;
}

cookie profile_for(const string& email) 
{
	cookie out;
	out.insert(std::make_pair("email", email));
	out.insert(std::make_pair("uid", "10"));
	out.insert(std::make_pair("role", "user"));
	return out;
}

std::string cookie2str(const cookie& c)
{
	string output;
	// C++ has no ordered dict. Over that.
	output += "email=" + c.at("email") + "&" + "uid=" + c.at("uid") + "&" + 
		"role=" + c.at("role");
	return output;
}

void encrypt_profile(const string& profile, vector<uint8_t>& key, 
		vector<uint8_t>& output)
{
	vector<uint8_t> v(profile.begin(), profile.end());
	aes_encrypt_ecb(v, key.data(), output);
}

cookie decrypt_profile(vector<uint8_t> ciphertext, vector<uint8_t>& key)
{
	vector<uint8_t> v(ciphertext.size());
	// FIXME rename func
	auto sz = run_aes(ciphertext.data(), ciphertext.size(), v.data(), key.data());
	v.resize(sz);
	return parse_string(string(v.begin(), v.end()));
}
