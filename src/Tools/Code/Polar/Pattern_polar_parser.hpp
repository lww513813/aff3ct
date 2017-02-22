/*!
 * \file
 * \brief Parses a polar code (represented as a tree) and returns a simplified tree with specialized nodes and tree
 *        cuts when possible.
 *
 * \section LICENSE
 * This file is under MIT license (https://opensource.org/licenses/MIT).
 */
#ifndef PATTERN_POLAR_PARSER_HPP
#define PATTERN_POLAR_PARSER_HPP

#include <map>
#include <vector>
#include <vector>

#include "Tools/Perf/MIPP/mipp.h"
#include "Tools/Algo/Tree/Binary_tree.hpp"
#include "Tools/Code/Polar/Patterns/Pattern_polar_i.hpp"

/*!
 * \class Pattern_parser_polar
 * \brief Parses a polar code (represented as a tree) and returns a simplified tree with specialized nodes and tree
 *        cuts when possible.
 */
template <typename B>
class Pattern_polar_parser
{
protected:
	const int                            N;             /*!< Codeword size. */
	const int                            m;             /*!< Tree depth. */
	const mipp::vector<B>               &frozen_bits;   /*!< Vector of frozen bits (true if frozen, false otherwise). */
	const std::vector<Pattern_polar_i*>  patterns;      /*!< Vector of patterns. */
	const Pattern_polar_i               *pattern_rate0; /*!< Terminal pattern when the bit is frozen. */
	const Pattern_polar_i               *pattern_rate1; /*!< Terminal pattern when the bit is an information bit. */
	      Binary_tree<Pattern_polar_i>  *polar_tree;    /*!< Tree of patterns. */
	      std::vector<unsigned char>     pattern_types; /*!< Tree of patterns represented with a vector of pattern IDs. */

public:
	/*!
	 * \brief Constructor.
	 *
	 * \param N:             codeword size.
	 * \param frozen_bits:   vector of frozen bits (true if frozen, false otherwise).
	 * \param patterns:      vector of patterns.
	 * \param pattern_rate0: terminal pattern when the bit is frozen.
	 * \param pattern_rate1: terminal pattern when the bit is an information bit.
	 */
	Pattern_polar_parser(const int& N,
	                     const mipp::vector<B>& frozen_bits,
	                     const std::vector<Pattern_polar_i*> patterns,
	                     const Pattern_polar_i *pattern_rate0,
	                     const Pattern_polar_i *pattern_rate1);

	/*!
	 * \brief Constructor.
	 *
	 * \param N:                codeword size.
	 * \param frozen_bits:      vector of frozen bits (true if frozen, false otherwise).
	 * \param patterns:         vector of patterns.
	 * \param pattern_rate0_id: id of the terminal pattern when the bit is frozen (id in the patterns vector).
	 * \param pattern_rate1_id: id of the terminal pattern when the bit is an info. bit (id in the patterns vector).
	 */
	Pattern_polar_parser(const int& N,
	                     const mipp::vector<B>& frozen_bits,
	                     const std::vector<Pattern_polar_i*> patterns,
	                     const int pattern_rate0_id,
	                     const int pattern_rate1_id);

	/*!
	 * \brief Destructor.
	 */
	virtual ~Pattern_polar_parser();

	/*!
	 * \brief Gets a binary tree of patterns.
	 *
	 * \return a binary tree of patterns.
	 */
	const Binary_tree<Pattern_polar_i>* get_polar_tree() const;

	/*!
	 * \brief Gets a vector of pattern IDs.
	 *
	 * The vector of patterns IDs is a compressed version of the binary tree of patterns provided by the
	 * Pattern_parser_polar::get_polar_tree method.
	 *
	 * \return a vector of pattern IDs.
	 */
	std::vector<unsigned char> get_pattern_types() const;

	/*!
	 * \brief Gets a node pattern type from the id of the node.
	 *
	 * \param node_id: id of the node
	 *
	 * \return the type of the node.
	 */
	inline polar_node_t get_node_type(const int node_id) const;

	/*!
	 * \brief Check if a node type exists in the the tree.
	 *
	 * \param node_type: the type of the requested node
	 * \param rev_depth: check for the given reversed depth
	 *
	 * \return true if the node type exists, false otherwise.
	 */
	inline bool exist_node_type(const polar_node_t node_type, const int rev_depth = -1) const;

	/*!
	 * \brief Release the polar patterns given in the constructor.
	 */
	void release_patterns() const;

private:
	void recursive_allocate_nodes_patterns  (      Binary_node<Pattern_polar_i>* node_curr);
	void generate_nodes_indexes             (const Binary_node<Pattern_polar_i>* node_curr);
	void recursive_deallocate_nodes_patterns(      Binary_node<Pattern_polar_i>* node_curr);
};

#include "Pattern_polar_parser.hxx"

#endif /* PATTERN_POLAR_PARSER_HPP */
