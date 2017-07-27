#ifndef ALGEBRA_BASIS_H
#define ALGEBRA_BASIS_H 

#include"../vector/basis.h"
#include"../group/concept.h"
#include"../group/minus.h"

#include<boost/hana.hpp>

namespace algebra{
	namespace hana=boost::hana;

	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT, class... ElementsT>
	concept bool BasisElementsTemplateParameters=
		   group::Group<GroupT, IdentityT, OperatorT, InverseT>
		&& vector::Scalar<ScalarT>
		&& static_cast<bool>(hana::all(hana::make_tuple(group::is_in_type_list<GroupT>(hana::type_c<ElementsT>)...)))
	;
	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT>
	concept bool ZeroBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT>;
	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT, class ElementT>
	concept bool OneBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT>;
	template<class GroupT, class IdentityT, class OperatorT, template<class> class InverseT, class ScalarT, class ElementA, class ElementB>
	concept bool TwoBasisElementTemplateParameters=BasisElementsTemplateParameters<GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementA, ElementB>;

	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	auto basis_element(ElementT const& e, ScalarT const& s){
		return vector::basis_element_t<ElementT, ScalarT>{s};
	}
	OneBasisElementTemplateParameters{GroupT, IdentityT, OperatorT, InverseT, ScalarT, ElementT}
	auto basis_element(group::generated_minus_t<OperatorT, ElementT> const& a, ScalarT const& s){
		return vector::basis_element_t<ElementT, ScalarT>{-s};
	}
}

#endif /* ALGEBRA_BASIS_H */