/**
 * 一系列服务方法对象的具体实现
 */

#pragma once

#include "service_method.h"
#include "../common/type_traits.h"

namespace fasci_rpc {
namespace server {
namespace impl {


// ------------------------------------------ 0 arguemnts -----------------------------------------

template <typename Cls, typename Ret>
class ServiceMethod0 : public IServiceMethod {
public:
	typedef Ret (Cls::*FuncType)();

	ServiceMethod0(Cls* that, FuncType func) : _that(that), _func(func) {
	}

	void execute(boost::archive::binary_iarchive& request_data,	boost::archive::binary_oarchive& response_data) {
		Ret r = (_that->*_func)();
		response_data << r;
	}

private:
	Cls* _that;
	FuncType _func;
};

template <typename Cls>
class ServiceMethod0<Cls, void> : public IServiceMethod {
public:
	typedef void (Cls::*FuncType)();

	ServiceMethod0(Cls* that, FuncType func) : _that(that), _func(func) {
	}

	void execute(boost::archive::binary_iarchive& request_data,	boost::archive::binary_oarchive& response_data) {
		(_that->*_func)();
	}

private:
	Cls* _that;
	FuncType _func;
};

// ------------------------------------------ 1 arguemnts -----------------------------------------

template <typename Cls, typename Arg1, typename Ret>
class ServiceMethod1 : public IServiceMethod {
public:
	typedef Ret (Cls::*FuncType)(Arg1);

	ServiceMethod1(Cls* that, FuncType func) : _that(that), _func(func) {
	}

	void execute(boost::archive::binary_iarchive& request_data,	boost::archive::binary_oarchive& response_data) {
		common::TypeTraits<Arg1>::ValueType arg1;
		request_data >> arg1;
		Ret r = (_that->*_func)(arg1);
		response_data << r;
	}

private:
	Cls* _that;
	FuncType _func;
};

template <typename Cls, typename Arg1>
class ServiceMethod1<Cls, Arg1, void> : public IServiceMethod {
public:
	typedef void (Cls::*FuncType)(Arg1);

	ServiceMethod1(Cls* that, FuncType func) : _that(that), _func(func) {
	}

	void execute(boost::archive::binary_iarchive& request_data,	boost::archive::binary_oarchive& response_data) {
		common::TypeTraits<Arg1>::ValueType arg1;
		request_data >> arg1;
		(_that->*_func)(arg1);
	}

private:
	Cls* _that;
	FuncType _func;
};

// ------------------------------------------ 2 arguemnts -----------------------------------------

template <typename Cls, typename Arg1, typename Arg2, typename Ret>
class ServiceMethod2 : public IServiceMethod {
public:
	typedef Ret (Cls::*FuncType)(Arg1, Arg2);

	ServiceMethod2(Cls* that, FuncType func) : _that(that), _func(func) {
	}

	void execute(boost::archive::binary_iarchive& request_data,	boost::archive::binary_oarchive& response_data) {
		common::TypeTraits<Arg1>::ValueType arg1;
		common::TypeTraits<Arg2>::ValueType arg2;
		request_data >> arg1 >> arg2;
		Ret r = (_that->*_func)(arg1, arg2);
		response_data << r;
	}

private:
	Cls* _that;
	FuncType _func;
};

template <typename Cls, typename Arg1, typename Arg2>
class ServiceMethod2<Cls, Arg1, Arg2, void> : public IServiceMethod {
public:
	typedef void (Cls::*FuncType)(Arg1, Arg2);

	ServiceMethod2(Cls* that, FuncType func) : _that(that), _func(func) {
	}

	void execute(boost::archive::binary_iarchive& request_data,	boost::archive::binary_oarchive& response_data) {
		common::TypeTraits<Arg1>::ValueType arg1;
		common::TypeTraits<Arg2>::ValueType arg2;
		request_data >> arg1 >> arg2;
		(_that->*_func)(arg1, arg2);
	}

private:
	Cls* _that;
	FuncType _func;
};


} // namespace impl
} // namespace server
} // namespace fasci_rpc