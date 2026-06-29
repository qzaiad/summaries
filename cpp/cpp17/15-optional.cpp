- std::optional<T>: simulates no value by using an internal flag
- has value semantic
- std::nullopt: no value
- Contructors:
-- create empty objects: optional<int> o1, o2(nullopt);
-- Due to a deduction guide, you do not have to specify the contained type:
--- optional o3{42}; // deduces optional<int>
--- std::optional o4{"hello"}; // deduces optional<const char*>
--- using namespace std::string_literals; std::optional o5{"hello"s}; // deduces optional<string>
-- Initializing with multiple arguments
--- std::optional o6{std::complex{3.0, 4.0}};
--- std::optional<std::complex<double>> o7{std::in_place, 3.0, 4.0}; // contained type cannot be deduced
---- No temporary object is created, i.e. the internal object is created only once
---- initialize set with lambda as sorting criterion:
  auto sc = [] (int x, int y) { return std::abs(x) < std::abs(y);};
  std::optional<std::set<int,decltype(sc)>> o8{std::in_place, {4, 8, -7, -2, 0, 5}, sc};
----- note that all initial values MUST match the container's element type (here int), otherwise initializer_list<> MUST BE used
  std::optional<std::set<int,decltype(sc)>> o8{std::in_place, std::initializer_list<int>{4, 5L}, sc};
-- Copy constructor including type conversion):
--- optional o9{"hello"}; <-- const char*    optional<string> o10{o9}; <-- string
--- optional<int> o11;    optional<any> o12{o1}; <-- any contains optional<int> --> because any can be constructed from optional -> prefer it

- make_optional<>(): initialization without using in_place argument
-- auto o13 = std::make_optional(3.0); // optional<double>
-- auto o14 = std::make_optional("hello"); // optional<const char*>
-- auto o15 = std::make_optional<std::complex<double>>(3.0, 4.0);
- auto o16 = pos != englishToGerman.end() ? std::optional{pos->second} : std::nullopt;
-- nullopt can be implicitly converted to optional<T>, i.e. call optional contains an implicit constructor with nullopt argument

- Accessing the Value:
-- opt.has_value() <-> if(opt) <-> if(!!opt)
-- *opt <-> .value(): accesses contained value by reference. If no value is contained -> undefined behaviour
-- opt->: accesses members of contained object. If no value is contained -> undefined behaviour
- cout << opt -> ERROR -> not defined
- cout << o.value(); // OK (throws std::bad_optional_access : std::exception if no value) (*o does not throw -> undefined behaviour)
- std::cout << o.value_or("NO VALUE"); // OK (writes fallback balue "NO VALUE" if no value) --> not like .value() -> .value_or() returns by value & might allocate memory
- There are two versions of value_or():
-- Called on an lvalue -> T value_or(U&& default_value) const &; <-> if (opt.has_value()) return *opt; else return "default"; -> contained type must be copyable
-- Called on an rvalue -> T value_or(U&& default_value) &&;      <-> if (opt.has_value()) return std::move(*opt); else return "default"; -> 
--- This is useful for move-only types such as unique_ptr
---- auto p = opt.value_or(nullptr);   // error
---- auto p = std::move(opt).value_or(nullptr);

- Comparisons
-- If both operands are objects with a value, the corresponding operator of the contained type is used.
-- If both operands are objects without a value, they are considered to be equal (== yields true and all other comparisons yield false).
-- If only one operand is an object with a value, the operand without a value is considered to be less thanthe other operand.
-- std::optional<int> o0; std::optional<int> o1{42};
  o0 == std::nullopt -> true;  o0 == 42 -> false;  o0 < 42 -> true;  o0 > 42 -> false;  o1 == 42 -> true;  o0 < o1 -> true
-- optional objects of unsigned int, there is a value less than 0 -> optional<unsigned> uo; uo < 0 -> true;  uo < -42 -> yields true;
-- optional objects of bool, there is a value less than false optional<bool>() < false -> true
-- To make your code more readable, you should use: if (!uo.has_value()) instead of if (uo < 0)
-- Mixed-Type Comparisons:
--- If the underlying type supports implicit type conversions, the mixed-type comparisons may also use implicit type conversions.
---- optional<int> o1{42}; optional<double> o2{42.0}; o2 == 42 -> true; o1 == o2 -> yields true
--- Special Cases:
---- optional<bool> ob{false};   if (!ob) -> false; if (ob == false) -> true
---- optional<int*> op{nullptr}; if (!op) -> false (because it has a value nullptr);  if (op == nullptr) -> true

- Changing the Value
-- optional<std::complex<double>> o; std::optional ox{77};
  o = 42; // value becomes complex(42.0, 0.0)
  o = {9.9, 4.4}; // value becomes complex(9.9, 4.4)
  o = ox; // OK, because int converts to complex<double>
  o.emplace(5.5, 7.7); // value becomes complex(5.5, 7.7)
  o = std::nullopt; // o no longer has a value -> same as o.reset() or o = {}
  if(o) *o = 42;

- Move Semantics
- opt1 = move(opt2); -> flag copied and contained object is moved
- optional<string> os; os = move(string("XXX")); -> moves;  auto s2 = *os -> copied;  s3 = move(*os) -> moved;
- Temporary optionals are moved: optional<std::string> func(); string s4 = func().value(); -> moves; string s5 = *func() -> moves  
-- due to the following rvalue overloads
  class optional {
    constexpr T& operator*() &;
    constexpr const T& operator*() const&;
    constexpr T&& operator*() &&;
    constexpr const T&& operator*() const&&;
    
    constexpr T& value() &;
    constexpr const T& value() const&;
    constexpr T&& value() &&;
    constexpr const T&& value() const&&;
  };

- Hashing
-- The hash value for an optional object is the hash value of the contained non-constant type (if there is one).
-- The hash value of an empty optional object evaluates to an unspecified value.
