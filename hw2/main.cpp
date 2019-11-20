#include <iostream>
#include <vector>

#include "typelist.h"
#include "typelist_operations.h"
#include "scatter_hierarchy.h"
#include "linear_hierarchy.h"
#include "furniture.h"
#include "abstract_factory.h"


int main() {
    std::cout << std::endl << "TypeList test:" << std::endl;
    TypeList<int, char, double> tl;
    PrintTypeList<TypeList<int, char, bool>>();

    std::cout << std::endl << "Scatter hierarchy test:" << std::endl;
    using SH = GenScatterHierarchy<TypeList<int, std::string>, Unit>;
    SH sh;
    std::string n = (static_cast<Unit<std::string> &>(sh)).GetValue();
    std::cout << n << std::endl;

    using LH = GenLinearHierarchy<TypeList<int, std::string, char, std::vector<int>>, EventHandler, EmptyList>;

    std::cout << std::endl << "IsIn test:" << std::endl;
    std::cout << IsIn<TypeList<char, int, bool>, int>::result << std::endl;
    std::cout << IsIn<TypeList<int, int, bool>, int>::result << std::endl;
    std::cout << IsIn<TypeList<char, bool, int>, int>::result << std::endl;
    std::cout << IsIn<TypeList<int, bool, char>, int>::result << std::endl;
    std::cout << IsIn<TypeList<bool, bool, char>, int>::result << std::endl;
    std::cout << IsIn<TypeList<>, int>::result << std::endl;

    std::cout << std::endl << "PushFront test" << std::endl;
    PrintTypeList<typename PushFront<int, TypeList<char, int>>::result>();

    std::cout << std::endl << "ReplaceFirst test" << std::endl;
    PrintTypeList<typename ReplaceFirst<TypeList<bool, char, int>, char, int>::result>();

    using tl_ex = TypeList<
            TypeList<WoodenChair, WoodenTable, WoodenSofa>,
            TypeList<MetalChair, MetalTable, MetalSofa>,
            TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>,
            TypeList<MetalPoorChair, MetalPoorTable, MetalPoorSofa>,
            TypeList<Chair, Table, Sofa>
    >;

    std::cout << std::endl << "FindTlWithElem test:" << std::endl;
    PrintTypeList<typename FindTlWithElem<tl_ex, Chair>::result>();
    PrintTypeList<typename FindTlWithElem<tl_ex, WoodenTable>::result>();
    PrintTypeList<typename FindTlWithElem<tl_ex, MetalPoorSofa>::result>();

    std::cout << std::endl << "IsDerived test:" << std::endl;
    std::cout << IsDerived<MetalPoorChair, Chair>::result << std::endl;
    std::cout << IsDerived<MetalPoorChair, Table>::result << std::endl;
    std::cout << IsDerived<Chair, Table>::result << std::endl;
    std::cout << IsDerived<Chair, MetalChair>::result << std::endl;


    std::cout << std::endl << "MostBase test:" << std::endl;
    PrintTypeList<typename MostBase<tl_ex>::result>();
    using tl_ex_base_first = TypeList<
            TypeList<Chair, Table, Sofa>,
            TypeList<WoodenChair, WoodenTable, WoodenSofa>,
            TypeList<MetalChair, MetalTable, MetalSofa>,
            TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>,
            TypeList<MetalPoorChair, MetalPoorTable, MetalPoorSofa>
    >;
    PrintTypeList<typename MostBase<tl_ex_base_first>::result>();

    using tl_ex_base_middle = TypeList<
            TypeList<WoodenChair, WoodenTable, WoodenSofa>,
            TypeList<MetalChair, MetalTable, MetalSofa>,
            TypeList<Chair, Table, Sofa>,
            TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>,
            TypeList<MetalPoorChair, MetalPoorTable, MetalPoorSofa>
    >;
    PrintTypeList<typename MostBase<tl_ex_base_middle>::result>();

    std::cout << std::endl << "FindElemBase test:" << std::endl;
    std::cout << typeid(FindElemBase<TypeList<Chair, Table, Sofa>, MetalRichTable>::result).name() << std::endl;
    std::cout << typeid(FindElemBase<TypeList<Chair, Table, Sofa>, MetalRichSofa>::result).name() << std::endl;
    std::cout << typeid(FindElemBase<TypeList<Chair, Table, Sofa>, MetalRichChair>::result).name() << std::endl;


    std::cout << std::endl << "Factory test:" << std::endl;

    using MyFactoryHierarchy = GetAbstractFactory<
            3,
            5,
            TypeList<WoodenChair, WoodenTable, WoodenSofa>,
            TypeList<MetalChair, MetalTable, MetalSofa>,
            TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>,
            TypeList<MetalPoorChair, MetalPoorTable, MetalPoorSofa>,
            TypeList<Chair, Table, Sofa>
    >;
    using Factory = MyFactoryHierarchy::BaseFactory;
    Factory* MyFactory = new MyFactoryHierarchy::GetConcreteFactory<MetalPoorChair>::result();
    Table* a = MyFactory->Get<Table>();

    Factory* MyFactory1 = new MyFactoryHierarchy::GetConcreteFactory<Chair>::result();
    Table* a1 = MyFactory1->Get<Table>();

    return 0;
}