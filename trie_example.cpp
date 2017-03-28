#include <iostream>
#include <utility>
#include <unordered_map>
#include <string>

using namespace std;

/*
Super simple demonstration of how a Trie might work for a tutorial/IA applicaion
The idea here is to be easy to follow. Not super elegant and functional

In the category of "Do as I say not as I do":
	-Nodes should be private members of the Trie
	-The Trie's root should be private too

	this is the big one
	-Notice how we used the keyword 'new'? That means we are managing memory
	 ourselves in this struct. I added a simple destructor so we don't bleed memory 
	 but things like assingment and copy will behave very poorly. Remeber the big three?
	 If you use write one of them, it is VERY unsafe not to write the other two. This is just a 
	 demo but in practice this struct would be un-usable because it lacks these
*/

struct Node{
	unordered_map<char,Node*> path;
	bool is_end;
};

struct Trie{
	Node* root;

	Trie(){
		root = new Node;
	}

	void insert(string str){
		Node* cur_node = root;
		
		for(size_t i = 0;i<str.size();i++){
			char ch = str[i];
			if(cur_node->path.count(ch) > 0){
				cur_node = cur_node->path.at(ch);
			}
			else{
				cur_node->path[ch] = new Node;
				cur_node = cur_node->path.at(ch);
			}

			cur_node->is_end = true;
			
		}
		cout << "inserted " << str << endl;
	}

	bool contains(string str){
		Node* cur_node = root;

		for(size_t i = 0;i<str.size();i++){
			char ch = str[i];
			if(cur_node->path.count(ch) > 0){
				cur_node = cur_node->path.at(ch);
			}
			else{
				return false;
			}

			return cur_node->is_end;
			
		}
	}

	void clean(Node* cur_node){
		for(auto pair:cur_node->path){
			clean(pair.second);
		}
		delete cur_node;
	}

	~Trie(){
		clean(root);
	}
};

int main(){
	cout << boolalpha;

	Trie dict;
	dict.insert("eecs280");
	dict.insert("bob");
	dict.insert("!@#$%^&^%$#");			//remeber how i said it is generalizable


	cout << "dict.contains eecs280: " << dict.contains("eecs280") << endl;
	cout << "dict.contains bob: " << dict.contains("bob") << endl;
	cout << "dict.contains !@#$%^&^%$#: " << dict.contains("!@#$%^&^%$#") << endl;

	cout << "dict.contains sam: " <<dict.contains("sam") << endl;
	cout << "dict.contains sarah: " <<dict.contains("sarah") << endl;
}