![license: MIT](https://img.shields.io/badge/license-MIT-blue)

# Verse
`verse` is an interpreter for the Verse programming language. This language was the result of various experimentations that ultimetly led to [Basalt](https://www.github.com/fDero/Basalt), 
my second language. It's important to note that what i created has nothing to do with [Verse made by epic games](https://dev.epicgames.com/documentation/en-us/uefn/verse-language-reference).

### Installation (Building from source)
In order to install verse, you have to build it from source. By default, the build process tries to use `clang++`, but you can change that
to make it use `g++` instead if you so desire. Either way `c++20` or higher is required.
```bash
$$ git clone https://www.github.com/fDero/Verse
$$ cd Verse
$$ make build
```

### Hello World
To make your first hello-world program in verse, all it takes is to create a file with the `.verse` extension (in this case, it will be called `hello.verse`)
containing the following code:
```go
func main(){
    println("Hello world!");
}
```

Once you have the file set up, to run it just use the `verse -r hello.verse` command in console.
```bash
$$ verse -r hello.verse
$$ Hello world!
```

### Types
Verse is a strictly typed language, it has a C-style type system with `Int`, `Float`, `Bool`, `Char`, `String` as primitive types. 
```go
func main(){
    var x : Int = 6;
    var y : Float = 9.4;
    var f : Bool = false;
    var c : Char = 'z';
    var s : String = "hello world";
}
```

### Recursion
Verse supports recursion just like any other language, and a good way to show it is with the classic fibonacci example, consider the following code:
```go
func fibo(n : Int){
    if (n < 2) {
        return 1;
    }
    else {
        return fibo(n-1) + fibo(n-2);
    }
}

func main(){
    println(fibo(6));
}
```
assuming the file is called `fibo.verse`, then it can be executed just like we did earlier with the hello-world example, using the `verse -r` command.
```bash
$$ verse -r fibo.verse
$$ 21
```
