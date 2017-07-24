#include <iostream>

#include "Tools/Codec/BCH/Codec_BCH.hpp"

#include "BCH.hpp"

namespace aff3ct
{
namespace launcher
{
template <class C, typename B, typename R, typename Q>
BCH<C,B,R,Q>
::BCH(const int argc, const char **argv, std::ostream &stream)
: C(argc, argv, stream)
{
	params_enc = new factory::Encoder_BCH::parameters();
	params_dec = new factory::Decoder_BCH::parameters();

	if (this->params->enc != nullptr) { delete this->params->enc; this->params->enc = params_enc; }
	if (this->params->dec != nullptr) { delete this->params->dec; this->params->dec = params_dec; }
}

template <class C, typename B, typename R, typename Q>
BCH<C,B,R,Q>
::~BCH()
{
}

template <class C, typename B, typename R, typename Q>
void BCH<C,B,R,Q>
::build_args()
{
	factory::Encoder_BCH::build_args(this->req_args, this->opt_args);
	factory::Decoder_BCH::build_args(this->req_args, this->opt_args);

	this->opt_args.erase({"enc-fra",       "F"});
	this->opt_args.erase({"enc-seed",      "S"});
	this->req_args.erase({"dec-cw-size",   "N"});
	this->req_args.erase({"dec-info-bits", "K"});
	this->opt_args.erase({"dec-fra",       "F"});
	this->opt_args.erase({"dec-no-sys"        });
	this->opt_args.erase({"dec-implem"        });
	this->opt_args.erase({"dec-type",      "D"});

	C::build_args();
}

template <class C, typename B, typename R, typename Q>
void BCH<C,B,R,Q>
::store_args()
{
	factory::Encoder_BCH::store_args(this->ar.get_args(), *params_enc);

	params_dec->K    = params_enc->K;
	params_dec->N_cw = params_enc->N_cw;

	factory::Decoder_BCH::store_args(this->ar.get_args(), *params_dec);

	this->params->pct->type = "NO";
	this->params->pct->K    = params_enc->K;
	this->params->pct->N    = params_enc->N_cw;
	this->params->pct->N_cw = this->params->pct->N;
	this->params->pct->R    = (float)this->params->pct->K / (float)this->params->pct->N;

	C::store_args();
}

template <class C, typename B, typename R, typename Q>
void BCH<C,B,R,Q>
::print_header()
{
	if (params_enc->type != "NO")
		factory::Encoder_BCH::header(this->pl_enc, *params_enc);
	factory::Decoder_BCH::header(this->pl_dec, *params_dec);

	C::print_header();
}

template <class C, typename B, typename R, typename Q>
void BCH<C,B,R,Q>
::build_codec()
{
	this->codec = new tools::Codec_BCH<B,Q>(*params_enc, *params_dec);
}
}
}