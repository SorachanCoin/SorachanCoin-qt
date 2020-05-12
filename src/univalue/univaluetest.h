﻿
namespace latest_json {

#define STRING_QUOTE(str) R"#(str)#"
#define FAIL_BLANK ""
static const char *const univalue_fail_test[] = {
    R"#("fail_test)#",

    R"#("This is a string that never ends, yes it goes on and on, my friends.)#",
    STRING_QUOTE(["Unclosed array"),
    STRING_QUOTE({ unquoted_key: "keys must be quoted" }),
    R"#(["extra comma",])#",
    R"#(["double extra comma",,])#",

    R"#([, "<-- missing value"])#",
    R"#(["Comma after the close"],)#",
    STRING_QUOTE(["Extra close"]]),
    R"#({ "Extra comma": true, })#",
    STRING_QUOTE({ "Extra value after close": true } "misplaced quoted value"),

    STRING_QUOTE({ "Illegal expression": 1 + 2 }),
    STRING_QUOTE({ "Illegal invocation": alert() }),
    STRING_QUOTE({ "Numbers cannot have leading zeroes": 013 }),
    STRING_QUOTE({ "Numbers cannot be hex": 0x14 }),
    STRING_QUOTE(["Illegal backslash escape: \x15"]),

    STRING_QUOTE([\naked]),
    STRING_QUOTE(["Illegal backslash escape: \017"]),
    FAIL_BLANK, // STRING_QUOTE([[[[[[[[[[[[[[[[[[[["Too deep"]]]]]]]]]]]]]]]]]]]]), // investigate
    STRING_QUOTE({ "Missing colon" null }),
    STRING_QUOTE({ "Double colon"::null }),

    R"#({ "Comma instead of colon", null })#",
    STRING_QUOTE(["Colon instead of comma":false]),
    R"#(["Bad value", truth])#",
    STRING_QUOTE(['single quote']),
    STRING_QUOTE(["	tab	character	in	string	"]),

    STRING_QUOTE(["tab\   character\   in\  string\  "]),
    R"#(["line
break"])#",
    R"#(["line\
break"])#",
    STRING_QUOTE([0e]),
    STRING_QUOTE([0e + ]),

    STRING_QUOTE([0e + -1]),
    R"#({ "Comma instead if closing brace": true,)#",
    STRING_QUOTE(["mismatch" }),
    STRING_QUOTE({} garbage),
    STRING_QUOTE([true true true[][][]]),

    STRING_QUOTE({ "a": }),
    STRING_QUOTE({ "a":1 "b" : 2 }),
    STRING_QUOTE(["\ud834"]),
    STRING_QUOTE(["\udd61"]),
    STRING_QUOTE(["揣｡"]),

    R"#(["・])#",
    STRING_QUOTE(["before nul byte"]"after nul byte"),
    FAIL_BLANK, // no file fail43.json
    R"#("This file ends without a newline or close - quote.)#",

};

#define PASS_BLANK R"#("pass")#"
static const char *const univalue_pass_test[] = {
    R"#("pass_test")#",

    R"#([
        "JSON Test Pattern pass1",
        { "object with 1 member":["array with 1 element"] },
        {},
        [],
        -42,
        true,
        false,
        null,
        {
            "integer": 1234567890,
            "real" : -9876.543210,
            "e" : 0.123456789e-12,
            "E" : 1.234567890E+34,
            "" : 23456789012E66,
            "zero" : 0,
            "one" : 1,
            "space" : " ",
            "quote" : "\"",
            "backslash" : "\\",
            "controls" : "\b\f\n\r\t",
            "slash" : "/ & \/",
            "alpha" : "abcdefghijklmnopqrstuvwyz",
            "ALPHA" : "ABCDEFGHIJKLMNOPQRSTUVWYZ",
            "digit" : "0123456789",
            "0123456789" : "digit",
            "special" : "`1~!@#$%^&*()_+-={':[,]}|;.</>?",
            "hex" : "\u0123\u4567\u89AB\uCDEF\uabcd\uef4A",
            "true" : true,
            "false" : false,
            "null" : null,
            "array" : [],
            "object" : {  },
            "address" : "50 St. James Street",
            "url" : "http://www.JSON.org/",
            "comment" : "// /* <!-- --",
            "# -- --> */" : " ",
            " s p a c e d " : [1,2 , 3

            ,

    4 , 5        ,          6           ,7],"compact" : [1,2,3,4,5,6,7],
    "jsontext" : "{\"object with 1 member\":[\"array with 1 element\"]}",
    "quotes" : "&#34; \u0022 %22 0x22 034 &#x22;",
    "\/\\\"\uCAFE\uBABE\uAB98\uFCDE\ubcda\uef4A\b\f\n\r\t`1~!@#$%^&*()_+-=[]{}|;:',./<>?"
    : "A key can be any string"
        },
    0.5 ,98.6
    ,
    99.44
    ,

    1066,
    1e1,
    0.1e1,
    1e-1,
    1e00,2e+00,2e-00
    ,"rosebud"])#",

    R"#([[[[[[[[[[[[[[[[[[["Not too deep"]]]]]]]]]]]]]]]]]]])#",

    R"#({
            "JSON Test Pattern pass3": {
            "The outermost value": "must be an object or array.",
                "In this test" : "It is an object."
        }
        })#",
};

#define ROUND_BLANK R"#("round")#"
static const char *const univalue_round_test[] = {
    R"#("round_test")#",

    R"#(["\u0000\u0001\u0002\u0003\u0004\u0005\u0006\u0007\b\t\n\u000b\f\r\u000e\u000f\u0010\u0011\u0012\u0013\u0014\u0015\u0016\u0017\u0018\u0019\u001a\u001b\u001c\u001d\u001e\u001f !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\u007f"])#",
    ROUND_BLANK, // R"#(["a§■𐎒𝅘𝅥𝅯"])#",
    R"#("abcdefghijklmnopqrstuvwxyz")#",
    R"#(7)#",
    R"#(true)#",

    R"#(false)#",
    R"#(null)#",
};

} // namespace latest_json
