#include <iostream>

int main(){
	std::string in;
	std::cin >> in;
//	std::cout << in << "DEBUG\n";
	int level = 0;
	bool key = false;
	for(int i = 0; i < in.size(); i ++){
		if(in[i] == '(') {
			level ++;
		}
		else level --;

		if(level == -1 && !key){
			std::cout << i+1 << " basement\n";
			key = true;
		}
	}
	std::cout << level << std::endl;
	return 0;
}
