#include"algebra.h"
#include"group/geometric.h"
#include"group/generate.h"

//generators
using e1_t=group::geometric::direction_positive_t<1>;
using e2_t=group::geometric::direction_positive_t<2>;
using e3_t=group::geometric::direction_positive_t<3>;
using namespace group::geometric;

//mult groups, finite order of generators plus commutation rules guarantees that the group is finite
constexpr auto geometric_group_2d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>), inverse, mult);
constexpr auto complex_group=group::generate(hana::make_set(hana::type_c<mult_t<e1_t,e2_t>>), inverse, mult);
constexpr auto geometric_group_3d=group::generate(hana::make_set(hana::type_c<e1_t>, hana::type_c<e2_t>, hana::type_c<e3_t>), inverse, mult);

template<class ElementT>
using geometric_basis_element_t=algebra::basis_element_t<decltype(geometric_group_3d), one_t, mult_t, inverse_t, double, ElementT>;

template<class A, class B>
using add_t=algebra::add_impl_binary_impl_t<decltype(geometric_group_3d), one_t, mult_t, inverse_t, double>;

int main(){
	geometric_basis_element_t<e1_t> a{2.};
	geometric_basis_element_t<e2_t> b{3.};
	std::cout<<(a*b)<<std::endl;
	return 0;
}
