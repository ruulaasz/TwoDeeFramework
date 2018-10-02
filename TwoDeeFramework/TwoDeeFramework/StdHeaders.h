#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <queue>

template<typename A, typename B>
using UnorderedMap = std::unordered_map<A, B>;

template<typename A, typename Alloc = std::allocator<A>>
using Vector = std::vector<A, Alloc>;

template<typename A>
using Shared_Ptr = std::shared_ptr<A>;

template<typename A>
using Queue = std::queue<A>;

using std::string;
using String = std::string;

using WString = std::wstring;

using std::ifstream;
using std::istreambuf_iterator;
using std::atof;
using std::atan2;
using std::sqrt;
using std::pow;
using std::pair;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;
using std::reverse;
using std::make_shared;