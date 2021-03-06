#ifndef ADDITION_H
#define ADDITION_H 

#include"basis.h"
#include"../group/commutation.h"
#include"../group/operation.h"
#include"../group/inverse.h"

#include<iostream>

namespace vector{
	template<Scalar ScalarT=double> 
	struct add_operation_t{
		template<class ElementT> 
		using basis_element_t=vector::basis_element_t<ElementT, ScalarT>;

		//commutation rule
		template<class ElementA, class ElementB>
			requires !std::is_same<ElementA,ElementB>::value 
			      && static_compare(ElementA{},ElementB{})<0
		static constexpr auto apply(basis_element_t<ElementA> const& a, basis_element_t<ElementB> const& b){
			return apply(b,a);
		}
		//colinear rule
		template<class ElementT>
		static constexpr auto apply(basis_element_t<ElementT> const& a, basis_element_t<ElementT> const& b){
			//if constexpr(a.coordinate+b.coordinate==0){
				//return group::identity_t<add_operation_t>{};
			//}else{
				return basis_element_t<ElementT>{a.coordinate+b.coordinate};
			//}
		}
		//group rules
		static constexpr auto apply(auto const& a, auto const& b){
			return group::operation<add_operation_t>(a,b);
		}

		static constexpr auto inverse(basis_element_t<auto> const& a){
			return std::decay_t<decltype(a)>{-a.coordinate};
		}
		static constexpr auto inverse(auto const& a){
			return group::inverse<add_operation_t>(a);
		}
	};

	std::ostream& operator<<(std::ostream& out, group::generated_element_t<add_operation_t<Scalar>, auto, auto> const& ab){
		return out<<"("<<ab.first<<") + ("<<ab.second<<")";
	}
}

#endif /* ADDITION_H */
