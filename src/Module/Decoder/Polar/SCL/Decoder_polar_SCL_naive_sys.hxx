#include <algorithm>
#include <cmath>
#include <map>

#include <iostream>
#include <fstream>

#include "Decoder_polar_SCL_naive_sys.hpp"

namespace aff3ct
{
namespace module
{
template <typename B, typename R, tools::proto_f<R> F, tools::proto_g<B,R> G>
Decoder_polar_SCL_naive_sys<B,R,F,G>
::Decoder_polar_SCL_naive_sys(const int& K, const int& N, const int& L, const std::vector<bool>& frozen_bits,
                              const int n_frames, const std::string name)
: Decoder(K, N, n_frames, 1, name),
  Decoder_polar_SCL_naive<B,R,F,G>(K, N, L, frozen_bits, n_frames, name)
{
}

template <typename B, typename R, tools::proto_f<R> F, tools::proto_g<B,R> G>
void Decoder_polar_SCL_naive_sys<B,R,F,G>
::_store(B *V, bool coded) const
{
	if (!coded)
	{
		auto k = 0;
		for (auto i = 0; i < this->N; i++)
			if (!this->frozen_bits[i])
				V[k++] = this->polar_trees[*this->active_paths.begin()]->get_root()->get_c()->s[i] ? 1 : 0;
	}
	else
		for (auto i = 0; i < this->N; i++)
			V[i] = this->polar_trees[*this->active_paths.begin()]->get_root()->get_c()->s[i] ? 1 : 0;
}
}
}
