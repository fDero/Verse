func fibonacci(n : Int){
    var a : Int = 1;
    var b : Int = 1;
    while (n > 0){
        func swap(a : Int, b : Int){
            var tmp : Int = #a;
            #a = #b;
            #b = tmp;
        }
        swap(#a,#b);
        #b = #b + 1;
        n = n - 1;
    }
    result = a;
}