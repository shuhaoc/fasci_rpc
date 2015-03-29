/**
 * 用于创建服务方法对象的一系列辅助方法
 */

#pragma once

#include "service_method_impl.h"

namespace fasci_rpc {
namespace server {


template <typename Cls, typename Ret>
std::shared_ptr<IServiceMethod> createServiceMethod(Cls* that, Ret (Cls::*func)()) {
	return std::shared_ptr<IServiceMethod>(new impl::ServiceMethod0<Cls, Ret>(that, func));
}

template <typename Cls, typename Ret, typename Arg1>
std::shared_ptr<IServiceMethod> createServiceMethod(Cls* that, Ret (Cls::*func)(Arg1)) {
	return std::shared_ptr<IServiceMethod>(new impl::ServiceMethod1<Cls, Arg1, Ret>(that, func));
}

template <typename Cls, typename Ret, typename Arg1, typename Arg2>
std::shared_ptr<IServiceMethod> createServiceMethod(Cls* that, Ret (Cls::*func)(Arg1, Arg2)) {
	return std::shared_ptr<IServiceMethod>(new impl::ServiceMethod2<Cls, Arg1, Arg2, Ret>(that, func));
}


} // namespace server
} // namespace fasci_rpc