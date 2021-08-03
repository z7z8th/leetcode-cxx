package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	var v0, v1 = 0, 1
	return func() int {
		var ret = v0
		v0 = v1
		v1 = ret +v0
		return ret
	}
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
