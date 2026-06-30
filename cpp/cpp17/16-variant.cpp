- std::variant<>: analog to C-Union
- Drawbacks of C-Unions
-- the type of the current value is unknown
-- can only have trivial members (int, float...). Since C++11 non-trivial members are possible by implementing special member funcs such as copy-constructor/destructor
-- you cannot derive from a union

- variant<alternative1, alternative2, ..., alternativeN>
-- Type of current value is known
-- can hold values of any type
-- you can derive from it
-- have fixed size of the maximum alternative-size + fixed management overhead to know which alternative is used (on stack)
-- cannot be empty EXCEPT a specific alternative signals emptiness.
--- at least one constructor has to be called -> default constructor initializes the first type with the default constructor
---- variant<string, int> var; -> var.index() == 0, value == ""
---- if no default constructor in alt1 -> compile-error
---- std::monostate provides the ability to deal with this situation and also provides the ability to simulate an empty state.
-- can come into a state that has no value at all (exception during assignment of a new value of a new type)
-- resulting objects have value semantics (like optional/any<>) -> deep copy is used
--- variants with reference members, variants with C-style array members, and variants with incomplete types (such as void) are not allowed in C++17 -> (might be added later)
-- Move semantics are supported
-- Initializations and assignments always use the best match to find the new alternative. If the type does not
fit exactly, there might be surprises.
  
- Example: variant<int, string> var{"hi"}; -> string alt.; var.index() -> 1; var = 42 -> now holds int alt.; get<0/1/int/string>(var) -> 42 access by idx/type;
-- std::bad_variant_access exception in case a wrong type/index is used

- std::monostate: simulate emptiness of a variant<> -> variant has no value of any other type
-- useful when alt1 has no defa. constructor -> SHOULD BE THE FIRST ALTERNATIVE
-- Objects of type monostate always have the same state -> equal
-- variant<monostate, NoDefConstr, int> v2; // OK -> v2.index() -> 0;
-- Check for emptiness:
--- if(v2.index() == 0) / if(!v2.index()) / if(std::holds_alternative<std::monostate>(v2)) / if(std::get_if<0>(&v2)) / if(std::get_if<std::monostate>(&v2))
--- get_if<T>(&var) returns a pointer to the current alternative if the current alternative is T, otherwise nullptr
--- get<T>(var_by_reference) returns the current alternative BY VALUE if the provided type is correct, but throws in all other cases.
-- Assigning values; v2 = 42 / monostate{} -> initialize new alt. then destroy old alt

- Deriving from Variants: you can define an aggregate that derives from a std::variant<>
-- class Derived : public std::variant<int, std::string> {};  Derived d = {{"hello"}};  d.emplace<0>(77); -> initializes int, destroys string

- std::variant<> Types
