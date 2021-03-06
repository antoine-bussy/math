#include"addition.h"
#include"../unit_test.h"

#include<cstdlib>

using e1_t=vector::basis_element_t<group::indexed_element_t<1>>;
using e2_t=vector::basis_element_t<group::indexed_element_t<2>>;
using e3_t=vector::basis_element_t<group::indexed_element_t<3>>;

template<class A, class B> constexpr auto operator+(A const& a, B const& b){
	return vector::add_operation_t<double>::apply(a,b);
}
template<class A> constexpr auto operator-(A const& a){
	return vector::add_operation_t<double>::inverse(a);
}
template<class A, class B> constexpr auto operator-(A const& a, B const& b){
	return a+(-b);
}

static constexpr auto e1=e1_t{1.};
static constexpr auto e2=e2_t{1.};
static constexpr auto e3=e3_t{1.};

int main(){
	//colinear
	check_equal(e1+2.*e1, 3.*e1);
	check_equal(-e1, -1.*e1);
	check_equal(2.*e1-e1, 1.*e1);
	check_equal(e1-e1, 0.*e1);
	//commutation
	check_equal(e2+e1, e1+e2);
	check_equal(e1+e2+e1, 2.*e1+e2);
	check_equal(e2+e1+e2, e1+2.*e2);
	check_equal(e1+e2+e1-e2, 2.*e1+0.*e2);


	return 0;
}

