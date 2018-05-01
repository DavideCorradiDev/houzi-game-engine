# Style guide

## Code structure conventions

### File structure
Headers contain only declarations.
Definitions should be contained in a corresponding source file, or in an inlined file included in the header (for template and inline function definitions).
This is done to keep interface and implementation details separate for templates as well.

Each header file normally has a corresponding source file (not always), and sometimes a corresponding inlined file.
The three files have the same name, save for the extension.
Header files have the .hpp extension, source files the .cpp extension, and inlined file the .inl extension.
The exception to this rule is when the definitions must be different according to the target compilation platform.
In that case, there can be multiple source files, one for each platform (and potentially one common one for the definitions that are the same for all platforms).
In this case the extra source files have a suffix identifying the type of platform (e.g. window\_impl.cpp and window\_impl\_win.cpp).

Ideally, each header file should only contain the declaration of a single class, of a single enum class together with associated functions, or of multiple functions which can be logically grouped together.
It is allowed to have multiple class declarations in a single header, as long as the classes are not too complex, but this should be avoided.



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

The user of the library can add the paths to the include folder of each used module to his project in order to be able to include header files conveniently:
```
#include "hou/gfx/texture.hpp"
#include "hou/mth/transform.hpp"
```



## Code style
In the following section the style rules observed in the source code and the reasons behind them are explained.



### Naming conventions

#### Main naming conventions
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
* Template parameter names must be written in camel case.
```
// Good
template <typename TemplateParam>
TemplateParam max(TemplateParam, TemplateParam b);

// Bad
template <typename template_param>
TemplateParam max(TemplateParam, TemplateParam b);
```
* It is forbidden to use names starting with an underscore, because such names are reserved to the implementation.
```
// Bad
int _my_variable;
```
* It is forbidden to use names containing two consecutive underscores, becuase such names are reserved to the implementation.
```
int my__variable;
```

#### Optional naming conventions
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
* Namespace names should be 2 to 4 characters long to reduce the verbosity of the code.
```
namespace hou {}
namespace std {}
```
* Preprocessor symbol names should be prefixed with 'HOU\_' to reduce the likelihood of name clashes with symbols defined in other libraries.
```
#define HOU_DO_STUFF(x) (x)*(x)
```

#### Reasons behind the naming conventions
The main reasons behind these naming conventions are:
* Consistency: these rules are consistent with the rules followed in the standard library.
* Simplicity: almost all names, with few exceptions, follow the same rules.
* Reduce the change of name clashing and the verbosity of the code.



### Formatting conventions

#### Basic formatting conventions
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



#### Indentation style
The code must be indented using spaces.
Tabs are forbidden.
An indentation level must be exactly two spaces long.

Spaces are chosen over tabs for visual consistency's sake: the code will look the same and will be properly formatted no matter what editor it is opened with.

The indentation has been chosen to be two spaces because:
* One space would be too little and easy to confuse with normal spacing.
* Two spaces already make it very clear where the scopes are.
* Having a longer indentation would require more frequent line breaks, thus reducing code readability.



#### Maximum line width
The maximum line width is 80 characters.
The reasons for this choice are:
* It is easier to read shorter lines.
* It is possible to read two or even three files side by side without word wrapping or the necessity to scroll horizontally.
* It is possible to comfortably read the code even when without access to a large widescreen monitor (e.g. on a tablet screen).
* It gives motivation to keep lines as short as possible and to avoid excessive indentation levels.

Any line longer than the limit must be split into multiple lines.
Lines which are a continuation of a previous line must be indented following the normal indentation rules (they shouldn't be aligned with brackets, assignment operators, and so on).
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
```
// Good
int very_long_sum = 8888 + 8888 + 8888 + 8888 + 8888 + 8888 + 8888 + 8888 + 8888 + 8888
  + 8888 + 8888;

// Bad
int very_long_sum = 8888 + 8888 + 8888 + 8888 + 8888 + 8888 + 8888 + 8888 + 8888 + 8888 +
  8888 + 8888;
```

Note: feel free to break lines manually if this can improve code readability.
Remember to deactivet clang-format around the formatted code.
```
// Good
// clang-format off
mat4x4i magic{
  0,  1,  2,  3,
  4,  5,  6,  7,
  8,  9, 10, 11,
 12, 13, 14, 15,
};
// clang-format on
```



#### Bracing style
Braces always occupy their own line.
This improves readability when a line before a scope has to be split.
Since both line continuations and the inner scopes are indented, they tend to mix together without the separating brace line.
The brace makes it clear at a glance where an actual inner scope is starting.
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



#### Line spacing
In header files, declarations are normally separated by a single line.
In source files (and inlined files), declarations and definitions are normally separated by three lines in a row.

The extra spacing in source files is there to improve readability by making it clearer where the boundaries between different function definitions are.
Single empty lines often come up inside the actual code blocks, therefore separating with a only single line (or no line) tends to mesh everything together.
The extra spacing is not neeeded for this purpose in header files because the documentation comments already separate the different elements well.
Even without the comments, since only definitions are present, readability would be satisfying without the extra line spacing.

Note: this is not enforced by clang-format. Just do what is best to improve code readability.



### Other conventions

#### Namespaces
All code is included in the **hou** namespace.
Code which is not supposed to be directly used by the user should be included in the **hou::prv** namespace.



#### Comments
Avoid comments that say what the code does, strive to write the code in a self-explanatory way.
Do add comments that say why the code does something if it may not be immediately clear.
Keep comments as short and crisp as possible.
Comments must be written in English.
```
a += 88;
// Good: a is increased by 88 because it is a lucky number.
// Bad: add 88 to a.
// Bad: a viene incrementata di 88 in quanto numbero fortunato.
// Bad: we have decided to use the 88 number because it has proven to increase the luck amount factor n-fold.
```



#### Order of class member declarations
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
  static int get_max_apples();

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


#### Header inclusion
Headers should be included only when  necessary to reduce compilation times and number of recompilations when a header is modified.
In all other cases forward declarations should be preferred.

For this reason, nested type definition should be avoided, since nested types cannot be forward declared.
An obvious exception is if the type is not public, as they will never need be forward declared.
Nested aliases are allowed.

When using forward declarations can be cumbersome, an extra forward declaration header can be added.
This header should have the same name of the normal header, with the suffix \_fwd (e.g. matrix.hpp and matrix\_fwd.hpp).
The forward declaration header should be included in the main header, to ensure that all symbols defined there are respected.

Files should be included in the following order:
* Headers containing where parent classes are declared.
* Headers from the project, grouped by module, in alphabetical order.
* Headers from the project defining the export symbol macros.
* Headers from external libraries.
* Headers from the standard library.

This order of inclusion makes it easier to detect non-consistent header files.

