# pebble
Messing around with compilers

## CLI commands
```make all ``` to build pebble and test_lexer. The previous executable gets removed \
```make test_lexer ``` to build test_lexer. \
```make test_arena ``` to build test_arena. \
```./build/pebble test.txt``` to build and run pebble with test_file.txt \
```./build/test_lexer ``` to run lexer tests \
```gdb ./build/pebble``` to debug with gdb \
```gdb ./build/test_lexer``` to debug test_lexer with gdb \
inside gdb: run test.txt -> to run pebble in gdb with the test file 

## style guide
TODO now my language rules are a mess because I can't decide what I prefere...:
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

## References
[Crafting interpreters](https://craftinginterpreters.com/)
[Writing an interpreter in go](https://interpreterbook.com/)
[Voxelrift - I made a language for the Nintendo ds](https://www.youtube.com/watch?v=jMIj893JJBg&t=376s)
[Voxelrift - arenas and strings](https://www.youtube.com/watch?v=3IAlJSIjvH0&t=114s)

