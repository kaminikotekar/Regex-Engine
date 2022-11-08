## REGULAR EXPRESSION ENGINE 

#### INTRODUCTION

A regular expression represents a pattern that can be used to match a string of characters. For example `a|b*` is a regular expression that matches a string of characters containing a single character `a`, an empty string `''` or one or more characters of `b`. 

A regular expreesion can be represented as a Finite State Machine (`FA`). Any set of strings that reaches the end state of this `FA` will correspond to the regular expression.

#### SYNTAX

Following operators are supported by this Regex Engine

|Operator | Symbol  | Regex| Strings |
|---|---|---|---|
| Union | `|` | `a|b` | eg: `a`, `b`|
| Concatenation | `.` | `a.b` | eg: `ab`|
| Closure | `*` | `a*` | eg: `''`, `a`, `aa`, `aaa`|

#### BUILD
Use `make` utility to build and execute.

* To compile
    ```
    make NFA
    ```
* To execute
    ```
    make execute
    ```
* To clean all object files
    ```
    make clean
    ```
#### REFERENCE
*  [Implementing a Regular Expression Engine by Denis Kyashif](https://deniskyashif.com/2019/02/17/implementing-a-regular-expression-engine/)