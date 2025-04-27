# pebble
Messing around with compilers

## CLI commands
```./build.sh ``` to build pebble and test_lexer. The previous executable gets removed \
```./build.sh run test_file.txt``` to build and run pebble with test_file.txt \
```./pebble``` to run pebble \
```gdb pebble``` to debug with gdb \
```gdb test_lexer``` to debug test_lexer with gdb \
```./build.sh test_lexer``` to build and run the lexer tests \
```./test_lexer``` to run ./test_lexer \
inside gdb: run test_file.txt -> to run pebble in gdb with the test file 

## style guide
[follow parts the cURL style guide](https://github.com/curl/curl/blob/master/docs/internals/CODE_STYLE.md)

## language
Decided to stop basing on Oding language and switch to a subset of Monkey language with static typing.

## TODO
- [ ] How to add linter to C code base? via LSP?
- [ ] parse the following:
    ``` 
    let a: int = 3;
    let b: int = 4;
    let c : int  = a + b;
    let d: int = c * a;
    let result : int = a + b * c + d;
    print result;
    ```

    ```
    // Cyclical dependency error
    let a: int = b + 1;
    let b: int = c + 1;
    let c: int = a + 1;
    print a, b, c;
    ```

- [ ] lexer
- [ ] Parser
- [ ] Graph + Walk AST for typechecking
- [ ] TAC
- [ ] ASM -> fasm (x86-64)

## Learned
- Arena and cache lining
- When arena is more usefule then (m)alloc
- Why arrays are faster then objects that lie farther apart




