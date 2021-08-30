#define max_alpha 26

#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

class TrieNode {
public:
	char data;
	unordered_map<char, TrieNode*> children;
	bool end_of_word;
	
	TrieNode() {
		data = '\0';
		end_of_word = false;
	}
};

class Trie {
public:
	TrieNode* root;

	Trie() {
		root = new TrieNode();
	}

	void insert(string word) {
		TrieNode* temp = root;
		for (int i = 0; i < word.length(); i++) {
			if (temp->children.count(word[i]) == 0) {
				TrieNode* newnode = new TrieNode;
				temp->children[word[i]] = newnode;
			}
			temp = temp->children[word[i]];
		}
		temp->end_of_word = true;
	}
};

void search(Trie t, string document, int i, unordered_map<string, bool>& mp) {
	TrieNode* temp = t.root;
	
	for (int j = i; j < document.length(); j++) {
		char ch = document[j];
		if (temp->children.count(ch) == 0) {
			return;
		}
		temp = temp->children[ch];
		if (temp->end_of_word == true) {
			string formed = document.substr(i, j - i + 1);
			mp[formed] = true;
		}
	}
	return;
}

void documentSearch(string document, vector<string> words) {
	//1. create a trie
	Trie t;
	
	//2. insert words in trie
	for (string w : words) {
		t.insert(w);
	}

	//3. searching 
	unordered_map<string, bool> mp;
	for (int i = 0; i < document.length(); i++) {
		search(t, document, i, mp);
	}

	//4. hashcheck
	for (string w : words) {
		if (mp[w]) {
			cout << w << " : " << "YES" << endl;
		}
		else {
			cout << w << " : " << "NO" << endl;
		}
	}
}

int main() {

	string document = "little cute cat loves to code in c++, java & python";
	vector<string> words{ "cute cat", "ttle", "cat","quick","big" };

	documentSearch(document, words);


	return 0;
}