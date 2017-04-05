#ifndef ENCODER_USER_HPP_
#define ENCODER_USER_HPP_

#include <string>

#include "../Encoder.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int>
class Encoder_user : public Encoder<B>
{
private:
	mipp::vector<mipp::vector<B>> codewords;
	int cw_counter;

public:
	Encoder_user(const int K, const int N, const std::string filename, const int n_frames = 1,
	             const std::string name = "Encoder_user");
	virtual ~Encoder_user();

protected:
	void _encode_fbf(const B *U_K, B *X_N);
};
}
}

#endif /* ENCODER_USER_HPP_ */
