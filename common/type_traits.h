#pragma once

namespace fasci_rpc {
namespace common {


/**
 * ��ȡ���͵�ֵ����
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