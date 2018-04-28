# Style guide

## Code structure

### File structure
Headers contain only declarations.
Definitions should be contained in a corresponding source file, or in an inlined file included in the header (for template and inline function definitions).
This keeps the interfaces clean while complying to the C++ rules.

Each header file normally has a corresponding source file (not always), and sometimes a corresponding inlined file.
The three files have the same name, save for the extension.
Header files have the .hpp extension, source files the .cpp extension, and inlined file the .inl extension.
The exception to this rule is when the definitions must be different according to the target compilation platform.
In that case, there can be multiple source files, one for each platform (and potentially one common one for the definitions that are the same for all platforms).
In this case the extra source files have a suffix identifying the type of platform (e.g. window\_impl.cpp and window\_impl\_win.cpp).



### Header inclusion
Headers should be included only when  necessary to reduce compilation times and number of recompilations when a header is modified.
In all other cases forward declarations should be preferred.

For this reason, nested type definition should be avoided, since nested types cannot be forward declared.
An obvious exception is if the type is not public.

In cases where using forward declarations can be cumbersome, an extra forward declaration header can be added.
This header should have the same name of the normal header, with the suffix \_fwd (e.g. matrix.hpp and matrix\_fwd.hpp).
The forward declaration header should be included in the main header, to ensure that all symbols defined there are respected.

```
template <typename T size_t rows, size_t cols>
class matrix;

template <typename T, size_t cols>
using vec = matrix<T, 1u, cols>;

template <typename T>
using vec2 = vec<T, 2u>;

using vec2i = vec2<int>;
using vec2f = vec2<float>;
```



### Directory structure
The directory structure of the code base follows the following pattern:

```
root
|_cmake
|_docs
|_external-libs
|_source
  |_module_name
    |_include/hou/module_id
    |_src/hou/module_id
    |_test/hou/module_id
```

* The **cmake** directory contains cmake specific files.
* The **docs** directory contains formatted documentation in html format.
* The **external-libs** directory contains the source files for all external libraries.
* The **source** directory contains the source code.
* Each **source/\[module\_name\]** directory contains the source files for a specific module.
* Each **source/\[module\_name\]/include** directory contains the all the .hpp and .inl files.
* Each **source/\[module\_name\]/src** directory contains the all the .cpp files.
* Each **source/\[module\_name\]/test** directory contains the all the test related files.

The user of the library should include the paths to the include folder of each used module in order to be able to include header files conveniently:
```
#include "hou/gfx/texture.hpp"
#include "hou/mth/transform.hpp"
```



## Code style
In the following the reasons why specific formatting rules have been chosen is explained.



## Naming conventions

The following rules should be strictly adhered to:
* By default all names must be written in lower-case snake case, except when differently specified below.
```
// Good
class my_class {};
int my_variable;

// Bad
class MyClass {};
int myVariable;
```
* Preprocessor names must be written in upper-case snake case.
```
// Good
#define HOU_MY_SYMBOL 0

// Bad
#define hou_my_symbol 0
#define HouMySymbol 0
```
* Template parameter and concept names must be written in camel case.
```
// Good
template <typename TemplateParam>
TemplateParam max(TemplateParam, TemplateParam b);

// Bad
template <typename template_param>
TemplateParam max(TemplateParam, TemplateParam b);
```
* It is forbidden to start names with an underscore, as such names might be reserved.
```
// Bad
int _my_variable;
```
* It is forbidden to use two or more consecutive underscores in names, as such names might be reserved.
```
int my__variable;
```

The following rules are preferences which do not need be necessarly respected, but it is preferred if they are:
* Non-public, non-static, class-scope variables should be prefixed with 'm\_' to reduce the likelihood of name clashes.
```
class my_class
{
private:
  int m_awesomes;
};
```
* Non-public, static, class-scope variables should be prefixed with 's\_' to reduce the likelihood of name clashes.
```
class my_class
{
private:
  static int s_awesomes;
};
```
* Non-exposed, namespace-scope variables should be prefixed with 'g\_' to reduce the likelihood of name clashes.
```
const float g_my_pi = 3.14f;
```
* The above prefixes should not be applied to variables being part of a public interface for consistency and so that the user does not need to remember the scope of a variable when writing it down.
```
const float my_wrong_pi = 3.14f;
class apple_pie
{
public:
  static const int max_apples;
  int apples;
};
```
* Function parameter names should be prefixed with 'p\_' to reduce the likelihood of name clashes.
```
void my_function(int p_apples, int p_pies);
```
* Namespace names should be 2 to 4 characters long to reduce the verbosity of the code.
```
namespace hou {}
namespace std {}
```
* Preprocessor symbol names should be prefixed with 'HOU\_' to reduce the likelihood of name clashes.
```
#define HOU_DO_STUFF(x) (x)*(x)
```

The main reasons behind these naming conventions are:
* Consistency with the standard library.
* Simplicity.
* Reduce the change of name clashing and the verbosity of the code.



### Basic formatting
The code is formatted using clang-format, according to the content of the .clang-format file.
Simply running clang-format should format the code in an acceptable way.
It does sometime happen that clang-format formats some lines of code in a slightly weird way.
If the output of clang-format ends up being unreadable, feel free to format the code manually.
If desired, clang-format can be disabled around such areas of code with the following comment lines
```
\\ clang-format off
...
\\ clang-format on
```



### Maximum line width
The maximum line width is 80 characters.
The reasons for this choice are:
* It is easier to the eyes to read shorter lines.
* It is possible to keep two or even three files side by side, even inside an IDE.
* It is possible for anyone to view the code properly in a small monitor, tablet screen, printed sheet of paper.
* It is a motivation to keep lines as short as possible and to avoid excessive indentation levels.

Any line longer than that must be split into multiple lines.
Lines which are a continuation of a previous line must be indented according to the standard indentation (i.e. they shouldn't be aligned with the brackets).
```
// Good
template <typename LongishTypename>
typename LongishTypename::internal_scope_type longish_function_name(int p_ie,
  my_class p_stuff);

// Bad
template <typename LongishTypename>
typename LongishTypename::internal_scope_type longish_function_name(int p_ie,
                                                                    my_class p_stuff);
```


Line breaks should start with an operator, when possible.
This is to make it clearer at a glance that this line is a continuation of the previous one, and not a new statement.
I personally like to also start lines with a comma ',' when breaking parameter lists for the same reason, but it appears that clang-format doesn't have an option for that, so this is an exception to the rule.



### Brace style
Braces always occupy their own line.
This improves readability when a line before a scope has to be split.
Since both the line continuation and the scope content are indented, they tend to mix together without the separating brace line.
The brace makes it clear when the actual scope starts and when it ends.
```
// Good
template <typename LongishTypename>
typename LongishTypename::internal_scope_type longish_function_name(int p_ie,
  my_class p_stuff)
{
  int hello = 2
}

// Bad
template <typename LongishTypename>
typename LongishTypename::internal_scope_type longish_function_name(int p_ie,
  my_class p_stuff) {
  int hello = 2
}
```

A scope should never be written in a single line and / or inlined with the preceding line.
This is also done to improve readability;
```
// Good
if (a == 2)
{
  return true;
}

// Bad
if(a == 2) { return true; }
```

Braces should always be used after conditions and loops, even when they contain a single instruction.
This reduces the likelihood of small programming errors and ultimately saves time.
```
// Good
if (a == 2)
{
  return true;
}

// Bad
if(a == 2) return true;

// Bad
if(a == 2)
  return true;
```


### Indentation style
Spaces, never tabs, are used for indentation.
An indentation level must be exactly two spaces long.

Spaces are chosen over tabs for visual consistency's sake.
The code will look the same and will be properly formatted no matter what editor it is opened with.

The indentation has been chosen to be two spaces because:
* One space would be too little, easy to confuse with normal spacing.
* Two spaces already make it very clear where the scopes are.
* Having a longer indentation would require more frequent line breaks, thus reducing code readability.



### Line spacing
In header files, declarations are normally separated by a single line.
In source files (and inlined files), declarations and definitions are normally separated by three lines in a row.

The extra spacing in source files is done to improve readability by making it clearer where the boundaries between different definitions are.
Single empty lines often come up inside blocks themselves, therefore separating with a single line tends to mesh everything together.
The extra spacing is not required in header files because the documentation comments already separate the different elements well.
Even without the comments, since only definitions are present, readability would be satisfying without the extra line spacing.

Note: this is not enforced by clang-format. Just do what is best to improve code readability.



### Namespaces
All code should be included in the **hou** namespace.
Code which is not supposed to be used by the user should be included in the **hou::prv** namespace.

using namespace should never be used in .hpp or .inl files.
It may be used in .cpp files.



### Comments
Avoid comments that say what the code does, strive to write the code in a self-explanatory way.
Do add comments that say why the code does something if it may not be immediately clear.
Keep comments as short and crisp as possible.
Comments must be written in English.



### Order of class member declarations
Declare public before protected before private members.
Declare members in the following orders:
* Types: classes, enums, aliases.
* Static functions.
* Static data members.
* Constructors and functions.
* Data members.
Repeat the visibility keyword before each group of members.
The visibility keyword should not be indented to avoid space waste.

```
class pie
{
public:
  using fruit_type = apple;
  using fruit_pointer_type = apple*;

public:
  static get_max_apples();

public:
  static const int max_slices;

public:
  pie(int p_apple_count);

  int get_apple_count() const;
  void set_apple_count(int p_apple_count);

protected:
  static const std::string& get_secret_recipe() const;

private:
  static const int s_secret_sugar_amount;

private:
  int m_apple_count;
  int m_sugar_amount;
};
```


