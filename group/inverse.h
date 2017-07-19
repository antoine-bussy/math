#ifndef INVERSE_H
#define INVERSE_H 

#include"apply_operation.h"
#include"identity.h"

namespace group{
	//inverse generates a new type by default
	template<class Operator, class T> struct generated_inverse_t{T value_before_inverse;};

	template<class Operator, class A>
	constexpr auto inverse(A const& a){return generated_inverse_t<Operator, A>{a};}
	//inverse of inverse is self
	template<class Operator, class A>
	constexpr auto inverse(generated_inverse_t<Operator, A> const& a){return a.value_before_inverse;}
	//inverse of identity is identity
	template<class Operator>
	constexpr auto inverse(identity_t<Operator> const& a){return a;}

	template<class Operator, class T> struct inverse_impl_t{using type=decltype(inverse<Operator>(T{}));};
	template<class Operator, class T> using inverse_t=typename inverse_impl_t<Operator, T>::type;

	template<class ElementT, class IdentityT, class OperatorT, template<class A> class InverseT>
	concept bool HasInverse=std::is_same<InverseT<InverseT<ElementT>>, ElementT>::value
	                     && std::is_same<decltype(apply_operation<OperatorT>(InverseT<ElementT>{},ElementT{})), IdentityT>::value
	                     && std::is_same<decltype(apply_operation<OperatorT>(ElementT{},InverseT<ElementT>{})), IdentityT>::value
	                     && AbsorbsIdentityElement<InverseT<ElementT>,IdentityT,OperatorT>
                         ;
} 

#endif /* INVERSE_H */
