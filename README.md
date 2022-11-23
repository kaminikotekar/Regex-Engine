## REGULAR EXPRESSION ENGINE 

#### Introduction

A regular expression is a pattern that can be used to match a string of characters. For example `a|b*` is a regular expression that matches a string of characters containing a single character `a`, an empty string `''` or one or more characters of `b`. 

A regular expression can be represented as a Finite State Machine (`FA`). Any set of strings that reaches the end state of this `FA` will correspond to the regular expression.

#### Syntax

Following operators are supported by this Regex Engine

|Operator | Symbol  | Regex| Strings |
|---|---|---|---|
| Union | `|` | `a|b` | eg: `a`, `b`|
| Concatenation | `.` | `a.b` | eg: `ab`|
| Closure | `*` | `a*` | eg: `''`, `a`, `aa`, `aaa`|

**NOTE**: `(` and `)` can also be used to construct a regular expression.

#### Operator precendence
The precendence order of the operators for a postfix expression are as follows:

1. Parentheses
2. Closure
3. Concatenation
4. Union

**Example**
A regular expression `a.b.c|(d.e)*` will be executed as follows
```

     a  .  b  .  c  |  ( d  .  e )  *
     ---------------------------------
     └─ 1 ─┘     │     │         │  │
        └── 2 ───┘     │         │  │
            │          └─── 3 ───┘  │
            │               └── 4 ──┘
            └─────── 5 ─────────┘
```


#### Build
Use `make` utility to build and execute.

* To compile/build
    ```
    make build
    ```
* To execute engine
    ```
    make run
    ```
* To run test cases
    ```
    make test
    ```
* To clean all object files
    ```
    make clean
    ```

#### Architecture

![image info](./data/raw/regex_architecture.png)

Following constants can be modified in a constants file `include/Constants.h` based on the requirement.

|Constant | Description |
|---|---|
|`HASHSIZE`| size of a custom hasmap used |
|`TOTAL_STATES`| maximum number of states an NFA can contain |
|`VISITED_EPSILON`| maximum number of epsilon states in an NFA |
|`INFIX_SIZE`| maximum size of a regex |
|`PATTERN_SIZE`| maximum size of a pattern |
|`TEST_SIZE`| maximum number of test cases in `data/tests/test.txt` |
|`LOG_SIZE`| maximum length of a log output |
|`LOG_PATH`| path to the log file `data/raw/regex.log` |
|`TEST_PATH`| path to the test file |
|`BANNER_PATH_INTRO`| path to ASCII banner |
|`BANNER_PATH_END`| path to ASCII banner |

#### Running Test cases

Test cases are recorded in a semicolon seperated file `data/tests/test.txt`. The first column of the file represents the Regex whereas all columns from second to last represents multiple pattern

```
re_1; pattr_11; pattr_12; pattr_13; .....
re_2; pattr_21; pattr_22; pattr_23; .....
```



#### REFERENCE
*  [Implementing a Regular Expression Engine by Denis Kyashif](https://deniskyashif.com/2019/02/17/implementing-a-regular-expression-engine/)