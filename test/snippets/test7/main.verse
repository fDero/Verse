func fibonacci(n : Int){
    var a : Int = 1;
    var b : Int = 1;

    func swap(a : Int*, b : Int*){
        var tmp : Int = #a;
        #a = #b;
        #b = tmp;
    }

    while (n > 0){
        swap(#a,#b);
        #b = #b + 1;
        n = n - 1;
    }
    result = a;
}