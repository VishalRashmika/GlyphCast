#pragma once

enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    
    // Literals.
    IDENTIFIER, STRING, NUMBER,
    
    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    END_OF_FILE
};

/*
 0  LEFT_PAREN
 1  RIGHT_PAREN
 2  LEFT_BRACE
 3  RIGHT_BRACE
 4  COMMA
 5  DOT
 6  MINUS
 7  PLUS
 8  SEMICOLON
 9  SLASH
10  STAR
11  BANG
12  BANG_EQUAL
13  EQUAL
14  EQUAL_EQUAL
15  GREATER
16  GREATER_EQUAL
17  LESS
18  LESS_EQUAL
19  IDENTIFIER
20  STRING
21  NUMBER
22  AND
23  CLASS
24  ELSE
25  FALSE
26  FUN
27  FOR
28  IF
29  NIL
30  OR
31  PRINT
32  RETURN
33  SUPER
34  THIS
35  TRUE
36  VAR
37  WHILE
38  END_OF_FILE
*/