#ifndef EXPLODE_HPP_
#define EXPLODE_HPP_

#include <iostream>
#include <sstream>
#include <vector>

class Explode {
	public:
		Explode() {};
		~Explode() {};

        static std::vector<std::string> explode(std::string const &s, char delim);

	protected:
	private:
};

#endif /* !EXPLODE_HPP_ */
