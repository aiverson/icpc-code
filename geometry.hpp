#include<array>

struct ZeroNumber{ static const int value = 0;
    template<typename A> operator A() {return 0;}
};
template<typename A>ZeroNumber operator *(A a, ZeroNumber b) {return ZeroNumber();}
template<typename B>ZeroNumber operator *(ZeroNumber a, B b) {return ZeroNumber();}
template<typename A>A operator +(A a, ZeroNumber b) {return a;}
template<typename B>B operator +(ZeroNumber a, B b) {return a;}

struct NIL {typedef NIL Head; typedef NIL Tail;};
template<typename H, typename T = NIL> struct TypeList{typedef H Head;typedef T Tail;};

template<typename LST1, typename LST2>
struct DotReduction {
    typedef decltype(declval(LST1::Head)*declval(LST2::Head) + declval(DotReduction<LST1::Tail, LST2::Tail>)) result;
};
template<> struct DotReduction<NIL, NIL> {typedef ZeroNumber result;};

template<bool b> struct Bit {static const bool value = b;};

template<int i> struct BitList {
    typedef TypeList<Bit<i & 1 == 1>, BitList<i / 2 > result;
};
template<> struct BitList<0> {
    typedef NIL result;
};

template<int start, typename LST> struct SumScan {
    typedef TypeList<LST::Head::value + start, SumScan<LST::Head::value + start, LST::Tail> result;
};
template<int val> struct InfIntList {
    typedef Int<val> Head;
    typedef InfIntList<val> Tail;
};
template<int start> struct SumScan<start, NIL> {
    typedef InfIntList<start> result;
};
template<int i> struct Int { static const int value = i;};
template<int start, typename LST> struct SumFold {
    typedef Int<SumFold<LST::Head::value + start, LST::Tail>::value> result;
};
template<int start> struct SumFold<start, NIL> {
    typedef Int<start> result;
};
template<typename LST1, typename LST2> struct ProdZip {
    typedef TypeList<Int<LST1::Head::value * LST2::Head::value>, ProdZip<LST1::Tail, LST2::Tail> > result;
};
template<typename LST1> struct ProdZip<LST1, NIL> {typedef NIL result;};
template<typename LST2> struct ProdZip<NIL, LST2> {typedef NIL result;};
template<int b1, int b2> struct BladeSign {
    typedef Int<SumFold<0, ProdZip<BitList<b1>::Tail, SumScan<0, BitList<b2> > > >::value * 2 - 1> result;
};
template<int b1, int b2> struct BladeBasis{static const int value = b1 ^ b2;};

template<typename LST> struct ValList {
    LST::Head Head;
    ValList<LST::Tail> Tail;
    template<int pos> inline decltype(Tail.val<pos - 1>()) val() {return Tail.val<pos - 1>();} const
    template<> inline LST::Head val<0>() {return Head;} const
};

template<typename Elm, typename LST, int idx> struct PrependNth {
    typedef TypeList<LST::Head, PrependNth<idx - 1, Elm, LST::Tail> > result;
};
template<typename Elm, typename LST> struct PrependNth<Elm, LST, 0> {
    typedef TypeList<TypeList<Elm, LST::Head>, LST::Tail> > result;
};

template<int dim> struct PrepList {typedef TypeList<NIL, PrepList<dim-1> result;};
template<> struct PrepList<0> {typedef TypeList<NIL, NIL> result;};

template<int sign, int op1, int op2> struct BladeProd{static const int sign = sign, op1 = op1, op2 = op2;};

template<typename A, typename B, int ai, int bi> struct BladeLoop {
    typedef PrependNth<BladeProd<BladeSign<ai, bi>::value, ai, bi>, BladeLoop<A, B::Tail, ai, bi+1>, BladeBasis<ai, bi>::value> result;
};
template<typename A, int ai, int bi> struct BladeLoop<A, NIL, ai, bi> {
    typedef PrependNth<BladeProd<BladeSign<ai, bi>::value, ai, bi>, BladeLoop<A::Tail, A::Head, ai+1, 0>, BladeBasis<ai, bi>::value> result;
};
template<int ai, int bi> struct BladeLoop<NIL, NIL, ai, bi> {
    typedef PrepList<ai> result;
};

template<typename A, typename B> struct BuildProd {
    
};

//accept MV_Impls here.
template<typename MVA, typename MVB> auto prod(MVA a, MVB b) {
    return MV_Impl<NIL> //TODO: compute correct type and initialize it.
}

template<typename LST> struct MV_Impl{
    ValList<LST> vals;
};


constexpr int bladeSign(int a, int b) {

}

struct mv3 {
    std::array<double, 8> components;
}