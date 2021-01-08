#include <random>
using namespace std;

int main(int argc, char const* argv[])
{
	srand(time(0));
	int op,val;
	#define MAX_OP 20
	for(int i = 0; i < MAX_OP; ++i){
		switch(rand() % 5){
			case 0:
			case 1: printf("0 %d\n", rand() % 15); break;
			case 2:
			case 3: printf("1 %d\n", rand() % 15); break;
			case 4: printf("2 %d\n", rand() % 15); break;
		}
	}
	return 0;
}
