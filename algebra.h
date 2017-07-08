#ifndef ALGEBRA_H
#define ALGEBRA_H 

#include"group/concept.h"
#include"group/operation.h"
#include"sorted.h"

#include<type_traits>
#include<iostream>

namespace algebra{
	namespace hana=boost::hana;

	template<class T> concept bool Scalar=std::is_arithmetic<T>::value;

	template<class GroupT, class IdentityT, template<class,class> class OperatorT, template<class> class InverseT, class ScalarT, class... ElementsT>
	concept bool BasisElementsTemplateParameters=
		   group::Group<GroupT, IdentityT, OperatorT, InverseT>
		&& Scalar<ScalarT>
		&& static_cast<bool>(hana::all(hana::make_tuple(group::is_in_type_list<GroupT>(hana::type_c<ElementsT>)...)))
	;
	template<class GroupT, class IdentityT, template<class,class> class OperatorT, template<class> class InverseT, class ScalarT>
	concept bool ZeroBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT>;
	template<class GroupT, class IdentityT, template<class,class> class OperatorT, template<class> class InverseT, class ScalarT, class ElementT>
	concept bool OneBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>;
	template<class GroupT, class IdentityT, template<class,class> class OperatorT, template<class> class InverseT, class ScalarT, class ElementA, class ElementB>
	concept bool TwoBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA, ElementB>;

	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	struct basis_element_t{
		ScalarT coordinate;
	};

	TwoBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA, ElementB}
	auto operator*(basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA> const& a, basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementB> const& b){
		return basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, OperatorT<ElementA,ElementB>>{a.coordinate*b.coordinate};
	}

	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	auto operator+(basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT> const& a, basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT> const& b){
		return basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ElementT, ScalarT>{a.coordinate+b.coordinate};
	}

	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	auto& operator<<(std::ostream& out, basis_element_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT> const& a){
		return out<<a.coordinate<<" * "<<typeid(ElementT).name();
	}


	//add rules
	//template<class GroupT, class IdentityT, template<class,class> class OperatorT, template<class> class InverseT, class ScalarT, class A, class B, template<class,class>>
	TwoBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, A, B}
	struct add_impl_t;
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	struct add_impl_binary_impl_t{
		template<class A,class B>
		using type=add_impl_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, A, B>;
	};
	TwoBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, A, B}
	struct add_impl_t: group::operation_t<
		add_impl_binary_impl_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>::template type
		,A,B
	>{};
	TwoBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, A, B}
	using add_t=typename add_impl_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT, A, B>::type;
	ZeroBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT}
	using zero_t=group::identity_t<
		add_impl_binary_impl_t<GroupT, IdentityT, OperatorT, InverseT, ScalarT>::template type
	>;

	//template<class GroupT, class IdentityT, template<class,class> class OperatorT, template<class> class InverseT, class ScalarT, class A, class B>
		//requires !std::is_same<A,B>::value 
			  //&& !Sorted<GroupT,A,B> 
			  //&& TwoBasisElementTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, A, B>
	//struct add_impl_t<GroupT,IdentityT,OperatorT,InverseT,ScalarT,A,B>:
		//add_impl_t<GroupT,IdentityT,OperatorT,InverseT,ScalarT,B,A>{};
	////add functions
	//constexpr auto add  =[](auto const& a, auto const& b){return hana::type_c<add_t <typename std::decay_t<decltype(a)>::type, typename std::decay_t<decltype(b)>::type>>;};
	//constexpr auto minus=[](auto const& a){return hana::type_c<minus_t<typename std::decay_t<decltype(a)>::type>>;};

}

#endif /* ALGEBRA_H */