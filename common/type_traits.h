#pragma once

namespace fasci_rpc {
namespace common {


/**
 * 萃取类型的值类型
 */
template <typename T>
struct TypeTraits {
	typedef T ValueType;
};

template <typename T>
struct TypeTraits<const T&> {
	typedef T ValueType;
};


} // namespace common
} // namespace fasci_rpc