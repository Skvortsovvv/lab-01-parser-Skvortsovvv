
#include <header.hpp>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		throw std::runtime_error{ "No argumets" };
	}
	parser pr(argv[1]);
	pr.Print();
}