# Context grammaars

## Syntax of `for` structure in C

Example:
```c
for (int i = 0; i < 10; i++) {
    ...
}

for (;;) { 
    printf("Cool!");
}
```

Normal BNF:
```xml
<for> ::= for (<init>; <condition>; <update>) <expression> 
| for (<init>; <condition>; <update>) {<expression>}
<init> ::= <type> <var> = <value> | <var> = <value> | <lambda>
<condition> ::= <expression> | <lambda>
<update> ::= <var><update-operator> | <update-operator><var>
<update-operator> ::= ++ | --
<expressions> ::= <expression> | <expression><expression-seq>
```

EBNF:
```bash
{} = una o mas  expresiones dentro
FOR ::= for '(' INIT ';' CONDITION ';' UPDATE' )'  ( EXPRESSION | '{' { EXPRESSION } '}' )
```