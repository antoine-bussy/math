#ifndef ALGEBRA_GEOMETRIC_H
#define ALGEBRA_GEOMETRIC_H 

#include"../group/geometric.h"
#include"../group/ordering.h"
#include"../vector/addition.h"
#include"multiplication.h"

#include<boost/hana.hpp>

namespace algebra::geometric{
	vector::Scalar{ScalarT} using  add_operation_t=vector:: add_operation_t<ScalarT>;
	vector::Scalar{ScalarT} using mult_operation_t=algebra::mult_operation_t<group::geometric::mult_operation_t, ScalarT>;

	namespace operators{
		template<class A, class B> constexpr auto operator*(A const& a, B const& b){
			return mult_operation_t<double>::apply(a,b);
		}
		template<class A, class B> constexpr auto operator+(A const& a, B const& b){
			return add_operation_t<double>::apply(a,b);
		}
		template<class A> constexpr auto operator-(A const& a){
			return add_operation_t<double>::inverse(a);
		}
		template<class A, class B> constexpr auto operator-(A const& a, B const& b){
			return a+(-b);
		}
	}

	namespace hana=boost::hana;
	using namespace hana::literals;

	auto constexpr grades(vector::basis_element_t<auto,auto> const& a){return hana::make_set(hana::llong_c<grade(a.element())>);}
	auto constexpr grades(group::generated_element_t<add_operation_t<auto>, auto,auto> const& a){
		return hana::union_(grades(a.first), grades(a.second));
	}
}
#endif /* ALGEBRA_GEOMETRIC_H */
